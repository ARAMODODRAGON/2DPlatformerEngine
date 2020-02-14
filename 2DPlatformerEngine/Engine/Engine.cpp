#include "Engine.h"
#include "Utility/DebugDraw.h"

Engine::Engine()
	: isRunning(false)
	, time(nullptr)
	, window(nullptr) { }

Engine::~Engine() { }


void Engine::Run() { 
	// dont try to run again if it already is
	if (isRunning) return;

	// OnCreate
	OnCreate();

	time->Start();
	isRunning = true;
	while (isRunning) {
		// update time
		time->UpdateGameTicks();

		// poll events
		PollEvents();

		// update
		Update(time->GetDeltaTime());

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
	time = new Utility::Time();

	Utility::DebugDraw::GetSingleton()->OnCreate();

}

void Engine::OnDestroy() { 


	Utility::DebugDraw::GetSingleton()->OnDestroy();

	// destroy components
	if (time) delete time; time = nullptr;
	if (window) delete window; window = nullptr; // needs to be last
}

void Engine::PollEvents() { 
	SDL_Event events;
	// goes through events one by one
	while (SDL_PollEvent(&events)) {
		switch (events.type) {
		case SDL_QUIT: isRunning = false; break;
		case SDL_WINDOWEVENT:
			time->AdjustCurrentTime(events.window.timestamp);
			break;
		default: return;
		}
	}

}

void Engine::Update(const float& delta) { 

	// draws a line
	Utility::DebugDraw::DrawLine(vec2(0.0f), vec2(0.3f, 0.2f), Graphics::Color::CYAN);

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
	SDL_Delay(time->GetSleepTime(60));
}
