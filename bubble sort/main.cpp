#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <ranges>
#include <random>
#include <algorithm>

bool is_sorted(std::vector<int> v);

void draw_state(
    std::vector<int> &v,
    SDL_Renderer *render,
    unsigned int blue
);

void draw_complete(
    std::vector<int> &v,
    SDL_Renderer *render,
    unsigned int green
);

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

    for (unsigned int i = 0; i < v.size()-1; i++)
    {
        bool end = false;
        for (unsigned int j = 0; j < v.size() - i - 1; j++)
        {
            if (v[j] < v[j+1])
            {
                std::swap(v[j+1], v[j]);
                end = true;
            }
            SDL_SetRenderDrawColor(render,0,0,0,255);
            SDL_RenderClear(render);

            draw_state(v, render, j);

            SDL_RenderPresent(render);
            SDL_Delay(1);
        }
        if (!end)
        {
            break;
        }
    }

    if (is_sorted(v))
    {
        std::cout<<"\nis sorted\n";
    }

    for (int i = 0; i < v.size(); i++)
    {
            SDL_SetRenderDrawColor(render,0,0,0,255);
            SDL_RenderClear(render);

            draw_complete(v, render, i);

            SDL_RenderPresent(render);
            SDL_Delay(5);
    }

    return EXIT_SUCCESS;
}
void draw_state(
    std::vector<int> &v,
    SDL_Renderer *render,
    unsigned int blue
){
    int index = 0;
    for (int i : v)
    {
        if (index == blue || index == blue + 1)
        {
            SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
        }
        else
        {   
            SDL_SetRenderDrawColor(render,255,255,255,255);
        }
        
        SDL_RenderDrawLine(render, index, 99, index, i);
        index += 1;
    }    
}
void draw_complete(
    std::vector<int> &v,
    SDL_Renderer *render,
    unsigned int green
){
    int index = 0;
    for (int i : v)
    {
        if (index < green)
        {
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        }
        else
        {   
            SDL_SetRenderDrawColor(render,255,255,255,255);
        }
        
        SDL_RenderDrawLine(render, index, 99, index, i);
        index += 1;
    }    
}
bool is_sorted(std::vector<int> v){
    
    int len = v.size()-1;
    for (int i = 0; i < len ; i++)
    {
        if (v[i] < v[i+1])
        {
            return false;
        }   
    }
    return true;
}