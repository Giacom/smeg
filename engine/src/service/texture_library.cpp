#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

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
			std::cout << "ERROR: Unable to load texture image: " << path << std::endl;
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
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		if (!texture) {
			std::cout << "ERROR: Unable to convert texture from surface to texture: " << key << std::endl;
			throw;
		}
		std::cout << "LOADED TEXTURE: " << key << std::endl;
		textureMap[key] = std::make_unique<Texture>(texture);
	}

	void TextureLibrary::Remove(const std::string &key) {
		textureMap.erase(key);
		std::cout << "UNLOADED TEXTURE:" << key << std::endl;
	}

	void TextureLibrary::Clear() {
		textureMap.clear();
		std::cout << "UNLOADED ALL TEXTURES" << std::endl;
	}
}