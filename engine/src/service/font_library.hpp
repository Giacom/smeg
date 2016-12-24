#pragma once

#include <unordered_map>
#include <memory>

#include "service.hpp"
#include "graphics/font.hpp"

namespace smeg {
	
	typedef std::unordered_map<std::string, std::unique_ptr<Font>> FontMap;

	class FontLibrary : Service {
		static const std::string fontPrefix;

		private:
			FontMap fontMap;

		public:
			Font& LoadFont(const std::string& path, float pixelSize);
			Font& Get(const std::string& key);
			bool HasKey(const std::string& key);

		private:
			void Cache(const std::string& key, const std::string& path, float pixelSize);
	};
}