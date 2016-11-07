cmake_minimum_required(VERSION 3.5.1)
project(SMEG)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG, -g -Wall -Wno-potentially-evaluated-expression -Werror)

# Source Code For Engine

# TODO: Replace with non-recursive
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(ProjectM ${SOURCES})

# CMake modules and find packages
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# SDL Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(ProjectM ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES})

# Copy resources

file(GLOB_RECURSE RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "res/*")
message("Looping over files: ${RESOURCES}\n")
foreach(RES_FILE ${RESOURCES})
    message("Copying ${RES_FILE} to ${CMAKE_BINARY_DIR}/${RES_FILE}\n")
    configure_file(${RES_FILE} "${CMAKE_BINARY_DIR}/${RES_FILE}" COPYONLY)
endforeach()

# Add run target

add_custom_target(run
    COMMAND ${PROJECT_BINARY_DIR}/ProjectM
    DEPENDS ProjectM
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)