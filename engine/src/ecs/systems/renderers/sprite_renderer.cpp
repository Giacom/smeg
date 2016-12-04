#include <SDL2/SDL.h>
#include <memory>

#include "sprite_renderer.hpp"
#include "../../../graphics/base_renderer.hpp"
#include "../../system.hpp"
#include "../../entity.hpp"
#include "../../components/sprite.hpp"
#include "../../components/transform.hpp"
#include "../../../service/texture_library.hpp"
#include "../../../service/time.hpp"

namespace smeg {

	SpriteRenderer::SpriteRenderer() {
		types.push_back(std::type_index(typeid(Transform)));
		types.push_back(std::type_index(typeid(Sprite)));
		executionOrder = System::LATE;
	}

    void SpriteRenderer::Initialise(BaseRenderer &renderer) {
    }

	void SpriteRenderer::Process(Entity &entity) {
		Transform& transform = entity.GetComponent<Transform>();
		Time& time = serviceContainer->Get<Time>();

		transform.position.x += (100.0f * time.delta);
		if (transform.position.x > 500) {
			transform.position.x = -100;
		}
	}

	void SpriteRenderer::Render(BaseRenderer &renderer, Entity &entity) {
        /*
		Transform& transform = entity.GetComponent<Transform>();
		Sprite& sprite = entity.GetComponent<Sprite>();

		SDL_Rect rect = SDL_Rect { (int)transform.position.x, (int)transform.position.y, sprite.w, sprite.h };
		auto& textureLibrary = serviceContainer->Get<TextureLibrary>();
        */
	}
}