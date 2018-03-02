#pragma once

#include "math/vector2.hpp"
#include "math/rect.hpp"

namespace smeg {
	/// Meta-data about each character glyph and its size metrics
	struct Character {
		Rect boundingBox;
		Vector2 offset;
		f32 advance;

		static Character New(f32 x0, f32 y0, f32 x1, f32 y1, f32 xOff, f32 yOff, f32 advance) {
			return Character { Rect::PointToPoint(x0, y0, x1, y1), Vector2::New(xOff, yOff), advance };
		}
	};

	/*

   unsigned short x0,y0,x1,y1; // coordinates of bbox in bitmap
   f32 xoff,yoff,xadvance;
	*/
}