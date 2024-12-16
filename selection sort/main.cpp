#include <SDL2/SDL.h>
#include <iostream>
#include <ranges>
#include <random>
#include <algorithm>

bool is_sorted(std::vector<int> v);

void draw_state(
    std::vector<int> &v,
    SDL_Renderer *render,
    unsigned int red,
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

    for (unsigned int i = 0; i < v.size(); i++)
    {
        int temp = i;
        for (unsigned int j = i; j < v.size(); j++)
        {
            if (v[temp] < v[j])
            {
                temp = j;
            }
            
            SDL_SetRenderDrawColor(render,0,0,0,255);
            SDL_RenderClear(render);
            draw_state(v, render, temp, j);
            SDL_RenderPresent(render);
            SDL_Delay(0);
        }
        std::swap(v[temp], v[i]);
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
    unsigned int red,
    unsigned int blue
){
    int index = 0;
    for (int i : v)
    {
        if (index == red)
        {
            SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
        }
        else if (index == blue)
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