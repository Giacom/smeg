cmake_minimum_required(VERSION 3.5)

# This will build both the engine and the sample.
# Sample is linked via CMake. You can use "make install"" to just install the engine to your computer

message("Processing engine")
add_subdirectory(engine)

message("Processing sample")
add_subdirectory(sample)