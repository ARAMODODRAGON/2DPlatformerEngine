#ifndef GRAPHICS_RECTANGLE_H
#define GRAPHICS_RECTANGLE_H

namespace Graphics {

	struct Rect {
		float x, y, w, h;

		Rect() : x(0.0f), y(0.0f), w(0.0f), h(0.0f) { }

	};

}

#endif // !GRAPHICS_RECTANGLE_H