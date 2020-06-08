//
//  readData.cpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/3.
//  Copyright © 2020 NYU. All rights reserved.
//


#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include "csv.hpp"
#include "readData.hpp"
#include "Matrix.hpp"

using namespace std;

double string_to_double(const string& s)
{
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        return 0;
    return x;
}

void readData(Matrix &data,string fileName)
{
    char tmp[20];
    ifstream file (strcpy(tmp, fileName.c_str()));
    Csv csv(file);
    
    string line;
    if (file.is_open())
    {
        int i=0;
        while (csv.getline(line) != 0) {
            
             for (int j = 0; j < csv.getnfield(); j++)
            {
                double temp=string_to_double(csv.getfield(j));
//                cout << "Asset " << j << ", Return "<<i<<"="<< temp<<"\n";
                data[i][j]=temp;
            }
            i++;
        }
        
        file.close();
    }
    else {cout <<fileName <<" missing\n";exit(0);}
}
