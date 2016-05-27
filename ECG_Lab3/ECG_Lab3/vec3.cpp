#include <stdio.h>
#include <iostream>
#include "vec3.h"
#include <math.h>

namespace egc {

	vec3 vec3::operator +(const vec3& srcVector) const {

		return vec3(x + srcVector.x, y + srcVector.y,z+srcVector.z);
	}

	vec3& vec3::operator =(const vec3 &srcVector) {
		x = srcVector.x;
		y = srcVector.y;
		z = srcVector.z;
		return *this;
	};

	vec3& vec3::operator +=(const vec3& srcVector) {
		x = x + srcVector.x;
		y = y + srcVector.y;
		z = z + srcVector.z;
		return *this;
	};

	vec3 vec3::operator *(float scalarValue) const {
		return vec3(x * scalarValue, y*scalarValue, z*scalarValue);
	};

	vec3 vec3::operator -(const vec3& srcVector) const {
		return vec3(x - srcVector.x, y - srcVector.y,z-srcVector.z);
	};

	vec3& vec3::operator -=(const vec3& srcVector) {
		x = x - srcVector.x;
		y = y - srcVector.y;
		z = z - srcVector.z;
		return *this;

	};

	vec3& vec3::operator -() {
		x = -x;
		y = -y;
		z = -z;
		return *this;
	};

	float vec3::length() const {
		//(int)x = x*x;
		return sqrt(x*x + y*y+z*z);

	};

	vec3& vec3::normalize() {
		float leng = length();
		x = x / leng;
		y = y / leng;
		z = z / leng;
		return *this;
	};


}