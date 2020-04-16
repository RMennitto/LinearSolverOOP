#include "LinearSolver.h"
#include <cassert>
#include <cmath>

Vector LinearSolver::Solver()
{
	double mSize = mat->Number_of_Rows();
	Vector m(mSize);
	Vector solution(mSize);

	Matrix& rA = *mat;
	Vector& rb = *vec;

	for (int k = 0; k < mSize; k++)
	{
		double max = 0.0;
		int row = -1;
		for (int i = k; i < mSize; i++)
		{
			if (fabs(rA(i, k)) > max)
			{
				row = i;
				max = fabs(rA(i, k));
			}
		}
		assert(row >= 0);

		if (row != k)
		{
			for (int i = 0; i < mSize; i++)
			{
				double temp = rA(k, i);
				rA(k, i) = rA(row, i);
				rA(row, i) = temp;
			}
			double temp = rb[k];
			rb[k] = rb[row];
			rb[row] = temp;
		}
		for (int i = k + 1; i < mSize; i++)
		{
			m[i] = rA(i, k) / rA(k, k);
			for (int j = k; j < mSize; j++)
			{
				rA(i, j) -= rA(k, j) * m[i];
			}
			rb[i] -= rb[k] * m[i];
		}
	}

	for (int i = mSize - 1; i > -1; i--)
	{
		solution[i] = rb[i];
		for (int j = i + 1; j < mSize; j++)
		{
			solution[i] -= rA(i, j) * solution[j];
		}
		solution[i] /= rA(i, i);
	}
	return solution;
}

void LinearSolver::LinearSystem(Matrix& A, Vector& b)
{
	mat = new Matrix(A);
	vec = new Vector(b);
	assert(A.Number_of_Cols() == b.GetSize());
}

void LinearSolver::FreeLinearSystem()
{
	delete mat;
	delete vec;

}