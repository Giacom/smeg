#include "SDL.h"
#include <memory>

#include "text_renderer.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/components/text.hpp"

namespace smeg {

	TextRenderer::TextRenderer() {
		types.push_back(std::type_index(typeid(Transform)));
		types.push_back(std::type_index(typeid(Text)));
		executionOrder = System::LATE;
	}

    void TextRenderer::Initialise(OpenGLRenderer &renderer) { }

	void TextRenderer::Register(OpenGLRenderer &renderer, Entity &entity) {	}	
	
	void TextRenderer::Deregister(OpenGLRenderer &renderer, Entity &entity) {}

	void TextRenderer::Process(Entity &entity) {}

	void TextRenderer::Render(OpenGLRenderer& renderer, SpriteBatchRenderer &batcher, Entity &entity) {	}
}