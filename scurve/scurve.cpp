// This file is part of sspline, a simple cubic spline interpolation.
// 
// Copyright (C) 2014 yinshichao <simpsonyin@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.

// Original : Aug. 29, 2014  Last Modification : Sep. 22, 2023

#include <memory>
#include "scurve.h"

namespace scurve
{

void Sspline::chasingMethod(const double* a, const double* b, const double* c, const Vector3D* f, int n/*dimension*/, _out_ Vector3D* x) {
	// solve Ax=f, where A is a tridiagonal matrix
	double* beta = new double[n + 1];
	Vector3D* y = new Vector3D[n + 1];

	memset(beta, 0, sizeof(double) * (n + 1));
	memset(y, 0, sizeof(Vector3D) * (n + 1));

	// factorization coefficient matrix: A=LU
	// calculate { beta[i] } (chase)
	for (int i = 1; i <= n - 1; i++) {
		if (1 == i) {
			beta[i] = c[1] / b[1];
		}
		else {
			beta[i] = c[i] / (b[i] - a[i] * beta[i - 1]);
		}
	}
	// solve Ly=f (calculate y[i]) (chase after)
	for (int i = 1; i <= n; i++) {
		if (1 == i) {
			y[i] = f[1] / b[1];
		}
		else {
			y[i] = (f[i] - a[i] * y[i - 1]) / (b[i] - a[i] * beta[i - 1]);
		}
	}
	// solve Ux=y (calculate x[i]) (catch up)
	for (int i = n; i >= 1; i--) {
		if (n == i) {
			x[n] = y[n];
		}
		else {
			x[i] = y[i] - beta[i] * x[i + 1];
		}
	}

	delete[] beta;
	delete[] y;
}

void Sspline::initCurve(int n_, Spoint* pts) {
	if (_t)
		delete[] _t;
	if (_dp)
		delete[] _dp;
	//////////////////////////////////////////////////////////////////////////
	_numpts = n_;
	//////////////////////////////////////////////////////////////////////////
	_pts = new Spoint[_numpts + 1];
	_t = new double[_numpts + 1];		// global
	_dp = new Vector3D[_numpts + 1];	// global

	memset(_pts, 0, sizeof(Spoint) * (_numpts + 1));
	memset(_t, 0, sizeof(double) * (_numpts + 1));
	memset(_dp, 0, sizeof(Vector3D) * (_numpts + 1));

	for (int i = 1; i <= _numpts; i++) {
		_pts[i] = pts[i - 1];
	}
	int n = _numpts;

	for (int i = 1; i <= n - 1; i++) {
		_t[i] = Vector3D::distance(_pts[i], _pts[i + 1]);
	}

	// testing, calculate p'(i)
	// int n = ptNum_P;
	double* a = new double[n + 1];
	double* b = new double[n + 1];
	double* c = new double[n + 1];
	Vector3D* f = new Vector3D[n + 1];
	Vector3D* x = new Vector3D[n + 1];
	memset(a, 0, sizeof(double) * (n + 1));
	memset(b, 0, sizeof(double) * (n + 1));
	memset(c, 0, sizeof(double) * (n + 1));
	memset(f, 0, sizeof(Vector3D) * (n + 1));
	memset(x, 0, sizeof(Vector3D) * (n + 1));

	memset(_dp, 0, sizeof(Vector3D) * (_numpts + 1));

	b[1] = 2; c[1] = 1; f[1] = (3 * (_pts[2] - _pts[1])) / _t[1];
	a[n] = 1; b[n] = 2; f[n] = (3 * (_pts[n] - _pts[n - 1])) / _t[n - 1];
	for (int i = 2; i <= n - 1; i++) {
		a[i] = _t[i];
		b[i] = 2 * (_t[i - 1] + _t[i]);
		c[i] = _t[i - 1];

		f[i] = ((3 * _t[i]) / _t[i - 1]) * (_pts[i] - _pts[i - 1])
			+ ((3 * _t[i - 1]) / _t[i]) * (_pts[i + 1] - _pts[i]);
	}
	chasingMethod(a, b, c, f, n, x);
	for (int i = 1; i <= n; i++) {
		_dp[i] = x[i];
	}

	delete[] a;
	delete[] b;
	delete[] c;
	delete[] f;
	delete[] x;
}

Spoint Sspline::curvept(double t, int section) {

	int i = section;
	// correct
	Spoint Result = _pts[i] + _dp[i] * t
		+ ((3 / pow(_t[i], 2)) * (_pts[i + 1] - _pts[i])
		   - (1 / _t[i]) * (_dp[i + 1] + 2 * _dp[i])) * pow(t, 2)
		+ ((-2 / pow(_t[i], 3)) * (_pts[i + 1] - _pts[i])
		   + (1 / pow(_t[i], 2)) * (_dp[i + 1] + _dp[i])) * pow(t, 3);
	//////////////////////////////////////////////////////////////////////////
	return Result;
}

}