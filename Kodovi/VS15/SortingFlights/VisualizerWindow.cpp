//============================================================================
// Name        : VisualizerWindow.cpp
// Author      : Vuk Radmilovic SV73/2020
// Date        : 2.1.2022.
// Copyright   :
// Description : Implementation of the VisualizerWindow class.
//============================================================================
#include "VisualizerWindow.h"

using Graph_lib::reference_to;

const int radius = 8;

/*
	Dinamicko racunanje sirine prozora
	vector<Info>& infos: vektor prikupljenih podataka tokom sortiranja na osnovu koga odredjujemo kolika sirina nam je potrebna
	Vraca se potrebna sirina prozora
*/
int calculateWidth(vector<Info>& infos) {
	return 460 + infos.size() * 75;
}

string visualizationHeader() {
	return "Destinacija;Vreme polaska;Br. leta;Br. izlaza";
}

void VisualizerWindow::cbPrevious(Address, Address pw) {
	reference_to<VisualizerWindow>(pw).previous();
}

void VisualizerWindow::cbNext(Address, Address pw) {
	reference_to<VisualizerWindow>(pw).next();
}

void VisualizerWindow::cbReset(Address, Address pw) {
	reference_to<VisualizerWindow>(pw).reset();
}

void VisualizerWindow::cbSimulateToEnd(Address, Address pw) {
	reference_to<VisualizerWindow>(pw).simulateToEnd();
}

void VisualizerWindow::resetEndBoxes() {
	for (int i = 0; i < endBoxes.size(); i++) {
		(*endBoxes[i]).put("");
	}
}

void VisualizerWindow::setEndBoxes() {
	for (int i = 0; i < endBoxes.size(); i++) {
		(*endBoxes[i]).put(_data[i].visualizationDisplay());
	}
}

void VisualizerWindow::previous() { // prelaz na proslu iteraciju
	if (iterNum > 0) {
		if (iterNum == _infos.size()) {
			resetEndBoxes();
		}
		iterNum--;
		for (int i = 0; i < _data.size(); i++) {
			detach(*lnConnections[iterNum][i]);
		}
		redraw();
	}
}

void VisualizerWindow::next() { // prelaz na sledecu iteraciju
	if (iterNum < _infos.size()) {
		for (int i = 0; i < _data.size(); i++) {
			attach(*lnConnections[iterNum][i]);
		}
		iterNum++;
		if (iterNum == _infos.size()) {
			setEndBoxes();
		}
		redraw();
	}
}

void VisualizerWindow::reset() { // brisanje svih linija koje povezuju nodeove
	for (int i = 0; i < _infos.size(); i++) {
		for (int j = 0; j < _data.size(); j++) {
			detach(*lnConnections[i][j]);
		}
	}
	redraw();
	iterNum = 0;
	resetEndBoxes();
}

void VisualizerWindow::simulateToEnd() { // prikaz svih linija koje povezuju nodeove
	for (int i = 0; i < _infos.size(); i++) {
		for (int j = 0; j < _data.size(); j++) {
			attach(*lnConnections[i][j]);
		}
	}
	redraw();
	iterNum = _infos.size();
	setEndBoxes();
}

VisualizerWindow::VisualizerWindow(Point xy, int h, const string& title, vector<Info>& infos,
	vector<Flight>& data, vector<Flight>& originalData) :
	VisualizerWindow(xy, calculateWidth(infos), h, title, infos, data, originalData) {};

/*
	Konstruktor koji formira prozor koji ce vrsiti vizuelizaciju sortiranja letova po korisnikovim kriterijumima. Lista argumenata:
	Point xy: offset prozora
	int w: sirina prozora
	int h: visina prozora
	const string& title: naslov prozora
	vector<Info>& infos: vektor informacija prikupljenih prilikom sortiranja
	vector<Flight>& data: vektor letova posle sortiranja
	vector<Flight>& originalData: vektor letova pre sortiranja
*/
VisualizerWindow::VisualizerWindow(Point xy, int w, int h, const string& title, vector<Info>& infos,
	vector<Flight>& data, vector<Flight>& originalData) :
	Window(xy, w, h, title),
	_infos(infos),
	_data(data),
	_originalData(originalData), 
	btnPrevious(Point(w * 0.1, 525), w * 0.15, 50, "Prosla iteracija", cbPrevious),
	btnNext(Point(w * 0.316, 525), w * 0.15, 50, "Sledeca iteracija", cbNext),
	btnReset(Point(w * 0.533, 525), w * 0.15, 50, "Reset", cbReset),
	btnSimulateToEnd(Point(w * 0.75, 525), w * 0.15, 50, "Simuliraj do kraja", cbSimulateToEnd),
	iterNum(0)
{
	Text* txtStart = new Text(Point(3, 30), visualizationHeader()); // kreiranje headera za podatke sa pocetka sortiranja
	(*txtStart).set_font_size(12);
	(*txtStart).set_color(Color::black);
	attach(*txtStart);
	Text* txtEnd = new Text(Point(w - 245, 30), visualizationHeader()); // kreiranje headera za podatke sa kraja sortiranja
	(*txtEnd).set_font_size(12);
	(*txtEnd).set_color(Color::black);
	attach(*txtEnd);

	Text* txtIters = new Text(Point(w * 0.48, 25), "Broj iteracije:");
	(*txtIters).set_color(Color::black);
	attach(*txtIters);

	for (int i = 0; i < originalData.size(); i++) {
		Out_box* boxStart = new Out_box(Point(15, 50 + i * 45), 215, 37, ""); // kreiranje "kutija" koji cuvaju podatke sa pocetka sortiranja
		attach(*boxStart);
		(*boxStart).put(originalData[i].visualizationDisplay());

		Out_box* boxEnd = new Out_box(Point(w - 230, 50 + i * 45), 215, 37, "");   // kreiranje "kutija" koji ce cuvati podatke sa kraja sortiranja
		attach(*boxEnd);
		endBoxes.push_back(boxEnd);
	}

	int circleWidthOffset = 250;
	int txtWidthOffset = 246;
	
	if (infos.size() > 5) {
		circleWidthOffset = 265;
		txtWidthOffset = 261;
	}

	for (int i = 0; i < infos.size() + 1; i++) { // formiranje krugova koji predstavljaju poziciju elementa u odredjenoj iteraciji
		vector<Circle*> circles;
		for (int j = 0; j < data.size(); j++) {
			Circle* circle = new Circle(Point(circleWidthOffset + i * 66, 68 + j * 45), radius);
			(*circle).set_color(Color::black);
			attach(*circle);
			circles.push_back(circle);
		}
		crcNodes.push_back(circles);
		Text* txtIter = new Text(Point(txtWidthOffset + i * 66, 47), to_string(i)); // kreiranje labela koji oznacavaju redni broj iteracije
		(*txtIter).set_color(Color::black);
		attach(*txtIter);
	}

	attach(btnPrevious);
	attach(btnNext);
	attach(btnReset);
	attach(btnSimulateToEnd);

	for (int i = 0; i < infos.size(); i++) { // formiranje linija koje predstavljaju promenu pozicije elemenata tokom iteracija
		vector<Line*> lines;
		for (int j = 0; j < data.size(); j++) {
			int nextNode = j;
			try {
				nextNode = infos[i].changes.at(j);
			}
			catch (out_of_range o) {};
			
			Point p1((*crcNodes[i][j]).center().x + radius, (*crcNodes[i][j]).center().y);
			Point p2((*crcNodes[i + 1][nextNode]).center().x - radius, (*crcNodes[i + 1][nextNode]).center().y);
			Line* line = new Line(p1, p2);
			(*line).set_color(Color::black);
			lines.push_back(line);
		}
		lnConnections.push_back(lines);
	}
}
