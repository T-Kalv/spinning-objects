// Program: customMathLib.cpp
// Author:
// Module:
// Email: 
// Student Number: 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------
// Code

#include "customMath.h"

float customAbs(float x)
{
    if (x < 0)
    {
        return -x;
    }
    return x;
}

float customFmod(float x, float y)
{
    float result = x;
    if (y == 0)
    {
        return 0;
    }

    int quotient = result/y;
    result = result - (quotient*y);

    if (x < 0 && result > 0)
    {
        result = result - customAbs(y);
    }
    else if (x > 0 && result < 0)
    {
        result = result + customAbs(y);
    }

    return result;
}

//Taylor Series Sine implementation
float custom_sine(float x)
{
    x = customFmod(x+PI, 2*PI) - PI;
    float x2 = x*x;
    float term = x;
    float sum = x;

    //x^3/3!
    term = (term*x2) / 6.0f;
    sum = sum - term;

    //x^5/5!
    term = (term*x2) / 20.0f;
    sum = sum - term;

    //x^7/7!
    term = (term*x2) / 42.0f;
    sum = sum - term;

    //x^9/9!
    term = (term*x2) / 72.0f;
    sum = sum - term;

    return sum;
}

float customcosine(float x)
{
    return customSine(x + PI/2.0f);
}