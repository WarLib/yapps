#include "world.hpp"
#include <set>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

#ifndef NODEBUG
#include <iostream>
#endif

using namespace std;

//galaxy

Galaxy* Galaxy::_instance = 0;

Galaxy& Galaxy::GetGalaxy(const int& n_systems, double min_colonization, const string& seed, bool seeded) {
    if (Galaxy::_instance == 0) {
        Galaxy::_instance = new Galaxy(n_systems, min_colonization, seed, seeded);
    }
    return (*Galaxy::_instance);
}

Galaxy::Galaxy(const int& n_systems, double min_colonization, const string& seed, bool seeded) : rand_gen(Random::Instance()) {
    string this_seed;
    _n_systems = n_systems;
    _min_colonization = min_colonization;
    _n_colonized_systems = 0;

    if (seeded) {
        this_seed = seed;
        rand_gen.init(seed);
    } else {
        this_seed = rand_gen.MakeSeed();
    }

    //generate n random, unique points and spread them with rising distance around the center
    MakeSystems();
    colonize();
}

Galaxy::~Galaxy() {
    for (int i = 0; i < _n_systems; i++) {
        delete _systems[i];
    }
    delete[] _systems;
}

void Galaxy::MakeSystems(void) {
    set<Ordinate> points;
    set<Ordinate>::iterator points_it;

    int next_jump = 30;
    int index = 0;

    Ordinate center(0, 0, 0);
    while (points.size() < (_n_systems - 1)) {
        Ordinate tmp(rand_gen.normal(), rand_gen.normal(), rand_gen.normal());
        while (tmp.Distance(center) < next_jump - (next_jump / 2)) {
            tmp *= 1.5;
        }
        while (tmp.Distance(center) > next_jump + ((next_jump * 2) - next_jump)) {
            tmp *= 0.75;
        }

        if (points.insert(tmp).second) {
            index++;
        }
        if (index == next_jump) {
            next_jump = next_jump << 1;
        }
    }

    //make systems, will be sorted by distance to center
    _systems = new System*[_n_systems]();
    _systems[0] = new System(center);
    points_it = points.begin();
    for (int i = 1; i < _n_systems; i++) {
        _systems[i] = new System((*points_it++));
    }
}

void Galaxy::colonize(void) {
    const double max_distance = _systems[_n_systems - 1]->GetCenter().Value();
    for (int idx = 0; idx < _n_systems; idx++) {
        unsigned int random = rand_gen.random();
        double val = 100 * ((double) random / (double) rand_gen.GetMax());
        double fak = pow(((max_distance - (_systems[idx]->GetCenter().Value())) / max_distance), 4.0);
        double result = val * fak;
        if (result > _min_colonization) {
            _n_colonized_systems++;
            _systems[idx]->SetColonization(result);
        }
    }
#ifndef NODEBUG    
    cout << "colonized systems: " << _n_colonized_systems << endl;
#endif
}

System** Galaxy::GetSystems(int& n) {
	n = _n_systems;
	return _systems;
}


//system

System::System(Ordinate center) {
    _center = center;
    _colonization = 0;
}

System::~System() {
    delete[] _connected_systems;
}

Ordinate& System::GetCenter(void) {
    return _center;
}

void System::SetColonization(double value) {
    _colonization = value;
}

void System::Init(void) {
    //todo: Initialize the world when someone enters the first time
}

void System::ConnectTo(int n_systems, System** systems) {
    _n_connections = n_systems;
    _connected_systems = systems;
}