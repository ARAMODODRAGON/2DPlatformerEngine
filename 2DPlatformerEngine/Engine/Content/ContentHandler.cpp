#include "ContentHandler.h"
#include <glew.h>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::getline;

namespace Content {

	ContentHandler::ContentHandler() { }
	ContentHandler::~ContentHandler() { }

	void ContentHandler::OnCreate() {
		resourceFolder = "Resources/";
	}

	void ContentHandler::OnDestroy() { UnloadContent(); }

	void ContentHandler::UnloadContent() {

		// unload all textures
		for (std::pair<string, Texture2D> tex : loadedTextures) {
			glDeleteTextures(1, &tex.second.texture);
		}
		loadedTextures.clear();

		// unload all shaders
		for (std::pair<string, Shader> sh : loadedShaders) {
			glDeleteProgram(sh.second.program);
		}
		loadedShaders.clear();

	}

	#pragma region Content loading

	template<>
	Texture2D ContentHandler::Load<Texture2D>(const string& file) {
		// check if the texture has already been loaded
		if (GetSingleton()->loadedTextures.find(file) != GetSingleton()->loadedTextures.end())
			return GetSingleton()->loadedTextures[file];

		// create the texture object
		Texture2D texture;

		// load image into and SDL_Surface
		SDL_Surface* surface = IMG_Load((GetSingleton()->resourceFolder + file).c_str());
		if (surface == nullptr) {
			PRINT_ERROR("Could not find file: " + file);
			return Texture2D(); // empty texture
		}
		// create and bind a texture object
		glGenTextures(1, &texture.texture);
		glBindTexture(GL_TEXTURE_2D, texture.texture);

		// check the pixel format of the image
		PRINT("bytes per pixel: " + TEXT(surface->format->BytesPerPixel));
		int mode = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		// load in the texture
		glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

		// Wrapping and filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// set the texture values
		texture.bytesPerPixel = surface->format->BytesPerPixel;
		texture.size = uvec2(surface->w, surface->h);

		// delete the SDL_Surface and unbind the texture
		SDL_FreeSurface(surface);
		glBindTexture(GL_TEXTURE_2D, 0);

		// add the texture to the map
		GetSingleton()->loadedTextures[GetSingleton()->resourceFolder + file] = texture;

		// return the texture
		return texture;
	}
	
	template<>
	Texture2D ContentHandler::LoadUnmanaged<Texture2D>(const string& file) {
		// create the texture object
		Texture2D texture;

		// load image into and SDL_Surface
		SDL_Surface* surface = IMG_Load((GetSingleton()->resourceFolder + file).c_str());
		if (surface == nullptr) {
			PRINT_ERROR("Could not find file: " + file);
			return Texture2D(); // empty texture
		}
		// create and bind a texture object
		glGenTextures(1, &texture.texture);
		glBindTexture(GL_TEXTURE_2D, texture.texture);

		// check the pixel format of the image
		PRINT("bytes per pixel: " + TEXT(surface->format->BytesPerPixel));
		int mode = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		// load in the texture
		glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

		// Wrapping and filtering options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// set the texture values
		texture.bytesPerPixel = surface->format->BytesPerPixel;
		texture.size = uvec2(surface->w, surface->h);

		// delete the SDL_Surface and unbind the texture
		SDL_FreeSurface(surface);
		glBindTexture(GL_TEXTURE_2D, 0);

		// return the texture
		return texture;
	}

	template<>
	string ContentHandler::LoadUnmanaged<string>(const string& file) {
		// file stream
		ifstream stream;
		stream.open(file);

		if (!stream.is_open()) {
			// failed to open file
			PRINT_ERROR("Failed to open file " + file);
			stream.close();
			return "";
		}

		// stores the code
		string source, line;

		// read every line from the file
		while (getline(stream, line))
			source.append(line).append("\n");
		source.append("\0");

		// finish and return
		stream.close();
		return source;
	}

	template<>
	Shader ContentHandler::Load<Shader>(const string& file) {
		// check if the texture has already been loaded
		if (GetSingleton()->loadedShaders.find(file) != GetSingleton()->loadedShaders.end())
			return GetSingleton()->loadedShaders[file];

		// create a shader
		Shader shader;

		// load the vertex file
		string vertsourcestring = LoadUnmanaged<string>((GetSingleton()->resourceFolder + file) + ".vert");
		const char* vertsource = vertsourcestring.c_str();

		//PRINT("Loaded vertex: \n");
		//PRINT(vertsource);

		// create vertex shader
		GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
		// load and compile the code
		glShaderSource(vertID, 1, &vertsource, 0);
		glCompileShader(vertID);

		/// check errors
		GLint success;
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
		if (!success) {
			// get error and print
			GLchar infoLog[512];
			glGetShaderInfoLog(vertID, 512, 0, infoLog);
			PRINT_ERROR("Failed to compile shader: " + string(infoLog) + "\n\n");

			// delete the shader and return
			glDeleteShader(vertID);
			return 0;
		}

		// load the fragment file
		string fragsourcestring = LoadUnmanaged<string>((GetSingleton()->resourceFolder + file) + ".frag");
		const char* fragsource = fragsourcestring.c_str();

		//PRINT("Loaded fragment: \n");
		//PRINT(fragsource);

		// create fragment shader
		GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
		// load and compile the code
		glShaderSource(fragID, 1, &fragsource, 0);
		glCompileShader(fragID);

		/// check errors
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
		if (!success) {
			// get error and print
			GLchar infoLog[512];
			glGetShaderInfoLog(vertID, 512, 0, infoLog);
			PRINT_ERROR("Failed to compile shader: " + string(infoLog) + "\n\n");

			// delete the shader and return
			glDeleteShader(vertID);
			return 0;
		}

		// create program
		shader.program = glCreateProgram();
		// attach and link shaders
		glAttachShader(shader.program, vertID);
		glAttachShader(shader.program, fragID);
		glLinkProgram(shader.program);

		// check linking errors
		glGetProgramiv(shader.program, GL_LINK_STATUS, &success);
		if (!success) {
			// get error message and print
			GLchar infoLog[512];
			glGetProgramInfoLog(shader.program, 512, 0, infoLog);
			PRINT("Failed to link program: " + string(infoLog));
		}

		// delete shaders
		glDeleteShader(vertID);
		glDeleteShader(fragID);

		// add the shader to the map
		GetSingleton()->loadedShaders[GetSingleton()->resourceFolder + file] = shader;

		// return the shader
		return shader;
	}

	template<>
	Shader ContentHandler::LoadUnmanaged<Shader>(const string& file) {
		// create a shader
		Shader shader;

		// load the vertex file
		string vertsourcestring = LoadUnmanaged<string>(file + ".vert");
		const char* vertsource = vertsourcestring.c_str();

		//PRINT("Loaded vertex: \n");
		//PRINT(vertsource);

		// create vertex shader
		GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
		// load and compile the code
		glShaderSource(vertID, 1, &vertsource, 0);
		glCompileShader(vertID);

		/// check errors
		GLint success;
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
		if (!success) {
			// get error and print
			GLchar infoLog[512];
			glGetShaderInfoLog(vertID, 512, 0, infoLog);
			PRINT_ERROR("Failed to compile shader: " + string(infoLog) + "\n\n");

			// delete the shader and return
			glDeleteShader(vertID);
			return 0;
		}

		// load the fragment file
		string fragsourcestring = LoadUnmanaged<string>(file + ".frag");
		const char* fragsource = fragsourcestring.c_str();

		//PRINT("Loaded fragment: \n");
		//PRINT(fragsource);

		// create fragment shader
		GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
		// load and compile the code
		glShaderSource(fragID, 1, &fragsource, 0);
		glCompileShader(fragID);

		/// check errors
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
		if (!success) {
			// get error and print
			GLchar infoLog[512];
			glGetShaderInfoLog(vertID, 512, 0, infoLog);
			PRINT_ERROR("Failed to compile shader: " + string(infoLog) + "\n\n");

			// delete the shader and return
			glDeleteShader(vertID);
			return 0;
		}

		// create program
		shader.program = glCreateProgram();
		// attach and link shaders
		glAttachShader(shader.program, vertID);
		glAttachShader(shader.program, fragID);
		glLinkProgram(shader.program);

		// check linking errors
		glGetProgramiv(shader.program, GL_LINK_STATUS, &success);
		if (!success) {
			// get error message and print
			GLchar infoLog[512];
			glGetProgramInfoLog(shader.program, 512, 0, infoLog);
			PRINT("Failed to link program: " + string(infoLog));
		}

		// delete shaders
		glDeleteShader(vertID);
		glDeleteShader(fragID);

		// return the shader
		return shader;
	}

	template<>
	Shader ContentHandler::LoadManaged<Shader>(const string& file) {
		// check if the texture has already been loaded
		if (GetSingleton()->loadedShaders.find(file) != GetSingleton()->loadedShaders.end())
			return GetSingleton()->loadedShaders[file];

		// create a shader
		Shader shader;

		// load the vertex file
		string vertsourcestring = LoadUnmanaged<string>(file + ".vert");
		const char* vertsource = vertsourcestring.c_str();

		//PRINT("Loaded vertex: \n");
		//PRINT(vertsource);

		// create vertex shader
		GLuint vertID = glCreateShader(GL_VERTEX_SHADER);
		// load and compile the code
		glShaderSource(vertID, 1, &vertsource, 0);
		glCompileShader(vertID);

		/// check errors
		GLint success;
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
		if (!success) {
			// get error and print
			GLchar infoLog[512];
			glGetShaderInfoLog(vertID, 512, 0, infoLog);
			PRINT_ERROR("Failed to compile shader: " + string(infoLog) + "\n\n");

			// delete the shader and return
			glDeleteShader(vertID);
			return 0;
		}

		// load the fragment file
		string fragsourcestring = LoadUnmanaged<string>(file + ".frag");
		const char* fragsource = fragsourcestring.c_str();

		//PRINT("Loaded fragment: \n");
		//PRINT(fragsource);

		// create fragment shader
		GLuint fragID = glCreateShader(GL_FRAGMENT_SHADER);
		// load and compile the code
		glShaderSource(fragID, 1, &fragsource, 0);
		glCompileShader(fragID);

		/// check errors
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
		if (!success) {
			// get error and print
			GLchar infoLog[512];
			glGetShaderInfoLog(vertID, 512, 0, infoLog);
			PRINT_ERROR("Failed to compile shader: " + string(infoLog) + "\n\n");

			// delete the shader and return
			glDeleteShader(vertID);
			return 0;
		}

		// create program
		shader.program = glCreateProgram();
		// attach and link shaders
		glAttachShader(shader.program, vertID);
		glAttachShader(shader.program, fragID);
		glLinkProgram(shader.program);

		// check linking errors
		glGetProgramiv(shader.program, GL_LINK_STATUS, &success);
		if (!success) {
			// get error message and print
			GLchar infoLog[512];
			glGetProgramInfoLog(shader.program, 512, 0, infoLog);
			PRINT("Failed to link program: " + string(infoLog));
		}

		// delete shaders
		glDeleteShader(vertID);
		glDeleteShader(fragID);

		// add the shader to the map
		GetSingleton()->loadedShaders[file] = shader;

		// return the shader
		return shader;
	}

	#pragma endregion

}