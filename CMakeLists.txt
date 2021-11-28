cmake_minimum_required(VERSION 3.7)

project(Matcha)

set(CMAKE_C_STANDARD 11)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

set(src_files
    # entry
    src/main.c
    # engine
    src/engine/draw.c
    src/engine/init.c
    src/engine/input.c
    src/engine/sound.c
    src/engine/text.c
    src/engine/util.c
    # app
    src/app/level.c
    src/app/menu.c
    src/app/options.c
    # data
    src/data/colors.c
    src/data/levels.c
)

add_executable(${PROJECT_NAME} ${src_files})
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

add_compile_options(-all_load)


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)