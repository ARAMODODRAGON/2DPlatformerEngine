#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H
#include "Common.h"
#include "Utility/Time.h"
#include "Graphics/Window.h"
#include "Math.h"

class Engine {
	SINGLETON(Engine);


	bool isRunning;

	vec2 offset;
	bool up = false, down = false, left = false, right = false;

	/// components
	Graphics::Window* window;

public:

	// starts the engine
	void Run();

	/// functions

	static void Quit() { GetSingleton()->isRunning = false; }


private:

	/// events

	void OnCreate();
	void OnDestroy();
	void Update(const float& delta);
	void PhysicsUpdate();
	void Draw();


	/// temp

	void PressedUp() { up = true; }
	void PressedDown() { down = true; }
	void PressedLeft() { left = true; }
	void PressedRight() { right = true; }
	void ReleasedUp() { up = false; }
	void ReleasedDown() { down = false; }
	void ReleasedLeft() { left = false; }
	void ReleasedRight() { right = false; }
};

#endif // !ENGINE_ENGINE_H