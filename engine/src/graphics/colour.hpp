#pragma once

namespace smeg {
	struct Colour {
		float r = 1;
		float g = 1;
		float b = 1;
		float a = 1;

		Colour() = default;

		Colour(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		static Colour FromHex(float r, float g, float b, float a) {
			return Colour(r / 0xFF, g / 0xFF, b / 0xFF, a / 0xFF);
		}
	};
}