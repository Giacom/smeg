#pragma once

#include "service.hpp"
#include "math/matrix4.hpp"
#include "math/vector2.hpp"


namespace smeg {
	class Viewport : public Service {

		Vector2 size;

		private:
			Matrix4 perspectiveMatrix;

		public:
			Viewport(int width, int height);
			void UpdateViewport(int width, int height);
			const Matrix4& GetPerspectiveMatrix();
	};
}