#include "Engine.h"
#include "Utility/DebugDraw.h"
#include "Utility/Time.h"
#include "Events/EventsHandler.h"
using Utility::Time;
#include "../Game/Entities/TestPlayer.h"

Engine::Engine()
	: isRunning(false)
	, window(nullptr)
	, camera(nullptr)
	, player(nullptr) { }

Engine::~Engine() { }


void Engine::Run() {
	// dont try to run again if it already is
	if (isRunning) return;

	// OnCreate
	OnCreate();

	Time::GetSingleton()->Start();
	isRunning = true;
	while (isRunning) {
		// update time
		Time::GetSingleton()->UpdateGameTicks();

		// poll events
		Events::EventHandler::GetSingleton()->PollEvents();

		// update
		Update(Time::GetSingleton()->GetDeltaTime());

		// physics update
		PhysicsUpdate();

		// draw event
		Draw();

	}

	// OnDestroy
	OnDestroy();
	isRunning = false;
}

void Engine::OnCreate() {
	// create components
	window = new Graphics::Window();
	window->OnCreate("2D Platformer Engine", 900, 900); // needs to be first

	Utility::DebugDraw::GetSingleton()->OnCreate();

	/// create camera
	camera = new Objects::Camera();
	camera->SetOrtho(900.0f, 900.0f, 20.0f, -20.0f);

	/// create player
	Game::Player* p = new Game::Player();
	player = p;
	p->OnCreate();
	p->SetCamera(camera);

}

void Engine::OnDestroy() {

	// destroy player
	if (player) {
		player->OnDestroy();
		delete player; player = nullptr;
	}
	// destroy camera
	if (camera) delete camera; camera = nullptr;

	// destroy singletons
	Utility::DebugDraw::GetSingleton()->OnDestroy();

	// destroy components
	if (window) delete window; window = nullptr; // needs to be last
}

void Engine::Update(const float& delta) {

	// update player
	player->Update(delta);

	using Utility::DebugDraw;

	// draw some random lines

	DebugDraw::DrawLine(vec2(60.0f, 80.0f), vec2(300.0f, 80.0f));
	DebugDraw::DrawLine(vec2(60.0f, 120.0f), vec2(300.0f, 120.0f));
	DebugDraw::DrawLine(vec2(60.0f, 80.0f), vec2(60.0f, 120.0f));
	DebugDraw::DrawLine(vec2(300.0f, 80.0f), vec2(300.0f, 120.0f));
}

void Engine::PhysicsUpdate() {

	// does nothing

}

void Engine::Draw() {
	// clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// start draw

	player->Draw(camera->GetView(), camera->GetOrtho());

	/// end draw

	// draw debug lines
	Utility::DebugDraw::GetSingleton()->DrawShapes(camera->GetView(), camera->GetOrtho());

	// swap buffers
	SDL_GL_SwapWindow(window->GetWindow());
	// wait for the end of the frame
	SDL_Delay(Time::GetSingleton()->GetSleepTime(60));
}
