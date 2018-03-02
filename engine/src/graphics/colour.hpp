#pragma once

namespace smeg {
	struct Colour {
		f32 r = 1;
		f32 g = 1;
		f32 b = 1;
		f32 a = 1;

		Colour() = default;

		Colour(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}

		static Colour FromHex(f32 r, f32 g, f32 b, f32 a) {
			return Colour(r / 0xFF, g / 0xFF, b / 0xFF, a / 0xFF);
		}
	};
}