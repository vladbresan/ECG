#include <stdio.h>
#include <iostream>
#include "mat3.h"
#include <math.h>.
#include <algorithm>
#include "vec3.h"

namespace egc {

	float& mat3::at(int i, int j) {
		return matrixData[j*3+i];
	};

	const float& mat3::at(int i, int j) const {
		return matrixData[j * 3 + i];
	};

	mat3& mat3::operator =(const mat3& srcMatrix) {
		for (int i = 0; i < 9; i++)
			 matrixData[i] = srcMatrix.matrixData[i] ;
		return *this;
	};

	mat3 mat3::operator *(float scalarValue) const {
		mat3 m ;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				m.at(i, j) =this->at(i,j)* scalarValue;
			//m.matrixData[i] =m.matrixData[i]* scalarValue; //this->matrixData*=scalarValue
		return m;
	};
	mat3 mat3::operator *(const mat3& srcMatrix) const {
		mat3 m;
		int aux=0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				aux = 0;
				for (int k = 0; k < 3; k++) {
					aux += this->at(i, k) * srcMatrix.at(k,j);
				}
				m.at(i, j) = aux;
			}
		}
		return m;
	};

	vec3 mat3::operator *(const vec3& srcVector) const {
		vec3 v;
		v.x =srcVector.x*this->at(0, 0) + srcVector.y*this->at(0, 1) + srcVector.z*this->at(0, 2);
		v.y = this->at(1, 0)*srcVector.x + srcVector.y*this->at(1, 1) + srcVector.z*this->at(1, 2);
		v.z = this->at(2, 0)*srcVector.x + srcVector.y*this->at(2, 1) + srcVector.z*this->at(2, 2);
		return v;
	};

	mat3 mat3::operator +(const mat3& srcMatrix) const {
		mat3 m;
		for (int i = 0; i < 9; i++) {
			m.matrixData[i] = matrixData[i] + srcMatrix.matrixData[i];
		}
		return m;
	};

	float mat3::determinant() const {
		return matrixData[0] * matrixData[4] * matrixData[8] + matrixData[1] * matrixData[5] * matrixData[6] + matrixData[3] * matrixData[7] * matrixData[2]
			-(matrixData[6] * matrixData[4] * matrixData[2] + matrixData[0] * matrixData[5] * matrixData[7] + matrixData[3] * matrixData[1] * matrixData[8]);
	};

	mat3 mat3::inverse() const {
		float det = this->determinant();
		float c = 1 / det;
		int sum = 0;
		mat3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = i + 1; j < 3; i++)
				for (int k = j; k < 3; i++)
					sum += ( this->at(j, k)* this->at(j, k) + this->at(j, k) * this->at(j, k))*pow(-1, j + k);
			m.matrixData[i] = sum;
		}
		return m;

	};
	mat3 mat3::transpose() const {
		mat3 m;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				m.at(j, i) = this->at(i, j);
			}
		}
		return m;
	};
}