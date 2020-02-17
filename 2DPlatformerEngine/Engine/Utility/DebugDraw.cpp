#include "DebugDraw.h"
#include <glm/gtc/type_ptr.hpp>

namespace Utility {

	DebugDraw::DebugDraw() { }
	DebugDraw::~DebugDraw() { }

	#pragma region Static definitions

	glm::vec2 DebugDraw::lineVerts[] = {
		glm::vec2(0.0f),
		glm::vec2(1.0f),
	};
	Graphics::Shader DebugDraw::lineShader;
	GLuint DebugDraw::lineVBO = 0;
	GLuint DebugDraw::lineVAO = 0;
	GLuint DebugDraw::scalarLoc = 0;
	GLuint DebugDraw::offsetLoc = 0;
	GLuint DebugDraw::colorLoc = 0;
	GLuint DebugDraw::projLoc = 0;
	GLuint DebugDraw::viewLoc = 0;
	std::list<DebugDraw::DrawRay> DebugDraw::drawRayList;

	#pragma endregion

	void DebugDraw::OnCreate() {
		// setup the two verts
		glGenBuffers(1, &lineVBO);
		glGenVertexArrays(1, &lineVAO);
		glBindVertexArray(lineVAO);
		glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lineVerts), lineVerts, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);

		lineShader.LoadShader("Engine/Utility/DebugDrawShader/LineShader.vert", "Engine/Utility/DebugDrawShader/LineShader.frag");
		lineShader.UseProgram();
		scalarLoc = glGetUniformLocation(lineShader.GetProgramID(), "scalar");
		offsetLoc = glGetUniformLocation(lineShader.GetProgramID(), "offset");
		colorLoc = glGetUniformLocation(lineShader.GetProgramID(), "color");
		projLoc = glGetUniformLocation(lineShader.GetProgramID(), "proj");
		viewLoc = glGetUniformLocation(lineShader.GetProgramID(), "view");
	}

	void DebugDraw::OnDestroy() {
		lineShader.UnloadShader();

		glDeleteVertexArrays(1, &lineVAO);
		glDeleteBuffers(1, &lineVBO);
	}

	void DebugDraw::DrawShapes(const mat4& proj, const mat4& view) {
		lineShader.UseProgram();

		glBindVertexArray(lineVAO);
		for (DrawRay& ray : drawRayList) {

			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniform4f(colorLoc, ray.color.r, ray.color.g, ray.color.b, ray.color.a);
			glUniform2f(scalarLoc, ray.direction.x, ray.direction.y);
			glUniform2f(offsetLoc, ray.position.x, ray.position.y);

			// draw lines
			glDrawArrays(GL_LINE_LOOP, 0, 4);
		}
		drawRayList.clear();

		glUseProgram(0);
		glBindVertexArray(0);
	}

	void DebugDraw::DrawCircle(glm::vec2 position, float radius, Graphics::Color color) {
		// draw 13 lines
		DrawLine(glm::vec2(0.0f, -1.0f) * radius + position, glm::vec2(0.5f, -0.866f) * radius + position, color);
		DrawLine(glm::vec2(0.5f, -0.866f) * radius + position, glm::vec2(0.866f, -0.5f) * radius + position, color);
		DrawLine(glm::vec2(0.866f, -0.5f) * radius + position, glm::vec2(1.0f, 0.0f) * radius + position, color);

		DrawLine(glm::vec2(1.0f, 0.0f) * radius + position, glm::vec2(0.866f, 0.5f) * radius + position, color);
		DrawLine(glm::vec2(0.866f, 0.5f) * radius + position, glm::vec2(0.5f, 0.866f) * radius + position, color);
		DrawLine(glm::vec2(0.5f, 0.866f) * radius + position, glm::vec2(0.0f, 1.0f) * radius + position, color);

		DrawLine(glm::vec2(0.0f, 1.0f) * radius + position, glm::vec2(-0.5f, 0.866f) * radius + position, color);
		DrawLine(glm::vec2(-0.5f, 0.866f) * radius + position, glm::vec2(-0.866f, 0.5f) * radius + position, color);
		DrawLine(glm::vec2(-0.866f, 0.5f) * radius + position, glm::vec2(-1.0f, 0.0f) * radius + position, color);

		DrawLine(glm::vec2(-1.0f, 0.0f) * radius + position, glm::vec2(-0.866f, -0.5f) * radius + position, color);
		DrawLine(glm::vec2(-0.866f, -0.5f) * radius + position, glm::vec2(-0.5f, -0.866f) * radius + position, color);
		DrawLine(glm::vec2(-0.5f, -0.866f) * radius + position, glm::vec2(0.0f, -1.0f) * radius + position, color);

	}

	void DebugDraw::DrawLine(glm::vec2 start, glm::vec2 end, Graphics::Color color) {
		GetSingleton()->drawRayList.push_back(DrawRay(start, end, color));
	}


}
