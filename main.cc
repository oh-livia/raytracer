#include "MyPoint.h"
#include "MyVector.h"
#include "Sphere.h"
#include "Surface.h"
#include "Intersection.h"
#include "Ray.h"
#include "Camera.h"
#include "PLight.h"
#include "DLight.h"
#include <iostream>
#include <cstdlib>
using namespace std;


float getTokenAsFloat (string inString, int whichToken);
void read_wavefront_file (const char *file, std::vector< int > &tris, std::vector< float > &verts);
void parseSceneFile (char *filnam);

int primaryRays = 3;
int secondaryRays = 1;

vector<Surface*> surfaces;
vector<Material*> materials;
vector<DLight*> dLights;
vector<PLight*> pLights;

extern Camera camera;
Array2D<Rgba> pixels(0, 0);

bool bboxFlag = false;

int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        primaryRays = atoi(argv[3]);
        secondaryRays = atoi(argv[4]);
    }
    if (argc == 6)
        bboxFlag = true;
	parseSceneFile(argv[1]);
	camera.render();
	camera.writeRgba(argv[2]);
    return 0;
}
