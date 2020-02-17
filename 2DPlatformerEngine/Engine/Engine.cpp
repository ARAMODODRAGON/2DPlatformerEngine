#include "Engine.h"
#include "Utility/DebugDraw.h"
#include "Utility/Time.h"
#include "Events/EventsHandler.h"
using Utility::Time;

Engine::Engine()
	: isRunning(false)
	, window(nullptr)
	, camera(nullptr)
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

	/// create camera
	camera = new Objects::Camera2D();
	camera->SetOrtho(900.0f, 900.0f, 20.0f, -20.0f);

	// bind input
	{
		Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_W, &Engine::PressedUp, this);
		Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_S, &Engine::PressedDown, this);
		Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_A, &Engine::PressedLeft, this);
		Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_D, &Engine::PressedRight, this);
		Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_E, &Engine::PressedCW, this);
		Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_Q, &Engine::PressedCCW, this);

		Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_W, &Engine::ReleasedUp, this);
		Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_S, &Engine::ReleasedDown, this);
		Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_A, &Engine::ReleasedLeft, this);
		Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_D, &Engine::ReleasedRight, this);
		Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_E, &Engine::ReleasedCW, this);
		Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_Q, &Engine::ReleasedCCW, this);
	}
}

void Engine::OnDestroy() {

	// unbind input
	{
		Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_W, &Engine::PressedUp, this);
		Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_S, &Engine::PressedDown, this);
		Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_A, &Engine::PressedLeft, this);
		Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_D, &Engine::PressedRight, this);
		Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_E, &Engine::PressedCW, this);
		Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_Q, &Engine::PressedCCW, this);

		Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_W, &Engine::ReleasedUp, this);
		Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_S, &Engine::ReleasedDown, this);
		Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_A, &Engine::ReleasedLeft, this);
		Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_D, &Engine::ReleasedRight, this);
		Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_E, &Engine::ReleasedCW, this);
		Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_Q, &Engine::ReleasedCCW, this);
	}

	// destroy camera
	if (camera) delete camera; camera = nullptr;

	// destroy singletons
	Utility::DebugDraw::GetSingleton()->OnDestroy();

	// destroy components
	if (window) delete window; window = nullptr; // needs to be last
}

void Engine::Update(const float& delta) {

	using Utility::DebugDraw;

	if (up != down) {
		if (up) offset.y += delta * 100.0f;
		if (down) offset.y -= delta * 100.0f;
	}
	if (right != left) {
		if (right) offset.x += delta * 100.0f;
		if (left) offset.x -= delta * 100.0f;
	}

	if (rotateCCW != rotateCW) {
		float rot = camera->GetRotation();

		if (rotateCCW)
			rot -= delta;
		if (rotateCW)
			rot += delta;

		camera->SetRotation(rot);
	}

	// update cameras position

	camera->SetPosition(offset);

	// draws a line
	DebugDraw::DrawLine(vec2(-30.0f, -30.0f) + offset, vec2(-30.0f, 30.0f) + offset, Graphics::Color::CYAN);
	DebugDraw::DrawLine(vec2(-30.0f, 30.0f) + offset, vec2(30.0f, 30.0f) + offset, Graphics::Color::CYAN);
	DebugDraw::DrawLine(vec2(30.0f, 30.0f) + offset, vec2(30.0f, -30.0f) + offset, Graphics::Color::CYAN);
	DebugDraw::DrawLine(vec2(30.0f, -30.0f) + offset, vec2(-30.0f, -30.0f) + offset, Graphics::Color::CYAN);

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

	Utility::DebugDraw::GetSingleton()->DrawShapes(camera->GetOrtho(), camera->GetView());

	// start draw



	// end draw

	// swap buffers
	SDL_GL_SwapWindow(window->GetWindow());
	// wait for the end of the frame
	SDL_Delay(Time::GetSingleton()->GetSleepTime(60));
}
