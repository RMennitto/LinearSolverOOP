#include "Vector.h"
#include "Matrix.h"
#include "LinearSolver.h"
#include <cmath>
#include<iostream>

int main()
{
	Vector x(2);
	x.FreeVector();
	int N = 4;
	Matrix A(N,N);
	Vector b(N);
	A(0, 0) = 3.0; A(0, 1) = 0.0; A(0, 2) = 2.0; A(0, 3) = 4.0;
	A(1, 0) = 2.0; A(1, 1) = 0.0; A(1, 2) = -2.0; A(1, 3) = 7.0;
	A(2, 0) = 0.0; A(2, 1) = 1.0; A(2, 2) = 1.0; A(2, 3) = 3.0;
	A(3, 0) = 8.0; A(3, 1) = 1.0; A(3, 2) = 0.0; A(3, 3) = 2.0;

	
	for (int i = 0; i < N; i++)
	{
		b[i] = (double)rand() / 1000;
		for (int j = 0; j < N; j++)
		{
			if (j != N - 1)
			{
				std::cout << A(i, j) << "\t";
			}
			else
			{
				std::cout << A(i, j) << "\t \t" << b[i] << "\n";
			}
		}
	}
	std::cout << "\n \n";
	Matrix B(A);
	B = A + A;
	Vector c(N);
	c = A * b;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j != N - 1)
			{
				std::cout << B(i, j) << "\t";
			}
			else
			{
				std::cout << B(i, j) << "\t \t" << c[i] << "\n";
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		b[i] = (double)rand() / 1000;
		for (int j = 0; j < N; j++)
		{
			A(i,j) = (double)rand() / 1000;
		}
	}

	LinearSolver LS;

	LS.LinearSystem(A, b);

	Vector sol(N);

	sol = LS.Solver();

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (j != N - 1)
			{
				std::cout << A(i, j) << "\t";
			}
			else
			{
				std::cout << A(i, j) << "\t \t"<< b[i] << "\n";
			}
		}
	}
	std::cout << "\n \n \n";

	for (int i = 0; i < N; i++)
	{
		std::cout << sol[i] << "\n";
	}
	LS.FreeLinearSystem();
	A.FreeMatrix();
	b.FreeVector();
	return 0;
}