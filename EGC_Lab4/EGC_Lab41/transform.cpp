//
//  transformations.hpp
//  Lab4_TODO
//
//  Copyright © 2016 CGIS. All rights reserved.
//

#pragma once

#include "vec2.h"
#include "vec3.h"
#include "mat3.h"
#include "mat4.h"
#include "transform.h"

namespace egc {
	//const double PI = atan(1.0) * 4;

	//transformation matrices in 2D
	mat3 translate(const vec2 translateArray) {
		mat3 m;
		m.at(0, 2) = translateArray.x;
		m.at(1, 2) = translateArray.y;
		return m;
	};

	mat3 translate(float tx, float ty) {
		mat3 m;
		m.at(0, 2) = tx;
		m.at(1, 2) = ty;
		return m;
	};

	mat3 scale(const vec2 scaleArray) {
		mat3 m;
		m.at(0, 0) = scaleArray.x;
		m.at(1, 1) = scaleArray.y;
		return m;
	};

	mat3 scale(float sx, float sy) {
		mat3 m;
		m.at(0, 0) = sx;
		m.at(1, 1) = sy;
		return m;
	};

	mat3 rotate(float angle) {
		float ang = angle * 180 / PI;
		mat3 m;
		m.at(0,0) = cos(ang);
		m.at(0, 1) = -sin(ang);
		m.at(1, 0) = sin(ang);
		m.at(1, 1) = cos(ang);

		return m;
	};

	//transformation matrices in 3D
	mat4 translate(const vec3 translateArray) {
		mat4 m;
		m.at(0, 3) = translateArray.x;
		m.at(1, 3) = translateArray.y;
		m.at(2, 3) = translateArray.z;
		return m;
	};
	mat4 translate(float tx, float ty, float tz) {
		mat4 m;
		m.at(0, 3) = tx;
		m.at(1, 3) = ty;
		m.at(2, 3) = tz;
		return m;
	};

	mat4 scale(const vec3 scaleArray) {
		mat4 m;
		m.at(0, 0) = scaleArray.x;
		m.at(1, 1) = scaleArray.y;
		m.at(2, 2) = scaleArray.z;
		return m;
	};
	mat4 scale(float sx, float sy, float sz) {
		mat4 m;
		m.at(0, 0) = sx;
		m.at(1, 1) = sy;
		m.at(2, 2) = sz;
		return m;
	};

	mat4 rotateX(float angle) {
		mat4 rx;
		float ang = angle * PI / 180;
		rx.at(1, 1) = cos(ang);
		rx.at(1, 2) = -sin(ang);
		rx.at(2, 1) = sin(ang);
		rx.at(2, 2) = cos(ang);
		return rx;
	};
	mat4 rotateY(float angle) {
		mat4 ry;
		float ang = angle * PI / 180;
		ry.at(0,0) = cos(ang);
		ry.at(2,0) = -sin(ang);
		ry.at(0,2) = sin(ang);
		ry.at(2, 2) = cos(ang);
		return ry;
	};
	mat4 rotateZ(float angle) {
		mat4 rz;
		float ang = angle * PI / 180;
		rz.at(0, 0) = cos(ang);
		rz.at(0,1) = -sin(ang);
		rz.at(1,0) = sin(ang);
		rz.at(1,1) = cos(ang);
		return rz;
	};
}