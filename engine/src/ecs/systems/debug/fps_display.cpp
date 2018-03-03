#include "fps_display.hpp"

#include <sstream>
#include <iomanip>

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

		label << "FPS: " << std::fixed << std::setprecision(3) << time.fps
			  << " - Delta: " << std::fixed << std::setprecision(3) << time.delta
			  << " - Ticks: " << time.ticks;

		text.SetText(label.str());
	}


	void FpsDisplay::Initialise() {}
	void FpsDisplay::Register(Entity &entity) {}
	void FpsDisplay::Deregister(Entity &entity) {}
	void FpsDisplay::Render(Entity &entity) {}
}