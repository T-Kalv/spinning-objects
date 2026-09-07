// Program: Cube.h
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape
{
    public:
        void drawToBuffer(float A, float B, float* zBuffer, char* frameBuffer, int screenWidth, int screenHeight) override;

    private:
        void calculateForSurface(float cubeX, float cubeY, float cubeZ, float normalX, float normalY, float normalZ, float A, float B, float* zBuffer, char* frameBuffer, int screenWidth, int screenHeight);
};

#endif