cmake_minimum_required(VERSION 3.5)
project(sample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE APP_SOURCES "src/*.cpp")
file(GLOB_RECURSE APP_HEADERS "src/*.hpp")

add_executable(sample ${APP_SOURCES} ${APP_HEADERS})

message("Linking to ${sample_SOURCE_DIR}")
target_link_libraries(sample SMEG)
if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	target_compile_options(sample PRIVATE -Wall -Werror -Wextra -g)
endif()

# Copy resources

#message("Copying resource files from " ${sample_SOURCE_DIR}/res " to build target ${sample_BINARY_DIR}/${CMAKE_INSTALL_CONFIG_NAME}.")
#file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${PROJECT_BINARY_DIR}/${CMAKE_CFG_INTDIR})

add_custom_command(TARGET sample PRE_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy_directory "${PROJECT_SOURCE_DIR}/res" "${CMAKE_CFG_INTDIR}/res" 
  COMMENT "Copying resources (${PROJECT_SOURCE_DIR}/res) to output directory (${CMAKE_CFG_INTDIR}/res)")

# Add run target

add_custom_target(run
    COMMAND ${PROJECT_BINARY_DIR}/sample
    DEPENDS sample 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)