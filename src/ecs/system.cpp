#include <SDL2/SDL.h>
#include <typeinfo>
#include <typeindex>

#include "system.hpp"
#include "entity.hpp"

System::System() : type(std::type_index(typeid(void))) {
}

void System::Process(Entity &entity) {

}

void System::Render(SDL_Renderer *renderer, Entity &entity) {

}