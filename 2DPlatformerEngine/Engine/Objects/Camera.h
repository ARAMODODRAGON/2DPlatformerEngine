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

		void SetPosition(const vec2& Position_) { position = Position_; UpdateView(); }
		void SetRotation(const float& Rotation_) { rotation = Rotation_; UpdateView(); }
		void SetScreenSize(const vec2& ScreenSize_) { screenSize = ScreenSize_; UpdateOrtho(); }
		void SetNearPlane(const float& NearPlane_) { nearPlane = NearPlane_; UpdateOrtho(); }
		void SetFarPlane(const float& FarPlane_) { farPlane = FarPlane_; UpdateOrtho(); }

		void SetOrtho(const float& screenWidth_, const float& screenHeight_, const float& nearPlane_, const float& farPlane_);

	private:

		/// functions

		void UpdateView();
		void UpdateOrtho();

	};

}

#endif // !OBJECTS_CAMERA_H