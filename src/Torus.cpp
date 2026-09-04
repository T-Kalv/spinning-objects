// Program: Torus.h
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#include "Torus.h"
#include "customMath.h"

//ASCII characters list ordered from dark to bright
const char illuminatonCharacters[] = ".,-~:;=!*#$@";

void Torus::drawToBuffer(float A, float B, float* zBuffer, char* frameBuffer, int screenWidth, int screenHeight)
{
    float cosineA = customCosine(A);
    float sineA = customSine(A);
    float cosineB = customCosine(B);
    float sineB = customSine(B);

    float twoDCircleRadius = 1.0f;
    float overallTorusRadius = 2.0f;
    float viewerToObjectDistance = 5.0f;
    float screenScaleFactor = 30.0f;

    for (float theta = 0; theta < 2*PI; theta = theta + 0.07f)
    {
        float cosineTheta = customCosine(theta);
        float sineTheta = customSine(theta);

        for (float phi = 0; phi < 2*PI; phi = phi + 0.02f)
        {
            float cosinePhi = customCosine(phi);
            float sinePhi = customSine(phi);

                //2D circle before the 3d rotation
                float circleX = overallTorusRadius + twoDCircleRadius * cosineTheta;
                float circleY = twoDCircleRadius * sineTheta;
                
                //3D coordinates by multiply by rotation matrices for A and B
                float x = circleX * (cosineB * cosinePhi - sineB * cosineA * sinePhi) + circleY * sineB * sineA;
                float y = circleX * (sineB * cosinePhi + cosineB * cosineA * sinePhi) - circleY * cosineB * sineA;
                float z = viewerToObjectDistance + circleX * sineA * sinePhi + circleY * cosineA;

                float oneOverZ = 1.0f/z;

                //Calculate screen coordinates
                int xProjection = (int)(screenWidth / 2.0f + screenScaleFactor * oneOverZ * x);
                int yProjection = (int)(screenHeight / 2.0f - (screenScaleFactor / 2.0f) * oneOverZ * y);

                if (xProjection >= 0 && xProjection < screenWidth && yProjection >= 0 && yProjection < screenHeight)
                {
                    float objectLuminance = cosinePhi * cosineTheta * sineB - cosineA * cosineTheta * sinePhi - sineA * sineTheta + cosineB * (cosineA * sineTheta - cosineTheta * sineA * sinePhi);
                
                    int oneDArrayIndex = xProjection + yProjection * screenWidth;

                    //Z Buffer check
                    if (oneOverZ > zBuffer[oneDArrayIndex])
                    {
                        zBuffer[oneDArrayIndex] = oneOverZ;
                    
                        //Scale luminance
                        int luminanceIndex = (int)(objectLuminance * 8.0f);
                        if (luminanceIndex > 0)
                        {
                            if (luminanceIndex > 11)
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
    }
}
