cmake_minimum_required(VERSION 3.26.1)

project(TeleCode VERSION 1.0 LANGUAGES CXX)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(CURL REQUIRED)

if(NOT CURL_FOUND)
    message(FATAL_ERROR "Библиотека CURL не найдена!")
endif()

add_executable(telecode src/main.cpp)
# cmake -S . -B build
# cmake --build build
add_subdirectory(src/client)
add_subdirectory(src/config)
add_subdirectory(src/interpreter)
add_subdirectory(src/json)
add_subdirectory(src/subprocess)
add_subdirectory(src/UI)

target_link_libraries(telecode client config interpreter json subprocess UI)