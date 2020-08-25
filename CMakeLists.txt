cmake_minimum_required(VERSION 3.7)

project("MATCHA")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# https://github.com/aminosbh/sdl2-cmake-modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# add_subdirectory(src)
set(src_files 
  ./src/draw.c
  ./src/init.c
  ./src/input.c
  ./src/level1.c
  ./src/main.c
  ./src/menu.c
  ./src/options.c
  ./src/sound.c
  ./src/text.c
  ./src/util.c
)
add_executable(${PROJECT_NAME} ${src_files})

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project

# target_link_libraries(MATCHA ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} 
  SDL2::Main
  SDL2::Image 
  SDL2::TTF
  SDL2::Mixer
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/gfx)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/snd $<TARGET_FILE_DIR:${PROJECT_NAME}>/snd)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts)