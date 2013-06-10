#ifndef _WORLD_HPP
#define _WORLD_HPP

#include "ordinates.hpp"
#include "pred_random.hpp"
#include "star.hpp"
#include "Asteroid.hpp"
#include "planet.hpp"
#include "giants.hpp"

using namespace std;
using namespace Yapps;

class Galaxy;

class System {
private:
	Vec3 _center;


	int _n_connections;
	int _n_objects;

	StellarObject** _objects;
	System** _connected_systems;

	Galaxy* _parent;
public:
	double _colonization;
	System(Vec3 center, Galaxy* parent);
	~System();
	Vec3& GetCenter(void);

	void SetColonization(double value);
	void Init(void);

	void ConnectTo(int n_systems, System** systems);
	StellarObject** GetObjects(int& n);
};

class Galaxy {
private:
	static Galaxy* _instance;
	

	System** _systems;
	int _n_systems;
	int _n_connections;
	double _min_colonization;

	int _n_colonized_systems;
	double _overall_colonization;
	double _average_colonization;

	Galaxy(const int& n_systems, double min_colonization, const string& seed, bool seeded);
	Galaxy(const Galaxy& orig);

	void colonize();
	void MakeSystems();
public:
	Random& rand_gen;
	static Galaxy& GetGalaxy(const int& n_systems, double min_colonization = 10.5, const string& seed = "magicalrootseed", bool seeded = false);
	System** GetSystems(int& n);
	~Galaxy();
};

#endif
