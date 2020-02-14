#ifndef UTILITY_DEBUG_DRAW_HPP
#define UTILITY_DEBUG_DRAW_HPP
#include "../Common.h"
#include <memory>
#include <glew.h>
#include "../Graphics/temp_Shader.h"
#include "../Math.h"
#include "../Graphics/Color.h"
#include <list>

namespace Utility {
	
	class DebugDraw {
		SINGLETON(DebugDraw);

		static vec2 lineVerts[];
		static Graphics::Shader lineShader;
		static GLuint lineVBO, lineVAO;
		static GLuint scalarLoc;
		static GLuint offsetLoc;
		static GLuint colorLoc;

		struct DrawRay {
			vec2 position;
			vec2 direction;
			Graphics::Color color;

			DrawRay(vec2 start_, vec2 end_, Graphics::Color color_)
				: position(start_), direction(end_ - start_), color(color_) { }
		};
		static std::list<DrawRay> drawRayList;

	public:

		void OnCreate();
		void OnDestroy();
		void DrawShapes();

		static void DrawCircle(vec2 position, float radius, Graphics::Color color = Graphics::Color::GREEN);
		static void DrawLine(vec2 start, vec2 end, Graphics::Color color = Graphics::Color::GREEN);

	};

}

#endif // !DEBUG_DRAW_HPP