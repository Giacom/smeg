#pragma once

#include "common.hpp"

#include <memory>
#include <utility>
#include <string>

namespace smeg {
	typedef std::pair<std::unique_ptr<unsigned char[]>, long> FileData;

	class File {
		public:
			static FileData Load(const char* filePath);
			static std::string LoadText(const char* filePath);

		private:
			static std::string GetFullPath(const char* relativePath);
	};
}