#include <stdio.h>
#include <iostream>
#include "vec4.h"
#include <math.h>

namespace egc {

	vec4 vec4::operator +(const vec4& srcVector) const {

		return vec4(x + srcVector.x, y + srcVector.y, z + srcVector.z,w+srcVector.w);
	}

	vec4& vec4::operator =(const vec4 &srcVector) {
		x = srcVector.x;
		y = srcVector.y;
		z = srcVector.z;
		w = srcVector.w;
		return *this;
	};

	vec4& vec4::operator +=(const vec4& srcVector) {
		x = x + srcVector.x;
		y = y + srcVector.y;
		z = z + srcVector.z;
		w = w + srcVector.w;
		return *this;
	};

	vec4 vec4::operator *(float scalarValue) const {
		return vec4(x * scalarValue, y*scalarValue, z*scalarValue,w*scalarValue);
	};

	vec4 vec4::operator -(const vec4& srcVector) const {
		return vec4(x - srcVector.x, y - srcVector.y, z - srcVector.z,w-srcVector.w);
	};

	vec4& vec4::operator -=(const vec4& srcVector) {
		x = x - srcVector.x;
		y = y - srcVector.y;
		z = z - srcVector.z;
		w = w - srcVector.w;
		return *this;

	};

	vec4& vec4::operator -() {
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	};

	float vec4::length() const {
		//(int)x = x*x;
		return sqrt(x*x + y*y + z*z+w*w);

	};

	vec4& vec4::normalize() {
		float leng = length();
		x = x / leng;
		y = y / leng;
		z = z / leng;
		w = w / leng;
		return *this;
	};


}