#ifndef SPHERE_H
#define SPHERE_H

#include "Ray.h"
#include "Intersection.h"
#include "MyPoint.h"
#include "MyVector.h"
#include "Surface.h"

class Sphere: public Surface
{
private:
	MyPoint o;
	float r;
    double color[3];
    int material;
	Intersection *i;
	double computeDiscriminant(Ray ray, MyPoint origin, float r);
public:
	Sphere ();
	Sphere (MyPoint origin, float radius, const int m);
    Sphere& operator=(const Sphere rhs);
	virtual bool intersect(Ray &r);
    virtual int getMaterial();
    virtual float getClosestT();
    virtual MyPoint getClosestInt();
    virtual MyVector getClosestNormal();
    virtual bool isClosedSurface(){return true;};
};

#endif
