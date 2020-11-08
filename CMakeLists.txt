cmake_minimum_required(VERSION 3.7)

project(Matcha)

set(CMAKE_C_STANDARD 11)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#
## https://github.com/aminosbh/sdl2-cmake-modules
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_mixer REQUIRED)

# set( SDL_extern ON CACHE BOOL "" FORCE )
# set( SDL_SHARED OFF CACHE BOOL "" FORCE )

# # add_subdirectory("ext/SDL/")
# find_package(SDL2 REQUIRED)
# # add_subdirectory("ext/SDL_image/")
# find_package(SDL2_image REQUIRED)
# # add_subdirectory("ext/SDL_ttf/")
# find_package(SDL2_ttf REQUIRED)
# # add_subdirectory("ext/SDL_mixer/")
# find_package(SDL2_mixer REQUIRED)

# include_directories("ext/SDL/" "ext/SDL_image/" "ext/SDL_ttf/" "ext/SDL_mixer/include")

# add_subdirectory(src)

set(src_files
    src/engine/draw.c
    src/engine/init.c
    src/engine/input.c
    src/app/level1.c
    src/main.c
    src/data/colors.c
    src/data/levels.c
    src/app/menu.c
    src/app/options.c
    src/engine/sound.c
    src/engine/text.c
    src/engine/util.c
)
# file(GLOB src_files
#     "src/*.c"
# )
add_executable(${PROJECT_NAME} ${src_files})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project

#target_link_libraries(Matcha ${SDL2_LIBRARIES})
#target_link_libraries(Matcha
#  SDL2::Main
#  SDL2::Image
#  SDL2::TTF
#  SDL2::Mixer
#)

#set (source "${CMAKE_SOURCE_DIR}/resources")
#set (destination "${CMAKE_CURRENT_BINARY_DIR}/resources")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)


#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#                       ${CMAKE_SOURCE_DIR}/gfx $<TARGET_FILE_DIR:${PROJECT_NAME}>/gfx)
#
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#                       ${CMAKE_SOURCE_DIR}/snd $<TARGET_FILE_DIR:${PROJECT_NAME}>/snd)
#
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                       COMMAND ${CMAKE_COMMAND} -E copy_directory
#                           ${CMAKE_SOURCE_DIR}/fnt $<TARGET_FILE_DIR:${PROJECT_NAME}>/fnt)