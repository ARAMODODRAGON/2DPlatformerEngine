#include "Window.h"

namespace Graphics {

	void Window::OnCreate(string name_, int width_, int height_) {
		// initialize sdl
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			PRINT_ERROR("Failed to create window");
			return;
		}

		// set window size
		width = width_;	height = height_;

		SetPreAttributes();

		// create window
		window = SDL_CreateWindow(
			name_.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL
		);

		// check if the window was created
		if (!window) {
			PRINT_ERROR("Failed to create window");
			return;
		}

		// create context
		context = SDL_GL_CreateContext(window);

		SetPostAttributes();


		// check if it was created
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			PRINT_ERROR("Failed to initialize GLEW");
			return;
		}

		// enable this shit
		glEnable(GL_DEPTH_TEST);

		// print graphics card and opengl version
		PRINT("Graphics card: " + string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
		PRINT("OpenGL version: " + string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));

	}

	void Window::OnDestroy() {
		// destroy window and context
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window); window = nullptr;

	}

	void Window::SetPreAttributes() {
		// set attributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		// this matches to the refresh rate of the display
		SDL_GL_SetSwapInterval(1);

		// experimental? something something, yea!
		glewExperimental = GL_TRUE;
	}

	void Window::SetPostAttributes() {
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	}

}