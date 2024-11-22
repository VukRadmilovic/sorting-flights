//============================================================================
// Name        : Sort.cpp
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   : 
// Description : Implementation of the sort classes with some helper functions
//============================================================================

#include "Sort.h"

using namespace std;

void swap(Flight& f1, Flight& f2) {
	Flight temp = f1;
	f1 = f2;
	f2 = temp;
}

int min(int x1, int x2) {
	return (x1 < x2) ? x1 : x2;
}

void resetOriginalIndexes(vector<Flight>& data) {
	for (int i = 0; i < data.size(); i++) {
		data[i].originalIndex = i;
	}
}

/*
	Funkcija koja sortira vektor letova po specificiranom kriterijumu i poretku pomocu selection sorta.
	vector<Flight>& data: vektor letova koji treba da bude sortiran
	Criterium criterium: kriterijum po kome sortiramo
	Order order: poredak tj. da li je rastuci ili padajuci
	Funkcija vraca vektor informacija o podacima prikupljenim prilikom svake iteracije sortiranja, dok se samo sortiranje vrsi in-place.
*/
vector<Info> SelectionSort::sort(vector<Flight>& data, Criterium criterium, Order order) {
	vector<Info> infos;
	for (int i = 0; i < data.size() - 1; i++) {
		Info info;
		int z = i;
		for (int j = i + 1; j < data.size(); j++) {
			int comparison = data[j].compare(data[z], criterium);
			info.numCmps++;

			if ((comparison < 0 && order == Order::Ascending) ||
				(comparison > 0 && order == Order::Descending)) {
				z = j;
			}
		}
		if (i != z) {
			info.numMoves += 2;
			info.changes[i] = z;
			info.changes[z] = i;
			swap(data[i], data[z]);
		}
		infos.push_back(info);
	}
	return infos;
}

/*
	Funkcija koja sortira vektor letova po specificiranom kriterijumu i poretku pomocu merge sorta.
	vector<Flight>& data: vektor letova koji treba da bude sortiran
	Criterium criterium: kriterijum po kome sortiramo
	Order order: poredak tj. da li je rastuci ili padajuci
	Funkcija vraca vektor informacija o podacima prikupljenim prilikom svake iteracije sortiranja, dok se samo sortiranje vrsi in-place.
*/
vector<Info> MergeSort::sort(vector<Flight>& data, Criterium criterium, Order order) {
	vector<Info> infos;
	int n = data.size();

	for (int currentSize = 1; currentSize < n; currentSize *= 2) {
		Info info;
		for (int left = 0; left < n - 1; left += 2 * currentSize) {
			int mid = min(left + currentSize - 1, n - 1);

			int right = min(left + 2 * currentSize - 1, n - 1);
			
			merge(data, left, mid, right, criterium, order, info);
		}
		infos.push_back(info);
	}

	return infos;
}

/*
	Funkcija koju koristi merge sort prilikom sortiranja. Ona spaja dva dela vektora ali po sortiranom redosledu.
	vector<Flight>& data: vektor letova koji treba da bude sortiran
	int left: indeks leve granice niza za spajanje - data[left do mid]
	int mid: indeks srednje granice niza za spajanje
	int right: indeks desne granice niza za spajanje - data[mid + 1 do right]
	Criterium criterium: kriterijum po kome sortiramo
	Order order: poredak tj. da li je rastuci ili padajuci
	Info& info: objekat informacija o trenutnoj iteraciji sortiranja koji azuriramo tokom sortiranja
*/
void MergeSort::merge(vector<Flight>& data, int left, int mid, int right, Criterium criterium, Order order, Info& info) {
	resetOriginalIndexes(data);

	int i, j, k;
	int leftN = mid - left + 1;
	int rightN = right - mid;

	Flight* L = new Flight[leftN]; // pravimo privremene nizove koji ce predstaviti levi i desni deo niza koji zatim mergeujemo po sortiranom redosledu
	Flight* R = new Flight[rightN];
	
	for (i = 0; i < leftN; i++) { // ubacujemo podatke u te privremene nizove
		L[i] = data[left + i];
	}
	for (j = 0; j < rightN; j++) {
		R[j] = data[mid + 1 + j];
	}

	i = 0;
	j = 0;
	k = left;
	
	while (i < leftN && j < rightN) { // ovde vrsimo samo mergeovanje podataka u niz po pravilnom sortiranom redosledu tako sto ih poredimo sa svakom iteracijom
		int comparison = L[i].compare(R[j], criterium);
		info.numCmps++;

		if ((comparison <= 0 && order == Order::Ascending) ||
			(comparison >= 0 && order == Order::Descending)){
			data[k] = L[i];
			i++;
		} else {
			data[k] = R[j];
			j++;
		}
		if (data[k].originalIndex != k) {
			info.numMoves++;
			info.changes[data[k].originalIndex] = k;
		}
		k++;
	}

	while (i < leftN) { // ono sto ostane od leve strane se ubacuje na kraj
		data[k] = L[i];
		if (data[k].originalIndex != k) {
			info.numMoves++;
			info.changes[data[k].originalIndex] = k;
		}
		i++;
		k++;
	}

	while (j < rightN) { // ono sto ostane od desne strane se ubacuje na kraj
		data[k] = R[j];
		if (data[k].originalIndex != k) {
			info.numMoves++;
			info.changes[data[k].originalIndex] = k;
		}
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}