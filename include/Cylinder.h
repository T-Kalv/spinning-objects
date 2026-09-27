// Program: Cylinder.h
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#ifndef CYLINDER_H
#define CYLINDER_H

#include "Shape.h"

class Cylinder : public Shape
{
    public:
        void drawToBuffer(float A, float B, float* zBuffer, char* frameBuffer, int* colorBufffer, int screenWidth, int screenHeight) override;

    private:
        void calculateForPoint(float pointX, float pointY, float pointZ, float normalX, float normalY, float normalZ, int colourCode, float A, float B, float* zBuffer, char* frameBuffer, int* colourBuffer, int screenWidth, int screenHeight);

};

#endif