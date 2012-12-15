#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "Surface.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Camera.h"
#include "PLight.h"
#include "AmbLight.h"
#include "AreaLight.h"
#include "DLight.h"

extern vector<Surface*> surfaces;
extern vector<Material*> materials;
extern vector<PLight*> pLights;
extern vector<DLight*> dLights;
AmbLight ambient = AmbLight(0.005, 0.005, 0.005);
AreaLight areaLight;

Camera camera(MyPoint (0, 0, 0), MyVector (0, 0, 0), 0, 0, 0, 0, 0);

vector<int> triangles;
vector<float> vertices;

using namespace std;

//#define IM_DEBUGGING

// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float getTokenAsFloat (string inString, int whichToken)
{
    
    float thisFloatVal = 0.;    // the return value
    
    if (whichToken == 0) {
        cerr << "error: the first token on a line is a character!" << endl;
        exit (-1);
    }
    
    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char [inString.size () + 1];
    
    strcpy (cstr, inString.c_str());
    
    char *p = strtok (cstr, " ");
    if (p == 0) {
        cerr << "error: the line has nothing on it!" << endl;
        exit (-1);
    }
    
    for (int i = 0; i < whichToken; i++) {
        p = strtok (0, " ");
        if (p == 0) {
            cerr << "error: the line is not long enough for your token request!" << endl;
            exit (-1);
        }
    }
    
    thisFloatVal = atof (p);
    
    delete[] cstr;
    
    return thisFloatVal;
}


// Given the name of a wavefront (OBJ) file that consists JUST of
// vertices, triangles, and comments, read it into the tris and verts
// vectors.
//
// tris is a vector of ints that is 3*n long, where n is the number of
// triangles. The ith triangle has vertex indexes 3*i, 3*i+1, and 3*i+2.
//
// The ith triangle has vertices verts[3*i], verts[3*i+1], and verts[3*i+2],
// given in counterclockwise order with respect to the surface normal
//
void read_wavefront_file (const char *file, std::vector< int > &tris, std::vector< float > &verts)
{
    
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        } 
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
            
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
        } 
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        } 
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
    }
    
    in.close();
    
    //   std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " << verts.size () / 3.0 << std::endl;
}

//
// read the scene file.
//
// You'll need a few globals (or add arguments to this function): for the
// list of surfaces (geometric objects like spheres, triangles, planes) and
// another for the lights. These can be of type std::vector. You'll also
// need a global (or other parameter) for the camera.
//
// This should be pretty self-explanatory: it reads through the lines, and
// using the first character figures out what kind of command it is. It
// then calls the "getTokenAsFloat" routine to pull out the needed values.
// NOTE: since different commands take different number of arguments, you
// must take care not to call getTokenAsFloat for an index that is beyond the
// end of the line!
//
// One tricky bit: when a material is read in, we want
// to keep a pointer to it so that for the next geometric object read in ,
// we can add that material to the object. In the code that follows, I use the
// variable "lastSurfaceLoaded" to do that, but the code is commented out since
// I don't know the class names you will be using.
//
// Very minimal error check here. You might improve it slightly, but we'll
// only use "correct" scene files.
//
//

void parseSceneFile (char *filnam)
{

    ifstream inFile(filnam);    // open the file
    string line;
    
    if (! inFile.is_open ()) {  // if it's not open, error out.
        cerr << "can't open scene file" << endl;
        exit (-1);
    }
    
    Material *lastMaterialFound = new Material();
    materials.push_back(lastMaterialFound);
    int materialNum = 0;
    
    
    // Note: you'll have to keep track of whatever the last material
    // you loaded in was, so you can apply it to any geometry that gets loaded. 
    // So here, you'll have something like:
    //
    // myMaterialClass *lastMaterialLoaded = 0;  // 0 or maybe a default material?
    //
    // and each time you load in a new piece of geometry (sphere, triangle, plane)
    // you will set its material to lastMaterialLoaded.

    
    while (! inFile.eof ()) {   // go through every line in the file until finished
        
        getline (inFile, line); // get the line
        
        //Set up parameter to save material for use in all objects after, before the next material
        
        switch (line[0])  {     // we'll decide which command based on the first character
            
            //
            // geometry types:
            //
            // NOTE: whichever type of geo you load in, set its material to
            // be "lastMaterialLoaded"
            //
            case 's':
			{
                // it's a sphere, load in the parameters
                
                float sx, sy, sz, r;
                sx = getTokenAsFloat (line, 1); 
                sy = getTokenAsFloat (line, 2); 
                sz = getTokenAsFloat (line, 3); 
                r = getTokenAsFloat (line, 4);

                MyPoint sorigin (sx, sy, sz);
                Sphere* aSphere  = new Sphere(sorigin, r, materialNum);
                surfaces.push_back (aSphere);

                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                // mySphereClass *ms = new mySphereClass (x, y, z, r);   // make a new instance of your sphere class
                // ms->setMaterial (lastMaterialLoaded)
                // objectsList->push_back (ms);  // objectsList is a global std:vector<surface *> for example.
                
#ifdef IM_DEBUGGING
                // if we're debugging, show what we got:
                cout << "got a sphere with ";
                cout << "parameters: " << sx << " " << sy << " " << sz << " " << r << endl;
#endif
                break;
			}
                
            case 't':   // triangle
            {
                float x1, y1, z1, x2, y2, z2, x3, y3, z3;
                x1 = getTokenAsFloat (line, 1);
                y1 = getTokenAsFloat (line, 2);
                z1 = getTokenAsFloat (line, 3);
                x2 = getTokenAsFloat (line, 4);
                y2 = getTokenAsFloat (line, 5);
                z2 = getTokenAsFloat (line, 6);
                x3 = getTokenAsFloat (line, 7);
                y3 = getTokenAsFloat (line, 8);
                z3 = getTokenAsFloat (line, 9);
                
                MyPoint p1 (x1, y1, z1);
                MyPoint p2 (x2, y2, z2);
                MyPoint p3 (x3, y3, z3);
                Triangle* aTriangle = new Triangle(p1, p2, p3, materialNum);
                surfaces.push_back(aTriangle);
                
                break;
            }
                
            case 'p':   // plane
            {
                float n1, n2, n3, d;
                n1 = getTokenAsFloat (line, 1);
                n2 = getTokenAsFloat (line, 2);
                n3 = getTokenAsFloat (line, 3);
                d = getTokenAsFloat (line, 4);
                
                MyVector normal (n1, n2, n3);
                Plane* aPlane = new Plane(normal, d, materialNum);
                surfaces.push_back(aPlane);
                break;
            }
                
            case 'w':
            {
                char fileName[100];
                snprintf(fileName, 99, "%s", &line[2]);
                read_wavefront_file (fileName, triangles, vertices);

                for (int i = 0; i < (int) triangles.size(); i+=3)
                {
                    int j = triangles[i];
                    MyPoint v1 (vertices[3*j], vertices[(3*j)+1], vertices[(3*j)+2]);
                    j = triangles[i+1];
                    MyPoint v2 (vertices[3*j], vertices[(3*j)+1], vertices[(3*j)+2]);
                    j = triangles[i+2];
                    MyPoint v3 (vertices[3*j], vertices[(3*j)+1], vertices[(3*j)+2]);
                    
                    Triangle * meshTriangle = new Triangle(v1, v2, v3, materialNum);
                    surfaces.push_back(meshTriangle);
                }
                
                break;
            }
            //
            // camera:
            //
            case 'c':   // camera
			{
				float cx, cy, cz, vx, vy, vz, d, iw, ih;
				int pw, ph;

				cx = getTokenAsFloat (line, 1); 
				cy = getTokenAsFloat (line, 2); 
				cz = getTokenAsFloat (line, 3); 
				vx = getTokenAsFloat (line, 4);
				vy = getTokenAsFloat (line, 5); 
				vz = getTokenAsFloat (line, 6); 
				d = getTokenAsFloat (line, 7); 
				iw = getTokenAsFloat (line, 8);
				ih = getTokenAsFloat (line, 9);
				pw = getTokenAsFloat (line, 10);
				ph = getTokenAsFloat (line, 11);

				MyPoint eye (cx, cy, cz);
                MyVector direction (vx, vy, vz);
				camera.setEye(eye);
				camera.setDirection(direction);
				camera.setDistance(d);
				camera.setImage(iw, ih);
				camera.setPixels(pw, ph);

		    	break;
			}
                
            //
            // lights:
            //
            case 'l':   // light
                
                // slightly different from the rest, we need to examine the second param,
                // which is at the third position on the line:
                switch (line[2]) {
                    case 'p':   // point light
                    {
                        float pr, pg, pb, cr, cg, cb;
                        pr = getTokenAsFloat(line, 2);
                        pg = getTokenAsFloat(line, 3);
                        pb = getTokenAsFloat(line, 4);
                        cr = getTokenAsFloat(line, 5);
                        cg = getTokenAsFloat(line, 6);
                        cb = getTokenAsFloat(line, 7);
                        
                        MyPoint position(pr, pg, pb);
                        PLight *aPLight = new PLight(position, cr, cg, cb);
                        pLights.push_back(aPLight);
                        
                        break;
                    }
                    case 'd':   // directional light
                    {
                        float vx, vy, vz, r, g, b;
                        vx = getTokenAsFloat(line, 2);
                        vy = getTokenAsFloat(line, 3);
                        vz = getTokenAsFloat(line, 4);
                        r = getTokenAsFloat(line, 5);
                        g = getTokenAsFloat(line, 6);
                        b = getTokenAsFloat(line, 7);
                        
                        MyVector direction (vx, vy, vz);
                        DLight * aDlight = new DLight(direction, r, g, b);
                        dLights.push_back(aDlight);
                        
                        break;
                    }
                    case 'a':   // ambient light
                    {
                        float r, g, b;
                        r = getTokenAsFloat(line, 2);
                        g = getTokenAsFloat(line, 3);
                        b = getTokenAsFloat(line, 4);
                        ambient.setColor(r, g, b);
                        break;
                    }
                        
                    case 's':
                    {
                        float x, y, z, dx, dy, dz, ux, uy, uz, len, r, g, b;
                        x = getTokenAsFloat(line, 2);
                        y = getTokenAsFloat(line, 3);
                        z = getTokenAsFloat(line, 4);
                        dx = getTokenAsFloat(line, 5);
                        dy = getTokenAsFloat(line, 6);
                        dz = getTokenAsFloat(line, 7);
                        ux = getTokenAsFloat(line, 8);
                        uy = getTokenAsFloat(line, 9);
                        uz = getTokenAsFloat(line, 10);
                        len = getTokenAsFloat(line, 11);
                        r = getTokenAsFloat(line, 12);
                        g = getTokenAsFloat(line, 13);
                        b = getTokenAsFloat(line, 14);
                        
                        MyPoint center (x, y, z);
                        MyVector normal (dx, dy, dz);
                        MyVector u_direction (ux, uy, uz);
                        RGB color (r, g, b);
                        
                        cout << "Center: " << center << endl;
                        cout << "Normal: " << normal << endl;
                        cout << "Udirection: " << u_direction << endl;
                        
                        areaLight = AreaLight(center, normal, u_direction, len, color);
                        
                        break;
                    }
                        
                }
                
                break;
            
            //
            // materials:
            //
            case 'm':   // material
                // the trick here: we should keep a pointer to the last material we read in,
                // so we can apply it to any subsequent geometry. Say it's called "lastMaterialLoaded"
                // we migh then do something like this:
                //
                //  1. read in the 10 material parameters: dr, dg, db, sr, sg, sb, r, ir, ig, ib
                //  2. call lastMaterialLoaded->setMaterial(dr, dg, db,...);
                //
            {
                
                float dr, dg, db, sr, sg, sb, ir, ig, ib;
                int r;
                
                dr = getTokenAsFloat (line, 1); 
				dg = getTokenAsFloat (line, 2); 
				db = getTokenAsFloat (line, 3); 
				sr = getTokenAsFloat (line, 4);
				sg = getTokenAsFloat (line, 5); 
				sb = getTokenAsFloat (line, 6); 
				r = getTokenAsFloat (line, 7); 
				ir = getTokenAsFloat (line, 8);
				ig = getTokenAsFloat (line, 9);
				ib = getTokenAsFloat (line, 10);
                
                Material *material = new Material(dr, dg, db, sr, sg, sb, r, ir, ig, ib);
                materials.push_back(material);
                materialNum++;
                break;
            }
            
            case '/':
                // don't do anything, it's a comment
                break;
                

            //
            // options
            //
            case 'o':   // make your own options if you wish
            {
                //                float materialNum, 
                break;
            }
        }
        
    }
}



//
// the main just makes sure that there is an argument passed, which is
// supposed to be the scenefile.
//

/*
int main (int argc, char *argv[])
{
  
    if (argc != 2) {
        cerr << "useage: raytra scenefilename" << endl;
        return -1;
    }
    
    parseSceneFile (argv[1]);

	camera.render(surfaces);
	
    
    return 0;
}
*/
