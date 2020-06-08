//
//  Matrix.cpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/3.
//  Copyright © 2020 NYU. All rights reserved.
//

#include "Matrix.hpp"
#include <cmath>
#include "math.h"
using namespace std;

Vector operator+(const Vector& V,const Vector& W) //两个vector相加
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = V[j] + W[j];
   return U;
}

Vector operator/(const Vector& V, const double& a) //vector除以一个常数
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = V[j]/a;
   return U;
}

Vector operator-(const Vector& V,const Vector& W)
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = V[j] - W[j];
   return U;
}

Vector operator*(const double& a,const Vector& V)
{
   int d = V.size();
   Vector U(d);
   for (int j=0; j<d; j++) U[j] = a*V[j];
   return U;
}

double operator*(const Vector& V,const Vector& W)
{
    int d = V.size();
    double s = 0.0;
    for (int j=0; j<d; j++) s+= V[j] * W[j];
    return s;
}

Vector operator*(const Matrix& C,const Vector& V)
{
    int d = C.size();
    Vector U(d);
    for (int j=0; j<d; j++){
        U[j] = C[j] * V;
    }
    return U;
}

Matrix operator+(const Matrix& C,const Matrix& V) //两个matrix相加
{
    Matrix W;
    for (int i = 0; i < C.size(); i++)
    {
        Vector U(C[i].size());
        for (int j = 0; j < C[i].size(); j++)
        {
            U[j]=C[i][j]+V[i][j];
        }
        W.push_back(U);
    }
    return W;
}

Matrix operator*(const double& a,const Matrix& V) //matrix乘常数
{
    Matrix W;
    for (int i = 0; i < V.size(); i++)
    {
        Vector U(V[i].size());
        for (int j = 0; j < U.size(); j++)
        {
            U[j] = a * V[i][j];
        }
        W.push_back(U);
    }
    return W;
}

Matrix operator/(const Matrix& V, const double& a) //matrix除以常数
{
    Matrix W;
    for (int i = 0; i < V.size(); i++)
    {
        Vector U(V[i].size());
        for (int j = 0; j < U.size(); j++)
        {
            U[j] = V[i][j] / a;
        }
        W.push_back(U);
    }
    return W;
}

Matrix operator-(const Matrix& C,const Matrix& V) //两个matrix相减
{
    Matrix W;
    for (int i = 0; i < C.size(); i++)
    {
        Vector U(C[i].size());
        for (int j = 0; j < C[i].size(); j++)
        {
            U[j]=C[i][j]-V[i][j];
        }
        W.push_back(U);
    }
    return W;
}

//Matrix operator*(const Matrix& C,const Matrix& V) //两个metrix点乘
//{
//    Matrix W;
//    for (int i = 0; i < C.size(); i++)
//    {
//        Vector U(C[i].size());
//        for (int j = 0; j < C[i].size(); j++)
//        {
//            U[j]=C[i][j]*V[i][j];
//        }
//        W.push_back(U);
//    }
//    return W;
//}


ostream & operator<<(ostream & out, Vector & V)
{
    for (Vector::iterator itr= V.begin(); itr != V.end(); itr++)
        out << *itr << "   ";
    out << endl;
    return out;
}

ostream & operator<<(ostream & out, Matrix & W)
{
    for (Matrix::iterator itr= W.begin(); itr != W.end(); itr++)
        out << *itr;
    out << endl;
    return out;
}
