#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "MyPoint.h"
#include "MyVector.h"

class Intersection
{
private:
	double t1, t2;
	MyPoint int1;
	MyPoint int2;
	MyVector normal1;
	MyVector normal2;
	bool multInt;
public:	Intersection();
	void setT1(double t);
	void setT2(double t);
	void setInt1(MyPoint p);
	void setInt2(MyPoint p);
	void setNormal1(MyVector n);
	void setNormal2(MyVector n);
	void setMult(bool mult);
	double getT1();
	double getT2();
	MyPoint getInt1();
	MyPoint getInt2();
	MyVector getN1();
	MyVector getN2();
	bool getMult();
};

#endif
	
