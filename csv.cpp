//
//  csv.cpp
//  Exercise1
//
//  Created by 李美漉 on 2020/6/2.
//  Copyright © 2020 NYU. All rights reserved.
//

#include "csv.hpp"

// endofline: check for and consume \r, \n, \r\n, or EOF
int Csv::endofline(char c)
{
    int eol;
    
    eol = (c=='\r' || c=='\n');
    // \r 回到目前所在行的开头，\n回到下一行
    if (c == '\r') {
        fin.get(c); //如果是'\r'就再往前读一个char
        if (!fin.eof() && c != '\n') //如果新读的char不是end of line且不是\n
            fin.putback(c);    // read too far，往后退
    }
    return eol;
}

// getline: get one line, grow as needed
int Csv::getline(string& str)
{
    char c;
    
    for (line = ""; fin.get(c) && !endofline(c); ) //一直读不是endofline的char
        line += c;
    split();
    str = line;
    return !fin.eof();
}

// split: split line into fields
int Csv::split()
{
    string fld;
    int i, j;
    
    nfield = 0;
    if (line.length() == 0)
        return 0;
    i = 0;
    
    do {
//        cout <<"line.length(): " << line.length() << endl;
//        cout <<"i: " << i << ", line[i]: " << line[i] << endl;
        if (i < line.length() && line[i] == '"'){
            j = advquoted(line, fld, ++i);// skip quote
//            cout << "advquoted: " << j << endl;
        }
        else{
            j = advplain(line, fld, i);
//            cout << "advplain: "<< j << endl;
        }
        if (nfield >= field.size())
            field.push_back(fld);
        else
            field[nfield] = fld;
        nfield++;
//        cout << "nfield: " << nfield << endl;
        i = j + 1;
    } while (j < line.length());
    
    return nfield;
}

// advquoted: quoted field; return index of next separator
int Csv::advquoted(const string& s, string& fld, int i)
{
    int j;
    
    fld = "";
    for (j = i; j < s.length(); j++) {
        if (s[j] == '"' && s[++j] != '"') {
            int k = s.find_first_of(fieldsep, j);
            if (k > s.length())    // no separator found
                k = s.length();
            for (k -= j; k-- > 0; )
                fld += s[j++];
            break;
        }
        fld += s[j];
    }
    return j;
}

// advplain: unquoted field; return index of next separator
// 找到下一个逗号，return它的index
int Csv::advplain(const string& s, string& fld, int i)
{
    int j;
    
    j = s.find_first_of(fieldsep, i); // look for separator
    if (j > s.length())               // none found
        j = s.length();
    fld = string(s, i, j-i);
    return j;
}


// getfield: return n-th field
string Csv::getfield(int n)
{
    if (n < 0 || n >= nfield)
        return "";
    else
        return field[n];
}

