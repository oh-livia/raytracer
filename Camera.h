#ifndef CAMERA_H
#define CAMERA_H

#include "MyVector.h"
#include "MyPoint.h"
#include "Ray.h"
#include "Intersection.h"
#include "Surface.h"
#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <vector>
#include "RGB.h"

using namespace Imf;
using namespace Imath;

class Camera
{
private:
	MyPoint eye;
    
	float d;
    
	MyVector u;
	MyVector v;
	MyVector w;
    
	int nx;
	int ny;
    
	float l, r, t, b;
    
    void shuffle();
    
public:
	Camera ();
	Camera (MyPoint position, MyVector direction, float focallength, const float iw, const float ih, const int pw, const int ph);
	Ray generateRay(const float i, const float j);
	void render();
	void writeRgba(const char fileName[]);
	void setEye(MyPoint eye);
	void setDirection(MyVector direction);
	void setDistance(float d);
	void setImage(float iw, float ih);
	void setPixels(float pw, float ph);
    bool checkShadow(MyPoint &intersect, MyVector &lightDirection, MyPoint &lightPosition);
    RGB lightRay(Ray &ray, int recurse_limit, int p, int q);
};

#endif