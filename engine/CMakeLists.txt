cmake_minimum_required(VERSION 3.5)
project(SMEG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(BUILD_SHARED_LIBS false)

# Source Code For Engine

# TODO: Replace with non-recursive
file(GLOB_RECURSE SMEG_SOURCES "src/*.cpp")
#file(GLOB_RECURSE SMEG_HEADERS "src/*.hpp")
add_library(SMEG ${SMEG_SOURCES} ${SMEG_HEADERS})

if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(SMEG PRIVATE -Wall -Wno-potentially-evaluated-expression -Werror -g)
endif()


# Include what you use linting
if(IWYU_ENABLED)
  find_program(iwyu_path NAMES include-what-you-use iwyu)
  if(NOT iwyu_path)
    message(FATAL_ERROR "Could not find the program include-what-you-use")
  endif()
endif()

set_property(TARGET SMEG PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})

# CMake modules and find packages
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message("CMake Directory: ${CMAKE_MODULE_PATH}")

# SDL Libraries
set(SDL2_BUILDING_LIBRARY)
find_package(SDL2 REQUIRED)

target_include_directories(SMEG PUBLIC ${SDL2_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/src)
                    
target_link_libraries(SMEG ${SDL2_LIBRARY}
                             ${SDL2_TTF_LIBRARIES})

install(TARGETS SMEG DESTINATION lib)
install(FILES ${SMEG_HEADERS} DESTINATION include)