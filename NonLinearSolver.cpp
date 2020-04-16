#include "NonLinearSolver.h"
#include "Matrix.h"
#include "Vector.h"
#include <cassert>
#include <iostream>
#include <string>

NonLinearSolver::NonLinearSolver(Vector(&myfunction)(Vector& y), Matrix(&myderivative)(Vector& y), int size)
{
	p_function = &myfunction;
	if (method.length() == 10)
	{
		p_Jacobian = &myderivative;
	}
	mSize = size;
}

void NonLinearSolver::SetInitialGuess(Vector& x0)
{
	initial_guess = new Vector(x0);
}

Vector NonLinearSolver::Solver()
{	
	Vector x_prev(mSize);
	Vector f(mSize);
	Matrix Jacobian(mSize, mSize);
	Matrix inv_Jac(mSize, mSize);
	Vector deltax(mSize);
	
	// First step
	x_prev = *initial_guess;
	f = -p_function(x_prev);
	if (method.length() == 10)
	{
		Jacobian = p_Jacobian(x_prev);
	}
	else
	{
		Jacobian = Num_Jac(*p_function,x_prev);
	}

	inv_Jac = Jacobian.Inverse();
	deltax = inv_Jac * f;

	// Newton's method
	int niter = 1;
	double norm = deltax.CalculateNorm();
	while ((deltax.CalculateNorm() > 1e-7) && niter < 1000)
	{
		deltax = inv_Jac * f;
		x_prev = x_prev + deltax;
		f = -p_function(x_prev);
		if (method.length() == 10)
		{
			Jacobian = p_Jacobian(x_prev);
		}
		else
		{
			Jacobian = Num_Jac(*p_function, x_prev);
		}
		inv_Jac = Jacobian.Inverse();

		niter++;
	}
	f.FreeVector();
	Jacobian.FreeMatrix();
	inv_Jac.FreeMatrix();
	deltax.FreeVector();

	return x_prev;
}

void NonLinearSolver::FreeSolver()
{
	initial_guess->FreeVector();
}

Matrix NonLinearSolver::Num_Jac(Vector(&myfunction)(Vector& y), Vector& x)
{
	Vector x_dx(mSize);
	Matrix NumJac(mSize, mSize);
	x_dx = x;
	for (int i = 0; i < mSize; i++)
	{
		for (int j = 0; j < mSize; j++)
		{
			x_dx[j] = 1.01 * x[j];
			NumJac(i, j) = (myfunction(x_dx)[i] -myfunction(x)[i]) / (0.01 * x[j]);
			x_dx[j] = x[j];
		}
	}
	x_dx.FreeVector();
	
	return NumJac;
}
