#include "file.hpp"

#include <string>

#include "SDL.h"


namespace smeg {
	/// Loads a file and returns a tuple with a unique ptr to its data and the data size
	FileData File::Load(const char* filePath) {
		std::string fullPath;
		{
			char* basePath = SDL_GetBasePath();
			if (!basePath) {
				SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading file (%s) failed: Unable to get base path - Details: %s.", filePath, SDL_GetError());
				throw;
			}

			fullPath = std::string(basePath) + filePath;
			SDL_free(basePath);
		}
		
		SDL_Log("Loading file: %s", fullPath.c_str());

		SDL_RWops* fileOp = SDL_RWFromFile(fullPath.c_str(), "rb");

		if (!fileOp) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading file (%s) failed: %s", filePath, SDL_GetError());
			throw;
		}

		Sint64 res_size = SDL_RWsize(fileOp);
		if (res_size <= 0) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading file (%s) failed: Unable to get file size.", filePath);
			throw;
		}

		std::unique_ptr<unsigned char[]> res = std::make_unique<unsigned char[]>(res_size + 1);

		Sint64 nb_read_total = 0, nb_read = 1;
		unsigned char* buf = res.get();
		while (nb_read_total < res_size && nb_read != 0) {
			nb_read = SDL_RWread(fileOp, buf, 1, (res_size - nb_read_total));
			nb_read_total += nb_read;
			buf += nb_read;
		}
		SDL_RWclose(fileOp);

		if (nb_read_total != res_size) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Loading file (%s) failed: Read total is not the same as file size.", filePath);
			throw;
		}

		res[nb_read_total] = '\0';

		return std::make_pair(std::move(res), res_size);
	}
}