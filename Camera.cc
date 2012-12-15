#include "Camera.h"
#include <iostream>
#include <typeinfo>
#include "Sphere.h"
#include "Material.h"
#include "AmbLight.h"
#include "AreaLight.h"
#include <cstdlib>
#include "RGB.h"

extern vector<Surface*> surfaces;
extern Array2D<Rgba> pixels;
extern vector<Material*> materials;
extern vector<PLight*> pLights;
extern AmbLight ambient;
extern AreaLight areaLight;

extern int primaryRays;
extern int secondaryRays;

extern bool bboxFlag;

using namespace std;

int RECURSE_LIMIT = 4;
vector<int> stratifyer;
int materialInt = 0;

bool specialCase1 = false;
bool specialCase2 = false;
bool specialCase3 = false;

Camera::Camera()
{
	eye = MyPoint(0, 0, 0);
	d = 0;
	u = MyVector(0, 0, 0);
	v = MyVector(0, 0, 0);
	w = MyVector(0, 0, 0);
	nx = 0;
	ny = 0;
	l = 0, r = 0, t = 0, b = 0;
}

Camera::Camera(MyPoint position, MyVector direction, const float focallength, const float iw, const float ih, const int pw, const int ph)
{
	eye = position;
	d = focallength;
	MyVector bigD = direction;
	bigD.normalize();
	w = bigD * (-1);
	u = crossProduct(bigD, MyVector (0, 1, 0));
	u.normalize();
	v = crossProduct(u, bigD);
	v.normalize();
	nx = pw;
	ny = ph;
	r = iw / 2;
	l = -r;
	t = ih / 2;
	b = -t;

}

//Generates a ray per pixel
Ray Camera::generateRay(const float i, const float j)
{ 
	const float rayu = l + ((r - l)*(i - 0.5))/nx;
	const float rayv = t + ((b - t)*(j - 0.5))/ny;
    MyVector dir = (w * (-d)) + (u * rayu) + (v * rayv);
	dir.normalize();
	Ray ray (eye, dir);
	return ray;
}

//Renders the image
void Camera::render()
{
    if (primaryRays == 1)
        specialCase1 = true;
    else if (primaryRays != 1 && secondaryRays == 1)
    {
        specialCase2 = true;
        for (int i = 0; i < (primaryRays * primaryRays); i++)
        {
            stratifyer.push_back(i);
        }
    }
    else
        specialCase3 = true;
    
    pixels.resizeErase(ny, nx);
    for (int j = 0; j < ny; j++)
    //int j = 168;
    {
        for (int i = 0; i < nx; i++)
        //int i = 231;
        {
            Rgba &px = pixels[j][i];
            RGB color = RGB();
            
            if (specialCase2)
                shuffle();

            for (int p = 0; p < primaryRays; p++)
            {
                for (int q = 0; q < primaryRays; q++)
                {
                    Ray ray;
                    if (specialCase1)
                        ray = generateRay(i, j);
                    else
                    {
                        float iRand = ((float) rand()) / RAND_MAX;
                        float jRand = ((float) rand()) / RAND_MAX;
                        ray = generateRay(i + (p + iRand)/primaryRays, j + (q + jRand)/primaryRays);
                    }
                    color = color + lightRay(ray, RECURSE_LIMIT, p, q);
                }
            }
            px.r = (color[0] / (primaryRays * primaryRays));
            px.g = (color[1] / (primaryRays * primaryRays));
            px.b = (color[2] / (primaryRays * primaryRays));
            px.a = 1;
        }
    }
}

void Camera::shuffle()
{
    for (int i = 0; i < (int) stratifyer.size(); i++)
    {
        int oldPos = rand() * stratifyer.size()/RAND_MAX;
        int newPos = rand() * stratifyer.size()/RAND_MAX;
        int temp = stratifyer[oldPos];
        stratifyer[oldPos] = stratifyer[newPos];
        stratifyer[newPos] = temp;
    }
}

bool Camera::checkShadow(MyPoint &intersect, MyVector &lightDirection, MyPoint &lightPosition)
{
    MyPoint lightP = lightPosition;
    double lightDistance = genVector(intersect, lightP).getMagnitude();
    MyPoint start = intersect + (lightDirection * 0.001); //Add a little distance so it doesn't intersect itself
    Ray shadow (start, lightDirection);
    for (int s = 0; s < (int) surfaces.size(); s++)
    {
    Surface * object = (Surface*) surfaces.at(s);
    bool intersects = object->intersect(shadow);
        if (intersects)
        {
            double t = object->getClosestT();
            Ray intersectRay (intersect, lightP);
            double tDistance = genVector(intersect, intersectRay.computePoint(t)).getMagnitude();
            if (t > 0 && tDistance < lightDistance)
            {
                return false;
            }
        }
    }
    return true;
}

RGB Camera::lightRay(Ray &ray, int recurse_limit, int p, int q)
{
    if (recurse_limit == 0)
        return RGB();
    
    int size = (int) surfaces.size();
    RGB pixelColor = RGB();
    double bestT = INFINITY;
    MyVector normal;
    Surface * closest = NULL;
    Material color;
    
    for (int s = 0; s < size; s++)
    {
        Surface * object = (Surface*) surfaces.at(s);
        bool intersects = object->intersect(ray);
        if (intersects)
        {
            double t = object->getClosestT();
            if (t > 0 && t < bestT)
            {
                closest = object;
                bestT = t;
                color = *materials[object->getMaterial()];
                normal = object->getClosestNormal();
            }
        }
    }
    
    if (closest == NULL)
    {
        materialInt = 0;
        return RGB();
    }
    if (dotProduct(ray.getD(), normal) > 0)
        normal = normal * (-1);
    for (int i = 0; i < (int) pLights.size(); i++)
    {
        Ray view = ray;
        MyPoint intersect = closest->getClosestInt();
        PLight thisLight = *(pLights[i]);
        MyPoint lightP = thisLight.getPosition();
        MyVector lightD = genVector(intersect, lightP);
        lightD.normalize();
        
        bool lit = checkShadow(intersect, lightD, lightP);
        if (lit)
        {
            RGB lightIntensity = thisLight.getIntensity();
            RGB diffuseColor = color.getDiffuse();
            double angle = dotProduct(lightD, normal);
            
            if (angle > 0)
            {
                pixelColor += diffuseColor * lightIntensity * angle;
                
                MyVector v = view.getD() * (-1);
                v.normalize();
                MyVector half = v + lightD;
                half.normalize();
                angle = dotProduct(normal, half);
                double phong = color.getPhong();
                double specAngle = pow(angle, phong);
                RGB specularAmount = color.getSpecular();
                pixelColor += specularAmount * lightIntensity * specAngle;
                
                double lightDistance = genVector(intersect, lightP).getMagnitude();
                pixelColor = pixelColor * (1 / (lightDistance * lightDistance));
            }
            else {
                pixelColor += color.getAmbientShade() * 0.25;
            }
        }
        else {
            pixelColor += color.getAmbientShade() * 0.25;
        }
    }
    
    if (areaLight.hasColor())
    {
        RGB arealightColor = RGB();
        if (specialCase2)
        {
            areaLight.sample(primaryRays);
            int segment = stratifyer[p + q];
            MyPoint lightP = areaLight.getSample(segment);
            MyPoint intersect = closest->getClosestInt();
            MyVector lightD = genVector(intersect, lightP);
            lightD.normalize();
            
            bool lit = checkShadow(intersect, lightD, lightP);
            if (lit)
            {
                RGB lightIntensity = areaLight.getColor();
                RGB diffuseColor = color.getDiffuse();
                double angle = dotProduct(lightD, normal);
                
                if (angle > 0)
                {
                    arealightColor += diffuseColor * lightIntensity * angle;
                    MyVector v = ray.getD() * (-1);
                    v.normalize();
                    MyVector half = v + lightD;
                    half.normalize();
                    angle = dotProduct(normal, half);
                    double phong = color.getPhong();
                    double specAngle = pow(angle, phong);
                    RGB specularAmount = color.getSpecular();
                    arealightColor += specularAmount * lightIntensity * specAngle;
                    
                    double lightDistance = genVector(intersect, lightP).getMagnitude();
                    arealightColor = arealightColor * (1 / (lightDistance * lightDistance)) * dotProduct((lightD * -1), areaLight.getNormal());
                    }
                else
                    arealightColor += color.getAmbientShade() * 0.25;
            }
            else
                arealightColor += color.getAmbientShade() * 0.25;

        }
        else
        {
            areaLight.sample(secondaryRays);            
            for (int r = 0; r < secondaryRays; r++)
            {
                for (int s = 0; s < secondaryRays; s++)
                {
                    MyPoint lightP = areaLight.getSample(r * s);
                    MyPoint intersect = closest->getClosestInt();
                    MyVector lightD = genVector(intersect, lightP);
                    lightD.normalize();
                
                    bool lit = checkShadow(intersect, lightD, lightP);
                    if (lit)
                    {
                        RGB lightIntensity = areaLight.getColor();
                        RGB diffuseColor = color.getDiffuse();
                        double angle = dotProduct(lightD, normal);
                    
                        if (angle > 0)
                        {
                            arealightColor += diffuseColor * lightIntensity * angle;
                            MyVector v = ray.getD() * (-1);
                            v.normalize();
                            MyVector half = v + lightD;
                            half.normalize();
                            angle = dotProduct(normal, half);
                            double phong = color.getPhong();
                            double specAngle = pow(angle, phong);
                            RGB specularAmount = color.getSpecular();
                            arealightColor += specularAmount * lightIntensity * specAngle;
                        }
                        else
                            arealightColor += color.getAmbientShade() * 0.25;
                    }
                    else
                        arealightColor += color.getAmbientShade() * 0.25;
                }
            }
            
            for (int i = 0; i < 3; i++)
            {
                arealightColor[i] = arealightColor[i] / (secondaryRays * secondaryRays);
            }
        }

        pixelColor += arealightColor;
    }

    RGB idealComponent = color.getIdeals();
    if (!idealComponent.hasColor())
    {
        pixelColor += color.getAmbientShade() * 0.25;
        return pixelColor;
    }
    else
    {
        pixelColor += color.getAmbientShade() * 0.25;
        MyVector direction = ray.getD();
        direction.normalize();
        double product = dotProduct(direction, normal);
        MyVector reflectiveD = direction + (normal * (product * (-2)));
        reflectiveD.normalize();
        MyPoint intersection = ray.computePoint(bestT);
        MyPoint reflectiveP = intersection + (reflectiveD * 0.001);
        Ray reflectiveRay (reflectiveP, reflectiveD);
        RGB reflectiveColor = lightRay(reflectiveRay, recurse_limit-1, 0, 0);
        return (pixelColor + (idealComponent * reflectiveColor));
        //return pixelColor;
    }
}

void Camera::writeRgba(const char fileName[])
{
	Box2i displayWindow (V2i (0, 0), V2i (nx-1, ny-1));
	Box2i dataWindow = displayWindow;
	RgbaOutputFile file (fileName, displayWindow, dataWindow, WRITE_RGBA);
	file.setFrameBuffer (&pixels[0][0], 1, nx);
	file.writePixels (dataWindow.max.y - dataWindow.min.y + 1);
    
}

void Camera::setEye(MyPoint theeye)
{
	eye = theeye;
}
void Camera::setDirection(MyVector thedirection)
{
	MyVector bigD = thedirection;
	bigD.normalize();
	w = (bigD * -1);
    if (bigD != MyVector(0, 1, 0) || bigD != MyVector(0, -1, 0))
    {
        u = crossProduct(bigD, MyVector(0, 1, 0));
        u.normalize();
        v = crossProduct(u, bigD);
        v.normalize();
    }
    else {
        u = crossProduct(bigD, MyVector(0, 0, 1));
        u.normalize();
        v = crossProduct(u, bigD);
        v.normalize();
    }
}
void Camera::setDistance(float thed)
{
	d = thed;
}
void Camera::setImage(float theiw, float theih)
{
	r = theiw / 2;
	l = -r;
	t = theih / 2;
	b = -t;
}
void Camera::setPixels(float thepw, float theph)
{
	nx = (int) thepw;
	ny = (int) theph;
}