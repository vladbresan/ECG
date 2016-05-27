#include <stdio.h>
#include <iostream>
#include "mat4.h"
#include "mat3.h"
#include <math.h>.
#include <algorithm>
#include "vec4.h"

namespace egc {

	mat4& mat4::operator =(const mat4& srcMatrix) {
		for (int i = 0; i < 16; i++)
			matrixData[i] = srcMatrix.matrixData[i];
		return *this;
	};

	const float& mat4::at(int i, int j) const {
		return matrixData[j * 4 + i];
	};

	float& mat4::at(int i, int j) {
		return matrixData[j * 4 + i];
	};

	mat4 mat4::operator *(float scalarValue) const {
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				m.at(i,j) = this->at(i, j)*scalarValue;
		}
		return m;
	};
	mat4 mat4::operator *(const mat4& srcMatrix) const {
		mat4 m;
		int aux = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				aux = 0;
				for (int k = 0; k < 4; k++) {
					aux += this->at(i, k) * srcMatrix.at(k, j);
				}
				m.at(i, j) = aux;
			}
		}
		return m;
	};

	vec4 mat4::operator *(const vec4& srcVector) const {
		vec4 v;
		v.x = at(0, 0)*srcVector.x + srcVector.y*at(0, 1) + srcVector.z*at(0, 2) + srcVector.w*at(0, 3);
		v.y = at(1, 0)*srcVector.x + srcVector.y*at(1, 1) + srcVector.z*at(1, 2) + srcVector.w*at(1, 3);
		v.z = at(2, 0)*srcVector.x + srcVector.y*at(2, 1) + srcVector.z*at(2, 2) + srcVector.w*at(2, 3);
		v.w = at(3, 0)*srcVector.x + srcVector.y*at(3, 1) + srcVector.z*at(3, 2) + srcVector.w*at(3, 3);
		return v;
	};

	mat4 mat4::operator +(const mat4& srcMatrix) const {
		mat4 m;
		for (int i = 0; i < 16; i++) {
			m.matrixData[i] = matrixData[i] + srcMatrix.matrixData[i];
		}
		return m;
	};

	float mat4::determinant() const {
		return
			this->matrixData[12] * this->matrixData[9] * this->matrixData[6] * this->matrixData[3] - this->matrixData[8] * this->matrixData[13] * this->matrixData[6] * this->matrixData[3] -
			this->matrixData[12] * this->matrixData[5] * this->matrixData[10] * this->matrixData[3] + this->matrixData[4] * this->matrixData[13] * this->matrixData[10] * this->matrixData[3] +
			this->matrixData[8] * this->matrixData[5] * this->matrixData[14] * this->matrixData[3] - this->matrixData[4] * this->matrixData[9] * this->matrixData[14] * this->matrixData[3] -
			this->matrixData[12] * this->matrixData[9] * this->matrixData[2] * this->matrixData[7] + this->matrixData[8] * this->matrixData[13] * this->matrixData[2] * this->matrixData[7] +
			this->matrixData[12] * this->matrixData[1] * this->matrixData[10] * this->matrixData[7] - this->matrixData[0] * this->matrixData[13] * this->matrixData[10] * this->matrixData[7] -
			this->matrixData[8] * this->matrixData[1] * this->matrixData[14] * this->matrixData[7] + this->matrixData[0] * this->matrixData[9] * this->matrixData[14] * this->matrixData[7] +
			this->matrixData[12] * this->matrixData[5] * this->matrixData[2] * this->matrixData[11] - this->matrixData[4] * this->matrixData[13] * this->matrixData[2] * this->matrixData[11] -
			this->matrixData[12] * this->matrixData[1] * this->matrixData[6] * this->matrixData[11] + this->matrixData[0] * this->matrixData[13] * this->matrixData[6] * this->matrixData[11] +
			this->matrixData[4] * this->matrixData[1] * this->matrixData[14] * this->matrixData[11] - this->matrixData[0] * this->matrixData[5] * this->matrixData[14] * this->matrixData[11] -
			this->matrixData[8] * this->matrixData[5] * this->matrixData[2] * this->matrixData[15] + this->matrixData[4] * this->matrixData[9] * this->matrixData[2] * this->matrixData[15] +
			this->matrixData[8] * this->matrixData[1] * this->matrixData[6] * this->matrixData[15] - this->matrixData[0] * this->matrixData[9] * this->matrixData[6] * this->matrixData[15] -
			this->matrixData[4] * this->matrixData[1] * this->matrixData[10] * this->matrixData[15] + this->matrixData[0] * this->matrixData[5] * this->matrixData[10] * this->matrixData[15];
	};

	mat4 mat4::inverse() const {
		mat4 m;
		//float c = 1 / det;
		mat4 inv[16];
		float det;
		int i;

		/*inv[0] = m[5] * m[10] * m[15] -
			m[5] * m[11] * m[14] -
			m[9] * m[6] * m[15] +
			m[9] * m[7] * m[14] +
			m[13] * m[6] * m[11] -
			m[13] * m[7] * m[10];

		inv[4] = -m[4] * m[10] * m[15] +
			m[4] * m[11] * m[14] +
			m[8] * m[6] * m[15] -
			m[8] * m[7] * m[14] -
			m[12] * m[6] * m[11] +
			m[12] * m[7] * m[10];

		inv[8] = m[4] * m[9] * m[15] -
			m[4] * m[11] * m[13] -
			m[8] * m[5] * m[15] +
			m[8] * m[7] * m[13] +
			m[12] * m[5] * m[11] -
			m[12] * m[7] * m[9];

		inv[12] = -m[4] * m[9] * m[14] +
			m[4] * m[10] * m[13] +
			m[8] * m[5] * m[14] -
			m[8] * m[6] * m[13] -
			m[12] * m[5] * m[10] +
			m[12] * m[6] * m[9];

		inv[1] = -m[1] * m[10] * m[15] +
			m[1] * m[11] * m[14] +
			m[9] * m[2] * m[15] -
			m[9] * m[3] * m[14] -
			m[13] * m[2] * m[11] +
			m[13] * m[3] * m[10];

		inv[5] = m[0] * m[10] * m[15] -
			m[0] * m[11] * m[14] -
			m[8] * m[2] * m[15] +
			m[8] * m[3] * m[14] +
			m[12] * m[2] * m[11] -
			m[12] * m[3] * m[10];

		inv[9] = -m[0] * m[9] * m[15] +
			m[0] * m[11] * m[13] +
			m[8] * m[1] * m[15] -
			m[8] * m[3] * m[13] -
			m[12] * m[1] * m[11] +
			m[12] * m[3] * m[9];

		inv[13] = m[0] * m[9] * m[14] -
			m[0] * m[10] * m[13] -
			m[8] * m[1] * m[14] +
			m[8] * m[2] * m[13] +
			m[12] * m[1] * m[10] -
			m[12] * m[2] * m[9];

		inv[2] = m[1] * m[6] * m[15] -
			m[1] * m[7] * m[14] -
			m[5] * m[2] * m[15] +
			m[5] * m[3] * m[14] +
			m[13] * m[2] * m[7] -
			m[13] * m[3] * m[6];

		inv[6] = -m[0] * m[6] * m[15] +
			m[0] * m[7] * m[14] +
			m[4] * m[2] * m[15] -
			m[4] * m[3] * m[14] -
			m[12] * m[2] * m[7] +
			m[12] * m[3] * m[6];

		inv[10] = m[0] * m[5] * m[15] -
			m[0] * m[7] * m[13] -
			m[4] * m[1] * m[15] +
			m[4] * m[3] * m[13] +
			m[12] * m[1] * m[7] -
			m[12] * m[3] * m[5];

		inv[14] = -m[0] * m[5] * m[14] +
			m[0] * m[6] * m[13] +
			m[4] * m[1] * m[14] -
			m[4] * m[2] * m[13] -
			m[12] * m[1] * m[6] +
			m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] +
			m[1] * m[7] * m[10] +
			m[5] * m[2] * m[11] -
			m[5] * m[3] * m[10] -
			m[9] * m[2] * m[7] +
			m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] -
			m[0] * m[7] * m[10] -
			m[4] * m[2] * m[11] +
			m[4] * m[3] * m[10] +
			m[8] * m[2] * m[7] -
			m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] +
			m[0] * m[7] * m[9] +
			m[4] * m[1] * m[11] -
			m[4] * m[3] * m[9] -
			m[8] * m[1] * m[7] +
			m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] -
			m[0] * m[6] * m[9] -
			m[4] * m[1] * m[10] +
			m[4] * m[2] * m[9] +
			m[8] * m[1] * m[6] -
			m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0)
			return false;

		det = 1.0 / det;

		for (i = 0; i < 16; i++)
			invOut.matrixData[i] = inv[i] * det;
		  */
		return *this;
	};

	mat4 mat4::transpose() const {
		mat4 m;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m.at(j, i) = this->at(i, j);
			}
		}
		return m;
	};
}