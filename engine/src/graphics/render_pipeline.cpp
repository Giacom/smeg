
#include "render_pipeline.hpp"
#include "common.hpp"

namespace smeg {
	RenderPipeline::RenderPipeline() {
		isize initialReserve = 32;
		opaqueCommands.reserve(initialReserve);
		transparentCommands.reserve(initialReserve);
		overlayCommands.reserve(initialReserve);
	}

	void RenderPipeline::Push(RenderLayer layer, RenderCommand command) {
		switch (layer) {
			case RenderLayer::Opaque:
				opaqueCommands.emplace_back(command);
				break;
			case RenderLayer::Transparent:
				transparentCommands.emplace_back(command);
				break;
			case RenderLayer::Overlay:
				overlayCommands.emplace_back(command);
				break;
		}
	}

	void RenderPipeline::ClearAll() {
		opaqueCommands.clear();
		transparentCommands.clear();
		overlayCommands.clear();
	}
}