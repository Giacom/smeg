#include "fps_display.hpp"

#include <sstream>

#include "service/time.hpp"
#include "ecs/components/debug/fps.hpp"
#include "ecs/components/text.hpp"

namespace smeg {

	FpsDisplay::FpsDisplay() {
		types.push_back(std::type_index(typeid(Fps)));
		types.push_back(std::type_index(typeid(Text)));
	}

	void FpsDisplay::Process(Entity &entity) {
		Time &time = serviceContainer->Get<Time>();
		Text &text = entity.GetComponent<Text>();
		std::stringstream label;
		label << "FPS: " << time.fps << " - Delta: " << time.delta << " - Ticks: " << time.ticks;

		text.SetText(label.str());
	}


	void FpsDisplay::Initialise(OpenGLRenderer &renderer) {}
	void FpsDisplay::Register(OpenGLRenderer &renderer, Entity &entity) {}
	void FpsDisplay::Deregister(OpenGLRenderer &renderer, Entity &entity) {}
	void FpsDisplay::Render(OpenGLRenderer& renderer, SpriteBatchRenderer& batcher, Entity &entity) {}
}