#ifndef AmbLight_h
#define AmbLight_h

#include "RGB.h"

class AmbLight
{
private:
    RGB color;
public:
    AmbLight();
    AmbLight(float r, float g, float b);
    void setColor(float &r, float &g, float &b);
    RGB getColor();
    float operator[](const int i);
};

#endif
