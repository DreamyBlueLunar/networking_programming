cmake_minimum_required(VERSION 3.0.0)

set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(. SRC_LIST)

add_library(leemuduo SHARED ${SRC_LIST})
