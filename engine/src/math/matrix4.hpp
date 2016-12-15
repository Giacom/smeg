#pragma once

namespace smeg {
	struct Matrix4 {
		static const unsigned int EntrySize = 4 * 4;
		float entries[EntrySize];

		Matrix4() {
			for(unsigned short i = 0; i < EntrySize; i++) {
				entries[i] = 0;
			}
		}

		Matrix4(float m11, float m12, float m13, float m14,
				float m21, float m22, float m23, float m24, 
		        float m31, float m32, float m33, float m34,
				float m41, float m42, float m43, float m44) {
			entries[0] = m11; entries[4] = m12; entries[8] = m13; entries[12] = m14;
			entries[1] = m21; entries[5] = m22; entries[9] = m23; entries[13] = m24;
			entries[2] = m31; entries[6] = m32; entries[10] = m33; entries[14] = m34;
			entries[3] = m41; entries[7] = m42; entries[11] = m43; entries[15] = m44;
		};

		static Matrix4 Identity() {
			return Matrix4(1, 0, 0, 0,
			               0, 1, 0, 0,
						   0, 0, 1, 0,
						   0, 0, 0, 1);
		}

		static Matrix4 Ortho(float right, float left, float top, float bottom, float far, float near) {
			return Matrix4(2.0f / (right - left),         0,                                   0,                            -((right + left) / (right - left)), 
			               0,                             2.0f / (top - bottom),               0,                            -((top + bottom) / (top - bottom)), 
						   0,                             0,                                   -(2.0f / (far - near)),       -((far + near) / (far - near)),
			               0,                             0,                                   0,                            1);
		}
	};
}