#include "file.hpp"

#include "SDL.h"

namespace smeg {
	/// Loads a file and returns a tuple with a unique ptr to its data and the data size
	FileData File::Load(const char* filePath) {
		SDL_RWops* fileOp = SDL_RWFromFile(filePath, "rb");

		if (!fileOp) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading file (%s) failed: %s", filePath, SDL_GetError());
			throw;
		}

		long size = SDL_RWsize(fileOp);
		if (size <= 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading file (%s) failed: Unable to get file size.", filePath);
			throw;
		}

		std::unique_ptr<unsigned char[]> fileData = std::make_unique<unsigned char[]>(size + 1);

		SDL_RWread(fileOp, fileData.get(), size, size);
		SDL_RWclose(fileOp);
		return std::make_pair(std::move(fileData), size); 
	}
}