#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "roman.h"

#define MAX_INPUT_LENGTH 10

// Function to handle the GUI
void handleEvent(SDL_Event event, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* inputTextTexture, SDL_Texture* resultTextTexture, char* inputText);

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL window and renderer
    SDL_Window* window = SDL_CreateWindow("Number to Roman Numeral Converter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 300, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize fonts and text handling (we'll use SDL_ttf for text rendering)
    if (TTF_Init() == -1) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Prepare textures for the input and result
    SDL_Texture* inputTextTexture = NULL;
    SDL_Texture* resultTextTexture = NULL;

    char inputText[MAX_INPUT_LENGTH] = "";
    SDL_Event event;
    int running = 1;

    // Main loop
    while (running) {
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else {
                handleEvent(event, window, renderer, inputTextTexture, resultTextTexture, inputText);
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Render the input and result text (you'd need to render using SDL_ttf for the actual text)
        // This is just a conceptual example:
        if (inputTextTexture) {
            SDL_RenderCopy(renderer, inputTextTexture, NULL, NULL);
        }
        if (resultTextTexture) {
            SDL_RenderCopy(renderer, resultTextTexture, NULL, NULL);
        }

        // Present the render
        SDL_RenderPresent(renderer);
    }

    // Clean up SDL
    SDL_DestroyTexture(inputTextTexture);
    SDL_DestroyTexture(resultTextTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void handleEvent(SDL_Event event, SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* inputTextTexture, SDL_Texture* resultTextTexture, char* inputText) {
    // Handle different events here
    if (event.type == SDL_KEYDOWN) {
        // Handle input (you can create a text input field in SDL2 here)
    }

    // Handle the "Convert" button press event
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        // Get the number from inputText and convert it to a Roman numeral
        int number = atoi(inputText);
        char result[64];

        if (number > 0 && number <= 3999) {
            strcpy(result, toRoman(number));
        } else {
            strcpy(result, "Invalid input! Enter a number between 1 and 3999.");
        }

        // Render the result to the screen (using SDL_ttf to display text)
        resultTextTexture = createTextureFromText(renderer, result);  // This is where you would render the Roman numeral result
    }
}
