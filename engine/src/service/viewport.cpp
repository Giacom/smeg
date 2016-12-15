#include "viewport.hpp"

namespace smeg {
	Viewport::Viewport(int width, int height) {
		UpdateViewport(width, height);
	}

	void Viewport::UpdateViewport(int width, int height) {
		perspectiveMatrix = Matrix4::Ortho(width / 2, -(width / 2), height / 2, -(height / 2), -1.0f, 1.0f);
		//perspectiveMatrix = Matrix4::Identity();
		size = Vector2(width, height);
	}

	const Matrix4& Viewport::GetPerspectiveMatrix() {
		return perspectiveMatrix;
	}
}