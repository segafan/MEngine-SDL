#ifndef MATRIX4_H
#define MATRIX4_H

#include "Math.h"

class Matrix4
{
public:
	Matrix4()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				values[i][j] = 0;
			}
		}
	}

	Matrix4 InitIndentity()
	{
		values[0][0] = 1;		values[0][1] = 0;		values[0][2] = 0;		values[0][3] = 0;
		values[1][0] = 0;		values[1][1] = 1;		values[1][2] = 0;		values[1][3] = 0;
		values[2][0] = 0;		values[2][1] = 0;		values[2][2] = 1;		values[2][3] = 0;
		values[3][0] = 0;		values[3][1] = 0;		values[3][2] = 0;		values[3][3] = 1;

		Matrix4 matrix = *(this);
		return matrix;
	}

	Matrix4 Mul(Matrix4 matrix)
	{
		Matrix4 newMatrix;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				newMatrix.SetAt(i, j, values[i][0] * matrix.GetAt(0, j) +
									  values[i][1] * matrix.GetAt(1, j) +
									  values[i][2] * matrix.GetAt(2, j) +
									  values[i][3] * matrix.GetAt(3, j));
			}
		}

		return newMatrix;
	}

	float GetAt(int x,int y)
	{
		return values[x][y];
	}
	void SetAt(int x,int y,float value)
	{
		this->values[x][y] = value;
	}

	void SetAll(float value)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				values[i][j] = value;
			}
		}
	}

private:
	float values[4][4];
};

#endif