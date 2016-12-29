#pragma once

namespace smeg {
	struct Matrix4 {
		static const unsigned short EntrySize = 4 * 4;
		float entries[EntrySize] = { 0 };

		static Matrix4 New() {
			return Matrix4();
		}

		static Matrix4 New(float m11, float m12, float m13, float m14,
			               float m21, float m22, float m23, float m24,
			               float m31, float m32, float m33, float m34,
			               float m41, float m42, float m43, float m44) {
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

		static Matrix4 Ortho(float right, float left, float top, float bottom, float far, float near) {
			return Matrix4::New(2.0f / (right - left),         0,                                   0,                            -((right + left) / (right - left)), 
			                    0,                             2.0f / (top - bottom),               0,                            -((top + bottom) / (top - bottom)), 
						        0,                             0,                                   -(2.0f / (far - near)),       -((far + near) / (far - near)),
			                    0,                             0,                                   0,                            1);
		}
	};
}