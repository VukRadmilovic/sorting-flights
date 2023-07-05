//============================================================================
// Name        : MyWindow.cpp
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Implementation of the MyWindow class
//============================================================================
#include "MyWindow.h"


using Graph_lib::reference_to;

/*
	Konstruktor koji inicijalizuje prozor koji se koristi za unos podataka za sortiranje
*/
MyWindow::MyWindow(Point xy, int w, int h, const string& title) :
	Window(xy, w, h, title),
	sortButton(Point(x_max() / 2 - 40, 250), 80, 40, "Sortiraj", cbSort),
	sortPushed(false)
{
	attach(sortButton);
}

/*
	Funkcija koja ceka da dugme bude pritisnuto i vraca da li je ono pritisnuto.
*/
bool MyWindow::wait_for_button()
{
	show();
	sortPushed = false;

	while (!sortPushed)
		Fl::wait();
	Fl::redraw();

	return sortPushed;
}

void MyWindow::cbSort(Address, Address pw)
{
	reference_to<MyWindow>(pw).sort();
}

void MyWindow::sort()
{
	sortPushed = true;
	hide();
}