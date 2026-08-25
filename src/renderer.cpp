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

//ASCII characters list ordered from dark to bright
const char illuminatonCharacters[] = ".,-~:;=!*#$@";

void clearScreen()
{
    std::cout << "\x1b[2J\x1b[H";
}

void renderFrame(float A, float B)
{
    float zBuffer[SCREEN_HEIGHT * SCREEN_WIDTH];
    char frameBuffer[SCREEN_WIDTH * SCREEN_WIDTH];

    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        zBuffer[i] = 0.0f;
        frameBuffer[i] = ' ';
    }

    float cosineA = customCosine(A);
    float sineA = customSine(A);
    float cosineB = customCosine(B);
    float sineB = customSine(B);

    float twoDCircleRadius = 1.0f;
    float overallTorusRadius = 2.0f;
    float viewerToObjectDistance = 5.0f;
    float screenScaleFactor = 40.0f;

    for (float theta=0; theta<2*PI; theta = theta + 0.07f)
    {
        float cosineTheta = customCosine(theta);
        float sineTheta = customSine(theta);

        for (float phi = 0; phi<2*PI; phi = phi+0.02f)
        {
            float cosinePhi = customCosine(phi);
            float sinePhi = customSine(phi);

            //2D circle before the 3d rotation
            float circleX = overallTorusRadius + twoDCircleRadius * cosineTheta;
            float circleY = twoDCircleRadius * sineTheta;

            //3D coordinates by multiplu by rotation matrices for A and B
            float x = circleX * (cosineB * cosinePhi + sineA * sineB * sinePhi) - circleY * cosineA * sineB;
            float y = circleX * (sineB * cosinePhi - sineA * cosineB * sinePhi) + circleY * cosineA * cosineB;
            float z = viewerToObjectDistance + cosineA * circleX * sinePhi + circleY * sineA;

            float oneOverZ = 1.0f / z;
            float oneOverZ = 1.0f/z;

            //Calculate screen coordinates
            int xProjection = (int)(SCREEN_WIDTH/2.0f + screenScaleFactor*oneOverZ*x);
            int yProjection = (int)(SCREEN_HEIGHT/2.0f - (screenScaleFactor/2.0f)*oneOverZ*y);

            //Luminance which is surface normal dotproduct light source
            float objectLuminance = cosinePhi * cosineTheta * sineB - cosineA*cosineTheta*sinePhi - sineA*sineTheta + cosineB * (cosineA*sineTheta - cosineTheta*sineA*sinePhi);

            int oneDArrayIndex = xProjection + yProjection * SCREEN_WIDTH;

            //Z Buffer check
            if(oneDArrayIndex >= 0 && oneDArrayIndex < SCREEN_WIDTH * SCREEN_HEIGHT && oneOverZ > zBuffer[oneDArrayIndex])
            {
                zBuffer[oneDArrayIndex] = oneOverZ;
                //Scale luminance
                int luminanceIndex = (int)(objectLuminance * 8.0f);
                if(luminanceIndex>0)
                {
                    if(luminanceIndex > 11)
                    {
                        luminanceIndex = 11;
                    }
                    frameBuffer[oneDArrayIndex] = illuminatonCharacters[luminanceIndex];
                }
                else
                {
                    frameBuffer[oneDArrayIndex] = '.';
                }
            }
        }
    }

    //Terminal render
    std::cout << "\x1b[H";
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
    {
        if (i % SCREEN_WIDTH == SCREEN_WIDTH - 1)
        {
            std::cout << '\n';
        }
        else
        {
            std::cout << frameBuffer[i];
        }
    }

    
}

