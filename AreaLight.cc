#include "AreaLight.h"
#include <vector>

extern int secondaryRays;
vector<MyPoint> samples;

extern int secondaryRays;

AreaLight::AreaLight()
{
    center = MyPoint();
    normal = MyVector();
    u_direction = MyVector();
    v_direction = MyVector();
    sideLen = 0;
    color = RGB();
}

AreaLight::AreaLight(MyPoint &c, MyVector &n, MyVector &u_d, float &len, RGB &intensity)
{
    center = c;
    normal = n;
    u_direction = u_d;
    v_direction = crossProduct(normal, u_direction);
    sideLen = len;
    color = intensity;
}

bool AreaLight::hasColor()
{
    if (color.hasColor())
        return true;
    return false;
}

MyVector AreaLight::getNormal()
{
    return normal;
}

void AreaLight::sample(int strats)
{
    samples.clear();
    for (int p = 0; p < strats; p++)
    {
        for (int q = 0; q < strats; q++)
        {
            float uRand = ((float) rand()) / RAND_MAX;
            float vRand = ((float) rand()) / RAND_MAX;
            
            MyPoint samplePoint = center + ((u_direction * (uRand * sideLen + (p / strats) - sideLen/2))
                                            + (v_direction * (vRand * sideLen + (q /strats) - sideLen/2)));
            samples.push_back(samplePoint);
        }
    }
}

MyPoint AreaLight::getSample(int segment)
{
    return samples[segment];
}

RGB AreaLight::getColor()
{
    return color;
}
