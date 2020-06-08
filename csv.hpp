//
//  csv.hpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/2.
//  Copyright © 2020 NYU. All rights reserved.
//

#ifndef csv_hpp
#define csv_hpp

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>


using namespace std;

class Csv {    // read and parse comma-separated values
    // sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625
private:
    istream& fin;            // input file pointer
    string line;            // input line
    vector<string> field;    // field strings
    int nfield;                // number of fields 
    string fieldsep;        // separator characters
    
    int split();
    int endofline(char);
    int advplain(const string& line, string& fld, int);
    int advquoted(const string& line, string& fld, int);
    
public:
    Csv(istream& fin = cin, string sep = ","):
    fin(fin), fieldsep(sep) {} // 和{fin = fin; fieldsep = sep;}一样
    
    int getline(string&);
    string getfield(int n);
    int getnfield() const { return nfield; }

};

#endif /* csv_hpp */
