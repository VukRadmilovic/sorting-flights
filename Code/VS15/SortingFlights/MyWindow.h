//============================================================================
// Name        : MyWindow.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Class which defines the GUI used for inputting the sorting criterium and arguments
//============================================================================
#pragma once

#include "..\graph_lib\Window.h"

#include "GUI.h"
#include "Graph.h"

using Graph_lib::Window;
using Graph_lib::Button;
using Graph_lib::Address;

class MyWindow : public Window
{
public:
	MyWindow(Point xy, int w, int h, const string& title);
	bool wait_for_button(); // event loop

private:
	Button sortButton;     // dugme koje vodi do prikaza vizuelizacije sorta nakon provere greske
	bool sortPushed;       // da li je dugme pritisnuto

	static void cbSort(Address, Address); // callback za sortButton
	void sort(); // prelazimo na vizuelizaciju sorta kada sortButton bude pritisnut
};

