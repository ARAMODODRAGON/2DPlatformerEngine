#include "EventsHandler.h"
#include "../Utility/Time.h"
#include "../Engine.h"

namespace Events {

	EventHandler::EventHandler() { }
	EventHandler::~EventHandler() { }

	void EventHandler::ClearBindings() {
		inPressBindings.clear();
		inReleaseBindings.clear();
	}


	void EventHandler::PollEvents() {
		SDL_Event ev;
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
			case SDL_QUIT:
				// stop running
				Engine::Quit();
				break;
			case SDL_WINDOWEVENT:
				// the window delays the next update call, 
				// so this will adjust the time so we dont get a delta of 20 seconds
				Utility::Time::GetSingleton()->AdjustCurrentTime(ev.window.timestamp);
				break;
			case SDL_KEYUP:
				KeyboardEventUp(ev.key);
				break;
			case SDL_KEYDOWN:
				KeyboardEventDown(ev.key);
				break;

			default: break;
			}
		}
	}


	void EventHandler::KeyboardEventUp(SDL_KeyboardEvent& ev) {
		if (ev.repeat) return;
		KeyCode code = (KeyCode)ev.keysym.sym;

		// call every function when key is released
		for (InputFunc& func : inReleaseBindings[code]) func();

	}

	void EventHandler::KeyboardEventDown(SDL_KeyboardEvent& ev) {
		if (ev.repeat) return;
		KeyCode code = (KeyCode)ev.keysym.sym;

		// call every function when key is pressed
		for (InputFunc& func : inPressBindings[code]) func();

	}

}