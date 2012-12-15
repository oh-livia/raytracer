#ifndef AreaLight_h
#define AreaLight_h

#include "MyPoint.h"
#include "MyVector.h"
#include "RGB.h"
#include <cstdlib>

class AreaLight
{
private:
    MyPoint center;
    MyVector normal;
    MyVector u_direction;
    MyVector v_direction;
    float sideLen;
    RGB color;
public:
    AreaLight();
    AreaLight(MyPoint &c, MyVector &n, MyVector &u_d, float &len, RGB &intensity);
    bool hasColor();
    RGB getColor();
    void sample(int strats);
    MyVector getNormal();
    MyPoint getSample(int segment);
};

#endif
