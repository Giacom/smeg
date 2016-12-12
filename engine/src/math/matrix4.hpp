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
			entries[0] = m11; entries[1] = m12; entries[2] = m13; entries[3] = m14;
			entries[4] = m21; entries[5] = m22; entries[6] = m23; entries[7] = m24;
			entries[8] = m31; entries[9] = m32; entries[10] = m33; entries[11] = m34;
			entries[12] = m41; entries[13] = m42; entries[14] = m43; entries[15] = m44;
		};

		static Matrix4 Identity() {
			return Matrix4(1, 0, 0, 0,
			               0, 1, 0, 0,
						   0, 0, 1, 0,
						   0, 0, 0, 1);
		};
	};
}