#include "fps_display.hpp"

#include <sstream>

#include "../../../service/time.hpp"
#include "../../components/debug/fps.hpp"
#include "../../components/text.hpp"

namespace smeg {

    FpsDisplay::FpsDisplay() {
        types.push_back(std::type_index(typeid(Fps)));
        types.push_back(std::type_index(typeid(Text)));
    }

    void FpsDisplay::Process(Entity &entity) {
        Time &time = serviceContainer->Get<Time>();
        Text &text = entity.GetComponent<Text>();
        std::stringstream label;
        label << "FPS: " << time.fps << " - Delta: " << time.delta;

        text.SetText(label.str());
    }
}