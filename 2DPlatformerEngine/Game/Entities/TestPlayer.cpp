#include "TestPlayer.h"
#include "../../Engine/Events/EventsHandler.h"
#include "../../Engine/Utility/DebugDraw.h"
#include "../../Engine/Content/ContentHandler.h"
#include <glm/gtc/type_ptr.hpp>

namespace Game {

	Player::Player()
		: camera(nullptr) {
		// set inputs to false
		in.up = false;
		in.down = false;
		in.left = false;
		in.right = false;
		in.rotateCW = false;
		in.rotateCCW = false;

		// set vertex array
		verts[0] = Vertex(vec2(-1.0f, -1.0f), vec2(0.0f, 1.0f)); // bottom left
		verts[1] = Vertex(vec2(1.0f, -1.0f), vec2(1.0f, 1.0f)); // bottom right
		verts[2] = Vertex(vec2(-1.0f, 1.0f), vec2(0.0f, 0.0f)); // top left
		verts[3] = Vertex(vec2(1.0f, 1.0f), vec2(1.0f, 0.0f)); // top right

		// set indicies array
		indices[0] = ivec3(3, 0, 2); // triangle A
		indices[1] = ivec3(3, 1, 0); // triangle B
	}

	Player::~Player() {
		// dereference the camera
		camera = nullptr;
	}

	void Player::OnCreate() {
		// bind input
		{
			Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_W, &Player::PressedUp, this);
			Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_S, &Player::PressedDown, this);
			Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_A, &Player::PressedLeft, this);
			Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_D, &Player::PressedRight, this);
			Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_E, &Player::PressedCW, this);
			Events::EventHandler::BindInputPressed(Events::KeyCode::KEY_Q, &Player::PressedCCW, this);

			Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_W, &Player::ReleasedUp, this);
			Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_S, &Player::ReleasedDown, this);
			Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_A, &Player::ReleasedLeft, this);
			Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_D, &Player::ReleasedRight, this);
			Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_E, &Player::ReleasedCW, this);
			Events::EventHandler::BindInputReleased(Events::KeyCode::KEY_Q, &Player::ReleasedCCW, this);
		}

		// load shader and texture
		texture = Content::ContentHandler::Load<Content::Texture2D>("testImage.png");
		shader = Content::ContentHandler::Load<Content::Shader>("playerShader");

		// get the uniforms
		glUseProgram(shader);

		///posLoc, sizeLoc, viewLoc, projLoc, imageLoc;
		posLoc = glGetUniformLocation(shader, "position");
		sizeLoc = glGetUniformLocation(shader, "size");
		viewLoc = glGetUniformLocation(shader, "view");
		projLoc = glGetUniformLocation(shader, "proj");

		// create VBO, VAO, EBO
		{
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
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
			// set the uvs to the location 1
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, uv));
		}

	}

	void Player::OnDestroy() {
		// unbind input
		{
			Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_W, &Player::PressedUp, this);
			Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_S, &Player::PressedDown, this);
			Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_A, &Player::PressedLeft, this);
			Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_D, &Player::PressedRight, this);
			Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_E, &Player::PressedCW, this);
			Events::EventHandler::UnbindInputPressed(Events::KeyCode::KEY_Q, &Player::PressedCCW, this);

			Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_W, &Player::ReleasedUp, this);
			Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_S, &Player::ReleasedDown, this);
			Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_A, &Player::ReleasedLeft, this);
			Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_D, &Player::ReleasedRight, this);
			Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_E, &Player::ReleasedCW, this);
			Events::EventHandler::UnbindInputReleased(Events::KeyCode::KEY_Q, &Player::ReleasedCCW, this);
		}

		// delete VBO, VAO, EBO
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void Player::Update(const float& delta) {

		vec2 pos = GetPosition();

		// move player
		if (in.up != in.down) {
			if (in.up) pos.y += delta * 100.0f;
			if (in.down) pos.y -= delta * 100.0f;
		}
		if (in.right != in.left) {
			if (in.right) pos.x += delta * 100.0f;
			if (in.left) pos.x -= delta * 100.0f;
		}

		// move camera
		if (camera) {
			// rotate
			if (in.rotateCCW != in.rotateCW) {
				float rot = camera->GetRotation();

				if (in.rotateCCW)
					rot -= delta;
				if (in.rotateCW)
					rot += delta;

				camera->SetRotation(rot);
			}

			// set position
			camera->SetPosition(pos);
		}

		// apply new position
		SetPosition(pos);


		// draws a box
		using Utility::DebugDraw;
		DebugDraw::DrawLine(vec2(-30.0f, -30.0f) + pos, vec2(-30.0f, 30.0f) + pos, Graphics::Color::CYAN);
		DebugDraw::DrawLine(vec2(-30.0f, 30.0f) + pos, vec2(30.0f, 30.0f) + pos, Graphics::Color::CYAN);
		DebugDraw::DrawLine(vec2(30.0f, 30.0f) + pos, vec2(30.0f, -30.0f) + pos, Graphics::Color::CYAN);
		DebugDraw::DrawLine(vec2(30.0f, -30.0f) + pos, vec2(-30.0f, -30.0f) + pos, Graphics::Color::CYAN);

	}

	void Player::Draw(const mat4& view, const mat4& proj) {

		// use shader and texture
		glEnable(GL_TEXTURE_2D);
		glUseProgram(shader.GetProgram());
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		// set unforms
		glUniform2f(posLoc, GetPosition().x, GetPosition().y);
		glUniform2f(sizeLoc, 60.0f, 60.0f);
		
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

		// bind the VAO and EBO
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		// draw using the EBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//remove program and shader and unbind the buffer
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);


		//{
		//	GLenum error = glGetError();
		//	switch (error) {
		//	case GL_NO_ERROR:
		//		PRINT("GL_NO_ERROR"); break;
		//	case GL_INVALID_ENUM:
		//		PRINT("GL_INVALID_ENUM"); break;
		//	case GL_INVALID_VALUE:
		//		PRINT("GL_INVALID_VALUE"); break;
		//	case GL_INVALID_OPERATION:
		//		PRINT("GL_INVALID_OPERATION"); break;
		//	case GL_INVALID_FRAMEBUFFER_OPERATION:
		//		PRINT("GL_INVALID_FRAMEBUFFER_OPERATION"); break;
		//	case GL_OUT_OF_MEMORY:
		//		PRINT("GL_OUT_OF_MEMORY"); break;
		//	case GL_STACK_UNDERFLOW:
		//		PRINT("GL_STACK_UNDERFLOW"); break;
		//	case GL_STACK_OVERFLOW:
		//		PRINT("GL_STACK_OVERFLOW"); break;
		//	default: PRINT("Other: " + TEXT(error)); break;
		//	}
		//}


	}


}