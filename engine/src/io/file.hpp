#pragma once

#include <memory>
#include <utility>

namespace smeg {
	typedef std::pair<std::unique_ptr<unsigned char[]>, long> FileData;
	class File {
		public:
			static FileData Load(const char* filePath);
	};
}