#ifndef PHYSICS_BOX_H
#define PHYSICS_BOX_H
#include "../Math.h"

namespace Physics {

	struct Box {

		float left;
		float right;
		float bottom;
		float top;

		Box() : left(0.0f), right(0.0f), bottom(0.0f), top(0.0f) { }
		~Box() { }

		/// setters

		void SetExtents(const vec2& extents_) {
			left = -extents_.x / 2.0f;
			right = extents_.x / 2.0f;
			bottom = -extents_.y / 2.0f;
			top = extents_.y / 2.0f;
		}


		/// functions

		static bool Intersects(const Box& boxA, const vec2& posA, const Box& boxB, const vec2& posB);

	};


}

#endif // !PHYSICS_BOX_H