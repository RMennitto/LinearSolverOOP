#pragma once
#ifndef MATRIXHEADERDEF
#define MATRIXHEADERDEF
#include "Vector.h"

class Matrix
{
private:
	int mNumRows;
	int mNumCols;
	double** mData;

public:
	// Constructor
	Matrix(int nRows, int nCols);
	Matrix(Matrix& otherMatrix);
	// Deconstructor
	void FreeMatrix();

	// Methods
	int Number_of_Rows();
	int Number_of_Cols();
	double Determinant();
	Matrix Adjoint();
	double Adj_coeff(int idx1, int idx2);
	Matrix Inverse();

	// Overload operators
	Matrix& operator=(const Matrix& otherMatrix);
	Matrix operator+(Matrix& otherMatrix) const;
	Matrix operator-(Matrix& otherMatrix) const;
	Matrix operator-();
	Matrix operator*(double n);
	double& operator()(int i,int j);
	friend Vector operator*(Matrix& mat, Vector& vec);
	friend Vector operator*(Vector& vec, Matrix& mat);
};
#endif

