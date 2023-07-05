//============================================================================
// Name        : Criterium.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Header file that contains enum classes used to describe the user's criterium for sorting.
//============================================================================
#pragma once
#include <string>

using std::string;

enum class SortAlgorithm { Selection = 1, Merge };

enum class Criterium { FlightNumber = 1, Destination, DepartureTime, GateNumber }; // po cemu sortiramo?

enum class Order { Ascending = 1, Descending };
