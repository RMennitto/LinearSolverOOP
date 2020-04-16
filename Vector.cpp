#include "Vector.h"
#include <cassert>
#include <cmath>

Vector::Vector(int size)
{
	assert(size > 0);
	mSize = size;
	mData = new double[mSize];
	for (int i = 0; i < mSize; i++)
	{
		mData[i] = 0.0;
	}
}

Vector::Vector(Vector& otherVector)
{
	mSize = otherVector.GetSize();
	mData = new double[mSize];
	for (int i = 0; i < mSize; i++)
	{
		mData[i] = otherVector.mData[i];
	}
}

void Vector::FreeVector()
{
	delete[] mData;
}

int Vector::GetSize()
{
	return mSize;
}

double& Vector::operator[](int i)
{
	return mData[i];
}

Vector& Vector::operator=(const Vector& otherVector)
{
	for (int i = 0; i < mSize; i++)
	{
		mData[i] = otherVector.mData[i];
	}
	return *this;
}

Vector Vector::operator+()const
{
	Vector v(mSize);
	for (int i = 0; i < mSize; i++)
	{
		v[i] = +mData[i];
	}
	return v;
}

Vector Vector::operator+(const Vector& v1) const
{
	Vector v(mSize);
	for (int i = 0; i < mSize; i++)
	{
		v[i] = +mData[i] + v1.mData[i];
	}
	return v;
}

Vector Vector::operator-()const
{
	Vector v(mSize);
	for (int i = 0; i < mSize; i++)
	{
		v[i] = -mData[i];
	}
	return v;
}

Vector Vector::operator-(const Vector& v1)
{
	Vector v(mSize);
	for (int i = 0; i < mSize; i++)
	{
		v[i] = +mData[i] - v1.mData[i];
	}
	return v;
}

Vector Vector::operator*(double a)
{
	Vector v(mSize);
	for (int i = 0; i < mSize; i++)
	{
		v[i] = a * mData[i];
	}
	return v;
}

double Vector::CalculateNorm(int p)
{
	double norm, sum = 0.0;
	for (int i = 0; i < mSize; i++)
	{
		sum += pow(fabs(mData[i]), p);
	}
	norm = pow(sum, 1.0 / ((double)(p)));
	return norm;
}

double Vector::ScalarProduct(Vector& otherVector)
{
	double scal_prod = 0.0;
	for (int i = 0; i < mSize; i++)
	{
		scal_prod +=mData[i] * otherVector.mData[i];
	}
	return scal_prod;
}

