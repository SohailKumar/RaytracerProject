#include <SDL3/SDL.h>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <vector>


#include "Sphere.h"
#include "Camera.h"
#include "Ray.h"
#include "World.h"

int main(int argc, char* argv[]) {
    //Sphere* bigsphere = new Sphere(glm::vec3(0.0f, 0.0f, -2.0f), 1, glm::vec3(1.0, 0, 0));
    //Ray* bigray = new Ray(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-0.049875, -0.049875, -0.997509));
    //bool test = bigsphere->Intersect(bigray);
    //std::cout << "Intersect: " << test << std::endl;

    //return 0;


    SDL_Event event; //event handler
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* surface;

    const int WINDOW_WIDTH = 500;
    const int WINDOW_HEIGHT = 500;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Basic Raytracer", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

    ////////////////////////////////////////////////////////////////////////////////////
    
    std::vector<Radiance*> radiance; //array of radiances

    //SET UP SCENE
	World* world = new World();

    Sphere* sphere = new Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 1, glm::vec3(0.0, 0.0, 1.0));
    std::cout << "Sphere: " << glm::to_string(sphere->center) << std::endl;
	world->Add(sphere);

    //Add camera
	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0, 2, 2);

    //Implement camera ray generation to camera field.
    //std::cout << "Sphere before: " << glm::to_string(sphere->center) << std::endl;
    //std::cout << "viewMat: " << glm::to_string(camera->GetViewMatrix()) << std::endl;
	world->transformAll(camera->GetViewMatrix());
    //std::cout << "Sphere after: " << glm::to_string(sphere->center) << std::endl;

    std::vector<glm::vec3> rgbArray = camera->RenderWorld(world, WINDOW_WIDTH, WINDOW_HEIGHT);
    std::cout << "lenght of vector is " << rgbArray.size() << std::endl;

	//Implement ray intersection with objects in world.
    //Display

    delete camera;
    delete world;
    //delete sphere;


    ////////////////////////////////////////////////////////////////////////////////////
    surface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_PIXELFORMAT_RGBA32);

    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);

    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            int index = y * WINDOW_WIDTH + x;
            glm::vec3 rgb = rgbArray[index];  // Get corresponding pixel radiance

            // Convert from float [0,1] to uint8_t [0,255]
            uint8_t r = static_cast<uint8_t>(rgb[0]);
            uint8_t g = static_cast<uint8_t>(rgb[1]);
            uint8_t b = static_cast<uint8_t>(rgb[2]);
			//std::cout << "r: " << radiance->radianceValues[0] << ", g: " << radiance->radianceValues[1] << ", b: " << radiance->radianceValues[2] << std::endl;
            uint8_t a = 255;  // Full opacity

            // Store pixel color in correct endian order
            pixels[index] = SDL_Swap32LE((a << 24) | (r << 16) | (g << 8) | b);
        }
    }

    //uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
    //for (int y = 0; y < WINDOW_HEIGHT; ++y) {
    //    for (int x = 0; x < WINDOW_WIDTH; ++x) {
    //        uint8_t r = x % 256;   // Example pattern
    //        uint8_t g = y % 256;
    //        uint8_t b = (x + y) % 256;
    //        uint8_t a = 255;
    //        pixels[y * (surface->pitch / 4) + x] = SDL_Swap32LE((a << 24) | (r << 16) | (g << 8) | b);
    //    }
    //}


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

    std::cout << "SDL3 test completed successfully!" << std::endl;
    return EXIT_SUCCESS;
}