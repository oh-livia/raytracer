#ifndef PLight_h
#define PLight_h

#include "MyPoint.h"
#include "RGB.h"

class PLight
{
private:
    MyPoint position;
    RGB color;
public:
    PLight();
    PLight(MyPoint &position, float cr, float cg, float cb);
    void setPosition(MyPoint &p);
    void setColor(float cr, float cg, float cb);
    MyPoint &getPosition();
    RGB getIntensity();
};

#endif
