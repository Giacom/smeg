#include "font_library.hpp"

#include <memory>

#include "texture_library.hpp"
#include "io/file.hpp"
#include "io/image.hpp"
#include "service_container.hpp"

#define STB_TRUETYPE_IMPLEMENTATION
#include "libs/stb_truetype.h"

namespace smeg {

	const std::string FontLibrary::fontPrefix = std::string("font::");

	Font& FontLibrary::LoadFont(OpenGLRenderer& renderer, const std::string& path, float pixelSize) {
		std::string key = fontPrefix + path + "::" + std::to_string(pixelSize);
		auto existingFont = fontMap.find(key);
		if (existingFont != fontMap.end()) {
			return Get(key);
		}
		Cache(renderer, key, path, pixelSize);
		return Get(key);
	}

	Font& FontLibrary::Get(const std::string& key) {
		return *fontMap.at(key).get();
	}

	bool FontLibrary::HasKey(const std::string &key) {
		return fontMap.count(key) > 0;
	}

	void FontLibrary::Cache(OpenGLRenderer& renderer, const std::string& key, const std::string& path, float pixelSize) {
		FileData fileData = File::Load(path.c_str());

		const int startCharacter = 32; // Space 
		const int numberOfCharacters = 94; // Ends at ~

		auto& data = fileData.first;
		long size = fileData.second;

		const int bitmapSize = 256;

		SDL_Surface* image = SDL_CreateRGBSurface(0, bitmapSize, bitmapSize, 8, 0, 0, 0, 0);

		auto charData = std::make_unique<stbtt_bakedchar[]>(numberOfCharacters);

		int extraSpace = stbtt_BakeFontBitmap(data.get(), stbtt_GetFontOffsetForIndex(data.get(), 0), pixelSize, (unsigned char*)image->pixels, bitmapSize, bitmapSize, startCharacter, numberOfCharacters, charData.get());

		SDL_Log("Font size: %li, Extra space: %i", size, extraSpace);

		// TODO: Libraries are storage only. They shouldn't be creating the textures.
		// Change TextureLibrary to not use the OpenGLRenderer and to have the SpriteRenderer do it.
		// Remove the Service::serviceContainer too.

		std::unique_ptr<Font> font = std::make_unique<Font>();

		char character = startCharacter;
		int i = 0;

		while (i < numberOfCharacters) {
			auto& bakedChar = charData[i];
			font->characters.emplace(std::make_pair(character, Character::New(bakedChar.x0, bakedChar.y0, bakedChar.x1, bakedChar.y1,
			                                                                 bakedChar.xoff, bakedChar.yoff, bakedChar.xadvance)));

			i++;
			character++;
		}

		font->textureFontId = "test";
		font->pixelSize = pixelSize;

		TextureLibrary& textureLibrary = serviceContainer->Get<TextureLibrary>();
		textureLibrary.Cache(renderer, "file::test", image);

		SDL_FreeSurface(image);

		fontMap[key] = std::move(font);
				
		SDL_Log("Created Font for %s ", key.c_str());
	}
}