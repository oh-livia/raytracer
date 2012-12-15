#include "BoundingBox.h"


BoundingBox::BoundingBox()
{
    xmin = 0;
    xmax = 0;
    ymin = 0;
    ymax = 0;
    zmin = 0;
    zmax = 0;
    txmin = 0;
    txmax = 0;
    tymin = 0;
    tymax = 0;
    tzmin = 0;
    tzmax = 0;
}

BoundingBox::BoundingBox(float minx, float miny, float minz, float maxx, float maxy, float maxz)
{
    xmin = minx;
    xmax = maxx;
    ymin = miny;
    ymax = maxy;
    zmin = minz;
    zmax = maxz;
    pushOut();
}

void BoundingBox::pushOut()
{
    xmax += 0.00001;
    ymax += 0.00001;
    zmax += 0.00001;
    xmin -= 0.00001;
    ymin -= 0.00001;
    zmin -= 0.00001;
}

bool BoundingBox::intersect(Ray &r)
{
    MyPoint eye = r.getP();
    MyVector direction = r.getD();
    
    float x = 1.0 / direction[0];
    float y = 1.0 / direction[1];
    float z = 1.0 / direction[2];

    txmin = x * (xmin - eye[0]);
    txmax = x * (xmax - eye[0]);

    tymin = y * (ymin - eye[1]);
    tymax = y * (ymax - eye[1]);

    tzmin = z * (zmin - eye[2]);
    tzmax = z * (zmax - eye[2]);

    float temp;
    if (txmin > txmax)
    {
        temp = txmax;
        txmax = txmin;
        txmin = temp;
    }
    if (tymin > tymax)
    {
        temp = tymax;
        tymax = tymin;
        tymin = temp;
    }
    if (tzmin > tzmax)
    {
        temp = tzmax;
        tzmax = tzmin;
        tzmin = temp;
    }
    
    if (txmin > tymin)
        bigmin = txmin;
    else {
        bigmin = tymin;
    }
    if (tzmin > bigmin)
        bigmin = tzmin;
    
    if (txmax < tymax)
        smallmax = txmax;
    else {
        smallmax = tymax;
    }
    if (tzmax < smallmax)
        smallmax = tzmax;
    
    if (bigmin > smallmax)
        return false;
     
    else
        return true;
}

float BoundingBox::mint()
{
    if (bigmin < smallmax && bigmin > 0)
        return bigmin;
    else {
        return smallmax;
    }
}

MyVector BoundingBox::normal()
{
    MyVector normal;
    if (bigmin < smallmax)
    {
        if (bigmin == txmin)
            normal = MyVector(-1, 0, 0);
        else if (bigmin == tymin)
            normal = MyVector(0, -1, 0);
        else if (bigmin == tzmin)
            normal = MyVector(0, 0, -1);
    }
    else
    {
        if (smallmax == txmax)
            normal = MyVector(1, 0, 0);
        else if (smallmax == tymax)
            normal = MyVector(0, 1, 0);
        else if (smallmax == tzmax)
            normal = MyVector(0, 0, 1);
    }
    
    return normal;
}





