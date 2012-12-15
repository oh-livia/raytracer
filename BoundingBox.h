#ifndef BoundingBox_h
#define BoundingBox_h

#include "Ray.h"
#include "MyPoint.h"
#include "MyVector.h"

class BoundingBox
{
private:
    float xmin, xmax, ymin, ymax, zmin, zmax;
    float txmin, txmax, tymin, tymax, tzmin, tzmax;
    float bigmin, smallmax;
    void pushOut();
public:
    BoundingBox();
    BoundingBox(float minx, float miny, float minz, float maxx, float maxy, float maxz);
    bool intersect(Ray &r);
    float mint();
    MyVector normal();
};

#endif
