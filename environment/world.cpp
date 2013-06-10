#include "world.hpp"
#include <set>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

#ifdef TESTING_ENV
#include <iostream>
#include <fstream>
#endif

class vec_compare {
public:

    bool operator() (const Vec3& lhs, const Vec3& rhs) const {
        cout << "comparing " << lhs.GlobalLength() << " with " << rhs.GlobalLength() << endl;
        return lhs.GlobalLength() < rhs.GlobalLength();
    }
};

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
    cout << "building galaxy.." << endl;
    MakeSystems();
    colonize();
    cout << "finished building galaxy!" << endl;
}

Galaxy::~Galaxy() {
    for (int i = 0; i < _n_systems; i++) {
        delete _systems[i];
    }
    delete[] _systems;
}

void Galaxy::MakeSystems(void) {
    set<Vec3, vec_compare> points;
    set<Vec3, vec_compare>::iterator points_it;

    int next_jump = 30;
    int index = 0;

    Vec3 center(0, 0, 0);
    while (points.size() < (_n_systems - 1)) {
        Vec3 tmp(rand_gen.normal(), rand_gen.normal(), rand_gen.normal());
        while (tmp.LocalDistance(center) < next_jump - (next_jump / 2)) {
            tmp *= 1.5;
        }
        while (tmp.LocalDistance(center) > next_jump + ((next_jump * 2) - next_jump)) {
            tmp *= 0.75;
        }

        if (points.insert(tmp).second) {
            index++;
        } else {
            cout << "same point? @" << index << endl;
            //ERROR!!
        }
        if (index == next_jump) {
            next_jump = next_jump << 1;
        }
    }

    //make systems, will be sorted by distance to center
    _systems = new System*[_n_systems]();
    _systems[0] = new System(center, this);
    points_it = points.begin();
    for (int i = 1; i < _n_systems; i++) {
        _systems[i] = new System((*points_it++), this);
    }
}

void Galaxy::colonize(void) {
    const double max_distance = _systems[_n_systems - 1]->GetCenter().LocalLength();
    for (int idx = 0; idx < _n_systems; idx++) {
        unsigned int random = rand_gen.random();
        double val = 100 * ((double) random / (double) rand_gen.GetMax());
        double fak = pow(((max_distance - (_systems[idx]->GetCenter().LocalLength())) / max_distance), 4.0);
        double result = val * fak;
        if (result > _min_colonization) {
            _n_colonized_systems++;
            _systems[idx]->SetColonization(result);
        }
    }
#ifdef TESTING_ENV
    cout << "colonized systems: " << _n_colonized_systems << endl;
#endif
}

System** Galaxy::GetSystems(int& n) {
    n = _n_systems;
    return _systems;
}


//system

System::System(Vec3 center, Galaxy* parent) {
    _center = center;
    _colonization = 0;
    _parent = parent;
    _n_objects = 0;
    _objects = 0;
}

System::~System() {
    delete[] _connected_systems;
    if (_objects != 0) {
        for (int i = 0; i < _n_objects; i++) {
            delete _objects[i];
        }
        delete[] _objects;
    }
}

Vec3& System::GetCenter(void) {
    return _center;
}

void System::SetColonization(double value) {
    _colonization = value;
}

void Rotate(double angle, Vec3 & vec) {
    angle = angle * Ogre::Math::PI / 180;
    double x = vec[0];
    double z = vec[2];
    vec[0] = x * cos(angle) - z * sin(angle);
    vec[2] = x * sin(angle) + z * cos(angle);

}

double betrag(double in) {
    if (in < 0)
        return -in;
    return in;
}

void System::Init(void) {
    //todo: Initialize the world when someone enters the first time
    _n_objects = _parent->rand_gen.random(4, 14);
    Vec3 center(0, 0, 0);
    set<Vec3, vec_compare> points;
    set<Vec3, vec_compare>::iterator points_it;

    double next_jump, next_jump_t;
    int index = 0;
    double theta = 360 / (double) (_n_objects - 1);

    _objects = new StellarObject*[_n_objects];
    _objects[0] = new Star(center, Ogre::Vector3(0, 0.1, 0));
    next_jump = _objects[0]->GetRadius() * 5;
    next_jump_t = next_jump;

    while (points.size() < (_n_objects - 1)) {
        Vec3 tmp(0, _parent->rand_gen.normal(), _parent->rand_gen.gamma(7.0));
        while (tmp.distance(center) < next_jump - (next_jump / 2)) {
            tmp *= Vec3(0, 1.01, 1.5);
        }
        while (tmp.distance(center) > next_jump + ((next_jump * 2) - next_jump)) {
            tmp *= Vec3(0, 0.95, 0.75);
        }

        Rotate(theta * (index - 1) * betrag(_parent->rand_gen.normal()), tmp);

        if (points.insert(tmp).second) {
            cout << index++ << endl;
            next_jump += next_jump_t * betrag(_parent->rand_gen.normal());
        }
    }


    points_it = points.begin();
    for (int i = 1; i < _n_objects; i++) {
        int type_t = _parent->rand_gen.random(0, 30000);
        int type = 30000 / type_t;
        cout << type << endl;
        switch (type) {
            case 0:
                cout << "new asteroid" << endl;
                _objects[i] = new Asteroid((*points_it++), Ogre::Vector3(0, 0, 0));
                break;
            case 1:
                cout << "new planet" << endl;
                _objects[i] = new Planet((*points_it++), Ogre::Vector3(0, 0, 0));
                break;
            case 2:
                cout << "new giant" << endl;
                _objects[i] = new Giant((*points_it++), Ogre::Vector3(0, 0, 0));
                break;
            default:
                cout << "new planet" << endl;
                _objects[i] = new Planet((*points_it++), Ogre::Vector3(0, 0, 0));
                break;

        }
    }
}

void System::ConnectTo(int n_systems, System** systems) {
    _n_connections = n_systems;
    _connected_systems = systems;
}

StellarObject** System::GetObjects(int& n) {
    cout << "initializing..." << endl;
    if (_n_objects == 0) {
        fstream MyFile("system.txt", ios::out);
        Init();
        for (int i = 0; i < _n_objects; i++) {
            MyFile.precision(10);
            MyFile << _objects[i]->GetCenter()[0] << "\t" << _objects[i]->GetCenter()[1] << "\t" << _objects[i]->GetCenter()[2] << "\t" << _objects[i]->GetRadius() << "\t";
            MyFile << sqrt(pow((float) _objects[i]->GetCenter()[0], 2.0) + pow((float) _objects[i]->GetCenter()[2], 2.0)) << endl;
        }
        MyFile.close();
    }
    cout << "INITIALZED!!!!" << endl;
    n = _n_objects;
    return _objects;
}