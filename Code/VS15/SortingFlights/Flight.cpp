//============================================================================
// Name        : Flight.cpp
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   : 
// Description : Implementation of the Flight class
//============================================================================

#include "Flight.h"
#include <iomanip>
#include "Helper.h"

using std::setw;

/*
	Funkcija za poredjenje dva Flight objekta. Lista ulaznih argumenata:
	const Flight& other: Flight objekat sa kojim poredimo ovaj
	Criterium criterium: kriterijum po kojem vrsimo poredjenje
	Funkcija vraca pozitivan rezultat ako je ovaj flight objekat veci od drugog, negativan ako je suprotno ili 0 ako su jednaki.
*/
int Flight::compare(const Flight& other, Criterium criterium) {
	int result = 0;

	if (criterium == Criterium::Destination) {
		result = _destination.compare(other.destination());
	}
	else if (criterium == Criterium::DepartureTime) {
		result = compareTime(_departureTime, other.departureTime());
	}
	else if (criterium == Criterium::FlightNumber) {
		result = _flightNumber.compare(other.flightNumber());
	}
	else {
		result = _gateNumber.compare(other.gateNumber());
	}

	return result;
}

string Flight::visualizationDisplay()
{
	return _destination + ";" + _departureTime + ";" + _flightNumber + ";" + _gateNumber;
}

/*
	Funkcija koja overrideuje operator << kako bi mogli lako da ispisujemo flight objekte u koji stream zelimo. Lista argumenata:
	ostream& stream: stream u koji upisujemo flight objekat
	const Flight& flight: flight objekat koji upisujemo
	Funkcija vraca stream sa upisanim podacima.
*/
ostream& operator <<(ostream& stream, const Flight& flight) {
	stream << setw(20) << flight.destination() << setw(16) << flight.departureTime()
		<< setw(15) << flight.flightNumber() << setw(13) << flight.gateNumber();

	return stream;
}