#ifndef _WORLD_HPP
#define _WORLD_HPP

#include "ordinates.hpp"

using namespace std;

class System {
private:
	Ordinate _center;
	double _colonization;
public:
	System(Ordinate center);
	Ordinate& GetCenter(void);
	
	void SetColonization(double value);
	void Init(void);
};

class Galaxy {
private:
	static Galaxy* _instance;
	
	System** _systems;
	int _n_systems;
	
	Galaxy(const int& n_systems, const int& seed, bool seeded);
	Galaxy(const Galaxy& orig);
public:
	static Galaxy& GetGalaxy(const int& n_systems, const int& seed = 0, bool seeded = false);
	~Galaxy();
};

#endif
