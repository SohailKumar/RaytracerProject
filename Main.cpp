#include <SDL3/SDL.h>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include <print>
#include <memory>

#include "Sphere.h"
#include "Triangle.h"
#include "Camera.h"
#include "Ray.h"
#include "World.h"

int main(int argc, char* argv[]) {
    //Sphere* bigsphere = new Sphere(glm::vec3(0.0f, 0.0f, -2.0f), 1, glm::vec3(1.0, 0, 0));
    //Ray* bigray = new Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-0.049875, -0.049875, -0.997509));
    //bool test = bigsphere->Intersect(bigray);
    //std::cout << "Intersect: " << test << std::endl;

    /*Polygon* bigpoly = new Polygon({ glm::vec3(-2, -2, -5), glm::vec3(0, 2, -5), glm::vec3(2, -2, -5) });
	Ray* bigray = new Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    bool test = bigpoly->Intersect(bigray);
    std::cout << "Intersect: " << test << std::endl;*/

    //glm::vec3 br = glm::vec3(1.0f, 0.0f, 0.0f);
    //br *= 255;
    //std::println("b before = {}", br[0]);

    //uint8_t r = static_cast<uint8_t>(br[0]);
    //std::println("r = {}", r);

    //return 0;


    SDL_Event event; //event handler
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* surface;

    const int WINDOW_WIDTH = 854;
    const int WINDOW_HEIGHT = 480;
    //const int WINDOW_WIDTH = 20;
    //const int WINDOW_HEIGHT = 10;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Basic Raytracer", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    ////////////////////////////////////////////////////////////////////////////////////
    
    std::vector<Material*> radiance; //array of radiances

    /////// SET UP SCENE
	World world = World();

    // objects
    world.Add(std::make_unique<Sphere>(Sphere(glm::vec3(-1.0f, 1.0f, -4.0f), 3, glm::vec3(1.0, 0.0, 0.0))));
    world.Add(std::make_unique<Sphere>(Sphere(glm::vec3(3.2f, -0.9f, -7.0f), 3, glm::vec3(1.0, 0.0, 0.0))));
    
    glm::vec3 quadp1 = glm::vec3(-6, -3.5, -1);
	glm::vec3 quadp2 = glm::vec3(-6, -3.5, -20);
	glm::vec3 quadp3 = glm::vec3(8, -3.5, -1);
	glm::vec3 quadp4 = glm::vec3(8, -3.5, -20);

    //world.Add(std::make_unique<Triangle>(Triangle({ quadp1, quadp2, quadp3 }, glm::vec3(1.0, 0.0, 0.0))));
    //world.Add(std::make_unique<Triangle>(Triangle({ quadp3, quadp2, quadp4 }, glm::vec3(1.0, 0.0, 0.0))));
    
    // lights
    world.Add(std::make_unique<Light>(Light(glm::vec3(-1.0f, 3.0f, -4.0f), glm::vec3(0.5f, 0.5f, 0.5f))));


    //Add camera
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -5.0f), 8.0, 16, 9);
	world.transformAll(camera.GetViewMatrix());

    std::vector<glm::vec3> radianceArray = camera.RenderWorld(world, WINDOW_WIDTH, WINDOW_HEIGHT);
    //std::println("length = {}", rgbArray.size());


    ////////////////////////////////////////////////////////////////////////////////////
    surface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_PIXELFORMAT_RGBA32);

    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);

    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            int index = y * WINDOW_WIDTH + x;
            glm::vec3 radianceValues = radianceArray[index];  // Get corresponding pixel radiance
            if (index == 31101) {
                radianceValues = radianceValues;
            }
            //if (radianceValues == glm::vec3(1.0f, 0.0f, 0.0f)) {
            //    radianceValues *= 255.0f;
            //}

            ///////////////////////
            ///TONE REPRODUCTION///
            radianceValues *= 255.0f;
            ///////////////////////

            // Convert from float [0,1] to uint8_t [0,255]
            uint8_t r = static_cast<uint8_t>(radianceValues[0]);
            uint8_t g = static_cast<uint8_t>(radianceValues[1]);
            uint8_t b = static_cast<uint8_t>(radianceValues[2]);
			//std::cout << "r: " << radiance->radianceValues[0] << ", g: " << radiance->radianceValues[1] << ", b: " << radiance->radianceValues[2] << std::endl;
            uint8_t a = 255;  // Full opacity

            // Store pixel color in correct endian order
            pixels[y * (surface->pitch/4) + x] = SDL_Swap32LE((a << 24) | (b << 16) | (g << 8) | r);

        }
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    
    //render texture
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    //Wait for user to close the window
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_EVENT_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    std::cout << "Completed Successfully!" << std::endl;
    return EXIT_SUCCESS;
}