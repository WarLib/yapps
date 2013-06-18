#include "fpscounter.hpp"
#include <iostream>

using namespace Yapps;

float* FPSCounter::_last50frames = 0;
FPSCounter FPSCounter::_instance;

FPSCounter::FPSCounter() {
	_last50frames = new float[50];
}

FPSCounter::~FPSCounter() {
	double tmp = 0;
	delete[] _last50frames;
	for (int i = 0; i < fps.size(); i++) {
		tmp += fps[i];
	}
	tmp /= fps.size();
	std::cout << "AVERAGE FPS REGISTERED: " << tmp << std::endl;
}

FPSCounter& FPSCounter::GetInstance() {
	return _instance;
}

void FPSCounter::InjectTime(float time) {
	for (int i = 0; i < 49; i++) {
		_last50frames[i] = _last50frames[i + 1];
	}

	_last50frames[49] = time;
}

float FPSCounter::GetFps(void) {
	double overalltime = 0;
	double averagetime = 0;
	for (int i = 0; i < 50; i++) {
		overalltime += _last50frames[i];
	}
	averagetime = overalltime / 50;
	if (fps.size() >= 10000) {
		fps.erase(fps.begin());
	}
	fps.push_back(1/averagetime);
	return 1 / averagetime;
}