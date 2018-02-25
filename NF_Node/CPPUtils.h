#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> String_Split(const string& toSplit, const string& delimiter);
vector<string> File_ReadAllLines(const char* fileName);
void File_WriteAllLines(const char* fileName, const vector<string>& lines);