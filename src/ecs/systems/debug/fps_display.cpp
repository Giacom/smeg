#include "fps_display.hpp"

#include "../../../service/time.hpp"
#include "../../components/debug/fps.hpp"
#include "../../components/text.hpp"

FpsDisplay::FpsDisplay() {
	types.push_back(std::type_index(typeid(Fps)));
	types.push_back(std::type_index(typeid(Text)));
}


void FpsDisplay::Process(Entity &entity) {
    Time &time = serviceContainer->Get<Time>();
    Text &text = entity.GetComponent<Text>();
    text.SetText(std::to_string((int)time.fps));
    text.SetColour({0x0, (Uint8)(time.ticks % 0xFF), 0x0, 0xFF});
}