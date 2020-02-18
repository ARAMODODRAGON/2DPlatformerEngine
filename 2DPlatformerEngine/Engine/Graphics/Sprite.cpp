#include "Sprite.h"
#include <glew.h>
#include "../Content/ContentHandler.h"
#include <glm/gtc/type_ptr.hpp>

namespace Graphics {

	const float Sprite::verts[] = {
		//  x,     y,     u,     v
		-1.0f, -1.0f,  0.0f,  1.0f,	// bottom left
		 1.0f, -1.0f,  1.0f,  1.0f,	// bottom right
		-1.0f,  1.0f,  0.0f,  0.0f,	// top left
		 1.0f,  1.0f,  1.0f,  0.0f,	// top right
	};
	const uint Sprite::indices[] = {
		3, 0, 2,	// triangle 0
		3, 1, 0,	// triangle 1
	};

	Sprite::Sprite()
		: VAO(0), VBO(0), EBO(0), shader(0), texture(), posLoc(0), scaleLoc(0), depthLoc(0)
		, uvOffsetLoc(0), uvScalarLoc(0), viewLoc(0), projLoc(0)
		, scale(1.0f), pivot(0.0f), depth(0.0f), rect() {
		// create a VAO, VBO, and EBO
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		// bind Vertex Array Object
		glBindVertexArray(VAO);
		// copy the indicies into a buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// copy the vertices into the VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
		// set the verticies to the location 0
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)0);
		// set the uvs to the location 1
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)2);

		// load shader
		shader = Content::ContentHandler::LoadManaged<Content::Shader>("Engine/Graphics/spriteShader");

		// get the uniforms
		posLoc = glGetUniformLocation(shader, "position");
		scaleLoc = glGetUniformLocation(shader, "scale");
		depthLoc = glGetUniformLocation(shader, "depth");
		uvOffsetLoc = glGetUniformLocation(shader, "uvOffset");
		uvScalarLoc = glGetUniformLocation(shader, "uvScalar");
		imagesizeLoc = glGetUniformLocation(shader, "imagesize");
		viewLoc = glGetUniformLocation(shader, "view");
		projLoc = glGetUniformLocation(shader, "proj");
	}

	Sprite::~Sprite() {
		// delete VBO, VAO, EBO
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}



	void Sprite::Draw(const mat4& view, const mat4& proj, const vec2& position) {

		// use shader and texture
		glUseProgram(shader);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// set unforms
		glUniform2f(posLoc, position.x + pivot.x, position.y + pivot.y);
		glUniform2f(scaleLoc, scale.x, scale.y);
		glUniform1f(depthLoc, depth);

		vec2 texSize = texture.GetSize();
		glUniform2f(uvOffsetLoc, rect.x / texSize.x, rect.y / texSize.y);
		glUniform2f(uvScalarLoc, rect.w / texSize.x, rect.h / texSize.y);

		//PRINT(TEXT((rect.w / texSize.x) + (rect.x / texSize.x)) + ", " + TEXT((rect.h / texSize.y) + (rect.y / texSize.y)));

		glUniform2f(imagesizeLoc, texSize.x, texSize.y);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// bind the VAO and EBO
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// draw the triangles
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// remove the shader program and unbind the VAO and EBO
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);
	}

	void Sprite::SetShader(const Content::Shader& shader_) {
		// set the new shader
		shader = shader_;

		// if it is not 0
		if (shader) {
			// get the uniforms
			posLoc = glGetUniformLocation(shader, "position");
			scaleLoc = glGetUniformLocation(shader, "scale");
			depthLoc = glGetUniformLocation(shader, "depth");
			uvOffsetLoc = glGetUniformLocation(shader, "uvOffset");
			uvScalarLoc = glGetUniformLocation(shader, "uvScalar");
			viewLoc = glGetUniformLocation(shader, "view");
			projLoc = glGetUniformLocation(shader, "proj");
		}
	}

	void Sprite::SetTexture(const Content::Texture2D& texture_) {
		// set the new texture
		texture = texture_;

		// reset the rect
		rect.x = 0.0f;
		rect.y = 0.0f;
		rect.w = static_cast<float>(texture.GetSize().x);
		rect.h = static_cast<float>(texture.GetSize().y);
	}


}