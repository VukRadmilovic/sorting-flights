//============================================================================
// Name        : Info.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Class which defines the information gathered during sorting
//============================================================================
#pragma once

#include <unordered_map>

using std::unordered_map;

class Info {
public:
	unsigned long numCmps; // broj poredjenja napravljenih tokom sortiranja u ovoj iteraciji
	unsigned long numMoves; // broj promena pozicije elemenata
	unordered_map<int, int> changes; // promene pozicije elemenata predstavljene mapom ciji key je originalan indeks a value novi indeks
	Info() : numCmps(0), numMoves(0), changes(unordered_map<int, int>()) {};
};