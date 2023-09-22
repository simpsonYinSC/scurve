// This file is part of sspline, a simple cubic spline interpolation.
// 
// Copyright (C) 2014 yinshichao <simpsonyin@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

// Original : Aug. 29, 2014  Last Modification : Sep. 22, 2023
#ifndef SPOINT_H
#define SPOINT_H

#include <cmath>

namespace scurve
{
using std::pow;
using std::sqrt;

struct Spoint
{
	Spoint() :x(0), y(0), z(0) {}
	Spoint(const Spoint& p) :x(p.x), y(p.y), z(p.z) {}
	Spoint(double x_, double y_, double z_) :x(x_), y(y_), z(z_) {}

	static double distance(const Spoint& p1, const Spoint& p2) {
		return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
	}
	void operator=(const Spoint& p) {
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}
	friend Spoint operator+(const Spoint& p1, const Spoint& p2) {
		Spoint result;
		result.x = p1.x + p2.x;
		result.y = p1.y + p2.y;
		result.z = p1.z + p2.z;
		return result;
	}
	friend Spoint operator-(const Spoint& p1, const Spoint& p2) {
		Spoint result;
		result.x = p1.x - p2.x;
		result.y = p1.y - p2.y;
		result.z = p1.z - p2.z;
		return result;
	}
	friend Spoint operator/(const Spoint& p1, const Spoint& p2) {
		Spoint result;
		result.x = p1.x / p2.x;
		result.y = p1.y / p2.y;
		result.z = p1.z / p2.z;
		return result;
	}
	friend Spoint operator/(const Spoint& p, double right) {
		Spoint result;
		result.x = p.x / right;
		result.y = p.y / right;
		result.z = p.z / right;
		return result;
	}
	friend Spoint operator/(double left, const Spoint& p) {
		Spoint result;
		result.x = left / p.x;
		result.y = left / p.y;
		result.z = left / p.z;
		return result;
	}
	friend Spoint operator*(const Spoint& p1, const Spoint& p2) {
		Spoint result;
		result.x = p1.x * p2.x;
		result.y = p1.y * p2.y;
		result.z = p1.z * p2.z;
		return result;
	}
	friend Spoint operator*(double left, const Spoint& p) {
		Spoint result;
		result.x = left * p.x;
		result.y = left * p.y;
		result.z = left * p.z;
		return result;
	}
	friend Spoint operator*(const Spoint& p, double right) {
		Spoint result;
		result.x = p.x * right;
		result.y = p.y * right;
		result.z = p.z * right;
		return result;
	}

	double x;
	double y;
	double z;
};

using Vector3D = Spoint;

}

#endif