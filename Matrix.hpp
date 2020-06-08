//
//  Matrix.hpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/3.
//  Copyright © 2020 NYU. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Vector operator+(const Vector& V,const Vector& W);
Vector operator/(const Vector& V,const double& a);
Vector operator-(const Vector& V,const Vector& W);
Vector operator*(const double& a,const Vector& V);
double operator*(const Vector& V,const Vector& W);

Vector operator*(const Matrix& C,const Vector& V);
Matrix operator+(const Matrix& C,const Matrix& V);
Matrix operator*(const double& a,const Matrix& V);
Matrix operator/(const Matrix& V,const double& a);
Matrix operator-(const Matrix& C,const Matrix& V);
//Matrix operator*(const Matrix& C,const Matrix& V);

ostream & operator<<(ostream & out, Vector & V);
ostream & operator<<(ostream & out, Matrix & W);

#endif /* Matrix_hpp */
