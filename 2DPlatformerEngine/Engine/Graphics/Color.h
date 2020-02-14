#ifndef GRAPHICS_COLOR_HPP
#define GRAPHICS_COLOR_HPP

namespace Graphics {

	struct Color {
		float r, g, b, a;

		Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) { }
		Color(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) { }
		Color(float r_, float g_, float b_) : r(r_), g(g_), b(b_), a(1.0f) { }



		/// static constants

		/// primary
		static const Color RED;
		static const Color BLUE;
		static const Color YELLOW;
		/// secondary
		static const Color GREEN;
		static const Color ORANGE;
		static const Color VIOLET;
		/// other
		static const Color CYAN;
		static const Color PINK;
		static const Color BROWN;
		static const Color BLACK;
		static const Color WHITE;
		static const Color GRAY;
		
	};


}
#endif // !GRAPHICS_COLOR_HPP