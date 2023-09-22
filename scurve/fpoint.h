// This file is part of sspline, a simple cubic spline interpolation.
// 
// Copyright (C) 2014 yinshichao <simpsonyin@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

// Original : Aug. 29, 2014  Last Modification : Sep. 22, 2023

#pragma once

#include <cmath>

namespace scurve
{

class FPoint{
public:
	double x;
	double y;
	double z;
public:
	FPoint():x(0),y(0),z(0){};
	FPoint(const FPoint& p):x(p.x),y(p.y),z(p.z){}
	FPoint(double inX,double inY,double intZ):x(inX),y(inY),z(intZ){}
	static double Distance(const FPoint& p1,const FPoint& p2){
		return sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2) + pow(p1.z - p2.z,2));
	}
	void operator=(const FPoint& p){
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}
	friend FPoint operator+(const FPoint& p1,const FPoint& p2){
		FPoint result;
		result.x = p1.x + p2.x;
		result.y = p1.y + p2.y;
		result.z = p1.z + p2.z;
		return result;
	}
	friend FPoint operator-(const FPoint& p1,const FPoint& p2){
		FPoint result;
		result.x = p1.x - p2.x;
		result.y = p1.y - p2.y;
		result.z = p1.z - p2.z;
		return result;
	}

	friend FPoint operator/(const FPoint& p1,const FPoint& p2){
		FPoint result;
		result.x = p1.x / p2.x;
		result.y = p1.y / p2.y;
		result.z = p1.z / p2.z;
		return result;
	}
	friend FPoint operator/(const FPoint& p,const double right){
		FPoint result;
		result.x = p.x / right;
		result.y = p.y / right;
		result.z = p.z / right;
		return result;
	}
	friend FPoint operator/(const double left, const FPoint& p){
		FPoint result;
		result.x = left / p.x;
		result.y = left / p.y;
		result.z = left / p.z;
		return result;
	}
	friend FPoint operator*(const FPoint& p1,const FPoint& p2){
		FPoint result;
		result.x = p1.x * p2.x;
		result.y = p1.y * p2.y;
		result.z = p1.z * p2.z;
		return result;
	}
	friend FPoint operator*(const double left,const FPoint& p){
		FPoint result;
		result.x = left * p.x;
		result.y = left * p.y;
		result.z = left * p.z;
		return result;
	}
	friend FPoint operator*(const FPoint& p,const double right){
		FPoint result;
		result.x = p.x * right;
		result.y = p.y * right;
		result.z = p.z * right;
		return result;
	}
};

typedef FPoint Vector3D;

}