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

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        zBuffer[i] = 0.0f;
        frameBuffer[i] = ' ';
    }

    //Populate buffer
    if(activeShape != nullptr)
    {
        activeShape->drawToBuffer(A, B, zBuffer, frameBuffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    //Render buffers to terminal with ANSI colours
    const char* PINK = "\x1b[38;5;213m";
    const char* DOUGH = "\x1b[38;5;136m";
    const char* RESET = "\x1b[0m";
    const char* SPRINKLES[] = {"\x1b[38;5;51m", "\x1b[38;5;226m", "\x1b[38;5;46m"};

    std::cout << "\x1b[H";
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        if (i % SCREEN_WIDTH == SCREEN_WIDTH - 1)
        {
            std::cout << '\n';
        }
        else
        {
            char c = frameBuffer[i];
            if (c == ' ')
            {
                std::cout << c;
            }
            else if (c == '.' || c == ',' || c == '-')
            {
                std::cout << DOUGH << c << RESET;
            }
            else
            {
                if (c == '@' || c == '#' || c == '$')
                {
                    if (i % 13 == 0)
                    {
                        int sprinkleColor = (i % 3);
                        std::cout << SPRINKLES[sprinkleColor] << c << RESET;
                        continue;
                    }
                }
                std::cout << PINK << c << RESET;
            }
        }
    }
}