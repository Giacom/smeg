#include "viewport.hpp"


namespace smeg {
	Viewport::Viewport(i32 width, i32 height) {
		UpdateViewport(width, height);
	}

	void Viewport::UpdateViewport(i32 width, i32 height) {
		perspectiveMatrix = Matrix4::Ortho(width, 0, 0, height, 10000, -10000);
		//perspectiveMatrix = Matrix4::Ortho(width / 2, -(width / 2), height / 2, -(height / 2), 10000, -10000);
		size = Vector2::New(width, height);
	}

	const Matrix4& Viewport::GetPerspectiveMatrix() {
		return perspectiveMatrix;
	}
}