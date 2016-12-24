#include "font_library.hpp"

#include <memory>

#include "texture_library.hpp"
#include "io/file.hpp"

#include "libs/stb_truetype.h"

namespace smeg {

	const std::string FontLibrary::fontPrefix = std::string("font::");

	Font& FontLibrary::LoadFont(const std::string& path, float pixelSize) {
		std::string key = fontPrefix + path + "::" + std::to_string(pixelSize);
		auto existingFont = fontMap.find(key);
		if (existingFont != fontMap.end()) {
			return Get(key);
		}
		Cache(key, path, pixelSize);
		return Get(key);
	}

	Font& FontLibrary::Get(const std::string& key) {
		return *fontMap.at(key).get();
	}

	bool FontLibrary::HasKey(const std::string &key) {
		return fontMap.count(key) > 0;
	}

	void FontLibrary::Cache(const std::string& key, const std::string& path, float pixelSize) {
		FileData fileData = File::Load(path.c_str());

		const int startCharacter = 32; // Space 
		const int numberOfCharacters = 94; // Ends at ~

		auto& data = fileData.first;
		long size = fileData.second;

		auto bitmap = std::make_unique<unsigned char[]>(512 * 512);
		auto charData = std::make_unique<stbtt_bakedchar[]>(numberOfCharacters);

		int extraSpace = stbtt_BakeFontBitmap(data.get(), 0, pixelSize, bitmap.get(), 512, 512, startCharacter, numberOfCharacters, charData.get());

		for (int i = 0; i < 

	}
}