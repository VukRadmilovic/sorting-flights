//============================================================================
// Name        : Arguments.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Class which defines arguments needed to perform sorts
//============================================================================
#pragma once

#include <string>
#include "Criterium.h"
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

class Arguments
{
private:
	string _inputFilePath; // putanja do izvornog fajla
	string _outputFilePath; // putanja do fajla u koji ispisujemo rezultate
	SortAlgorithm _sortAlgorithm; // algoritam koji koristimo za sortiranje
	Criterium _criterium; // po cemu sortiramo
	Order _order; // ascending/descending
public:
	Arguments() {};
	Arguments(string inputFilePath, string outputFilePath,
		string sortAlgorithm, string criterium, string order);

	string inputFilePath() const { return _inputFilePath; }
	string outputFilePath() const { return _outputFilePath; }
	SortAlgorithm sortAlgorithm() const { return _sortAlgorithm; }
	Criterium criterium() const { return _criterium; }
	Order order() const { return _order; }
};

