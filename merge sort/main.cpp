#include <SDL2/SDL.h>
#include <iostream>
#include <ranges>
#include <random>
#include <algorithm>
#include "setting.h"
#include "sdl_utils.cpp"
using namespace std;

void mergeSort(vector<int> &v, int l, int r, SDL_Renderer *render);
void merge(vector<int> &v, int l, int m, int r, SDL_Renderer *render);

void mergeSort(vector<int> &v, int l, int r, SDL_Renderer *render)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(v, l, m, render);
        mergeSort(v, m + 1, r, render);
        merge(v, l, m, r, render);
    }
}

void merge(vector<int> &v, int l, int m, int r, SDL_Renderer *render)
{
    int k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    int L[n1], R[n2];
 
    for(int i = 0; i < n1; i++)
        L[i] = v[l + i];
    for(int j = 0; j < n2; j++)
        R[j] = v[m + 1+ j];

    int i = 0;
    int j = 0;
    k = l;
     
    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        draw_state(v, render, k);
        k++;
    }
 
    while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
        draw_state(v, render, k);
    }
 
    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
        draw_state(v, render, k);
    }
}
 
void printArray(vector<int> v)
{
    for(int i : v)
        printf("%d ", i);
         
    cout << "\n";
}

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
    int arr_size = v.size();
 
    mergeSort(v, 0, arr_size - 1, render);

    if (is_sorted(v))
    {
        draw_complete(v, render);
    }

    return EXIT_SUCCESS;
}