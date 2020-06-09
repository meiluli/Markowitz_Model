//
//  main.cpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/2.
//  Copyright © 2020 NYU. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "csv.hpp"
#include "Matrix.hpp"
#include "readData.hpp"
#include "assetsReturns.hpp"

using namespace std;

int main() {
    remove("results.csv");
//    srand(time(NULL));
    int numberAssets=83;
    int numberReturns=700;
    Matrix returnMatrix; // a matrix to store the return data
    
    returnMatrix.resize(numberReturns);
    for(int i=0;i<numberReturns;i++)
        returnMatrix[i].resize(numberAssets);
    
    string fileName="asset_returns.csv";
    readData(returnMatrix,fileName);
    
    double temp[] = {0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05,
        0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.085, 0.09, 0.095, 0.1};
    Vector tReturns(temp, temp + 20);
    
    int isWindow = 100;
    int oosWindow = 12;
    int rollingWindow = 12;
    int rollingTimes = (int) (numberReturns - oosWindow - isWindow)/ rollingWindow + 1;
//    FTSE onePort(isWindow, oosWindow, rollingWindow, returnMatrix, tReturns[0]);
//
//    onePort.calOosMean();
//    onePort.calOosCovariance();
//    onePort.calIsMean();
//    onePort.calIsCovariance();
//    onePort.calIsQ();
//    double epsilon = 0.000001;
//    onePort.weightSolver(epsilon);
//    onePort.backtest();
//
//    Vector actAvgReturn = onePort.getActAvgReturn();
//    cout << actAvgReturn << endl;
    
    vector<FTSE> portfolios;
    Vector x;
    double epsilon = 0.000001;
    ofstream myfile;
    myfile.open ("results.csv");
    myfile << "Target return,";
    for (int k = 0; k < rollingTimes-1; k++){
        myfile << k+1 << ",";
    }
    myfile << rollingTimes << endl;
    for (int i = 0; i < 20; i++){
        cout << "Initialize portfolio with target return " << tReturns[i] << endl;
        FTSE onePort(isWindow, oosWindow, rollingWindow, returnMatrix, tReturns[i]);
        onePort.calOosMean();
        onePort.calOosCovariance();
        onePort.calIsMean();
        onePort.calIsCovariance();
        onePort.calIsQ();
        onePort.weightSolver(epsilon);
        onePort.backtest();
        portfolios.push_back(onePort);
        
        cout << "For target return " << tReturns[i] <<", the actual return is: " << endl;
        Vector actAvgReturn = onePort.getActAvgReturn();
        cout << actAvgReturn;
        cout << "Sharpe: " << onePort.getSharpe() << " AAR: " << onePort.getAAR() << " Std: " << onePort.getStd() << " CAAR: " << onePort.getCAAR() << endl << endl;
        
        myfile << tReturns[i] << ",";
        for (int j = 0; j < actAvgReturn.size()-1; j++){
            myfile << actAvgReturn[j] << ",";
        }
        myfile << actAvgReturn[actAvgReturn.size()-1] << endl;
        
    }
    return 0;
}
