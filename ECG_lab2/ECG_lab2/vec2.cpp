#include <stdio.h>
#include <iostream>
#include "vec2.h"
#include <math.h>

namespace egc {

	vec2 vec2::operator +(const vec2& srcVector) const {

		return vec2(x + srcVector.x, y + srcVector.y);
	}
	
	vec2& vec2::operator =(const vec2 &srcVector) {
		x = srcVector.x;
		y = srcVector.y;
		return *this;
	};

	vec2& vec2::operator +=(const vec2& srcVector) {
		x = x + srcVector.x;
		y = y + srcVector.y;
		return *this;
	};

	vec2 vec2::operator *(float scalarValue) const {
		return vec2(x * scalarValue, y*scalarValue);
	};

	vec2 vec2::operator -(const vec2& srcVector) const {
		return vec2(x - srcVector.x, y - srcVector.y);
	};

	vec2& vec2::operator -=(const vec2& srcVector) {
		x = x - srcVector.x;
		y = y - srcVector.y;
		return *this;

	};

	vec2& vec2::operator -() {
		x = -x;
		y = -y;
		return *this;
	};

	float vec2::length() const {
		//(int)x = x*x;
		return sqrt(x*x+y*y);

	};

	vec2& vec2::normalize() {
		float leng = length();
		x = x / leng ;
		y = y / leng;
		return *this;
	};


}