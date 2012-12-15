#include "Material.h"

extern vector<PLight*> pLights;
extern vector<DLight*> dLights;
extern vector<Surface*> surfaces;
extern AmbLight ambient;

Material::Material()
{
    //Set to something bright and noticable so it's easier to tell when an object's material was not set
    for (int i = 0; i < 3; i++)
    {
        diffuse[i] = 1;
        specular[i] = 0.5;
        ideals[i] = 1;
    }
    phong = 50;
}

Material::Material(float &dr, float &dg, float &db, float &sr, float &sg, float &sb, int &r, float &ir, float &ig, float &ib)
{
    diffuse[0] = dr;
    diffuse[1] = dg;
    diffuse[2] = db;
    specular[0] = sr;
    specular[1] = sg;
    specular[2] = sb;
    phong = r;
    ideals[0] = ir; 
    ideals[1] = ig;
    ideals[2] = ib;
}

void Material::operator=(const Material &m)
{
    for (int i = 0; i < 3; i++)
    {
        diffuse[i] = m.diffuse[i];
        specular[i] = m.specular[i];
        ideals[i] = m.ideals[i];
    }
    phong = m.phong;
}

RGB Material::getAmbientShade()
{
    RGB ambientColor = diffuse * ambient.getColor();
    return ambientColor;
}

RGB Material::getDiffuse()
{
    return diffuse;
}

RGB Material::getSpecular()
{
    return specular;
}

RGB Material::getIdeals()
{
    return ideals;
}

int Material::getPhong()
{
    return phong;
}

