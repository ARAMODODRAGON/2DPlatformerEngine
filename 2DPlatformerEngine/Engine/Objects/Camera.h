#ifndef OBJECTS_CAMERA_H
#define OBJECTS_CAMERA_H
#include "../Common.h"
#include "../Math.h"

namespace Objects {

	class Camera {

		/// camera orientation
		vec2 position;
		float rotation;

		/// camera view
		vec2 screenSize;
		float nearPlane, farPlane;

		/// matricies
		mat4 view;
		mat4 ortho;

	public:
		Camera();
		~Camera();


		/// getters

		QUICK_GETTER(vec2, position, Position);
		QUICK_GETTER(float, rotation, Rotation);
		QUICK_GETTER(vec2, screenSize, ScreenSize);
		QUICK_GETTER(float, nearPlane, NearPlane);
		QUICK_GETTER(float, farPlane, FarPlane);

		QUICK_GETTER(mat4, view, View);
		QUICK_GETTER(mat4, ortho, Ortho);


		/// setters

		void SetPosition(const vec2& position_) { position = position_; UpdateView(); }
		void SetRotation(const float& rotation_) { rotation = rotation_; UpdateView(); }
		void SetScreenSize(const vec2& screenSize_) { screenSize = screenSize_; UpdateOrtho(); }
		void SetNearPlane(const float& nearPlane_) { nearPlane = nearPlane_; UpdateOrtho(); }
		void SetFarPlane(const float& farPlane_) { farPlane = farPlane_; UpdateOrtho(); }

		void SetOrtho(const float& screenWidth_, const float& screenHeight_, const float& nearPlane_, const float& farPlane_);

	private:

		/// functions

		void UpdateView();
		void UpdateOrtho();

	};

}

#endif // !OBJECTS_CAMERA_H