#include <SDL2/SDL.h>
#include <memory>
#include <iostream>

#include "sprite_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/sprite.hpp"
#include "../components/transform.hpp"
#include "../../service/texture_library.hpp"

SpriteRenderer::SpriteRenderer() {
	types.push_back(std::type_index(typeid(Transform)));
	types.push_back(std::type_index(typeid(Sprite)));
}

void SpriteRenderer::Process(Entity &entity) {

}

void SpriteRenderer::Render(SDL_Renderer *renderer, Entity &entity) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);

	Transform *transform = entity.GetComponent<Transform>();
	Sprite *sprite = entity.GetComponent<Sprite>();

	const SDL_Rect rect = SDL_Rect { (int)transform->position.x, (int)transform->position.y, sprite->w, sprite->h };
	auto textureLibrary = serviceContainer->Get<TextureLibrary>();
	SDL_RenderCopy(renderer, textureLibrary->Load(sprite->texturePath)->sdlTexture, NULL, &rect);
}