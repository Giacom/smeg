#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>

#include "service.hpp"
#include "../graphics/texture.hpp"
#include "../graphics/opengl_renderer.hpp"

namespace smeg {

	typedef std::unordered_map<std::string, std::unique_ptr<Texture>> TextureMap;

	struct TextureLibrary : public Service {
		static const std::string filePrefix;
		static const std::string resPrefix;
		
		private:
			TextureMap textureMap;

		public:
			Texture& LoadFile(OpenGLRenderer& renderer, const std::string &path);
			Texture& Get(const std::string &key);
			bool HasKey(const std::string &key);
			void Remove(const std::string &key);
			void Clear();

		private:
			void Cache(OpenGLRenderer& renderer, const std::string &key, SDL_Surface *image);
	};
}