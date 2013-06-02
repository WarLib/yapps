#ifndef _WORLD_HPP
#define _WORLD_HPP

#include "ordinates.hpp"
#include "pred_random.hpp"


using namespace std;

class System {
private:
	Ordinate _center;


	int _n_connections;
	System** _connected_systems;
public:
	double _colonization;
	System(Ordinate center);
	~System();
	Ordinate& GetCenter(void);

	void SetColonization(double value);
	void Init(void);

	void ConnectTo(int n_systems, System** systems);
};

class Galaxy {
private:
	static Galaxy* _instance;
	Random& rand_gen;

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
	static Galaxy& GetGalaxy(const int& n_systems, double min_colonization = 10.5, const string& seed = "magicalrootseed", bool seeded = false);
	System** GetSystems(int& n);
	~Galaxy();
};

#endif
