#ifndef _FILE_H_
#define _FILE_H_

#include <string>

bool readFileToVector();
bool writeVectorToFile();
bool addToVector(std::string str);
void deleteWordFromVector(std::string str);
void sortVector();
std::string getString(std::string str);
int getScore(std::string str);
std::string findFromVector(std::string str);

#endif
