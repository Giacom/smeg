#pragma once

#include "math/vector2.hpp"
#include "math/rect.hpp"

namespace smeg {
	/// Meta-data about each character glyph and its size metrics
	struct Character {
		Rect boundingBox;
		Vector2 offset;
		float advance;

		static Character New(float x0, float y0, float x1, float y1, float xOff, float yOff, float advance) {
			return Character { Rect::PointToPoint(x0, y0, x1, y1), Vector2::New(xOff, yOff), advance };
		}
	};

	/*

   unsigned short x0,y0,x1,y1; // coordinates of bbox in bitmap
   float xoff,yoff,xadvance;
	*/
}