#include <string>
#include <memory>

#include "SDL.h"

#include "graphics/image.hpp"
#include "texture_library.hpp"

namespace smeg {

	const std::string TextureLibrary::filePrefix = std::string("file::");
	const std::string TextureLibrary::resPrefix= std::string("res::");

	Texture& TextureLibrary::LoadFile(OpenGLRenderer& renderer, const std::string &path) {
		std::string key = filePrefix + path;
		auto existingTexture = textureMap.find(key); 
		if (existingTexture != textureMap.end()) {
			return Get(key);
		}

		SDL_Surface* image = Image::Load(path.c_str());
		Cache(renderer, key, image);
		SDL_FreeSurface(image);
		return Get(key);
	}

	Texture& TextureLibrary::Get(const std::string &key) {
		return *textureMap.at(key).get();
	}

	bool TextureLibrary::HasKey(const std::string &key) {
		return textureMap.count(key) > 0;
	}

	void TextureLibrary::Remove(const std::string &key) {
		// TODO: Unloading texture from memory
		textureMap.erase(key);
		SDL_Log("Texture Unloaded: %s", key.c_str());
	}

	void TextureLibrary::Clear() {
		textureMap.clear();
		SDL_Log("Unloaded All Textures");
	}

	void TextureLibrary::Cache(OpenGLRenderer& renderer, const std::string &key, SDL_Surface *image) {
		Texture texture = renderer.GenerateTexture(image);
		SDL_Log("Texture Loaded: %s", key.c_str());
		textureMap[key] = std::make_unique<Texture>(texture);
	}
}