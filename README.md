README for raytracer
Olivia Winn

    This is a raytracer that can render spheres, triangles, and planes, with blinn-phong shading, shadows, reflection, and soft lighting. It uses Monte Carlo bounding boxes as well, and those can be shown using command-line options. The object files follow a particular format - each line starts with a certain letter noting what kind of object the rest of the line is describing, and those objects are then described accordingly. There can also be special object mesh files, which describe a set of triangles with shared vertices that the object file can include, along with other objects to render.
    
    The format of the object files can be garnered from the example txt files given - each line has a letter at the beginning denoting what the object is that is about to be described - m for material, s for sphere, w for wavefile, etc. Some examples: s 0.5 0.6 0.7 8 : A sphere centered at (0.5, 0.6, 0.7) with radius 8 w paraboloid.obj : A triangle mesh file called parabolod.obj should be included in the scene


Triangle mesh files:
The vertices are listed first, each vertex line starts with a v then lists the 3D coordinates. Then the faces are listed, each line starting with an f, and the indices of the vertices that make each face are listed in counterclockwise order (from the perspective of looking at the face of the triangle in 3D). The indices of the vertices are counted by counting the first given vertex as index 1.

To compile:
type make

To run:
./raytra [a] [b] [c] [d] [e]

a - the name of the object txt file to render - test0.txt through test3.txt
b - the name of the image file that will be rendered, ex: test1.exr
c - the number of primary rays per pixel the renderer uses to compute the color
d - the number of shadow rays the renderer will use (should be at least the number of primary rays)
e - optional, put 1 to render the objects as their bounding boxes, leave out to render as originally intended

Files:
AmbLight.cc, AmbLight.h
    Class for handling ambient light
AreaLight.cc, AreaLight.h
    Class for handling an area light for soft shadows - defined by a point in the center then two vectors delineating how the rectangular light is oriented in space
BoundingBox.cc, BoundingBox.h
    Each object gets a bounding box that fits perfectly around the object to shorten computation time. When the option to see the bounding boxes is turned on, it is this that is rendered instead of the actual object
Camera.cc, Camera.h
    The "camera" that is positioned in 3D space and looks at all the objects. It sends out the rays through each pixel of the image to see what objects are visible and to determine what color each pixel should be.
DLight.cc, DLight.h
    Directional lights mimic light sources such as the sun, which are so far away that every object essentially sees light coming from the same direction
Intersection.cc, Intersection.h
    When a ray from the camera hits an object, the object stores the hit position here, along with any other useful information
Makefile
    For easy compilation
Material.cc, Material.h
    Defines the color properties of an object - it's diffuse color and specular properties, and whether the object is reflective
MyPoint.cc, MyPoint.h
    A 3D point that has the functionalities associated with a point in space. Can be added, multiplied by a scalar, and works in tandem with the MyVector class
MyVector.cc, MyVector.h
    3D vectors with the necessary functionalities; addition, subtraction, multiplication, and functions that involve points
PLight.cc, PLight.h
    A point light that exists at a particular point in space and radiates light equally in all directions. Mimics light sources such as a light bulb or other small and close object
Plane.cc, Plane.h
    A plane object that is defined by it's normal and distance from the origin
RGB.cc, RGB.h
    A helper class to make using colors much easier - holds the r, g, and b value of a color as floats
Ray.cc, Ray.h
    Class that defines a ray, which the camera uses extensively when rendering a scene
Sphere.cc, Sphere.h
    The sphere object is defined by its center and radius
Surface.h
    Abstract object class - gives the prototype for the basic funtions that all the objects would need, such as material description and intersection method
Triangle.cc, Triangle.h
    The triangle object class defines triangles by its three vertices and a normal, computed from the cross product of the vectors that can be made between the vertices
main.cc
    Instantiates all the objects, reads the object file, and starts up the camera
readscene.cc
    The method that parses the object file and saves the necessary information in the appropriate places
test0.txt - test3.txt
    Examples object files that can be rendered
