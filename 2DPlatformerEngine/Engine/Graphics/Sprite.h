#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H
#include "../Content/Texture2D.h"
#include "../Content/Shader.h"
#include "../Math.h"
#include "Rectangle.h"

namespace Graphics {

	class Sprite {

		static const float verts[];
		static const uint indices[];

		GLuint VAO, VBO, EBO;

		Content::Shader shader;
		Content::Texture2D texture;
		GLuint posLoc, scaleLoc, depthLoc, uvOffsetLoc, uvScalarLoc, imagesizeLoc;
		GLuint viewLoc, projLoc;

		vec2 scale;
		vec2 pivot;
		float depth;
		Rect rect;

	public:

		Sprite();
		~Sprite();

		/// events

		void Draw(const mat4& view, const mat4& proj, const vec2& position);

		/// setters
		
		void SetShader(const Content::Shader& shader_);
		void SetTexture(const Content::Texture2D& texture_);
		QUICK_SETTER(vec2, scale, Scale);
		QUICK_SETTER(vec2, pivot, Pivot);
		QUICK_SETTER(float, depth, Depth);
		QUICK_SETTER(Rect, rect, Rect);

		/// getters

		QUICK_GETTER(Content::Shader, shader, Shader);
		QUICK_GETTER(Content::Texture2D, texture, Texture);
		QUICK_GETTER(vec2, scale, Scale);
		QUICK_GETTER(vec2, pivot, Pivot);
		QUICK_GETTER(float, depth, Depth);
		QUICK_GETTER(Rect, rect, Rect);

	};

}

#endif // !GRAPHICS_SPRITE_H