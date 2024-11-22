//============================================================================
// Name        : Helper.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Helper file with functions which are used in other classes
//============================================================================
#pragma once
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;

vector<string> split(const string &line, char seperator);
int compareTime(string first, string second);
