#pragma once

#include "common.hpp"

namespace smeg {
	struct Matrix4 {
		static const u8 EntrySize = 4 * 4;
		f32 entries[EntrySize] = { 0 };

		static Matrix4 New() {
			return Matrix4();
		}

		static Matrix4 New(f32 m11, f32 m12, f32 m13, f32 m14,
			               f32 m21, f32 m22, f32 m23, f32 m24,
			               f32 m31, f32 m32, f32 m33, f32 m34,
			               f32 m41, f32 m42, f32 m43, f32 m44) {
			return Matrix4 { { m11, m21, m31, m41,
							   m12, m22, m32, m42,
							   m13, m23, m33, m43,
			                   m14, m24, m34, m44 } };
		}

		static Matrix4 Identity() {
			return Matrix4::New(1, 0, 0, 0,
			                    0, 1, 0, 0,
						        0, 0, 1, 0,
						        0, 0, 0, 1);
		}

		static Matrix4 Ortho(f32 right, f32 left, f32 top, f32 bottom, f32 far, f32 near) {
			return Matrix4::New(2.0f / (right - left),         0,                                   0,                            -((right + left) / (right - left)), 
			                    0,                             2.0f / (top - bottom),               0,                            -((top + bottom) / (top - bottom)), 
						        0,                             0,                                   -(2.0f / (far - near)),       -((far + near) / (far - near)),
			                    0,                             0,                                   0,                            1);
		}
	};
}