#include "Plane.h"

Plane::Plane()
{
    normal = MyVector();
    d = 0;
    i = new Intersection();
    i->setNormal1(normal);
    material = 0;
}

Plane::Plane(MyVector &n, float &distance, int &m)
{
    normal = n;
    normal.normalize();
    d = distance;
    material = m;
    i = new Intersection();
    i->setNormal1(normal);
}

bool Plane::intersect(Ray &r)
{
    Ray ray = r;
    float denom = dotProduct(ray.getD(), normal);
    if (denom == 0)
    {
        return false;
    }
    else
    {
        MyVector p0 = genVector(ray.getP());
        double p0dot = dotProduct(p0, normal);
        double numer = p0dot + d;
        double t = (numer * (-1))/ denom;
        if (t < 0)
            return false;
        else {
            i->setT1(t);
            MyPoint p = ray.computePoint(t);
            i->setInt1(p);
            return true;
        }
    }
}
float Plane::getClosestT()
{   return i->getT1();  }

MyPoint Plane::getClosestInt()
{   return i->getInt1();    }

int Plane::getMaterial()
{   return material;    }

MyVector Plane::getClosestNormal()
{   return i->getN1();  }
