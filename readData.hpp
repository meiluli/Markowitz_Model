//
//  readData.hpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/3.
//  Copyright © 2020 NYU. All rights reserved.
//

#ifndef readData_hpp
#define readData_hpp

#include <stdio.h>
#include "Matrix.hpp"

using namespace std;

double string_to_double( const string& s );
void readData(Matrix &data,string fileName);

#endif /* readData_hpp */
