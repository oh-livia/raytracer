#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>

#include <cmath>

//Hack: make the constructors with points in the point class
using namespace std;

class MyVector
{
	friend ostream& operator<<(ostream &output, const MyVector p);
	friend const double dotProduct(const MyVector v1, const MyVector v2);
	friend const MyVector crossProduct(const MyVector v1, const MyVector v2);
private:
	double pos[3];
	double magnitude;
public:
	MyVector ();// Constructs a vector (0, 0, 0)
	MyVector (float x_pos, float y_pos, float z_pos);// Constructor from three floats
	MyVector &operator=(const MyVector rhs);// Overloads =
	bool operator==(const MyVector rhs) const;// Overloads ==
	bool operator!=(const MyVector rhs) const;// Overloads !=
	MyVector & operator+=(const MyVector rhs);// Overloads +=
	MyVector & operator-=(const MyVector rhs);// Overloads -=
	const MyVector operator+(const MyVector other) const;	// Overloads +
	const MyVector operator-(const MyVector other) const;	// Overloads -
	const MyVector operator*(float scalar);	// Overloads * to multiply vector by scalar *
	const double operator[](int i) const;	// Overloads []
	void normalize();// Normalizes the vector
	double getMagnitude();// Return the magnitude of the vector
};

#endif
