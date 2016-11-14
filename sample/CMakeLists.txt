cmake_minimum_required(VERSION 3.5)
project(sample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(sample src/main.cpp)

message("Linking to ${sample_SOURCE_DIR}")
target_link_libraries(sample SMEG)
target_compile_options(sample PRIVATE -Wall -Werror -Wextra)

# Copy resources

message("Copying resource files from " ${PROJECT_SOURCE_DIR}/res " to build target ${PROJECT_BINARY_DIR}.")
file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR})

# Add run target

add_custom_target(run
    COMMAND ${PROJECT_BINARY_DIR}/sample
    DEPENDS sample 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)