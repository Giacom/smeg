#pragma once

#include "common.hpp"

#include "service.hpp"
#include "math/matrix4.hpp"
#include "math/vector2.hpp"


namespace smeg {
	class Viewport : public Service {

		Vector2 size;

		private:
			Matrix4 perspectiveMatrix;

		public:
			Viewport(i32 width, i32 height);
			void UpdateViewport(i32 width, i32 height);
			const Matrix4& GetPerspectiveMatrix();
	};
}