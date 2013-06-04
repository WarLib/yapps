#ifndef _WORLD_HPP
#define _WORLD_HPP

#include "ordinates.hpp"
#include "pred_random.hpp"
#include "star.hpp"
#include "Asteroid.hpp"
#include "planet.hpp"


using namespace std;

class Galaxy;

class System {
private:
	Ordinate _center;


	int _n_connections;
	int _n_objects;

	StellarObject** _objects;
	System** _connected_systems;

	Galaxy* _parent;
public:
	double _colonization;
	System(Ordinate center, Galaxy* parent);
	~System();
	Ordinate& GetCenter(void);

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
