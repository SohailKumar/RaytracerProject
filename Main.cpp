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
#include <string>

#include "Sphere.h"
#include "Triangle.h"
#include "Cylinder.h"
#include "Camera.h"
#include "Ray.h"
#include "World.h"
#include "Mat_Phong.h"
#include "Mat_Checkerboard.h"
#include "Mat_ImageTexture.h"
#include "Mat_AshikhminShirley.h"
#include "Mat_PhongBlinn.h"

int main(int argc, char* argv[]) {
    //TESTING
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

 //   World newWorld;
 //   glm::vec3 incident = glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f));
 //   glm::vec3 normal = glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f));
 //   glm::vec3 out = newWorld.Refract(incident *-1.0f, normal, 1.0f, 1.0f);
	//std::cout << "incident: " << glm::to_string(incident) << std::endl;
	//std::cout << "normal: " << glm::to_string(normal) << std::endl;
	//std::cout << "out: " << glm::to_string(out) << std::endl;
	//std::cout << "dot" << glm::dot(incident, normal) << std::endl;

 //   std::cout << "dot" << glm::dot(incident * -1.0f, normal) << std::endl;
 //   //glm::vec3 prev = glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f));
 //   //glm::vec3 newVector3 = newWorld.Reflect(glm::vec3(0.0f, 0.0f, 0.0f), glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
 //   //std::println("previous = {}, {}, {}", prev[0], prev[1], prev[2]);
 //   //std::println("newVector3 = {}, {}, {}", newVector3[0], newVector3[1], newVector3[2]);

 //   return 0;


    SDL_Event event; //event handler
    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Surface* surface;

    const int WINDOW_WIDTH = 854;
    const int WINDOW_HEIGHT = 480;
    //const int WINDOW_WIDTH = 1024;
    //const int WINDOW_HEIGHT = 768;
    //const int WINDOW_WIDTH = 85;
    //const int WINDOW_HEIGHT = 48;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer("Basic Raytracer", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    //std::string toneReproductionType = "Ward";
    std::string toneReproductionType = "Lazy";
    std::println("tone reproduction type = {}", toneReproductionType);

    ////////////////////////////////////////////////////////////////////////////////////

    /////// SET UP SCENE
	World world = World();

    // objects
    //THE DUO
    //world.Add(std::make_unique<Sphere>(glm::vec3(-1.0f, 1.0f, -4.0f), 3, 0.0f, 0.95f, std::make_unique<Mat_Phong>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.40f, 0.4f, 1.3f)));
    //world.Add(std::make_unique<Sphere>(glm::vec3(3.2f, -0.9f, -7.0f), 3, 0.8f, 0.0f, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.4f, 1.3f)));
	

    //world.Add(std::make_unique<Cylinder>(glm::vec3(-1.0f, 0.0f, -4.0f), glm::vec3(-1.0f, 1.0f, -4.5f), 2.0f, 0.0f, 0.0f, std::make_unique<Mat_Phong>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.4f, 1.3f)));
    //world.Add(std::make_unique<Cylinder>(glm::vec3(-1.0f, 2.0f, -4.0f), glm::vec3(-1.0f, 5.0f, -9.0f), 2.0f, 0.0f, 0.0f, std::make_unique<Mat_Phong>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.4f, 1.3f)));
    //world.Add(std::make_unique<Sphere>(glm::vec3(-1.0f, 1.0f, -4.0f), 2, 0.0f, 0.0f, std::make_unique<Mat_PhongBlinn>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.7f, 0.7f)));

    world.Add(std::make_unique<Sphere>(glm::vec3(-1.0f, 1.0f, -9.0f), 3, 0.0f, 0.0f, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 1.0f, 2.5f)));


    //test sphere
    //world.Add(std::make_unique<Sphere>(glm::vec3(1.0f, -3.0f, -7.0f), 1, 1.0f, 0.0f, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 0.9f, 2.0f)));
    
    Vertex corner1 = Vertex(glm::vec3(-9, -5, -1), 0, 0);
	Vertex corner2 = Vertex(glm::vec3(-9, -5, -25), 0, 1);
	Vertex corner3 = Vertex(glm::vec3(10, -5, -1), 1, 0);
	Vertex corner4 = Vertex(glm::vec3(10, -5, -25), 1, 1);

    // plane right in front of camera
    //Vertex corner1 = Vertex(glm::vec3(-10, -5.7, -5), 0, 0);
    //Vertex corner2 = Vertex(glm::vec3(-10, 5.8, -5), 0, 1);
    //Vertex corner3 = Vertex(glm::vec3(10, -5.7, -5), 1, 0);
    //Vertex corner4 = Vertex(glm::vec3(10, 5.8, -5), 1, 1);
    
    //Ashikhmin Shirley
    //world.Add(std::make_unique<Triangle>(Triangle({ corner1, corner2, corner3 }, 0.0f, 0.0f, std::make_unique<Mat_AshikhminShirley>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), 10, 10))));
    //world.Add(std::make_unique<Triangle>(Triangle({ corner3, corner2, corner4 }, 0.0f, 0.0f, std::make_unique<Mat_AshikhminShirley>(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f), 10, 10))));


    //Image Texture
    world.Add(std::make_unique<Triangle>(Triangle({ corner1, corner2, corner3 }, 0.0f, 0.0f, std::make_unique<Mat_ImageTexture>("ornn.jpg"))));
    world.Add(std::make_unique<Triangle>(Triangle({ corner3, corner2, corner4 }, 0.0f, 0.0f, std::make_unique<Mat_ImageTexture>("ornn.jpg"))));

    //Checkerboard ground
	glm::vec3 color1 = glm::vec3(1.0f, 0.2f, 0.6f);
    glm::vec3 color2 = glm::vec3(0.6f, 0.0f, 0.6f);
    //world.Add(std::make_unique<Triangle>(Triangle({ corner1, corner2, corner3 }, 0.0f, 0.0f, std::make_unique<Mat_Checkerboard>(color1, color2, 0.1, 0.25))));
    //world.Add(std::make_unique<Triangle>(Triangle({ corner3, corner2, corner4 }, 0.0f, 0.0f, std::make_unique<Mat_Checkerboard>(color1, color2, 0.1, 0.25))));

    //Phong Shaded ground
    //world.Add(std::make_unique<Triangle>(Triangle({ corner1, corner2, corner3 }, 0.0f, 0.0f, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 1.0f, 15.0f))));
    //world.Add(std::make_unique<Triangle>(Triangle({ corner3, corner2, corner4 }, 0.0f, 0.0f, std::make_unique<Mat_Phong>(glm::vec3(0.0f, 0.4f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 1.0f, 1.0f, 2.0f))));

    // lights
    world.Add(std::make_unique<Light>(Light(glm::vec3(1.5f, 10.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f)));
    //world.Add(std::make_unique<Light>(Light(glm::vec3(3.0f, 2.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f)));
    
    //test light
    //world.Add(std::make_unique<Light>(Light(glm::vec3(1.0f, 10.0f, -15.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f)));



    //Add camera
	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -5.0f), 8.0, 16, 9);
	world.TransformAll(camera.GetViewMatrix());

    std::vector<glm::vec3> radianceArray = camera.RenderWorld(world, WINDOW_WIDTH, WINDOW_HEIGHT);
    //std::println("length = {}", rgbArray.size());


    ////////////////////////////////////////////////////////////////////////////////////
    surface = SDL_CreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_PIXELFORMAT_RGBA32);

    Uint32* pixels = static_cast<Uint32*>(surface->pixels);

    float logAverageLuminance = 0.0f;
    
    float ri = 0.0f;
    float gi = 0.0f;
    float bi = 0.0f;

	//Calculate log-average luminance for tone reproduction with Ward's method
    float totalLuminance = 0.0f;
    float delta = 0.0001;

    float keyValue = 0.0f;


    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            int index = y * WINDOW_WIDTH + x;
            glm::vec3 radianceValues = radianceArray[index];
            ri = radianceValues[0];
            gi = radianceValues[1];
            bi = radianceValues[2];
            float Lxy = 0.27 * ri + 0.67 * gi + 0.06 * bi;
            //if (Lxy < 0) {
            //std::println("r = {}, g = {}, b = {}, Lxy = {}", ri, gi, bi, Lxy);
            //}
			//float logthing = std::log(0.0001 + Lxy);
            //if (logthing < 0) {
                //std::println("r = {}, g = {}, b = {}, Lxy = {}", r, g, b, Lxy);
                //std::println("logthing = {}", logthing);
            //}
            if (x == 495 and y == 245) {
				keyValue = Lxy;
            }

            totalLuminance += std::log(delta + Lxy);
        }
    }
    int numPixels = WINDOW_WIDTH * WINDOW_HEIGHT;
    logAverageLuminance = std::exp(totalLuminance / numPixels);
    if (keyValue == -1.0f) {
        keyValue = logAverageLuminance;
    }
    //   std::println("totalLuminance = {}", totalLuminance);
       //std::println("divided = {}", totalLuminance / numPixels);
	std::println("logAverageLuminance = {}", logAverageLuminance);


    float Ldmax = 100.0f;
    float maxNormalizedLuminance = 0.0f;
    int b = 0.25;

    if (toneReproductionType == "adaptive") {
        //Get maxnormalizedLuminance
        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
            for (int x = 0; x < WINDOW_WIDTH; ++x) {
                int index = y * WINDOW_WIDTH + x;
                glm::vec3 radianceValues = radianceArray[index];
                ri = radianceValues[0];
                gi = radianceValues[1];
                bi = radianceValues[2];

                float Lxy = 0.27 * ri + 0.67 * gi + 0.06 * bi;
                float normalizedLxy = Lxy / logAverageLuminance;
				//std::println("Lxy = {}, normalizedLxy = {}", Lxy, normalizedLxy);

                if (normalizedLxy > maxNormalizedLuminance) {
                    maxNormalizedLuminance = normalizedLxy;
                }
            }
        }
		std::println("maxNormalizedLuminance = {}", maxNormalizedLuminance);

        // Get Ldmax
        Ldmax = 0.0f;
        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
            for (int x = 0; x < WINDOW_WIDTH; ++x) {
                int index = y * WINDOW_WIDTH + x;
                glm::vec3 radianceValues = radianceArray[index];
                ri = radianceValues[0];
                gi = radianceValues[1];
                bi = radianceValues[2];

                float Lxy = 0.27 * ri + 0.67 * gi + 0.06 * bi;
                float normalizedLxy = Lxy / logAverageLuminance;

                float Lwa = logAverageLuminance; //adaptation luminance = log-average luminance in scene
                float val1 = 1 / std::log10(1 + maxNormalizedLuminance);
                float val2Numerator = std::log(normalizedLxy + 1);

                float val2Denominator = std::log(2 + (std::pow(normalizedLxy / maxNormalizedLuminance, std::log(b) / std::log(0.5))) * 8);

                float val2 = val2Numerator / val2Denominator;

                float Ld = val1 * val2;

                if (Ld > Ldmax) {
                    Ldmax = Ld;
                }
            }
        }
    }
	std::println("Ldmax = {}", Ldmax);

                
    for (int y = 0; y < WINDOW_HEIGHT; ++y) {
        for (int x = 0; x < WINDOW_WIDTH; ++x) {
            int index = y * WINDOW_WIDTH + x;
            glm::vec3 radianceValues = radianceArray[index];  // Get corresponding pixel radiance

            ///////////////////////
            ///TONE REPRODUCTION///

            // Convert from float [0,1] to uint8_t [0,255]
            float ri = radianceValues[0];
            float gi = radianceValues[1];
            float bi = radianceValues[2];

            if (ri != 0 or gi != 0 or bi != 0) {
                bool ihatebenson = false;
            }
            // Calculate luminance
			float Lxy = 0.27 * ri + 0.67 * gi + 0.06 * bi;

            float rs = 0;
            float gs = 0;
            float bs = 0;
            // Compress luminance to range [0, Ldmax]
            if (toneReproductionType == "Ward") {
                float Lwa = logAverageLuminance; //adaptation luminance = log-average luminance in scene
                Lwa = 0.01f;
                float innerDiv = std::pow((Ldmax / 2), 0.4);
                float numerator = 1.219 + innerDiv;
				float denom = 1.219 + std::pow(Lwa, 0.4);
				float quotient = numerator / denom;
				float sf = std::pow(quotient, 2.5);
				//float sf = std::pow( ((1.219 + std::pow((Ldmax / 2), 0.4)) / (1.219 + std::pow(Lwa, 0.4))), 2.5);
				//std::println("sf = {}", sf);
				rs = ri * sf;
				gs = gi * sf;
				bs = bi * sf;
                if (rs > Ldmax or gs > Ldmax or bs > Ldmax) {
                    bool whoisbenson = false;
                }
            }
            else if (toneReproductionType == "Reinhard")
            {
				float a = 0.18f; // percent gray zone for zone 
                //std::println("LAL: {}", keyValue);// 0.00047111965
                //keyValue = 0.01;
                float toMult = a / keyValue;
                ri *= toMult;
				gi *= toMult;
                bi *= toMult;
				rs = ri / (1 + ri);
				gs = gi / (1 + gi);
                bs = bi / (1 + bi);
                //if (r > 1.0f or g > 1.0f or b > 1.0f) {
                //    std::println("r = {}, g = {}, b = {}", r, g, b);
                //}

				rs *= Ldmax;
				gs *= Ldmax;
                bs *= Ldmax;

            }
            else if (toneReproductionType == "adaptive") {
                //adpaptive logarithmic mapping
				float normalizedLxy = Lxy / Ldmax;
                float Lwa = logAverageLuminance; //adaptation luminance = log-average luminance in scene
                float val1 = 1 / std::log10(1 + maxNormalizedLuminance);
                float val2Numerator = std::log(normalizedLxy + 1);

				float val2Denominator = std::log(2 + (std::pow(normalizedLxy/maxNormalizedLuminance, std::log(b)/std::log(0.5))) * 8);

                float val2 = val2Numerator / val2Denominator;

                float Ld = val1 * val2;

                rs = ri * Ld / Lxy;
                gs = gi * Ld / Lxy;
                bs = bi * Ld / Lxy;
				//std::println("Lxy = {}, Ld = {}", Lxy, Ld);
				//std::println("r = {}, g = {}, b = {}", r, g, b);
				//std::println("rs = {}, gs = {}, bs = {}", rs, gs, bs);
				//if (r > 1.0f or g > 1.0f or b > 1.0f) {
				//    std::println("r = {}, g = {}, b = {}", r, g, b);
				//}
            }
            else if (toneReproductionType == "Lazy")
            {
                //std::println("r = {}, g = {}, b = {}", radianceValues[0], radianceValues[1], radianceValues[2]);
                rs = std::clamp(radianceValues[0], 0.0f, 1.0f);
                gs = std::clamp(radianceValues[1], 0.0f, 1.0f);
                bs = std::clamp(radianceValues[2], 0.0f, 1.0f);
                //std::println("r = {}, g = {}, b = {}", ri, gi, bi);

            }


            // Apply device model (assuming device with max output of Ldmax and gamma of 1 with sRGB color space
            if (toneReproductionType != "Lazy") {
                rs = rs / Ldmax;
                gs = gs / Ldmax;
                bs = bs / Ldmax;
            }

			//std::println("r = {}, g = {}, b = {}", r, g, b);

            //radianceValues *= 255.0f;
            ///////////////////////
            //if (r > 1.0f or g > 1.0f or b > 1.0f) {
            //std::println("r = {}, g = {}, b = {}", rs, gs, bs);
            //}
			rs = glm::clamp(rs, 0.0f, 1.0f);
            gs = glm::clamp(gs, 0.0f, 1.0f);
            bs = glm::clamp(bs, 0.0f, 1.0f);
            //std::println("r = {}, g = {}, b = {}", rs, gs, bs);

    //        if (x > 490 and x < 500 and y > 240 and y < 250) {
    //            rs = 0.0f;
				//gs = 1.0f;
				//bs = 0.0f;
    //        }

			//cast to uint8_t and convert to 0-255 range
            uint8_t r8 = static_cast<uint8_t>(rs * 255.0f);
            uint8_t g8 = static_cast<uint8_t>(gs * 255.0f);
            uint8_t b8 = static_cast<uint8_t>(bs * 255.0f);
            uint8_t a8 = 255;  // Full opacity

			//std::cout << "r8 = " << (int)r8 << ", g8 = " << (int)g8 << ", b8 = " << (int)b8 << std::endl;

            // Store pixel color in correct endian order
            //pixels[y * (surface->pitch/4) + x] = SDL_Swap32LE((a << 24) | (b << 16) | (g << 8) | r);
            Uint32 color = (a8 << 24) | (b8 << 16) | (g8 << 8) | r8;

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