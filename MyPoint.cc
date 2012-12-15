#include "MyPoint.h"
#include <assert.h>

//Creates the origin
MyPoint::MyPoint()
{
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
}

//Creates a point from three floats
MyPoint::MyPoint(float x_pos, float y_pos, float z_pos)
{
	pos[0] = x_pos;
	pos[1] = y_pos;
	pos[2] = z_pos;
}

//Creates a point from the end of a vector
MyPoint::MyPoint(MyVector v)
{
	pos[0] = v[0];
	pos[1] = v[1];
	pos[2] = v[2];
}

//Assigns one point to another
MyPoint& MyPoint::operator=(MyPoint rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	pos[0] = rhs[0];
	pos[1] = rhs[1];
	pos[2] = rhs[2];
	return *this;
}

//Constructs a vector from a given point
MyVector genVector(MyPoint p)
{
	return MyVector(p[0], p[1], p[2]);
}

//Constructs a vector between the two points, pointing from the first to the second
MyVector genVector(MyPoint p1, MyPoint p2)
{
    if (p1 == p2)
        return MyVector(0, 0, 0);
    else
        return MyVector(p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2]);
}

//Checks if two points are equal (overloads == operator)
bool MyPoint::operator==(MyPoint other) const
{
	if (pos[0] == other[0] && pos[1] == other[1] && pos[2] == other[2])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Overloads * operator to multiply point by scalar
const MyPoint MyPoint::operator*(float scalar)
{
	float x = pos[0] * scalar;
	float y = pos[1] * scalar;
	float z = pos[2] * scalar;
	return MyPoint (x, y, z);
}

//Overloads [] so that calling MyPoint[0], [1], [2] gets the x, y, and z values respectively
float MyPoint::operator[](const int i)
{
    assert (i >= 0 && i < 3);
    return pos[i];
}

//Overloads << to print out a point in the format (#, #, #)
ostream& operator<<(ostream& output, MyPoint p)
{
	cout << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")";
	return output;
}

//Overloads + to add a vector to a point and get another vector
const MyPoint MyPoint::operator+(const MyVector other)
{
	MyPoint p (pos[0], pos[1], pos[2]);
	p.pos[0] += other[0];
	p.pos[1] += other[1];
	p.pos[2] += other[2];
	return p;
}






