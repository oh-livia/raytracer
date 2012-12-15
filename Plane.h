#ifndef raytra_Plane_h
#define raytra_Plane_h

#include "Surface.h"
#include "MyVector.h"
#include "Intersection.h"

class Plane: public Surface
{
private:
    MyVector normal;
    float d;
    Intersection *i;
    int material;
public:
    Plane();
    Plane(MyVector &n, float &distance, int &m);
    virtual bool intersect(Ray &r);
    virtual float getClosestT();
    virtual MyPoint getClosestInt();
    virtual int getMaterial();
    virtual MyVector getClosestNormal();
    virtual bool isClosedSurface() {return false;};
};

#endif
