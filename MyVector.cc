#include "MyVector.h"
#include <assert.h>

//Constructs the origin vector
MyVector::MyVector()
{
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	magnitude = 0.0;
}

//Constructs a vector from three floats
MyVector::MyVector(float x_pos, float y_pos, float z_pos)
{
	pos[0] = (double) x_pos;
	pos[1] = (double) y_pos;
	pos[2] = (double) z_pos;
	magnitude = getMagnitude();
}

//Assigns one vector to another
MyVector& MyVector::operator=(const MyVector rhs)
{
	if (this == &rhs)
		return *this;
	
	pos[0] = rhs[0];
	pos[1] = rhs[1];
	pos[2] = rhs[2];
	magnitude = rhs.magnitude;
	return *this;
}

//Checks if two vectors are equal (overloads == operator)
bool MyVector::operator==(const MyVector other) const
{
	if (pos[0] == other[0] && pos[1] == other[1] && pos[2] == other[2])
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Checks if two vectors are not equal (overloads != operator)
bool MyVector::operator!=(const MyVector other) const
{
	return !(*this == other);
}

//Overloads += operator
MyVector & MyVector::operator+=(const MyVector rhs)
{
	pos[0] += rhs[0];
	pos[1] += rhs[1];
	pos[2] += rhs[2];
	magnitude = getMagnitude();
	return *this;
}

//Overloads -= operator
MyVector & MyVector::operator-=(const MyVector rhs)
{
	pos[0] -= rhs[0];
	pos[1] -= rhs[1];
	pos[2] -= rhs[2];
	magnitude = getMagnitude();
	return *this;
}

//Adds two vectors together (overloads + operator)
const MyVector MyVector::operator+(const MyVector other) const
{
	MyVector v (pos[0], pos[1], pos[2]);
	return v += other;
}	

//Subtracts one vector from another (overloads - operator)
const MyVector MyVector::operator-(const MyVector other) const
{
	MyVector v (pos[0], pos[1], pos[2]);
	return v -= other;
}

//Overloads * operator to multiply vector by scalar
const MyVector MyVector::operator*(float scalar)
{
	double x = pos[0] * scalar;
	double y = pos[1] * scalar;
	double z = pos[2] * scalar;
	return MyVector (x, y, z);
}

//Overloads [] so that calling MyVector[0], [1], [2] gets the x, y, and z values respectively
const double MyVector::operator[](int i) const
{
    assert (i >= 0 && i < 3);
	return pos[i];
}

//Overloads << to print out a vector in the format [#, #, #]
ostream& operator<<(ostream& output, const MyVector v)
{
	cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]";
	return output;
}

//Normalizes the vector
void MyVector::normalize()
{
    magnitude = getMagnitude();
	if (magnitude != 0)
	{
		double x = pos[0] / magnitude;
		double y = pos[1] / magnitude;
		double z = pos[2] / magnitude;
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
		magnitude = getMagnitude();
	}
}

//Computes the dot product of two vectors
const double dotProduct(const MyVector v1, const MyVector v2)
{
    double v1x = v1[0];
    double v1y = v1[1];
    double v1z = v1[2];
    double v2x = v2[0];
    double v2y = v2[1];
    double v2z = v2[2];
	double x = v1x * v2x;
	double y = v1y * v2y;
	double z = v1z * v2z;
	double dot = x + y + z;
	return dot;
}

//Computes the cross product of two vectors
const MyVector crossProduct(const MyVector v1, const MyVector v2)
{
	double x = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	double y = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	double z = (v1[0] * v2[1]) - (v1[1] * v2[0]);
	return MyVector (x, y, z);
}

//Computes and returns the magnitude of the vector
double MyVector::getMagnitude()
{
	double squares = (pos[0] * pos[0]) + (pos[1] * pos[1]) + (pos[2] * pos[2]);
	double mag = sqrt(squares);
	return mag;
}
