#include "Sphere.h"
#include <cmath>

extern bool bboxFlag;

Sphere::Sphere()
{
	o = MyPoint();
	r = 0.0;
    i = new Intersection();
    bbox = BoundingBox();
}

Sphere::Sphere(MyPoint origin, float radius, const int m)
{
	o = origin;
	r = radius;
    material = m;
    i = new Intersection();
    float xmin = o[0] - radius;
    float xmax = o[0] + radius;
    float ymin = o[1] - radius;
    float ymax = o[1] + radius;
    float zmin = o[2] - radius;
    float zmax = o[2] + radius;
    bbox = BoundingBox(xmin, ymin, zmin, xmax, ymax, zmax);
}

Sphere& Sphere::operator=(const Sphere rhs)
{
    if (o == rhs.o && r == rhs.r)
        return *this;
    else {
        o = rhs.o;
        r = rhs.r;
        material = rhs.material;
        return *this;
    }
}

//Sees if the ray intersects the sphere, and generates data about the intersection in the Intersection if it does
bool Sphere::intersect(Ray &ray)
{
    if (bbox.intersect(ray))
    {
        if (!bboxFlag)
        {
            double discr = computeDiscriminant(ray, o, r);
            if (discr < 0)
            {
                return false;
            }
            else
            {
                MyVector d = ray.getD();
                MyPoint p0 = ray.getP();
                MyVector p0_O = genVector(o, p0);
                double term = dotProduct((d * (-1)), p0_O);

                if (discr == 0)
                {
                    return false;
                }
                else
                {
                    //All values related to t1 in the intersection are set as the closest t useful to the camera
            
                    double discr_sqrt = (double) sqrt(discr);
                    i->setMult(true);
                    double t1 = term + discr_sqrt;
                    MyPoint ints1 = ray.computePoint(t1);
                    MyVector normal1 = genVector(o, ints1);
                    normal1.normalize();
                    double t2 = term - discr_sqrt;
                    MyPoint ints2 = ray.computePoint(t2);
                    MyVector normal2 = genVector(o, ints2);
                    normal2.normalize();
                    if (t1 < t2 && t1 > 0)
                    {
                        i->setT1(t1);
                        i->setT2(t2);
                        i->setInt1(ints1);
                        i->setInt2(ints2);
                        i->setNormal1(normal1);
                        i->setNormal2(normal2);
                    }
                    else {
                        i->setT1(t2);
                        i->setT2(t1);
                        i->setInt1(ints2);
                        i->setInt2(ints1);
                        i->setNormal1(normal2);
                        i->setNormal2(normal1);
                    }
                    return true;
                }
            }
        }
        else {
            float t = bbox.mint();
            i->setT1(t);
            i->setNormal1(bbox.normal());
            MyPoint intPoint = ray.computePoint(t);
            i->setInt1(intPoint);
            return true;
        }
    }
    else {
        return false;
    }
}

//Computes the determinant of the intersection fuction given a ray
double Sphere::computeDiscriminant(Ray ray, MyPoint origin, float r)
{
	MyVector d = ray.getD();
	MyPoint p0 = ray.getP();
	MyVector p0_O = genVector(origin, p0);
	double r_squared = r * r;
	double first_dot = dotProduct(d, p0_O);
	double second_dot = dotProduct(d, d);
	double third_dot = dotProduct(p0_O, p0_O);
	double first_term = (first_dot * first_dot);
	double second_term = (third_dot) - r_squared;
    double third_term = second_dot * second_term;
	double determ = first_term - third_term;
	return determ;
}

int Sphere::getMaterial()
{   return material;    }

float Sphere::getClosestT()
{
    if (!bboxFlag)
        return i->getT1();
    else {
        return bbox.mint();
    }
}

MyPoint Sphere::getClosestInt()
{   return i->getInt1();    }

/*
float Sphere::getFarthestT()
{   return i->getT2();  }
 */

MyVector Sphere::getClosestNormal()
{   return i->getN1();  }

/*
MyVector Sphere::getFarthestNormal()
{   return i->getN2();  }
 */
