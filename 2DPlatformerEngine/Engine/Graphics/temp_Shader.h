#ifndef GRAPHICS_SHADER_HPP
#define GRAPHICS_SHADER_HPP
#include "../Common.h"
#include <glew.h>

namespace Graphics {

	class Shader {
		// shader program
		GLuint programID;

	public:

		Shader();
		~Shader();


		/// functions

		void LoadShader(const string& vertpath, const string& fragpath);
		void UnloadShader();

		void UseProgram();


		/// getters

		GLuint GetProgramID() { return programID; }

	private:

		/// static functions
		static string LoadSource(const string& filepath);

	};
}

#endif // !GRAPHICS_SHADER_HPP