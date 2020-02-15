#include "Engine.h"
#include "Utility/DebugDraw.h"
#include "Utility/Time.h"
#include "Events/EventsHandler.h"
using Utility::Time;

Engine::Engine()
	: isRunning(false)
	, window(nullptr)
	, offset(0.0f) { }

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

	// bind input
	Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_W, &Engine::PressedUp, this);
	Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_S, &Engine::PressedDown, this);
	Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_A, &Engine::PressedLeft, this);
	Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_D, &Engine::PressedRight, this);
	Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_W, &Engine::ReleasedUp, this);
	Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_S, &Engine::ReleasedDown, this);
	Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_A, &Engine::ReleasedLeft, this);
	Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_D, &Engine::ReleasedRight, this);

}

void Engine::OnDestroy() {

	// unbind input
	Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_W, &Engine::PressedUp, this);
	Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_S, &Engine::PressedDown, this);
	Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_A, &Engine::PressedLeft, this);
	Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_D, &Engine::PressedRight, this);
	Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_W, &Engine::ReleasedUp, this);
	Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_S, &Engine::ReleasedDown, this);
	Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_A, &Engine::ReleasedLeft, this);
	Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_D, &Engine::ReleasedRight, this);

	// destroy singletons
	Utility::DebugDraw::GetSingleton()->OnDestroy();

	// destroy components
	if (window) delete window; window = nullptr; // needs to be last
}

void Engine::Update(const float& delta) {

	if (up != down) {
		if (up) offset.y += delta;
		if (down) offset.y -= delta;
	}
	if (right != left) {
		if (right) offset.x += delta;
		if (left) offset.x -= delta;
	}

	// draws a line
	Utility::DebugDraw::DrawLine(vec2(-0.5f, -0.5f) + offset, vec2(-0.5f, 0.5f) + offset, Graphics::Color::CYAN);
	Utility::DebugDraw::DrawLine(vec2(-0.5f, 0.5f) + offset, vec2(0.5f, 0.5f) + offset, Graphics::Color::CYAN);
	Utility::DebugDraw::DrawLine(vec2(0.5f, 0.5f) + offset, vec2(0.5f, -0.5f) + offset, Graphics::Color::CYAN);
	Utility::DebugDraw::DrawLine(vec2(0.5f, -0.5f) + offset, vec2(-0.5f, -0.5f) + offset, Graphics::Color::CYAN);

}

void Engine::PhysicsUpdate() {

	// does nothing

}

void Engine::Draw() {
	// clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Utility::DebugDraw::GetSingleton()->DrawShapes();

	// start draw



	// end draw

	// swap buffers
	SDL_GL_SwapWindow(window->GetWindow());
	// wait for the end of the frame
	SDL_Delay(Time::GetSingleton()->GetSleepTime(60));
}
