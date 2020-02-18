#ifndef CONTENT_SHADER_H
#define CONTENT_SHADER_H
#include "../Common.h"

/// typedef to keep the scope clean
/// this is so I dont have to include glew
typedef unsigned int GLuint;

namespace Content {

	struct Shader {
		friend class ContentHandler;

		Shader() : program(0) { }
		Shader(const GLuint& program_) : program(program_) { }
		~Shader() { }

		/// getter

		QUICK_GETTER(GLuint, program, Program);

		/// operators
		
		// returns the program so you can call useShader(shader)
		operator GLuint() { return program; }


	private:

		GLuint program;

	};

}

#endif // !CONTENT_SHADER_H