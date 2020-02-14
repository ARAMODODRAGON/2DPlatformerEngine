#ifndef UTILITY_TIME_H
#define UTILITY_TIME_H
#include "../Common.h"

namespace Utility {

	class Time {

		// time related variables
		uint prevTicks, currentTicks;

	public:
		// constructor and destructor
		Time();
		~Time() { }

		// member functions
		void Start();
		void UpdateGameTicks();
		float GetDeltaTime() const;
		unsigned int GetSleepTime(const uint fps_);
		float GetCurrentTicks();
		void AdjustCurrentTime(uint timeStamp);

	public:
		// delete copy and move contructors/operators
		Time(const Time&) = delete;
		Time(Time&&) = delete;
		Time& operator=(const Time&) = delete;
		Time& operator=(Time&&) = delete;
	};

}

#endif // !UTILITY_TIME_H