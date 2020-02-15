#include "Time.h"
#include <SDL.h>

namespace Utility {

	Time::Time()
		: prevTicks(0), currentTicks(0) { }

	Time::~Time() { }

	void Time::Start() {
		// set ticks
		currentTicks = prevTicks = SDL_GetTicks();
	}

	void Time::UpdateGameTicks() {
		prevTicks = currentTicks;
		currentTicks = SDL_GetTicks();
	}

	float Time::GetDeltaTime() const {
		return static_cast<float>(currentTicks - prevTicks) / 1000.0f;
	}

	unsigned int Time::GetSleepTime(const uint fps_) {
		unsigned int milliperframe = 1000 / fps_;
		if (milliperframe == 0) return 0;

		unsigned int sleepTime = milliperframe - SDL_GetTicks();
		if (sleepTime > milliperframe) return milliperframe;

		return sleepTime;
	}

	float Time::GetCurrentTicks() {
		return static_cast<float>(currentTicks);
	}

	void Time::AdjustCurrentTime(uint timeStamp) {
		prevTicks += timeStamp - currentTicks;
		currentTicks = timeStamp;
	}


}