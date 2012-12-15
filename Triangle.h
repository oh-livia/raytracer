#ifndef raytra_Triangle_h
#define raytra_Triangle_h

#include "Surface.h"
#include "MyPoint.h"
#include "MyVector.h"
#include "Intersection.h"

class Triangle: public Surface
{
private:
    MyPoint p1;
    MyPoint p2;
    MyPoint p3;
    MyVector normal;
    Intersection *intersection;
    int material;
public:
    Triangle();
    Triangle(MyPoint &p1, MyPoint &p2, MyPoint &p3, int m);
    virtual bool intersect(Ray &r);
    virtual float getClosestT();
    virtual MyPoint getClosestInt();
    virtual int getMaterial();
    virtual MyVector getClosestNormal();
    virtual bool isClosedSurface() {return false;};
};

#endif
