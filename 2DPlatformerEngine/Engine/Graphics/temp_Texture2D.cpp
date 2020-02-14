#include "temp_Texture2D.h"
#include <SDL_image.h>
#include <iostream>


namespace Graphics {
	Texture2D::Texture2D()
		: texID(0), bytesPerPixel(0), width(0), height(0) { }

	Texture2D::~Texture2D() { UnloadImage(); }

	void Texture2D::LoadImage(string filepath) {
		// if the prev image is still loaded in memory, unload it
		if (!texID) UnloadImage();

		// load image into and SDL_Surface
		SDL_Surface* textureSurface = IMG_Load(filepath.c_str());
		if (textureSurface == nullptr) {
			PRINT("Could not find file: " + filepath);
			return;
		}

		// create and bind a texture
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		// check the pixel format of the image
		printf("%i bytes per pixel\n", textureSurface->format->BytesPerPixel);
		int mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

		// load in the texture
		glTexImage2D(GL_TEXTURE_2D, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);

		/// Wrapping and filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// delete the SDL_Surface
		SDL_FreeSurface(textureSurface);

		return;
	}

	void Texture2D::UnloadImage() {
		// if its already unloaded
		if (!texID) return;
		// delete the texture
		glDeleteTextures(1, &texID);
		texID = 0;
	}

	void Texture2D::BindImage() {
		// bind this texture
		glBindTexture(GL_TEXTURE_2D, texID);
	}
}