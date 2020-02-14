#ifndef RENDERING_TEXTURE2D_HPP
#define RENDERING_TEXTURE2D_HPP
#include "../Common.h"
#include <glew.h>

namespace Graphics {

	class Texture2D {
	private:
		// texture ID
		GLuint texID;

		// image data
		ubyte bytesPerPixel;
		uint width, height;

	public:

		Texture2D();
		~Texture2D();

		// load image
		void LoadImage(string filepath);
		void UnloadImage();

		// binding
		void BindImage();

		// getter
		GLuint GetTextureID() { return texID; }
	};

}

#endif // !RENDERING_TEXTURE2D_HPP