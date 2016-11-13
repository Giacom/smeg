cmake_minimum_required(VERSION 3.5)
project(sample)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG, -g -Wall -Wno-potentially-evaluated-expression -Werror)

add_subdirectory(engine)

add_executable(sample sample/src/main.cpp)
target_link_libraries(sample SMEG)
target_include_directories(sample PUBLIC engine/src)

# Copy resources

message("Copying resource files from " ${CMAKE_CURRENT_SOURCE_DIR}/sample/res " to build target.")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sample/res DESTINATION ${CMAKE_BINARY_DIR})

# Add run target

add_custom_target(run
    COMMAND ${PROJECT_BINARY_DIR}/sample
    DEPENDS sample 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)