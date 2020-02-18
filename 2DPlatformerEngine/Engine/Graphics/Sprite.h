#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H
#include "../Content/Texture2D.h"
#include "../Content/Shader.h"

namespace Graphics {

	class Sprite {


		GLuint VBO, VAO, EBO;

		#pragma region Static arrays


		#pragma endregion

	public:

		Sprite();
		~Sprite();

	};

}

#endif // !GRAPHICS_SPRITE_H