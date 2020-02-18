#ifndef CONTENT_TEXTURE2D_H
#define CONTENT_TEXTURE2D_H
#include "../Common.h"
#include "../Math.h"

/// typedef to keep the scope clean
/// this is so I dont have to include glew
typedef unsigned int GLuint;

namespace Content {

	struct Texture2D {
		friend class ContentHandler;

		Texture2D() : texture(0), bytesPerPixel(0), size(0) { }
		~Texture2D() { }

		/// getters

		QUICK_GETTER(GLuint, texture, TextureID);
		QUICK_GETTER(ubyte, bytesPerPixel, BytesPerPixel);
		QUICK_GETTER(uvec2, size, Size);

		/// operators

		// returns the texture id so you can call bindTexture(texture)
		operator GLuint() { return texture; }

	private:

		GLuint texture;

		ubyte bytesPerPixel;
		uvec2 size;

	};

}

#endif // !CONTENT_TEXTURE2D_H