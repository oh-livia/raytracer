#include "RGB.h"
#include <assert.h>

RGB::RGB()
{
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

RGB::RGB(float &red, float &green, float &blue)
{
    color[0] = red;
    color[1] = green;
    color[2] = blue;
}

const RGB RGB::operator+(const RGB other) const
{
    float r = color[0] + other[0];
    float g = color[1] + other[1];
    float b = color[2] + other[2];
    return RGB (r, g, b);
}

const RGB RGB::operator*(const RGB other) const
{
    float r = color[0] * other[0];
    float g = color[1] * other[1];
    float b = color[2] * other[2];
    return RGB (r, g, b);
}

const RGB RGB::operator*(const double amount) const
{
    float r = color[0] * amount;
    float g = color[1] * amount;
    float b = color[2] * amount;
    return RGB (r, g, b);
}

bool RGB::operator==(RGB other) const
{
    if (color[0] != other[0] || color[1] != other[1] || color[2] != other[2])
        return false;
    return true;
}

RGB & RGB::operator+=(const RGB rhs)
{
    color[0] += rhs[0];
    color[1] += rhs[1];
    color[2] += rhs[2];
    return *this;
}

RGB & RGB::operator=(RGB rhs)
{
    if (this == &rhs)
        return *this;
    
    color[0] = rhs[0];
    color[1] = rhs[1];
    color[2] = rhs[2];
    return *this;
}

float & RGB::operator[](const int i)
{
    assert (i >= 0 && i < 3);
    return color[i];
}

const float RGB::operator[](const int i) const
{
    assert (i >= 0 && i < 3);
    return color[i];
}

bool RGB::hasColor()
{
    if (color[0] != 0 || color[1] != 0 || color[2] != 0)
    {
        return true;
    }
    return false;
}

