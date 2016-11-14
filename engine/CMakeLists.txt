cmake_minimum_required(VERSION 3.5)
project(SMEG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

# Source Code For Engine

# TODO: Replace with non-recursive
file(GLOB_RECURSE SMEG_SOURCES "src/*.cpp")
file(GLOB_RECURSE SMEG_HEADERS "src/*.hpp")
add_library(SMEG ${SMEG_SOURCES})

target_compile_options(SMEG PRIVATE -Wall -Wno-potentially-evaluated-expression -Werror)

# Include what you use linting
find_program(iwyu_path NAMES include-what-you-use iwyu)
if(NOT iwyu_path)
  message(FATAL_ERROR "Could not find the program include-what-you-use")
endif()

set_property(TARGET SMEG PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})

# CMake modules and find packages
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
message("CMake Directory: ${CMAKE_MODULE_PATH}")

# SDL Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_include_directories(SMEG PUBLIC ${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR}
                    ${PROJECT_SOURCE_DIR}/src)
                    
target_link_libraries(SMEG ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES})

install(TARGETS SMEG DESTINATION lib)
install(FILES ${SMEG_HEADERS} DESTINATION include