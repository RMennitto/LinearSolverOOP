#include "Matrix.h"
#include <cassert>
#include <cmath>
#include <iostream>

Matrix::Matrix(int nRows, int nCols)
{
	mNumRows = nRows;
	mNumCols = nCols;
	mData = new double*[mNumRows];
	for (int i = 0; i < mNumRows; i++)
	{
		mData[i] = new double[mNumCols];
	}
}

Matrix::Matrix(Matrix& otherMatrix)
{
	mNumRows = otherMatrix.Number_of_Rows();
	mNumCols = otherMatrix.Number_of_Cols();
	mData = new double* [mNumRows];
	for (int i = 0; i < mNumRows; i++)
	{
		mData[i] = new double[mNumCols];
	}
	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			mData[i][j] = otherMatrix(i,j);
		}
	}
}

void Matrix::FreeMatrix()
{
	for (int i = 0; i < mNumRows; i++)
	{
		delete mData[i];
	}
}

int Matrix::Number_of_Rows()
{
	return mNumRows;
}

int Matrix::Number_of_Cols()
{
	return mNumCols;
}

double Matrix::Determinant()
{
	assert(mNumRows == mNumCols);
	double det = 0.0;
	if (mNumRows == 1)
	{
		det = mData[0][0];
	}
	else
	{
		for (int i_outer = 0; i_outer < mNumRows; i_outer++)
		{
			Matrix sub_mat(mNumRows - 1, mNumRows - 1);
			for (int i = 0; i < mNumRows-1; i++)
			{
				for (int j = 0; j < i_outer; j++)
				{
					sub_mat(i, j) = mData[i + 1][j];
				}
				for (int j = i_outer; j < mNumRows - 1; j++)
				{
					sub_mat(i, j) = mData[i + 1][j + 1];
				}
			}
			double sub_mat_det = sub_mat.Determinant();
			det += pow(-1.0, i_outer) * mData[0][i_outer] * sub_mat_det;
		}

	}

	return det;
}

Matrix Matrix::Adjoint()
{
	Matrix Adj(mNumRows, mNumRows);

	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			Adj(i, j) = Adj_coeff(i, j);
		}
	}

	return Adj;
}

double Matrix::Adj_coeff(int idx1, int idx2)
{
	Matrix cof(mNumRows-1, mNumCols-1);

	int i = 0, j = 0;
	for (int row = 0; row < mNumRows; row++)
	{
		for (int col = 0; col < mNumCols; col++)
		{
			if ((row != idx1) && (col != idx2))
			{
				cof(i, j) = mData[row][col];
				if (j < mNumRows - 2)
				{
					j++;
				}
				else
				{
					j = 0;
					i++;
				}
			}
		}
	}

	return pow(-1.0, idx1 + idx2) * cof.Determinant();
}

Matrix Matrix::Inverse()
{
	Matrix inv(mNumRows, mNumRows);

	for (int row = 0; row < mNumRows; row++)
	{
		for (int col = 0; col < mNumCols; col++)
		{
			inv(row, col) = mData[row][col];
		}
	}
	double det = inv.Determinant();
	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			inv(i, j) = Adj_coeff(j,i) / det;
		}
	}

	return inv;
}

Matrix& Matrix::operator=(const Matrix& otherMatrix)
{
	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			mData[i][j] = otherMatrix.mData[i][j];
		}
	}

	return *this;
}

Matrix Matrix::operator+(Matrix& otherMatrix) const
{
	int r = otherMatrix.Number_of_Rows();
	int c = otherMatrix.Number_of_Cols();
	Matrix mat(r,c);
	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			mat.mData[i][j] = mData[i][j] + otherMatrix(i,j);
		}
	}

	return mat;
}

Matrix Matrix::operator-(Matrix& otherMatrix) const
{
	int r = otherMatrix.Number_of_Rows();
	int c = otherMatrix.Number_of_Cols();
	Matrix mat(r, c);
	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			mat(i,j) = mData[i][j] - otherMatrix(i,j);
		}
	}

	return mat;
}

Matrix Matrix::operator-()
{
	Matrix mat(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			mat(i,j) = -mData[i][j];
		}
	}

	return mat;
}

Matrix Matrix::operator*(double n)
{
	Matrix mat(mNumRows, mNumCols);
	for (int i = 0; i < mNumRows; i++)
	{
		for (int j = 0; j < mNumCols; j++)
		{
			mat(i,j) = n * mData[i][j];
		}
	}

	return mat;
}

double& Matrix::operator()(int i, int j)
{
	return mData[i][j];
}

Vector operator*(Matrix& mat, Vector& vec)
{
	int r = mat.Number_of_Rows();
	int c = mat.Number_of_Cols();
	int s = vec.GetSize();
	assert(c == s);
	Vector v(s);
	for (int i = 0; i < r; i++)
	{
		v[i] = 0;
		for (int j = 0; j < c; j++)
		{
			v[i] += vec[j] * mat(i,j);
		}
	}

	return v;
}

Vector operator*( Vector& vec, Matrix& mat)
{
	int r = mat.Number_of_Rows();
	int c = mat.Number_of_Cols();
	int s = vec.GetSize();
	assert(r == s);
	Vector v(s);
	for (int j = 0; j < c; j++)
	{
		v[j] = 0;
		for (int i = 0; i < r; i++)
		{
			v[j] += vec[i] * mat(i,j);
		}
	}

	return v;
}
