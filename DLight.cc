#include "DLight.h"

DLight::DLight()
{
    direction = MyVector();
    for (int i = 0; i < 3; i++)
        color[i] = 0;
}

DLight::DLight(MyVector &d, float &r, float &g, float &b)
{
    direction = d;
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

MyVector DLight::getDirection()
{
    return direction;
}

RGB DLight::getIntensity()
{
    return color;
}