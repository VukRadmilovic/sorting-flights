//============================================================================
// Name        : main.cpp
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Main class which runs the actual program - gets user input via GUI/command line, sorts and displays the visualization of the sort algorithm as well as the data gathered during sorting
//============================================================================

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Flight.h"
#include <sstream>
#include "MyWindow.h"
#include "Arguments.h"
#include "Sort.h"
#include <iomanip>
#include "Helper.h"
#include "VisualizerWindow.h"

using std::vector;
using std::string;
using std::cout;

using Graph_lib::In_box;
using Graph_lib::Text;
using Graph_lib::Color;
using Graph_lib::gui_main;

void sortFlights(Arguments args);
vector<Flight> loadFlights(const string path);

const string SortAlgorithmToString(SortAlgorithm sortAlgorithm);
const string CriteriumToString(Criterium criterium);
const string OrderToString(Order order);

int handleCommandLine(int argc, char *argv[]);
void handleInputGUI();

void performSort(Arguments args, vector<Flight> data, vector<Flight> originalData, Sort* sorter);

int main(int argc, char *argv[])
{
	int retVal = handleCommandLine(argc, argv);
	if (retVal != 1) {
		return retVal;
	}

	handleInputGUI();

	return 0;
}

/*
	Funkcija koja kreira GUI za unos podataka za sortiranje i obradjuje ono sto korisnik unese
*/
void handleInputGUI() {
	MyWindow window(Point(100, 100), 800, 330, "Sortiranje letova");
	In_box txtInput(Point(125, 25), 600, 25, "Ulazna datoteka:");
	In_box txtOutput(Point(125, 65), 600, 25, "Izlazna datoteka:");
	In_box txtSort(Point(340, 105), 385, 25, "Sort algoritam (unesite 1 za selection, 2 za merge):");
	In_box txtCriterium(Point(575, 145), 150, 25, "Kriterijum (unesite 1 za broj leta, 2 za destinaciju, 3 za vreme poletanja, 4 za broj izlaza):");
	In_box txtOrder(Point(315, 185), 410, 25, "Poredak (unesite 1 za rastuci, 2 za opadajuci):");


	window.attach(txtInput);
	window.attach(txtOutput);
	window.attach(txtSort);
	window.attach(txtCriterium);
	window.attach(txtOrder);

	Text txtError(Point(330, 235), "");
	txtError.set_color(Color::red);
	window.attach(txtError);

	while (true) {
		window.wait_for_button();
		try {
			Arguments args(txtInput.get_string(), txtOutput.get_string(),
				txtSort.get_string(), txtCriterium.get_string(), txtOrder.get_string());
			sortFlights(args);
			break;
		}
		catch (runtime_error err) {
			txtError.set_label(err.what());
			window.set_label("Sortiranje letova");
		}
	}
}

/*
	Funkcija koja obradjuje slucaj koriscenja komandne linije za unos podataka umesto GUI-a
	Argumenti komandne linije:
	argv[1] - putanja do ulaznog fajla
	argv[2] - putanja do izlaznog fajla
	argv[3] - algoritam za sortiranje (1 - selection sort, 2 - merge sort)
	argv[4] - kriterijum sortiranja (1 - flightNumber, 2 - destination, 3 - departureTime, 4 - gateNumber)
	argv[5] - poredak (1 - ascending, 2 - descending)
	Primer:
	in.txt out.txt 1 1 2
	To znaci sortiranje podataka iz in.txt u out.txt pomocu selection sorta po kriterijumu flightNumber descending.
*/
int handleCommandLine(int argc, char *argv[]) {
	if (argc > 1) {
		if (argc != 6) {
			cout << "Niste uneli tacan broj argumenata.\n";
			return -1;
		}
		try {
			Arguments args(argv[1], argv[2], argv[3], argv[4], argv[5]);
			sortFlights(args);
			return 0;
		}
		catch (runtime_error err) {
			cout << err.what();
			return -1;
		}
	}
	return 1;
}

void printFlights(ostream& stream, vector<Flight> flights) {
	stream << setfill('-') << setw(65) << "-" << endl << setfill(' ');
	stream << setw(20) << "DESTINATION" << setw(16) << "DEPARTURE TIME"
		<< setw(15) << "FLIGHT NUMBER" << setw(13) << "GATE NUMBER" << endl;
	stream << setfill('-') << setw(65) << "-" << endl << setfill(' ');
	for (int i = 0; i < flights.size(); i++) {
		stream << flights[i] << endl;
	}
}

void printGatheredData(ostream& stream, Arguments args, vector<Info> infos) {
	stream << setfill('-') << setw(65) << "-" << endl << setfill(' ');
	stream << setw(20) << "Br. iteracije" << setw(20) << "Br. poredjenja"
		<< setw(25) << "Br. pomeranja elem." << endl;
	stream << setfill('-') << setw(65) << "-" << endl << setfill(' ');

	int swapsNum = 0;
	int comparisonsNum = 0;
	for (int i = 0; i < infos.size(); i++) {
		stream << setw(20) << (i + 1) << setw(20) << infos[i].numCmps
			<< setw(25) << infos[i].numMoves << endl;
		swapsNum += infos[i].numMoves;
		comparisonsNum += infos[i].numCmps;
	}

	stream << setfill('-') << setw(65) << "-" << endl << setfill(' ');
	stream << setw(19) << "Ukupno iteracija:" << infos.size() << setw(18)
		<< "Poredjenja:" << comparisonsNum << setw(23) << "Pomeranja elemenata:" << swapsNum << endl;
	stream << setfill('-') << setw(65) << "-" << endl << setfill(' ');

	stream << "Tabele su dobijene sortiranjem ulaznog fajla " << args.inputFilePath() << " sa kriterijumom " << CriteriumToString(args.criterium())
		<< ", " << OrderToString(args.order()) << " pomocu algoritma " << SortAlgorithmToString(args.sortAlgorithm()) <<
		". Ovi podaci su ispisani u konzoli i izlaznom fajlu " << args.outputFilePath() << "." << endl;
}

void printAllData(ostream& stream, vector<Flight> flights, Arguments args, vector<Info> infos) {
	printFlights(stream, flights);
	printGatheredData(stream, args, infos);
}

const string SortAlgorithmToString(SortAlgorithm sortAlgorithm) {
	switch (sortAlgorithm) {
	case SortAlgorithm::Selection: return "selection sort";
	case SortAlgorithm::Merge: return "merge sort";
	default: return "";
	}
}

const string CriteriumToString(Criterium criterium) {
	switch (criterium) {
	case Criterium::FlightNumber: return "flight number";
	case Criterium::Destination: return "destination";
	case Criterium::DepartureTime: return "departure time";
	case Criterium::GateNumber: return "gate number";
	default: return "";
	}
}

const string OrderToString(Order order) {
	switch (order) {
	case Order::Ascending: return "ascending";
	case Order::Descending: return "descending";
	default: return "";
	}
}


/*
	Funkcija koja pokrece mehanizam za sortiranje podataka odabranim algoritmom po odabranim kriterijumima i podacima. Argumenti:
	Arguments args: argumenti sortiranja (kriterijum, poredak, ulazni i izlazni fajl, korisceni algoritam)
*/
void sortFlights(Arguments args) {
	vector<Flight> data = loadFlights(args.inputFilePath());
	vector<Flight> originalData = vector<Flight>(data);

	if (args.sortAlgorithm() == SortAlgorithm::Selection) {
		SelectionSort sorter;
		performSort(args, data, originalData, &sorter);
	} else {
		MergeSort sorter;
		performSort(args, data, originalData, &sorter);
	}
}

void performSort(Arguments args, vector<Flight> data, vector<Flight> originalData, Sort* sorter) {
	vector<Info> infos = (*sorter).sort(data, args.criterium(), args.order());
	printAllData(cout, data, args, infos);
	ofstream file(args.outputFilePath());
	printAllData(file, data, args, infos);
	file.close();
	VisualizerWindow visualizerWindow(Point(25, 25), 600, "Vizuelizacija sortiranja",
		infos, data, originalData);
	gui_main();
}

/*
	Funkcija koja ucitava letove iz fajla u vektor letova i vraca ga. Argument:
	const string path: putanja do fajla koji sadrzi letove
*/
vector<Flight> loadFlights(const string path) {
	vector<Flight> flights;
	std::ifstream file(path);
	string line;
	std::getline(file, line);
	int i = 0;
	while (std::getline(file, line)) {
		if (i >= 10) {
			break;
		}
		flights.push_back(Flight(split(line, ';')));
		i++;
	}
	return flights;
}
