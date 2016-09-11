#include <SDL2/SDL.h>
#include <memory>
#include <iostream>

#include "sprite_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/sprite.hpp"
#include "../components/transform.hpp"
#include "../../service/texture_library.hpp"
#include "../../service/time.hpp"

SpriteRenderer::SpriteRenderer() {
	types.push_back(std::type_index(typeid(Transform)));
	types.push_back(std::type_index(typeid(Sprite)));
}

void SpriteRenderer::Process(Entity &entity) {
	/*
	Transform& transform = entity.GetComponent<Transform>();
	Time& time = serviceContainer->Get<Time>();

	transform.position.x += 10 * time.delta;
	std::cout << time.delta << std::endl;
	*/
}

void SpriteRenderer::Render(BatchRenderer &renderer, Entity &entity) {
	Transform& transform = entity.GetComponent<Transform>();
	Sprite& sprite = entity.GetComponent<Sprite>();

	SDL_Rect rect = SDL_Rect { (int)transform.position.x, (int)transform.position.y, sprite.w, sprite.h };
	auto& textureLibrary = serviceContainer->Get<TextureLibrary>();
	renderer.Batch(textureLibrary.LoadFile(sprite.texturePath), {}, rect, sprite.layer);
}