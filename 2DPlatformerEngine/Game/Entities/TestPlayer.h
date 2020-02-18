#ifndef GAME_TEST_PLAYER_H
#define GAME_TEST_PLAYER_H
#include "../../Engine/Objects/Entity.h"
#include "../../Engine/Objects/Camera.h"
#include "../../Engine/Content/Texture2D.h"
#include "../../Engine/Content/Shader.h"

namespace Game {
	using Objects::Entity;
	using Objects::Camera;

	class Player : public Entity {

		/// player will control the camera
		Camera* camera;

		/// input
		struct {
			bool up;
			bool down;
			bool left;
			bool right;
			bool rotateCW;
			bool rotateCCW;
		} in;

		// drawing
		Content::Shader shader;
		Content::Texture2D texture;
		GLuint posLoc, sizeLoc, viewLoc, projLoc;
		GLuint VBO, VAO, EBO;

		struct Vertex {
			vec2 position;
			vec2 uv;
			Vertex() : position(0.0f), uv(0.0f) { }
			Vertex(const vec2& position_, const vec2& uv_)
				: position(position_), uv(uv_) { }
		};

		Vertex verts[4];
		ivec3 indices[2];

	public:

		Player();
		virtual ~Player() override;


		/// events

		virtual void OnCreate() override;
		virtual void OnDestroy() override;
		virtual void Update(const float& delta) override;
		virtual void Draw(const mat4& view, const mat4& proj) override;

		/// functions

		void SetCamera(Camera* Camera_) { camera = Camera_; }

	private:

		/// input callbacks

		void PressedUp() { in.up = true; }
		void PressedDown() { in.down = true; }
		void PressedLeft() { in.left = true; }
		void PressedRight() { in.right = true; }
		void PressedCW() { in.rotateCW = true; }
		void PressedCCW() { in.rotateCCW = true; }

		void ReleasedUp() { in.up = false; }
		void ReleasedDown() { in.down = false; }
		void ReleasedLeft() { in.left = false; }
		void ReleasedRight() { in.right = false; }
		void ReleasedCW() { in.rotateCW = false; }
		void ReleasedCCW() { in.rotateCCW = false; }

	};

}

#endif // !GAME_TEST_PLAYER_H