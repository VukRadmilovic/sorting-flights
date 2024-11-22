//============================================================================
// Name        : Helper.cpp
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Implementation of the Helper header functions
//============================================================================
#include "Helper.h"


/*
	Funkcija koja deli string na niz(vektor) stringova koji su bili podeljeni seperatorom.
	const string &line: string koji delimo
	char seperator: seperator po kome delimo
	Funkcija vraca niz stringova koji su bili podeljeni seperatorom.
*/
vector<string> split(const string &line, char seperator) {
	std::stringstream ss(line);
	vector<string> result;
	string entry;

	while (std::getline(ss, entry, seperator)) {
		result.push_back(entry);
	}

	return result;
}

/*
	Funkcija koja poredi dva departureTime-a po 24hr formatu
	string first: prvo vreme
	string second: drugo vreme
	Funkcija vraca 1 ako je prvo vreme vece, -1 ako je drugo vreme vece ili 0 ako su jednaki.
*/
int compareTime(string first, string second) {
	vector<string> firstTime = split(first, ':');
	vector<string> secondTime = split(second, ':');
	
	if (stoi(firstTime[0]) > stoi(secondTime[0])) {
		return 1;
	}
	else if (stoi(firstTime[0]) < stoi(secondTime[0])) {
		return -1;
	}
	else {
		if (stoi(firstTime[1]) > stoi(secondTime[1])) {
			return 1;
		}
		else if (stoi(firstTime[1]) == stoi(secondTime[1])) {
			return 0;
		} else {
			return -1;
		}
	}
}