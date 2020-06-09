//
//  assetsReturns.cpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/4.
//  Copyright © 2020 NYU. All rights reserved.
//

#include "assetsReturns.hpp"
#include "Matrix.hpp"
#include <cmath>

using namespace std;

//Vector genIniX(int size){
//    Vector res(size);
//    double sum = 0.0;
//    for (int i = 0; i < size; i++){
//        res[i] = rand();
//        sum += res[i];
//    }
//    res = res/sum;
//    return res;
//}

Vector avgFunc(Matrix matrix_)
{
    Vector res = matrix_[0];
    for (int i = 1; i < matrix_.size(); i++)
        res = (i * res + matrix_[i]) / (i+1.0);
    return res;
};

Matrix covFunc(Matrix matrix_, Vector mean_)
{
    Matrix res;
    Matrix demean;
    Vector temp1;
    double temp2 = 0.0;
    
    //the dimension of the return matrix
    res.resize(matrix_[0].size());
    for (int k = 0; k < res.size(); k++){
        res[k].resize(matrix_[0].size());
    };
    
    //deduct mean for the original matrix
    for (int i = 0; i < matrix_.size(); i++){
        temp1 = matrix_[i] - mean_;
        demean.push_back(temp1);
    };
    
    //calculate autocovariance
    for (int m = 0; m < demean[0].size(); m++)
    {
        for (int n = 0; n < demean.size(); n++){
            temp2 += demean[n][m] * demean[n][m];
        }
        res[m][m] = temp2 / (demean.size() - 1);
        temp2 = 0;
    };
    
    for (int j = 0; j < demean[0].size()-1; j++){
        for (int l = j + 1; l < demean[0].size(); l++){
            for (int h = 0; h < demean.size(); h++ )
            {
                temp2 += demean[h][j] * demean[h][l];
            }
            res[j][l] = res[l][j]= temp2 / (demean.size() - 1);
            temp2 = 0;
        }
    };
    return res;
};

//template<typename T>
//vector<T> slice(vector<T> const &v, int m, int n)
//{
//    auto first = v.cbegin() + m;
//    auto last = v.cbegin() + n + 1;
//
//    vector<T> vec(first, last);
//    return vec;
//}
 
void OOS::calOosMean(){
    Matrix temp1;
    Vector temp2;
    
    for (int i = 0; i < rollingTimes; i++){
        for (int j = isWindow + rollingWindow * i; j < isWindow + rollingWindow * i + oosWindow; j++){
            temp1.push_back(assetsReturns[j]);
        }
        temp2 = avgFunc(temp1);
        oosMean.push_back(temp2);
        temp1.clear();
    }
};

void OOS::calOosCovariance(){
    Matrix temp1;
    Matrix temp2;
    
    for (int i = 0; i < rollingTimes; i++){
        for (int j = isWindow + rollingWindow * i; j < isWindow + rollingWindow * i + oosWindow; j++){
            temp1.push_back(assetsReturns[j]);
        }
        temp2 = covFunc(temp1, oosMean[i]);
        oosCovariance.push_back(temp2);
        temp1.clear();
    };
};
    
void IS::calIsMean()
{
    Matrix temp1;
    Vector temp2;
    
    for (int i = 0; i < rollingTimes; i++){
        for (int j = rollingWindow * i; j < rollingWindow * i + isWindow; j++){
            temp1.push_back(assetsReturns[j]);
        }
//            temp1 = slice(assetsReturns, isWindow + rollingWindow * i, isWindow + rollingWindow * i + oosWindow - 1);
            
        temp2 = avgFunc(temp1);
        isMean.push_back(temp2);
        temp1.clear();
    };
};

//要在有isMean之后生成isCovariance
void IS::calIsCovariance()
{
    Matrix temp1;
    Matrix temp2;
    
    for (int i = 0; i < rollingTimes; i++){
        for (int j = rollingWindow * i; j < rollingWindow * i + isWindow; j++){
            temp1.push_back(assetsReturns[j]);
        }
        temp2 = covFunc(temp1, isMean[i]);
        isCovariance.push_back(temp2);
        temp1.clear();
    };
};

//要在有isMean和isCovariance之后生成Q
void IS::calIsQ()
{
    Matrix tempQ;
    Matrix tempCov;
    Vector tempMean;
    Vector tempOnes(isCovariance[0].size(), -1.0);
    
    tempOnes.push_back(0);
    tempOnes.push_back(0);
    
    for(int i = 0; i < rollingTimes; i++){
        tempCov = isCovariance[i];
        tempMean = (-1) * isMean[i];
        
        for(int j = 0; j < isCovariance[0].size(); j++){
            tempCov[j].push_back(tempMean[j]);
            tempCov[j].push_back(-1.0);
            tempQ.push_back(tempCov[j]);
        }
        
        tempMean.push_back(0);
        tempMean.push_back(0);
        
        tempQ.push_back(tempMean);
        tempQ.push_back(tempOnes);
        isQ.push_back(tempQ);
        tempQ.clear();
    };
};

void IS::weightSolver(double epsilon)
{
    Vector s_pre, p_pre, s_aft, p_aft, tempWeight;
    double alpha, beta;
    
    for (int i = 0; i < rollingTimes; i++){
        Vector x_(83, 0.01205);
        x_.push_back(0.1);
        x_.push_back(0.1);
        
        s_pre = isb - isQ[i] * x_;
        p_pre = s_pre;
        
        while (s_pre * s_pre > epsilon){
            alpha = s_pre * s_pre / (p_pre * (isQ[i] * p_pre));
            x_ = x_ + alpha * p_pre;
//            cout << x_ << endl;
            s_aft = s_pre - alpha * isQ[i] * p_pre;
            beta = (s_aft * s_aft) / (s_pre * s_pre);
            p_aft = s_aft + beta * p_pre;
            s_pre = s_aft;
            p_pre = p_aft;
        }
        isX.push_back(x_);
        for (int j = 0; j < x_.size()-2; j++){
            tempWeight.push_back(x_[j]);
        }
        weights.push_back(tempWeight);
        tempWeight.clear();
        isLambda.push_back(x_[x_.size()-2]);
        isMu.push_back(x_[x_.size()-1]);
    }
    
};

void FTSE::backtest()
{
    AAR = 0.0;
    CAAR = 0.0;
    double var = 0.0;
    for (int i = 0; i < rollingTimes; i++){
        actAvgReturn.push_back(weights[i] * oosMean[i]);
        AAR = (i * AAR + weights[i] * oosMean[i])/ (i+1);
        CAAR += weights[i] * oosMean[i];
        actCov.push_back(weights[i] * (oosCovariance[i] * weights[i]));
    }
    
    for (int j = 0; j < rollingTimes; j++){
        var += pow((weights[j] * oosMean[j] - AAR), 2.0);
    }
    std = sqrt(var/rollingTimes);
    Sharpe = AAR/std;
    
    
};




