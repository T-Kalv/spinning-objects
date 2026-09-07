// Program: Cube.cpp
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#include "Cube.h"
#include "customMath.h"

const char illuminatonCharacters[] = ".,-~:;=!*#$@";

void Cube::calculateForSurface(float cubeX, float cubeY, float cubeZ, float normalX, float normalY, float normalZ, float A, float B, float* zBuffer, char* frameBuffer, int screenWidth, int screenHeight)
{
    float cosineA = customCosine(A);
    float sineA = customSine(A);
    float cosineB = customCosine(B);
    float sineB = customSine(B);

    //Rotate 3D coordiates around Y-axis angle B
    float x1 = cubeX * cosineB + cubeZ * sineB;
    float y1 = cubeY;
    float z1 = -cubeX * sineB + cubeZ * cosineB;

    //Rotation 3D coordinated around X-axis angle A
    float rotatedX = x1;
    float rotatedY = y1 * cosineA - z1 * sineA;
    float rotatedZ = y1 * sineA + z1 * cosineA;

    //Rotate surface normal for lighting conditions
    float normalY1 = normalY;
    float normalZ1 = -normalX * sineB + normalZ * cosineB;

    float rotatedNormalZ = normalY1 * sineA + normalZ1 * cosineA;

    //3D projection
    float viewerToObjectDistance = 5.0f;
    float screenScaleFactor = 30.0f;
    float z = rotatedZ + viewerToObjectDistance;
    float oneOverZ = 1.0f / z;

    int xProjection = (int)(screenWidth / 2.0f + screenScaleFactor * oneOverZ * rotatedX);
    int yProjection = (int)(screenHeight / 2.0f + (screenScaleFactor / 2.0f) * oneOverZ * rotatedY);

    if (xProjection >= 0 && xProjection < screenWidth && yProjection >= 0 && yProjection < screenHeight)
    {
        //Calculate luminiance which is the dot product of rotated normal and light source direction
        //Asumme light is from begind viewer at 0,0,-1
        float objectLuminance = - rotatedNormalZ;
        int oneDArrayIndex = xProjection + yProjection * screenWidth;

        if (oneOverZ > zBuffer[oneDArrayIndex])
        {
            zBuffer[oneDArrayIndex] = oneOverZ;
            //Map luminance -1 to 1 to array index 0 to 11
            int luminanceIndex = (int)((objectLuminance + 1.0f) *5.5f);
            if (luminanceIndex >= 0)
            {
                if (luminanceIndex > 11)
                {
                    luminanceIndex = 11;
                }
                frameBuffer[oneDArrayIndex] = illuminatonCharacters[luminanceIndex];
            }
            //Don't draw when it is back-facing in the cube
            else
            {
                frameBuffer[oneDArrayIndex] = ' ';
            }
        }
    }
}

void Cube::drawToBuffer(float A, float B, float* zBuffer, char* frameBuffer, int screenWidth, int screenHeight)
{
    float cubeSize = 1.5f;
    float densityStep = 0.05f;

    //Draw 6 flat faces of cube on 2D cartesian grid
    for (float cubeX = -cubeSize; cubeX < cubeSize; cubeX = cubeX + densityStep)
    {
        for (float cubeY = -cubeSize; cubeY < cubeSize; cubeY = cubeY + densityStep)
        {
            //Back face
            calculateForSurface(cubeX, cubeY, cubeSize, 0, 0, 1, A, B, zBuffer, frameBuffer, screenWidth, screenHeight);
            //Front face
            calculateForSurface(cubeX, cubeY, -cubeSize, 0, 0, -1, A, B, zBuffer, frameBuffer, screenWidth, screenHeight);
            //Right face
            calculateForSurface(cubeSize, cubeY, cubeX, 1, 0, 0, A, B, zBuffer, frameBuffer, screenWidth, screenHeight);
            //Left face
            calculateForSurface(-cubeSize, cubeY, cubeX, -1, 0, 0, A, B, zBuffer, frameBuffer, screenWidth, screenHeight);
            //Top face
            calculateForSurface(cubeX, -cubeSize, cubeY, 0, -1, 0, A, B, zBuffer, frameBuffer, screenWidth, screenHeight);
            //Bottom face
            calculateForSurface(cubeX, cubeSize, cubeY, 0, 1, 0, A, B, zBuffer, frameBuffer, screenWidth, screenHeight);
        }  
    }
}
