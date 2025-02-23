cmake_minimum_required(VERSION 3.10)
project(ecs)

## ----------- CMAKE -----------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## ----------- Executable -----------
set(SOURCE_FILES
  Registry.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

## ----------- Include -----------
target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

## ----------- Compile Options -----------
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
