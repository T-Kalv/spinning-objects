// Program: Torus.h
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#ifndef TORUS_H
#define TORUS_H

#include "Shape.h"

class Torus : public Shape
{
    public:
        void drawToBuffer(float A, float B, float* zBuffer, char* frameBuffer, int* colourBuffer, int screenWidth, int screenHeight) override;
};

#endif