#ifndef EVENTS_EVENT_HANDLER_H
#define EVENTS_EVENT_HANDLER_H
#include "../Common.h"
#include <map>
#include <list>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "KeyCodeEnum.h"
#include <SDL_events.h>

namespace Events {

	class EventHandler {
		SINGLETON(EventHandler);

		typedef boost::function0<void> InputFunc;
		//typedef boost::function1<void, float> AxisFunc;

		// each key contains a list of functions to call
		std::map<Events::KeyCode, std::list<InputFunc>> inPressBindings;
		std::map<Events::KeyCode, std::list<InputFunc>> inReleaseBindings;

	public:

		/// get events

		void PollEvents();
		void ClearBindings();

		/// bind functions
		template<typename T>
		static void BindInputPressed(Events::KeyCode keyCode, void(T::* function)(), T* object);
		template<typename T>
		static void BindInputReleased(Events::KeyCode keyCode, void(T::* function)(), T* object);
		template<typename T>
		static void UnbindInputPressed(Events::KeyCode keyCode, void(T::* function)(), T* object);
		template<typename T>
		static void UnbindInputReleased(Events::KeyCode keyCode, void(T::* function)(), T* object);

	private:      

		/// functions

		void KeyboardEventUp(SDL_KeyboardEvent& ev);
		void KeyboardEventDown(SDL_KeyboardEvent& ev);

	};

	#pragma region Binding functions

	template<typename T>
	inline void EventHandler::BindInputPressed(Events::KeyCode keyCode, void(T::* function)(), T* object) {
		// insert into the list
		GetSingleton()->inPressBindings[keyCode].push_back(boost::bind(function, object));
	}

	template<typename T>
	inline void EventHandler::BindInputReleased(Events::KeyCode keyCode, void(T::* function)(), T* object) {
		// insert into the list
		GetSingleton()->inReleaseBindings[keyCode].push_back(boost::bind(function, object));
	}

	template<typename T>
	inline void EventHandler::UnbindInputReleased(Events::KeyCode keyCode, void(T::* function)(), T* object) {
		// create the function binding
		auto func = boost::bind(function, object);

		// remove that binding from the list
		GetSingleton()->inReleaseBindings[keyCode].remove_if([func](InputFunc& f)->bool {
			return f == func;
		});
	}

	template<typename T>
	inline void EventHandler::UnbindInputPressed(Events::KeyCode keyCode, void(T::* function)(), T* object) {
		// create the function binding
		auto func = boost::bind(function, object);

		// remove that binding from the list
		GetSingleton()->inPressBindings[keyCode].remove_if([func](InputFunc& f)->bool {
			return f == func;
		});
	}

	#pragma endregion

}

#endif // !EVENTS_EVENT_HANDLER_H