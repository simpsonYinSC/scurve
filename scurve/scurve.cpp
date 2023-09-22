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

Sspline::Sspline(){
}

Sspline::Sspline(int N, FPoint* pt){
	InitCurveP(N,pt);
}

void Sspline::ChasingMethod_P(const double a[], const double b[], const double c[], const Vector3D f[], const int n/*ά��*/, /*[out]*/Vector3D x[]){

	double* beta = new double[n+1];
	Vector3D* y = new Vector3D[n+1];

	memset(beta,0,sizeof(double)*(n+1));
	memset(y,0,sizeof(Vector3D)*(n+1));

	for(int i=1;i<=n-1;i++){
		if(1 == i){
			beta[i] = c[1] / b[1];
		}
		else{
			beta[i] = c[i] / (b[i] - a[i] * beta[i-1]);
		}
	}

	for(int i=1;i<=n;i++){
		if(1 == i){
			y[i] = f[1] / b[1];
		}
		else{
			y[i] = (f[i] - a[i] * y[i-1]) / (b[i] - a[i] * beta[i-1]);
		}
	}

	for(int i=n;i>=1;i--){
		if(n == i){
			x[n] = y[n];
		}
		else{
			x[i] = y[i] - beta[i] * x[i+1];
		}
	}

	delete[] beta;
	delete[] y;
}

void Sspline::InitCurveP(int N, FPoint* pt){
	if(t_P)
		delete[] t_P;
	if(dP_P)
		delete[] dP_P;
	//////////////////////////////////////////////////////////////////////////
	ptNum_P = N;
	//////////////////////////////////////////////////////////////////////////
	pt_P = new FPoint[ptNum_P+1];
	t_P = new double[ptNum_P+1];	//
	dP_P = new Vector3D[ptNum_P+1];	//

	memset(pt_P,0,sizeof(FPoint)*(ptNum_P+1));
	memset(t_P,0,sizeof(double)*(ptNum_P+1));
	memset(dP_P,0,sizeof(Vector3D)*(ptNum_P+1));
	
	for(int i=1;i<=ptNum_P;i++){
		pt_P[i] = pt[i-1];
	}
	int n = ptNum_P;

	for(int i=1;i<=n-1;i++){
		t_P[i] = Vector3D::Distance(pt_P[i],pt_P[i+1]);
	}

	//int n=ptNum_P;
	double* a = new double[n+1];
	double* b = new double[n+1];
	double* c = new double[n+1];
	Vector3D* f = new Vector3D[n+1];
	Vector3D* x = new Vector3D[n+1];
	memset(a,0,sizeof(double)*(n+1));
	memset(b,0,sizeof(double)*(n+1));
	memset(c,0,sizeof(double)*(n+1));
	memset(f,0,sizeof(Vector3D)*(n+1));
	memset(x,0,sizeof(Vector3D)*(n+1));

	memset(dP_P,0,sizeof(Vector3D)*(ptNum_P+1));

	b[1] = 2; c[1] = 1; f[1] = (3*(pt_P[2] - pt_P[1])) / t_P[1];
	a[n] = 1; b[n] = 2; f[n] = (3*(pt_P[n] - pt_P[n-1])) / t_P[n-1];
	for(int i=2;i<=n-1;i++){
		a[i] = t_P[i];
		b[i] = 2*(t_P[i-1] + t_P[i]);
		c[i] = t_P[i-1];

		f[i] = ((3*t_P[i]) / t_P[i-1])*(pt_P[i] - pt_P[i-1]) 
			+ ((3*t_P[i-1]) / t_P[i])*(pt_P[i+1] - pt_P[i]) ;
	}
	ChasingMethod_P(a,b,c,f,n,x);
	for(int i=1;i<=n;i++){
		dP_P[i] = x[i];
	}

	delete[] a;
	delete[] b;
	delete[] c;
	delete[] f;
	delete[] x;
}

FPoint Sspline::CurveP(double t, int curSection){

	int i = curSection;

	FPoint Result = pt_P[i] + dP_P[i]*t
		+ ( (3 / pow(t_P[i],2))*(pt_P[i+1] - pt_P[i]) 
		- (1 / t_P[i])*(dP_P[i+1] + 2*dP_P[i]) )*pow(t,2)
		+ ( (-2 / pow(t_P[i],3))*(pt_P[i+1] - pt_P[i])
		+ (1/pow(t_P[i],2))* (dP_P[i+1] + dP_P[i]))*pow(t,3);
	//////////////////////////////////////////////////////////////////////////
	return Result;
}

}