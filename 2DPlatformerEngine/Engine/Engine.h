#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H
#include "Common.h"
#include "Utility/Time.h"
#include "Graphics/Window.h"

class Engine {
	SINGLETON(Engine);


	bool isRunning;

	/// components
	Graphics::Window* window;

public:

	// starts the engine
	void Run();

private:

	/// events

	void OnCreate();
	void OnDestroy();
	void PollEvents();
	void Update(const float& delta);
	void PhysicsUpdate();
	void Draw();

};

#endif // !ENGINE_ENGINE_H