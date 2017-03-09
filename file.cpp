#include "file.h"
#include "global.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

string getString(string str);
bool isData(string str);
bool readFileToVector()
{
    bool success = true;
    string tmpstr;
    fstream file;
    file.open(filePath, ios::in);
    if(file){
        while(getline(file, tmpstr)){
            vecData.push_back(tmpstr);
        }
    }else
        success = false;
    
    file.close();
    return success;
}

bool writeVectorToFile()
{
    bool success = true;
    int i;
    ofstream file;

    file.open(filePath, ios::out);
    if(file){
        for(i = 0; i < vecData.size(); i++){
            file << vecData[i] << endl;
        }
    }else
        success = false;
    
    file.close();
    return success;
}

bool isData(std::string str)
{
    vector<string> result;
    string::size_type pos;
    str+=" ";
    int size = str.size();
    for(int i = 0; i < size; i++){
        pos = str.find(" ", i);
        if(pos < size){
            string s = str.substr(i, pos-i);
            result.push_back(s);
            i = pos + 1 - 1;
        }
    }
    if(result.size() != 2)
        return false;

    string tmp = *(result.begin());
    for(int i = 0; i < tmp.size(); i++){
        if(!isalpha(tmp[i]))
            return false;
    }
    for(int i = 0; i < vecData.size(); i++){
        string wordtmp = *(vecData.begin()+i);
        wordtmp = getString(wordtmp);
        if(wordtmp == tmp)
            return false;
    }
    tmp = *(result.begin()+1);
    for(int i = 0; i < tmp.size(); i++){
        if(!isdigit(tmp[i]))
            return false;
    }
    return true;
}

string getString(string str)
{
    string tmp = str;
    string::size_type pos;
    pos = tmp.find(" ");
    tmp = tmp.substr(0, pos);
    
    return tmp;
}

int getScore(string str)
{
    string tmp = findFromVector(str);
    if(tmp != ""){
        string::size_type pos;
        pos = tmp.find(" ");
        tmp = tmp.substr(pos, tmp.size()-1);
        return atoi(tmp.c_str());
    }
    return 0;
}
bool addToVector(std::string str)
{
    if(isData(str)){
        vecData.push_back(str);
        sortVector();
        return true;
    }
    else
        return false;
}

bool wordname(const string &s1, const string &s2)
{
    return s1 < s2;
}

void sortVector()
{
    sort(vecData.begin(), vecData.end(), wordname);
}

string findFromVector(string str)
{
    string s = "";
    for(int i = 0; i < vecData.size(); i++){
        string tmp = *(vecData.begin() + i);
        if(getString(tmp) == str)
            return tmp;
    }
    return s;
}

void deleteWordFromVector(string str)
{
    for(auto it = vecData.begin(); it != vecData.end(); ++it){
        if(*it == str){
            vecData.erase(it);
            break;
        }
    }
}
