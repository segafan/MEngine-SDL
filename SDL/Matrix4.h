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

	Matrix4 InitScaleTransform(float scaleX, float scaleY, float scaleZ)
	{
		values[0][0] = scaleX; values[0][1] = 0.0f;   values[0][2] = 0.0f;   values[0][3] = 0.0f;
		values[1][0] = 0.0f;   values[1][1] = scaleY; values[1][2] = 0.0f;   values[1][3] = 0.0f;
		values[2][0] = 0.0f;   values[2][1] = 0.0f;   values[2][2] = scaleZ; values[2][3] = 0.0f;
		values[3][0] = 0.0f;   values[3][1] = 0.0f;   values[3][2] = 0.0f;   values[3][3] = 1.0f;

		Matrix4 matrix = *(this);
		return matrix;
	}

	Matrix4 InitRotateTransform(float rotateX, float rotateY, float rotateZ)
	{
		Matrix4 rx, ry, rz;

		const float x = ToRadian(rotateX);
		const float y = ToRadian(rotateY);
		const float z = ToRadian(rotateZ);

		rx.values[0][0] = 1.0f;    rx.values[0][1] = 0.0f;     rx.values[0][2] = 0.0f;     rx.values[0][3] = 0.0f;
		rx.values[1][0] = 0.0f;    rx.values[1][1] = cosf(x);  rx.values[1][2] = -sinf(x); rx.values[1][3] = 0.0f;
		rx.values[2][0] = 0.0f;    rx.values[2][1] = sinf(x);  rx.values[2][2] = cosf(x);  rx.values[2][3] = 0.0f;
		rx.values[3][0] = 0.0f;    rx.values[3][1] = 0.0f;     rx.values[3][2] = 0.0f;     rx.values[3][3] = 1.0f;

		ry.values[0][0] = cosf(y); ry.values[0][1] = 0.0f;     ry.values[0][2] = -sinf(y); ry.values[0][3] = 0.0f;
		ry.values[1][0] = 0.0f;	   ry.values[1][1] = 1.0f;     ry.values[1][2] = 0.0f;	   ry.values[1][3] = 0.0f;
		ry.values[2][0] = sinf(y); ry.values[2][1] = 0.0f;     ry.values[2][2] = cosf(y);  ry.values[2][3] = 0.0f;
		ry.values[3][0] = 0.0f;    ry.values[3][1] = 0.0f;     ry.values[3][2] = 0.0f;     ry.values[3][3] = 1.0f;

		rz.values[0][0] = cosf(z); rz.values[0][1] = -sinf(z); rz.values[0][2] = 0.0f;     rz.values[0][3] = 0.0f;
		rz.values[1][0] = sinf(z); rz.values[1][1] = cosf(z);  rz.values[1][2] = 0.0f;     rz.values[1][3] = 0.0f;
		rz.values[2][0] = 0.0f;	   rz.values[2][1] = 0.0f;     rz.values[2][2] = 1.0f;     rz.values[2][3] = 0.0f;
		rz.values[3][0] = 0.0f;    rz.values[3][1] = 0.0f;     rz.values[3][2] = 0.0f;     rz.values[3][3] = 1.0f;

		*this = rz * ry * rx;

		Matrix4 matrix = *(this);
		return matrix;
	}

	Matrix4 InitTranslationTransform(float x, float y, float z)
	{
		values[0][0] = 1.0f; values[0][1] = 0.0f; values[0][2] = 0.0f; values[0][3] = x;
		values[1][0] = 0.0f; values[1][1] = 1.0f; values[1][2] = 0.0f; values[1][3] = y;
		values[2][0] = 0.0f; values[2][1] = 0.0f; values[2][2] = 1.0f; values[2][3] = z;
		values[3][0] = 0.0f; values[3][1] = 0.0f; values[3][2] = 0.0f; values[3][3] = 1.0f;
	}


	Matrix4 InitCameraTransform(const Vector3& target, const Vector3& up)
	{
		Vector3 n = target;
		n.Normalize();

		Vector3 u = up;
		u.Normalize();
		u = u.Cross(n);

		Vector3 v = n.Cross(u);

		values[0][0] = u.x;   values[0][1] = u.y;   values[0][2] = u.z;   values[0][3] = 0.0f;
		values[1][0] = v.x;   values[1][1] = v.y;   values[1][2] = v.z;   values[1][3] = 0.0f;
		values[2][0] = n.x;   values[2][1] = n.y;   values[2][2] = n.z;   values[2][3] = 0.0f;
		values[3][0] = 0.0f;  values[3][1] = 0.0f;  values[3][2] = 0.0f;  values[3][3] = 1.0f;

		Matrix4 matrix = *(this);
		return matrix;
	}

	Matrix4 InitPersProjTransform(float fov, float width, float height, float zNear, float zFar)
	{
		const float ar = width / height;
		const float zRange = zNear - zFar;
		const float tanHalfFOV = tanf(ToRadian(fov / 2.0f));

		values[0][0] = 1.0f / (tanHalfFOV * ar); values[0][1] = 0.0f;              values[0][2] = 0.0f;                     values[0][3] = 0.0;
		values[1][0] = 0.0f;                     values[1][1] = 1.0f / tanHalfFOV; values[1][2] = 0.0f;                     values[1][3] = 0.0;
		values[2][0] = 0.0f;                     values[2][1] = 0.0f;              values[2][2] = (-zNear - zFar) / zRange; values[2][3] = 2.0f*zFar*zNear / zRange;
		values[3][0] = 0.0f;                     values[3][1] = 0.0f;              values[3][2] = 1.0f;                     values[3][3] = 0.0;

		Matrix4 matrix = *(this);
		return matrix;
	}

	Matrix4 operator* (Matrix4 matrix)
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