#ifndef Material_h
#define Material_h

#include "Ray.h"
#include "MyVector.h"
#include "Surface.h"
#include "PLight.h"
#include "DLight.h"
#include "AmbLight.h"
#include "RGB.h"
#include <vector>

class Material
{
private:
    RGB diffuse;
    RGB specular;
    RGB ideals;
    int phong;
    RGB sceneColor;
public:
    Material();
    Material(float &dr, float &dg, float &db, float &sr, float &sg, float &sb, int &r, float &ir, float &ig, float &ib);
    void operator=(const Material &m);
    RGB getAmbientShade();
    RGB getDiffuse();
    RGB getSpecular();
    RGB getIdeals();
    int getPhong();
};

#endif
