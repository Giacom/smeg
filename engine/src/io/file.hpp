#pragma once

#include <memory>
#include <utility>

namespace smeg {

	class File {
		public:
			static std::pair<std::unique_ptr<unsigned char[]>, int> Load(const char* filePath);
	};
}