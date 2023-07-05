//============================================================================
// Name        : VisualizerWindow.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Class which defines the GUI for visualizing sorting algorithms
//============================================================================
#pragma once

#include "..\graph_lib\Window.h"

#include "GUI.h"
#include "Graph.h"
#include "Sort.h"
#include <string>
#include <iostream>

using Graph_lib::Window;
using Graph_lib::Button;
using Graph_lib::Circle;
using Graph_lib::Line;
using Graph_lib::Text;
using Graph_lib::Address;
using Graph_lib::Out_box;
using Graph_lib::Color;

class VisualizerWindow : public Window
{
public:
	VisualizerWindow(Point xy, int h, const string& title, vector<Info>& infos,
		vector<Flight>& data, vector<Flight>& originalData); // konstruktor bez sirine koji je prakticniji za koriscenje jer sirinu mozemo izracunati u zavisnosti od parametara i uzeti koliko nam je potrebno
	VisualizerWindow(Point xy, int w, int h, const string& title, vector<Info>& infos, 
		vector<Flight>& data, vector<Flight>& originalData);

private:
	int iterNum; // predstavlja na kojoj smo iteraciji po redu i koristi se da bi znali koja je sledeca/prosla prilikom simuliranja korak po korak

	vector<Flight> _data; // podaci nakon sortiranja
	vector<Flight> _originalData; // podaci pre sortiranja
	vector<Info> _infos; // informacije prikupljene prilikom sortiranja

	vector<vector<Circle*>> crcNodes; // krugovi koji oznacavaju poziciju elementa tokom iteracije
	vector<vector<Line*>> lnConnections; // linije koje povezuju krugove i oznacavaju pomeranje elemenata tokom iteracija
	vector<Out_box*> endBoxes; // "kutije" u koje postavljamo tekst za rezultantni niz sortiranih letova

	Button btnPrevious; // dugme koje vodi do simuliranja prosle iteracije
	Button btnNext; // dugme koje vodi do simuliranja sledece iteracije
	Button btnReset; // dugme koje resetuje simulaciju i vraca na pocetak
	Button btnSimulateToEnd; // dugme koje simulira sortiranje do kraja i prikazuje sve korake dotle

	void previous(); // funkcija koju dugme poziva da bi izvrsilo simuliranje prosle iteracije
	void next(); // funkcija koju dugme poziva da bi izvrsilo simuliranje sledece iteracije
	void reset(); // funkcija koju dugme poziva da bi izvrsilo resetovanje simulacije
	void simulateToEnd(); // funkcija koju dugme poziva da bi izvrsilo simuliranje do kraja

	void resetEndBoxes();  // funkcija koja resetuje sve krajnje kutije tako da se u njima vise ne nalazi krajnje stanje niza
	void setEndBoxes();  // funkcija koja namesta sve krajnje kutije tako da se u njima nalazi krajnje stanje niza

	static void cbPrevious(Address, Address); // callback funkcija za btnPrevious
	static void cbNext(Address, Address); // callback funkcija za btnNext
	static void cbReset(Address, Address); // callback funkcija za btnReset
	static void cbSimulateToEnd(Address, Address); // callback funkcija za btnSimulateToEnd
};

