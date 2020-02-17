#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H
#include "Common.h"
#include "Utility/Time.h"
#include "Graphics/Window.h"
#include "Math.h"
#include "Objects/Camera.h"
#include "Objects/Entity.h"

class Engine {
	SINGLETON(Engine);

	// the engine state
	bool isRunning;

	/// components
	Graphics::Window* window;

	/// camera
	Objects::Camera* camera;

	/// entity
	Objects::Entity* player;

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

};

#endif // !ENGINE_ENGINE_H