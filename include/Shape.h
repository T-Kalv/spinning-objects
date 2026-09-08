// Program: Shape.h
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
    public:
        virtual void drawToBuffer(float A, float B, float* zBuffer, char* frameBuffer, int* colourBuffer, int screenWidth, int screenHeight) = 0;
        virtual ~Shape() {}

};

#endif