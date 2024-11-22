//============================================================================
// Name        : Flight.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Class which defines flights which can be compared and printed
//============================================================================
#pragma once

#include <string>
#include <vector>
#include "Criterium.h"
#include <ostream>

using std::ostream;
using std::string;
using std::vector;

class Flight
{
private:
	string _destination;
	string _departureTime;
	string _flightNumber;
	string _gateNumber;
public:
	int originalIndex;

	Flight() : _destination(""), _departureTime(""), _flightNumber(""), _gateNumber("") {};
	Flight(vector<string> data) : _destination(data[0]), _departureTime(data[1]), _flightNumber(data[2]), _gateNumber(data[3]) {};
	Flight(const Flight& f1) : _destination(f1.destination()), _departureTime(f1.departureTime()),
		_flightNumber(f1.flightNumber()), _gateNumber(f1.gateNumber()) {};

	string destination() const { return _destination; }
	string departureTime() const { return _departureTime; }
	string flightNumber() const { return _flightNumber; }
	string gateNumber() const { return _gateNumber; }

	int compare(const Flight& other, Criterium criterium);
	friend ostream& operator <<(ostream& stream, const Flight& flight);

	string visualizationDisplay();
};
