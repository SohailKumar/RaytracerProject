#include <SDL3/SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


#include "Sphere.h"
#include "Camera.h"
#include "Ray.h"
#include "World.h"

int main(int argc, char* argv[]) {
    //SDL_Event event; //event handler
    //SDL_Renderer* renderer;
    //SDL_Window* window;
    //SDL_Surface* surface;

    //const int WIDTH = 256;
    //const int HEIGHT = 256;
    //
    //SDL_Init(SDL_INIT_VIDEO);
    //SDL_CreateWindowAndRenderer("Basic Raytracer", WIDTH, HEIGHT, 0, &window, &renderer);

    ////////////////////////////////////////////////////////////////////////////////////
    
    glm::vec3 vec(1.0f, 2.0f, 3.0f);
	glm::mat3x3 mat(2.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
    vec = mat * vec;
    
    Sphere* sphere = new Sphere();
	std::cout << "Sphere: " << glm::to_string(sphere->center) << std::endl;

    std::cout << "Vector: " << glm::to_string(vec) << std::endl;

    //SET UP SCENE
	World* world = new World();
	world->Add(new Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 5));

    //Add camera
    
    //Implement camera ray generation to camera field.
    

	//Implement ray intersection with objects in world.
    //Display



    ////////////////////////////////////////////////////////////////////////////////////
    //surface = SDL_CreateSurface(WIDTH, HEIGHT, SDL_PIXELFORMAT_RGBA32);
    //
    //uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
    //for (int y = 0; y < HEIGHT; ++y) {
    //    for (int x = 0; x < WIDTH; ++x) {
    //        uint8_t r = x % 256;   // Example pattern
    //        uint8_t g = y % 256;
    //        uint8_t b = (x + y) % 256;
    //        uint8_t a = 255;
    //        pixels[y * (surface->pitch / 4) + x] = SDL_Swap32LE((a << 24) | (r << 16) | (g << 8) | b);
    //    }
    //}

    //SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    //SDL_DestroySurface(surface);
    //
    ////render texture
    //SDL_RenderClear(renderer);
    //SDL_RenderTexture(renderer, texture, nullptr, nullptr);
    //SDL_RenderPresent(renderer);

    ////Wait for user to close the window
    //while (1) {
    //    if (SDL_PollEvent(&event) && event.type == SDL_EVENT_QUIT)
    //        break;
    //}

    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    //// Quit SDL subsystems
    //SDL_Quit();

    //std::cout << "SDL3 test completed successfully!" << std::endl;
    return EXIT_SUCCESS;
}