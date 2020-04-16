#pragma once
#ifndef  NONLINEARHEADERDEF
#define NONLINEARHEADERDEF
#include "Vector.h"
#include "Matrix.h"
#include <string>

struct param {
	std::string method;
	int N;
};

class NonLinearSolver
{
private:
	int mSize; // number of equations to solve
	Vector* initial_guess;
	Vector (*p_function)(Vector& y);
	Matrix (*p_Jacobian)(Vector& y);
	std::string method;
public:
	NonLinearSolver(Vector(&myfunction)(Vector& y), Matrix(&myderivative)(Vector& y), int size);
	void SetInitialGuess(Vector& x0);
	virtual Vector Solver();
	void FreeSolver();
	Matrix Num_Jac(Vector(&myfunction)(Vector& y),Vector& x);
};

#endif



