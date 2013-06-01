#include "world.hpp"
#include <cstdlib>
#include <ctime>
#include <set>
#include <fstream>

#ifndef NODEBUG
#include <iostream>
#endif

using namespace std;

//galaxy

Galaxy* Galaxy::_instance = 0;

Galaxy& Galaxy::GetGalaxy(const int& n_systems, const int& seed, bool seeded) {
	if (Galaxy::_instance == 0) {
		Galaxy::_instance = new Galaxy(n_systems,seed,seeded);
	}
	return (*Galaxy::_instance);
}

int RandomSign() {
	int tmp = (rand() % 100) - 50;
	int tmp2 = int(tmp <= 0);
	if (tmp2 == 0)
		tmp2 = -1;
	return tmp2;
}

Galaxy::Galaxy(const int& n_systems, const int& seed, bool seeded) {
	fstream MyFile("test.txt",ios::out);
	set<Ordinate> points;
	set<Ordinate>::iterator points_it;
	int this_seed;
	double tmp = 0;
	_n_systems = n_systems;

	if (seeded) {
		this_seed = seed;
	} else {
		srand(time(0));
		this_seed = rand();
	}
	
	int i = 1;
	while (points.size() < (n_systems - 1)) {
		points.insert(Ordinate(double(rand()) * (double(rand()) / double((rand()+1))) * RandomSign(),double(rand()) * (double(rand()) / double((rand()+1))) * RandomSign(),double(rand()) * (double(rand()) / double((rand()+1))) * RandomSign()));
	}

	srand(this_seed);
	_systems = new System*[_n_systems];
	_systems[0] = new System(Ordinate(0,0,0));
	MyFile << _systems[0]->GetCenter().GetOrdinates(X) << " " << _systems[0]->GetCenter().GetOrdinates(Y) << " " << _systems[0]->GetCenter().GetOrdinates(Z) << endl;
	points_it = points.begin();
	for (int i=1; i < _n_systems; i++) {
		_systems[i] = new System((*points_it++));
		MyFile << _systems[i]->GetCenter().GetOrdinates(X) << " " << _systems[i]->GetCenter().GetOrdinates(Y) << " " << _systems[i]->GetCenter().GetOrdinates(Z) << endl;
	}

	for (int i=1; i < _n_systems; i++) {
		tmp += _systems[0]->GetCenter().Distance(_systems[i]->GetCenter());
		cout << tmp << endl;
	}

	cout << "Average Distance of Systems: " << tmp / double(n_systems) << endl;

	MyFile.close();
};

Galaxy::~Galaxy() {
	for (int i=0; i < _n_systems; i++) {
		delete _systems[i];
	}
	delete[] _systems;
}


//system
System::System(Ordinate center) {
	_center = center;
}

Ordinate& System::GetCenter(void) {
	return _center;
}

void System::SetColonization(double value) {
	_colonization = value;
}

void Init(void) {
	//todo: Initialize the world when someone enters the first time
}