#include <SDL2/SDL.h>
#include <iostream>
#include <ranges>
#include <random>
#include <algorithm>
#include "setting.h"
#include "sdl_utils.cpp"

int main(int argc, char *argv[])
{
    std::random_device rd;
    std::uniform_int_distribution d(1,99);
    std::vector <int> v;

    SDL_Window *win = nullptr;
    SDL_Renderer *render = nullptr;
    SDL_CreateWindowAndRenderer(500, 500, 0, &win, &render);
    SDL_RenderSetScale(render, 5, 5);

    //creating random number
    for (int i = 0; i < 100; i++)
    {
        v.push_back(d(rd));
    }

    for (int i = 1; i < v.size(); ++i) {
            int key = v[i];
            int j = i - 1;

        while (j >= 0 && v[j] < key) {
            v[j + 1] = v[j];
            j = j - 1;
            
            draw_state(v, render, i, j);
        }

        v[j + 1] = key;
        SDL_Delay(delay);
    }

    if (is_sorted(v))
    {
        draw_complete(v, render);
    }

    return EXIT_SUCCESS;
}
