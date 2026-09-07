// Program: main.cpp
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#include "renderer.h"
#include "Torus.h"
#include "Cube.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void sleepMilliseconds(int milliseconds)
{
    #ifdef _WIN32
        Sleep(milliseconds);
    #else
        usleep(milliseconds * 1000);
    #endif  
}

int main()
{
    float A = 0.0f;
    float B = 0.0f;

    clearScreen();
    Torus donut;
    Cube cube;
    while (true)
    {
        renderFrame(&cube,A, B);
        A = A + 0.04f;
        B = B + 0.02f;
        sleepMilliseconds(30);
    }
    return 0;
}