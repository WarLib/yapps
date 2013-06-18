#ifndef _FPSCOUNTER_HPP
#define _FPSCOUNTER_HPP

#include <vector>

namespace Yapps {
	class FPSCounter {
	private:
		FPSCounter();
		FPSCounter(const FPSCounter& orig);

		static float* _last50frames;
		static FPSCounter _instance;
		std::vector<float> fps;
	public:

		~FPSCounter();

		static FPSCounter& GetInstance(void);
		void InjectTime(float);
		float GetFps();
	};
};


#endif