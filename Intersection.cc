#include "Intersection.h"

Intersection::Intersection()
{
	t1 = 0, t2 = 0;
	int1 = MyPoint();
	int2 = MyPoint();
	normal1 = MyVector();
	normal2 = MyVector();
	multInt = false;
}

void Intersection::setT1(double t)
{	t1 = t;	}

void Intersection::setT2(double t)
{	t2 = t;	}

void Intersection::setInt1(MyPoint p)
{	int1 = p;	}

void Intersection::setInt2(MyPoint p)
{	int2 = p;	}

void Intersection::setNormal1(MyVector n)
{	normal1 = n;	}

void Intersection::setNormal2(MyVector n)
{	normal2 = n;	}

void Intersection::setMult(bool mult)
{	multInt = mult;	}

double Intersection::getT1()
{	return t1;  }

double Intersection::getT2()
{   return t2;   }

MyPoint Intersection::getInt1()
{	return int1;	}

MyPoint Intersection::getInt2()
{	return int2;	}

MyVector Intersection::getN1()
{	return normal1;	}

MyVector Intersection::getN2()
{	return normal2;	}

bool Intersection::getMult()
{	return multInt;	}
