#include "AmbLight.h"
#include <assert.h>

AmbLight::AmbLight()
{
    for (int i = 0; i < 3; i ++)
        color[i] = 0;
}

AmbLight::AmbLight(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void AmbLight::setColor(float &r, float &g, float &b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

RGB AmbLight::getColor()
{
    return color;
}

float AmbLight::operator[](const int i)
{
    assert (i >= 0 && i < 3);
    return color[i];
}