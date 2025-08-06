cmake_minimum_required(VERSION 3.26.1)

project(client)

set(CLIENT_LIB bot_requests.cpp bot.cpp requests.cpp)

add_library(client STATIC ${CLIENT_LIB})

target_link_libraries(client CURL::libcurl)