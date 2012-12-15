#ifndef RAY_H
#define RAY_H

#include "MyVector.h"
#include "MyPoint.h"

class Ray
{
private:
	MyPoint origin;
	MyVector direction;
public:
	Ray();
	Ray(MyPoint p, MyVector v);	//Constructs a ray from a point and a vector
	Ray(MyPoint p1, MyPoint p2);	//Constructs a ray pointing from p1 to p2
	MyPoint computePoint(double t);	//Computes and returns a point given a parameter t
	MyPoint getP();
	MyVector getD();
};

#endif
