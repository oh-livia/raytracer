#include "PLight.h"

PLight::PLight()
{
    for (int i = 0; i < 3; i++)
        color[i] = 0;
    position = MyPoint(0, 0, 0);
}

PLight::PLight(MyPoint &p, float cr, float cg, float cb)
{
    position = p;
    color[0] = cr;
    color[1] = cg;
    color[2] = cb;
}

void PLight::setPosition(MyPoint &p)
{
    position = p;
}

void PLight::setColor(float cr, float cg, float cb)
{
    color[0] = cr;
    color[1] = cg;
    color[2] = cb;
}

MyPoint &PLight::getPosition()
{
    return position;
}

RGB PLight::getIntensity()
{
    return color;
}