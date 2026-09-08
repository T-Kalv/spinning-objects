// Program: renderer.cpp
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#include "renderer.h"
#include "customMath.h"
#include <iostream>

void clearScreen()
{
    std::cout << "\x1b[2J\x1b[H";
}

void renderFrame(Shape* activeShape, float A, float B)
{
    float zBuffer[SCREEN_HEIGHT * SCREEN_WIDTH];
    char frameBuffer[SCREEN_HEIGHT * SCREEN_WIDTH];
    int colourBuffer[SCREEN_HEIGHT * SCREEN_WIDTH];

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        zBuffer[i] = 0.0f;
        frameBuffer[i] = ' ';
        //Default white colour
        colourBuffer[i] = 231;
    }

    //Populate buffer
    if(activeShape != nullptr)
    {
        activeShape->drawToBuffer(A, B, zBuffer, frameBuffer, colourBuffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    std::cout << "\x1b[H";
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        if (i % SCREEN_WIDTH == SCREEN_WIDTH - 1)
        {
            std::cout << '\n';
        }
        else
        {
            if (frameBuffer[i] == ' ')
            {
                std::cout << ' ';
            }
            else
            {
                std::cout << "\x1b[38;5;" << colourBuffer[i] << "m" << frameBuffer[i] << "\x1b[0m";
            }
            
        }
    }
}
