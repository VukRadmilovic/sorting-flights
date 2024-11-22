//============================================================================
// Name        : Arguments.cpp
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Implementation of the Arguments class
//============================================================================
#include "Arguments.h"

using std::runtime_error;

/*
	Konstruktor koji automatski proverava i validnost unesenih argumenata
	U slucaju greske baca runtime_error sa odgovarajucom porukom.
*/
Arguments::Arguments(string inputFilePath, string outputFilePath,
	string sortAlgorithm, string criterium, string order)
{
	ifstream test(inputFilePath);
	if (!test.good()) {
		throw runtime_error("Nevalidan ulazni fajl.");
	}
	test.close();
	_inputFilePath = inputFilePath;

	ofstream test2(outputFilePath);
	if (!test2.good()) {
		throw runtime_error("Nevalidan izlazni fajl.");
	}
	test2.close();
	_outputFilePath = outputFilePath;

	if (sortAlgorithm != "1" && sortAlgorithm != "2") {
		throw runtime_error("Nevalidna vrednost za sort.");
	}
	_sortAlgorithm = SortAlgorithm(stoi(sortAlgorithm));

	if (criterium != "1" && criterium != "2" &&
		criterium != "3" && criterium != "4") {
		throw runtime_error("Nevalidna vrednost za kriterijum.");
	}
	_criterium = Criterium(stoi(criterium));

	if (order != "1" && order != "2") {
		throw runtime_error("Nevalidna vrednost za poredak.");
	}
	_order = Order(stoi(order));
}