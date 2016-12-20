#include "file.hpp"

#include "SDL.h"

namespace smeg {
	/// Loads a file and returns a tuple with a unique ptr to its data and the data size
	std::pair<std::unique_ptr<unsigned char[]>, int> File::Load(const char* filePath) {
		SDL_RWops* fileOp = SDL_RWFromFile(filePath, "rb");
		int size = SDL_RWsize(fileOp);
		if (size <= 0) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Loading file failed: Unable to get file size for %s", filePath);
			throw;
		}

		std::unique_ptr<unsigned char[]> fileData = std::make_unique<unsigned char[]>(size + 1);

		SDL_RWread(fileOp, fileData.get(), size, size);
		SDL_RWclose(fileOp);
		return std::make_pair(std::move(fileData), size); 
	}
}