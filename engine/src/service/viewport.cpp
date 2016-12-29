#include "viewport.hpp"

namespace smeg {
	Viewport::Viewport(int width, int height) {
		UpdateViewport(width, height);
	}

	void Viewport::UpdateViewport(int width, int height) {
		perspectiveMatrix = Matrix4::Ortho(width / 2, -(width / 2), height / 2, -(height / 2), 10000, -10000);
		size = Vector2::New(width, height);
	}

	const Matrix4& Viewport::GetPerspectiveMatrix() {
		return perspectiveMatrix;
	}
}