#include <SDL2/SDL.h>
#include <memory>

#include "sprite_renderer.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/sprite_component.hpp"

void SpriteRenderer::Process(Entity &entity) {

}

void SpriteRenderer::Render(SDL_Renderer *renderer, Entity &entity) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
	SpriteComponent *spriteComponent = entity.GetComponent<SpriteComponent>();

	const SDL_Rect rect = SDL_Rect { spriteComponent->x, spriteComponent->y, spriteComponent->w, spriteComponent->h };
	SDL_RenderFillRect(renderer, &rect);
}