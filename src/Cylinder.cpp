// Program: Cylinder.cpp
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#include "Cylinder.h"
#include "customMath.h"

const char illuminationCharacters[] = ".,-~:;=!*#$@";

void Cylinder::calculateForPoint(float pointX, float pointY, float pointZ, float normalX, float normalY, float normalZ, int colourCode, float A, float B, float* zBuffer, char* frameBuffer, int* colourBuffer, int screenWidth, int screenHeight)
{
    float cosineA = customCosine(A);
    float sineA = customSine(A);
    float cosineB = customCosine(B);
    float sineB = customSine(B);

    //Rotate 3D coordinates
    float x1 = pointX * cosineB + pointZ * sineB;
    float y1 = pointY;
    float z1 = -pointX * sineB + pointZ * cosineB;

    float rotatedX = x1;
    float rotatedY = y1 * cosineA - z1 * sineA;
    float rotatedZ = y1 * sineA + z1 * cosineA;

    //Rotate surface normal for lighting conditions
    //float normalX1 = normalX * cosineB + normalZ * sineB;
    float normalY1 = normalY;
    float normalZ1 = -normalX * sineB + normalZ * cosineB;

    float rotatedNormalZ = normalY1 * sineA + normalZ1 * cosineA;

    //3D projection
    float z = rotatedZ + 5.0f;
    float oneOverZ = 1.0f / z;

    int xProjection = (int)(screenWidth / 2.0f + 30.0f * oneOverZ * rotatedX);
    int yProjection = (int)(screenHeight / 2.0f + 15.0f * oneOverZ * rotatedY);

    if (xProjection >= 0 && xProjection < screenWidth && yProjection >= 0 && yProjection < screenHeight)
    {
        float objectLuminance = -rotatedNormalZ;
        int oneDArrayIndex = xProjection + yProjection * screenWidth;
        if (oneOverZ > zBuffer[oneDArrayIndex])
        {
            zBuffer[oneDArrayIndex] = oneOverZ;
            colourBuffer[oneDArrayIndex] = colourCode;

            int luminanceIndex = (int)((objectLuminance + 1.0f) * 5.5f);
            if (luminanceIndex >= 0)
            {
                if (luminanceIndex > 11)
                {
                    luminanceIndex = 11;
                }
                frameBuffer[oneDArrayIndex] = illuminationCharacters[luminanceIndex];
            }
            else
            {
                frameBuffer[oneDArrayIndex] = ' ';
            }
            
        }
        
    }
    
}

void Cylinder::drawToBuffer(float A, float B, float* zBuffer, char* frameBuffer, int* colourBuffer, int screenWidth, int screenHeight)
{
    float radius = 1.0f;
    float halfHeight = 1.2f;
    float thetaStep = 0.05f;
    float lengthStep = 0.05f;
    float radiusStep = 0.05f;

    //Curved cylinder wall tube
    for (float theta = 0; theta < 6.28f; theta = theta + thetaStep)
    {
        float cosineTheta = customCosine(theta);
        float sineTheta = customSine(theta);
        float pointX = radius * cosineTheta;
        float pointZ = radius * sineTheta;
        float normalX = cosineTheta;
        float normalZ = sineTheta;

        for (float pointY = -halfHeight; pointY <= halfHeight; pointY = pointY + lengthStep)
        {
            //Green for main cylinder tube
            calculateForPoint(pointX, pointY, pointZ, normalX, 0, normalZ,  46, A, B, zBuffer, frameBuffer, colourBuffer, screenWidth, screenHeight);
        }
    }

    for (float theta = 0; theta < 6.28f; theta = theta + thetaStep)
    {
        float cosineTheta = customCosine(theta);
        float sineTheta = customSine(theta);

        for (float r = 0; r <= radius; r = r + radiusStep)
        {
            float pointX = r * cosineTheta;
            float pointZ = r * sineTheta;

            //Red for top circle
            calculateForPoint(pointX, -halfHeight, pointZ, 0, -1, 0, 196, A, B, zBuffer, frameBuffer, colourBuffer, screenWidth, screenHeight);

            //Blue for bottom circle
            calculateForPoint(pointX, halfHeight, pointZ, 0, 1, 0, 39, A, B, zBuffer, frameBuffer, colourBuffer, screenWidth, screenHeight);
        }   
    }
}