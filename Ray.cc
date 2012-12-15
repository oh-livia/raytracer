#include "Ray.h"

//Constructs a zero ray
Ray::Ray()
{
	origin = MyPoint(0,0,0);
	direction = MyVector(0,0,0);
	direction.normalize();
}

//Constructs a ray from a point and a vector
Ray::Ray(MyPoint p, MyVector v)
{
	origin = p;
	direction = v;
	direction.normalize();
}

//Constructs a ray from two points, with the first as the origin
Ray::Ray(MyPoint p1, MyPoint p2)
{
	origin = p1;
	direction = genVector(p1, p2);
	direction.normalize();
}

//Computes and returns a point given a parameter t
MyPoint Ray::computePoint(double t)
{
	MyVector v = direction * t;
	MyPoint p = origin + v;
	return p;
}

MyPoint Ray::getP()
{	return origin;	}

MyVector Ray::getD()
{	return direction;	}
