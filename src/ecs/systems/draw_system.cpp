#include <SDL2/SDL.h>

#include "draw_system.hpp"
#include "../system.hpp"
#include "../entity.hpp"

void DrawSystem::Process(Entity &entity) {

}

void DrawSystem::Render(SDL_Renderer *renderer, Entity &entity) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
	SDL_RenderFillRect(renderer);
}