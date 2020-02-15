#ifndef UTILITY_TIME_H
#define UTILITY_TIME_H
#include "../Common.h"

namespace Utility {

	class Time {
		SINGLETON(Time);

		// time related variables
		uint prevTicks, currentTicks;

	public:

		// member functions
		void Start();
		void UpdateGameTicks();
		float GetDeltaTime() const;
		unsigned int GetSleepTime(const uint fps_);
		float GetCurrentTicks();
		void AdjustCurrentTime(uint timeStamp);

	};

}

#endif // !UTILITY_TIME_H