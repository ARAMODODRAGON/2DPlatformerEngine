#include <SDL.h>
#include "Engine/Engine.h"
//#include <boost/function.hpp>
//#include <map>
//#include <list>
//#include <boost/bind.hpp>
//#include "Engine/Events/EventsHandler.h"
//
//typedef boost::function0<void> InputFunc;
////typedef boost::function1<void, float> AxisFunc;
//
//// each key contains a list of functions to call
//std::map<Events::KeyCode, std::list<InputFunc>> inPressBindings;
//
//struct foo {
//
//	void test1() {
//		PRINT("test 1");
//	}
//};

int main(int argc, char* argv[]) {
	//
	//foo* f = new foo();
	//
	//inPressBindings[Events::KeyCode::KEY_A].push_back(boost::bind(&foo::test1, f));
	//
	//inPressBindings[Events::KeyCode::KEY_A].back()();
	//
	//auto func = boost::bind(&foo::test1, f);
	//
	//inPressBindings[Events::KeyCode::KEY_A].remove_if([func](InputFunc& f)->bool {
	//	return f == func;
	//});
	//
	//PRINT("Size: " + TEXT(inPressBindings[Events::KeyCode::KEY_A].size()));

	//inPressBindings[Events::KeyCode::KEY_A].back()();

	Engine::GetSingleton()->Run();

	return 0;
}