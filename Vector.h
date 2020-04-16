#pragma once
#ifndef VECTORHEADERDEF
#define VECTORHEADERDEF
class Vector
{
private:
	double* mData; // data stored in vector
	int mSize; // size of vector
public:
	// Constructors
	Vector(int size);
	Vector(Vector& otherVector);
	// Deconstructor
	void FreeVector();
	
	// Overloading methods
	double& operator[](int i);
	Vector& operator=(const Vector& otherVector); // Overload "=" to allow vector equality
	Vector operator+() const;               // Overload "+" to allow Vector = + OtherVector
	Vector operator+(const Vector& v1) const;     // Overload "+" to allow v1 + v2;
	Vector operator-() const;				// Overload "-" to allow Vector = - OtherVector
	Vector operator-(const Vector& v1);     // Overload "+" to allow v1 - v2;
	Vector operator*(double a);             // Overload "*" to allow (Scalar x Vector)

	// Other methods
	int GetSize();
	double CalculateNorm(int p = 2);     
	double ScalarProduct(Vector& otherVector);
};

#endif
