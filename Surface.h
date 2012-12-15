#ifndef SURFACE_H
#define SURFACE_H

#include "Intersection.h"
#include "Ray.h"
#include "Material.h"
#include "BoundingBox.h"

class Surface
{
protected:
    BoundingBox bbox;
public:
	virtual bool intersect(Ray &r) = 0;
    virtual float getClosestT() = 0;
    virtual MyPoint getClosestInt() = 0;
    virtual int getMaterial() = 0;
    virtual MyVector getClosestNormal() = 0;
    virtual bool isClosedSurface() = 0;
};

#endif
