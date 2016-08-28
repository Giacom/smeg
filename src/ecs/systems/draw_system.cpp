#include <SDL2/SDL.h>
#include <memory>

#include "draw_system.hpp"
#include "../system.hpp"
#include "../entity.hpp"
#include "../components/sprite_component.hpp"

void DrawSystem::Process(Entity &entity) {

}

void DrawSystem::Render(SDL_Renderer *renderer, Entity &entity) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
	SpriteComponent *spriteComponent = dynamic_cast<SpriteComponent*>(entity.GetComponent(type));

	const SDL_Rect rect = SDL_Rect { spriteComponent->x, spriteComponent->y, spriteComponent->w, spriteComponent->h };
	SDL_RenderFillRect(renderer, &rect);
}