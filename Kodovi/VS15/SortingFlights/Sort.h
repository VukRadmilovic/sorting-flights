//============================================================================
// Name        : Sort.h
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   : 
// Description : Sort interface class and selection & merge sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include "Info.h"
#include <vector>

// Sort class
class Sort
{
public:
	// main entry point
	virtual vector<Info> sort(vector<Flight>& data, Criterium criterium, Order order) = 0;
};

// SelectionSort class
class SelectionSort : public Sort
{
public:
	// main entry point
	vector<Info> sort(vector<Flight>& data, Criterium criterium, Order order);
};

// MergeSort class
class MergeSort : public Sort
{
public:
	vector<Info> sort(vector<Flight>& data, Criterium criterium, Order order);
	void merge(vector<Flight>& data, int left, int mid, int right, Criterium criterium, Order order, Info& info);
};