#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture_library.hpp"

namespace smeg {

	const std::string TextureLibrary::filePrefix = std::string("file::");
	const std::string TextureLibrary::resPrefix= std::string("res::");

	Texture& TextureLibrary::LoadFile(const std::string &path) {
		std::string key = filePrefix + path;
		auto existingTexture = textureMap.find(key); 
		if (existingTexture != textureMap.end()) {
			return Get(key);
		}

		SDL_Surface* image = IMG_Load(path.c_str());
		if (!image) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load texture image: %s", path.c_str());
			throw;
		}

		Cache(key, image);
		SDL_FreeSurface(image);
		return Get(key);
	}

	Texture& TextureLibrary::Get(const std::string &key) {
		return *textureMap.at(key).get();
	}

	bool TextureLibrary::HasKey(const std::string &key) {
		return textureMap.count(key) > 0;
	}

	void TextureLibrary::Cache(const std::string &key, SDL_Surface *image) {
		/*SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		if (!texture) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to convert texture from surface to texture: %s", key.c_str());
			throw;
		}
		SDL_Log("Texture Loaded: %s", key.c_str());
		textureMap[key] = std::make_unique<Texture>(texture);*/
	}

	void TextureLibrary::Remove(const std::string &key) {
		textureMap.erase(key);
		SDL_Log("Texture Unloaded: %s", key.c_str());
	}

	void TextureLibrary::Clear() {
		textureMap.clear();
		SDL_Log("Unloaded All Textures");
	}
}