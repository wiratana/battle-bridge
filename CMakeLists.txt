cmake_minimum_required(VERSION 3.10)

project(BattleBridge    VERSION 0.1.0 
                        DESCRIPTION "Defend Your Motherland"
                        LANGUAGES C)

#Add SDL2 CMake Modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

#Find SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB SRC src/*c)

add_compile_options(-Wall -Wextra -pedantic)
add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF)
