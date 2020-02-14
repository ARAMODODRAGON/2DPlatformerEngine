#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H
#include "../Common.h"
#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>

namespace Graphics {

	class Window {

		// variables
		int width, height;
		SDL_Window* window;
		SDL_GLContext context;

	public:

		/// oncreate and ondestroy
		void OnCreate(string name_, int width_, int height_);
		void OnDestroy();

		/// constructor & destructor
		Window() : width(0), height(0), window(nullptr), context(0) { }
		~Window() { OnDestroy(); }



		/// getters
		int GetWidth() { return width; }
		int GetHeight() { return height; }
		SDL_Window* GetWindow() const { return window; }

	private:

		// attributes
		void SetPreAttributes();
		void SetPostAttributes();

	};

}

#endif // !GRAPHICS_WINDOW_H