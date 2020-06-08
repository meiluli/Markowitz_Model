//
//  assetsReturns.hpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/4.
//  Copyright © 2020 NYU. All rights reserved.
//

#ifndef assetsReturns_hpp
#define assetsReturns_hpp

#include "Matrix.hpp"
using namespace std;

Vector genIniX(int size);

Vector avgFunc(Matrix matrix_);

Matrix covFunc(Matrix matrix_, Vector mean_);

class AR
{
protected:
    int isWindow, oosWindow, rollingWindow, rollingTimes;
    size_t numberAssets, numberReturns; //实际上就是int
    Matrix assetsReturns;
    
public:
    AR(int isWindow_, int oosWindow_, int rollingWindow_, Matrix assetsReturns_)
    {isWindow = isWindow_; oosWindow = oosWindow_; rollingWindow = rollingWindow_; assetsReturns = assetsReturns_;
        numberReturns = assetsReturns_.size();numberAssets = assetsReturns_[0].size();
        rollingTimes = (int) (numberReturns - oosWindow - isWindow)/ rollingWindow + 1;
    };
    void setIsWindow(int isWindow_){isWindow = isWindow_;rollingTimes = (int) (numberReturns - oosWindow - isWindow)/ rollingWindow + 1;};
    void setOosWindow(int oosWindow_){oosWindow_ = oosWindow_;rollingTimes = (int) (numberReturns - oosWindow - isWindow)/ rollingWindow + 1;};
    void setRollingWindow(int rollingWindow_){rollingWindow = rollingWindow_; rollingTimes = (int) (numberReturns - oosWindow - isWindow)/ rollingWindow + 1;};
    void setAssetsReturns(Matrix assetsReturns_)
    {assetsReturns = assetsReturns_; numberReturns = assetsReturns_.size(); numberAssets = assetsReturns_[0].size();};
    
    int getIsWindow(){return isWindow;};
    int getOosWindow(){return oosWindow;};
    int getRollingWindow(){return rollingWindow;};
    int getRollingTimes(){return rollingTimes;};
    int getNumberAssets(){return (int)numberAssets;};
    int getNumberReturns(){return (int)numberReturns;};
    
    virtual~AR(){};
    
};

class OOS: public virtual AR
{
protected: //或者private待考量
    Matrix oosMean;
    vector<Matrix> oosCovariance;

public:
    OOS(int isWindow_, int oosWindow_, int rollingWindow_, Matrix assetsReturns_):AR(isWindow_, oosWindow_, rollingWindow_, assetsReturns_){};
    
    void calOosMean();
    
    void calOosCovariance();
    
    Matrix getOosMean(){return oosMean;}
    vector<Matrix> getOosCovariance(){return oosCovariance;}
    ~OOS(){};
};

class IS: public virtual AR
{
protected: //或者private待考量
    double targetReturn;
    Vector isb, isLambda, isMu;
    Matrix isMean, weights, isX;
    vector<Matrix> isCovariance, isQ;

public:
    IS(int isWindow_, int oosWindow_, int rollingWindow_, Matrix assetsReturns_, double targetReturn_):AR(isWindow_, oosWindow_, rollingWindow_, assetsReturns_)
    {targetReturn = targetReturn_; Vector temp(numberAssets, 0.0);
        temp.push_back(-targetReturn_); temp.push_back(-1); isb = temp;};
    
    void calIsMean();
    void calIsCovariance(); //要在有isMean之后生成isCovariance
    void calIsQ(); //要在有isMean和isCovariance之后生成Q
    void weightSolver(double epsilon);
    
    void setTargetReturn(double targetReturn_)
    {targetReturn = targetReturn_; Vector temp(numberAssets, 0.0);
    temp.push_back(-targetReturn_); temp.push_back(-1); isb = temp;};
   
    double getTargetReturn(){return targetReturn;};
    Vector getIsb(){return isb;};
    Vector getIsLambda(){return isLambda;};
    Vector getIsMu(){return isMu;};
    Matrix getIsMean(){return isMean;};
    Matrix getWeights(){return weights;};
    Matrix getIsX(){return isX;};
    vector<Matrix> getIsCovariance(){return isCovariance;};
    vector<Matrix> getIsQ(){return isQ;};
    
    ~IS(){};
};

class FTSE: public OOS, public IS
{
private:
    Vector actAvgReturn;
    Vector actCov;
    double AAR; //average of port returns
    double vol;
    double sharpe;
    
public:
//    FTSE(){};
    FTSE(int isWindow_, int oosWindow_, int rollingWindow_, Matrix assetsReturns_, double targetReturn_):OOS(isWindow_, oosWindow_, rollingWindow_, assetsReturns_), IS(isWindow_, oosWindow_, rollingWindow_, assetsReturns_, targetReturn_), AR(isWindow_, oosWindow_, rollingWindow_, assetsReturns_){};
    
    void backtest();
    double getAAR(){return AAR;};
    Vector getActAvgReturn(){return actAvgReturn;};
    Vector getActCov(){return actCov;};
    
    ~FTSE(){};
};

#endif /* assetsReturns_hpp */
