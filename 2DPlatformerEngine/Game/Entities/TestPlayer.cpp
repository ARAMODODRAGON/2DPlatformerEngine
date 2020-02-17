#include "TestPlayer.h"
#include "../../Engine/Events/EventsHandler.h"
#include "../../Engine/Utility/DebugDraw.h"

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

		using Utility::DebugDraw;

		// draws a box
		DebugDraw::DrawLine(vec2(-30.0f, -30.0f) + pos, vec2(-30.0f, 30.0f) + pos, Graphics::Color::CYAN);
		DebugDraw::DrawLine(vec2(-30.0f, 30.0f) + pos, vec2(30.0f, 30.0f) + pos, Graphics::Color::CYAN);
		DebugDraw::DrawLine(vec2(30.0f, 30.0f) + pos, vec2(30.0f, -30.0f) + pos, Graphics::Color::CYAN);
		DebugDraw::DrawLine(vec2(30.0f, -30.0f) + pos, vec2(-30.0f, -30.0f) + pos, Graphics::Color::CYAN);


	}

	void Player::Draw(const mat4& view, const mat4& proj) { }

}