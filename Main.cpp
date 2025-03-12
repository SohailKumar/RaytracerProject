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
#include "Mat_Phong.h"
#include "Mat_Checkerboard.h"

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

    //World.Reflect(primaryIntersection.point, primaryIntersection.incoming, primaryIntersection.normal);
    //World newWorld;
    //glm::vec3 prev = glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f));
    //glm::vec3 newVector3 = newWorld.Reflect(glm::vec3(0.0f, 0.0f, 0.0f), glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
    //std::println("previous = {}, {}, {}", prev[0], prev[1], prev[2]);
    //std::println("newVector3 = {}, {}, {}", newVector3[0], newVector3[1], newVector3[2]);

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

    /////// SET UP SCENE
	World world = World();

    // objects
    //std::make_unique<Mat_Phong>(mat.diffuseColor, mat.specularColor, mat.ambient_k, mat.diffuse_k, mat.specular_k, mat.shiny_exp);
    world.Add(std::make_unique<Sphere>(glm::vec3(-1.0f, 1.0f, -4.0f), 3, std::make_unique<Mat_Phong>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.9f, 2.0f)));
    world.Add(std::make_unique<Sphere>(glm::vec3(3.2f, -0.9f, -7.0f), 3, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.9f, 2.0f)));
    //world.Add(std::make_unique<Sphere>(Sphere(glm::vec3(0.0f, 4.0f, 0.0f), 1, Material(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.9f, 2.0f))));

    Vertex corner1 = Vertex(glm::vec3(-9, -5, -1), 0, 0);
	Vertex corner2 = Vertex(glm::vec3(-9, -5, -25), 0, 1);
	Vertex corner3 = Vertex(glm::vec3(10, -5, -1), 1, 0);
	Vertex corner4 = Vertex(glm::vec3(10, -5, -25), 1, 1);
    
    //Checkerboard ground
	glm::vec3 color1 = glm::vec3(1.0f, 0.2f, 0.6f);
    glm::vec3 color2 = glm::vec3(0.6f, 0.0f, 0.6f);
    world.Add(std::make_unique<Triangle>(Triangle({ corner1, corner2, corner3 }, std::make_unique<Mat_Checkerboard>(color1, color2, 0.1, 0.1))));
    world.Add(std::make_unique<Triangle>(Triangle({ corner3, corner2, corner4 }, std::make_unique<Mat_Checkerboard>(color1, color2, 0.1, 0.1))));

    //Phong Shaded ground
    //world.Add(std::make_unique<Triangle>(Triangle({ corner1, corner2, corner3 }, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 1.0f, 2.0f))));
    //world.Add(std::make_unique<Triangle>(Triangle({ corner3, corner2, corner4 }, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.5f, 0.5f, 1.0f, 2.0f))));


    // lights
    world.Add(std::make_unique<Light>(Light(glm::vec3(1.5f, 10.0f, 1.0f), glm::vec3(0.7f, 0.7f, 0.7f))));
    //world.Add(std::make_unique<Light>(Light(glm::vec3(1.5f, 10.0f, 1.0f), glm::vec3(0.3f, 0.3f, 0.3f))));
    //world.Add(std::make_unique<Light>(Light(glm::vec3(0.0f, 8.0f, 4.0f), glm::vec3(0.2f, 0.2f, 0.2f))));


    //Add camera
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -5.0f), 8.0, 16, 9);
	world.TransformAll(camera.GetViewMatrix());

    std::vector<glm::vec3> radianceArray = camera.RenderWorld(world, WINDOW_WIDTH, WINDOW_HEIGHT);
    //std::println("length = {}", rgbArray.size());


    ////////////////////////////////////////////////////////////////////////////////////
    surface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_PIXELFORMAT_RGBA32);

    Uint32* pixels = static_cast<Uint32*>(surface->pixels);

    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            int index = y * WINDOW_WIDTH + x;
            glm::vec3 radianceValues = radianceArray[index];  // Get corresponding pixel radiance
            if (radianceValues[0] > 0) {
                radianceValues = radianceValues;
            }
            //if (radianceValues == glm::vec3(1.0f, 0.0f, 0.0f)) {
            //    radianceValues *= 255.0f;
            //}

            ///////////////////////
            ///TONE REPRODUCTION///
            radianceValues[0] = std::clamp(radianceValues[0], 0.0f, 1.0f);
            radianceValues[1] = std::clamp(radianceValues[1], 0.0f, 1.0f);
            radianceValues[2] = std::clamp(radianceValues[2], 0.0f, 1.0f);
            radianceValues *= 255.0f;
            ///////////////////////

            int offset = y * WINDOW_WIDTH + x;

            // Convert from float [0,1] to uint8_t [0,255]
            uint8_t r = static_cast<uint8_t>(radianceValues[0]);
            uint8_t g = static_cast<uint8_t>(radianceValues[1]);
            uint8_t b = static_cast<uint8_t>(radianceValues[2]);
            uint8_t a = 255;  // Full opacity

            //Uint32 color = SDL_MapSurfaceRGBA(surface, r, g, b, a);
            //if (radianceValues != glm::vec3(0.0f, 0.0f, 0.0f)) {
            //    std::cout << "r: " << radianceValues[0] << ", g: " << radianceValues[1] << ", b: " << radianceValues[2] << std::endl;
            //}


            // Store pixel color in correct endian order

            //pixels[y * (surface->pitch/4) + x] = SDL_Swap32LE((a << 24) | (b << 16) | (g << 8) | r);
            Uint32 color = (a << 24) | (b << 16) | (g << 8) | r;

            // Store the pixel value in the correct position in the pixels array
            pixels[y * WINDOW_WIDTH + x] = color;

        }
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    
    //render texture
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    std::cout << "Done" << std::endl;

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