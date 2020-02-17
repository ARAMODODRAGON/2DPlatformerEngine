#include "Camera2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Objects {

	Camera2D::Camera2D()
		: position(0.0f), rotation(0.0f), screenSize(1000.0f, 1000.0f), nearPlane(100.0f), farPlane(-100.0f), ortho(0.0f), view(0.0f) {

		UpdateOrtho();
		UpdateView();
	}

	Camera2D::~Camera2D() { }

	void Camera2D::SetOrtho(const float& screenWidth_, const float& screenHeight_, const float& nearPlane_, const float& farPlane_) { 
		// set the new values
		screenSize = vec2(screenWidth_, screenHeight_);
		nearPlane = nearPlane_;
		farPlane = farPlane_;

		// create the half sizes
		float halfWidth = screenSize.x / 2.0f;
		float halfHeight = screenSize.y / 2.0f;

		// create the new orthographic view
		ortho = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
	}

	void Camera2D::UpdateView() {
		// set the view matrix
		view = glm::rotate(mat4(), rotation, vec3(0.0f, 0.0f, 1.0f));
		view = glm::translate(view, vec3(-position, 0.0f));
	}

	void Camera2D::UpdateOrtho() { 
		// create the half sizes
		float halfWidth = screenSize.x / 2.0f;
		float halfHeight = screenSize.y / 2.0f;

		// create the new orthographic view
		ortho = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, nearPlane, farPlane);
	}



}
