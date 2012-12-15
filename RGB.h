#ifndef RGB_h
#define RGB_h

class RGB
{
private:
    float color[3];
public:
    RGB();
    RGB(float &red, float &green, float &blue);
    float & operator[](const int i);
    const float operator[](const int i) const;
    bool operator==(RGB other) const;
    RGB & operator=(RGB rhs);
	const RGB operator+(const RGB other) const;
	const RGB operator*(const RGB other) const;
	const RGB operator*(const double amount) const;
    RGB & operator+=(const RGB rhs);
    bool hasColor();
};

#endif
