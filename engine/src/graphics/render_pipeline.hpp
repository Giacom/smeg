#pragma once

#include <vector>

#include "render_command.hpp"

namespace smeg {
	class RenderPipeline {
		private:
			std::vector<RenderCommand> opaqueCommands;
			std::vector<RenderCommand> transparentCommands;
			std::vector<RenderCommand> overlayCommands;

		public:
			RenderPipeline();

			void Push(RenderLayer layer, RenderCommand command);
			void ClearAll();
		};
}