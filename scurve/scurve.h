// This file is part of sspline, a simple cubic spline interpolation.
// 
// Copyright (C) 2014 yinshichao <simpsonyin@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

// Original : Aug. 29, 2014  Last Modification : Sep. 22, 2023
#pragma once

#include "fpoint.h"

namespace scurve
{

class Sspline{
public:
	FPoint* pt_P = nullptr;
	int ptNum_P;	//

	double* t_P = nullptr;	//
	Vector3D* dP_P = nullptr;	//
public:
	Sspline();
	Sspline(int N, FPoint* pt);	//

	void ChasingMethod_P(const double a[], const double b[], const double c[], const Vector3D f[], const int n, /*[out]*/Vector3D x[]);
	void InitCurveP(int N, FPoint* pt);	//P(t)
	FPoint CurveP(double t, int curSection);
};

}