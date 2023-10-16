// This file is part of sspline, a simple cubic spline interpolation.
// 
// Copyright (C) 2014 yinshichao <simpsonyin@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

// Original : Aug. 29, 2014  Last Modification : Sep. 22, 2023
#ifndef SCURVE_H
#define SCURVE_H
#include <cassert>
#include <cstring>
#include "spoint.h"

namespace scurve
{
#ifndef _out_
#	define _out_
#endif

class Sspline 
{
public:
	Sspline() = default;
	Sspline(int n, Spoint* pts) { initCurve(n, pts); }

	double chordLength(int section) { assert(section >= 0 && section <= _numpts); return _t[section]; }
	Spoint curvept(double t, int section);
protected:
	void chasingMethod(const double* a, const double* b, const double* c, const Vector3D* f, int n, _out_ Vector3D* x);
	void initCurve(int n, Spoint* pts);
private:
	int _numpts;				// sampling points number
	Spoint* _pts = nullptr;

	double* _t = nullptr;		// chord length of sections
	Vector3D* _dp = nullptr;	// point derivative (t)
};

}

#endif
