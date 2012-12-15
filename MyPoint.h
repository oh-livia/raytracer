#ifndef MYPOINT_H
#define MYPOINT_H

#include "MyVector.h"

#include <iostream>
using namespace std;

class MyPoint
{
	friend ostream& operator<<(ostream& output, const MyPoint p);
	friend MyVector genVector (MyPoint p);	// Creates a vector from a point
	friend MyVector genVector (MyPoint p1, MyPoint p2); // Creates a vector from two points
private:
	float pos[3];
public:
	MyPoint (); // Constructs the origin
	MyPoint (float x, float y, float z);// Constructor
	MyPoint (MyVector v);// Constructs point at tip of vector
	MyPoint &operator=(MyPoint rhs);// Overloads =
	bool operator==(MyPoint other) const;// Overloads ==
	const MyPoint operator*(float scalar);// Overloads *
	float operator[](const int i);// Overloads []
	const MyPoint operator+(const MyVector other);	// Overloads +
};

#endif
