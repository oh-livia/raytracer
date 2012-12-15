#include "Triangle.h"

extern bool bboxFlag;

Triangle::Triangle()
{
    p1 = MyPoint();
    p2 = MyPoint();
    p3 = MyPoint();
    normal = MyVector();
    intersection = new Intersection();
    material = 0;
}

Triangle::Triangle(MyPoint &pfirst, MyPoint &psecond, MyPoint &pthird, int m)
{
    p1 = pfirst;
    p2 = psecond;
    p3 = pthird;
    MyVector v1 = genVector(p1, p2);
    MyVector v2 = genVector(p1, p3);
    normal = crossProduct(v1, v2);
    normal.normalize();
    intersection = new Intersection();
    intersection->setNormal1(normal);
    material = m;
    
    float xmin, xmax, ymin, ymax, zmin, zmax;
    
    if (p1[0] > p2[0]) {
        xmax = p1[0];
        xmin = p2[0];
    }
    else {
        xmax = p2[0];
        xmin = p1[0];
    }
    if (p3[0] > xmax)
        xmax = p3[0];
    else if (p3[0] < xmin)
        xmin = p3[0];
    
    if (p1[1] > p2[1]) {
        ymax = p1[1];
        ymin = p2[1];
    }
    else {
        ymax = p2[1];
        ymin = p1[1];
    }
    if (p3[1] > ymax)
        ymax = p3[1];
    else if (p3[1] < ymin)
        ymin = p3[1];
    
    if (p1[2] > p2[2]) {
        zmax = p1[2];
        zmin = p2[2];
    }
    else {
        zmax = p2[2];
        zmin = p1[2];
    }
    if (p3[2] > zmax)
        zmax = p3[2];
    else if (p3[2] < zmin)
        zmin = p3[2];
    
    bbox = BoundingBox(xmin, ymin, zmin, xmax, ymax, zmax);
}

bool Triangle::intersect(Ray &r)
{
    if (bbox.intersect(r))
    {
        if (!bboxFlag)
        {
            MyVector rayVector = r.getD();
            MyPoint rayPoint = r.getP();
    
            double a = p1[0] - p2[0];
            double b = p1[1] - p2[1];
            double c = p1[2] - p2[2];
            double d = p1[0] - p3[0];
            double e = p1[1] - p3[1];
            double f = p1[2] - p3[2];
            double g = rayVector[0];
            double h = rayVector[1];
            double i = rayVector[2];
            double j = p1[0] - rayPoint[0];
            double k = p1[1] - rayPoint[1];
            double l = p1[2] - rayPoint[2];
    
            double ei_hf = (e * i) - (h * f);
            double gf_di = (g * f) - (d * i);
            double dh_eg = (d * h) - (e * g);
            double ak_jb = (a * k) - (j * b);
            double jc_al = (j * c) - (a * l);
            double bl_kc = (b * l) - (k * c);
    
            double m = (a * ei_hf) + (b * gf_di) + (c * dh_eg);
            double t = ((-1) * ((f * ak_jb) + (e * jc_al) + (d * bl_kc))) / m;
    
            if (t <= 0)
                return false;

            double alpha = ((i * ak_jb) + (h * jc_al) + (g * bl_kc)) / m;
            if (alpha < 0 || alpha > 1)
                return false;

            double beta = ((j * ei_hf) + (k * gf_di) + (l * dh_eg)) / m;
            if (beta < 0 || beta > (1 - alpha))
                return false;
            intersection->setT1(t);
            MyPoint intPoint = r.computePoint(t);
            intersection->setInt1(intPoint);
            return true;
        }
        else {
            float t = bbox.mint();
            intersection->setT1(t);
            intersection->setNormal1(bbox.normal());
            MyPoint intPoint = r.computePoint(t);
            intersection->setInt1(intPoint);
            return true;
        }
    }
    else {
        return false;
    }
}

float Triangle::getClosestT()
{
    if (!bboxFlag)
        return intersection->getT1();
    else {
        return bbox.mint();
    }
}

MyPoint Triangle::getClosestInt()
{   return intersection->getInt1(); }

int Triangle::getMaterial()
{   return material;    }

MyVector Triangle::getClosestNormal()
{   return intersection->getN1();   }



