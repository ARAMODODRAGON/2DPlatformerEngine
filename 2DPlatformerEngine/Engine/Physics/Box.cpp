#include "Box.h"

namespace Physics {

	bool Box::Intersects(const Box& boxA, const vec2& posA, const Box& boxB, const vec2& posB) {
		// this checks if boxA is outside of boxB
		if ((boxA.right + posA.x) < (boxB.left + posB.x)) return false;
		if ((boxA.left + posA.x) > (boxB.right + posB.x)) return false;
		if ((boxA.top + posA.y) < (boxB.bottom + posB.y)) return false;
		if ((boxA.bottom + posA.y) > (boxB.top + posB.y)) return false;
		
		// if none of the previous were true then the boxes are overlapping
		return true;
	}
}
