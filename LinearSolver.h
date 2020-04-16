#pragma once
#ifndef LINEARSOLVERHEADERDEF
#define LINEARSOLVERHEADERDEF

#include "Matrix.h"
#include "Vector.h"

class LinearSolver
{
private:
	Matrix* mat;
	Vector* vec;
public:
	virtual Vector Solver();
	void LinearSystem(Matrix& A, Vector& b);
	void FreeLinearSystem();
};

#endif // !LINEARSOLVERHEADERDEF



