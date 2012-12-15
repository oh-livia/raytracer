#ifndef DLight_h
#define DLight_h

#include "MyVector.h"
#include "RGB.h"

class DLight
{
private:
    MyVector direction;
    RGB color;
public:
    DLight();
    DLight(MyVector &d, float &r, float &g, float &b);
    MyVector getDirection();
    RGB getIntensity();
};

#endif
