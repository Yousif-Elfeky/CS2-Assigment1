cmake_minimum_required(VERSION 3.20)

project(CS2_Assigment1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_program(CLANG_COMPILER NAME clang++)

if(CLANG_COMPILER)
    set(CMAKE_CXX_COMPILER ${CLANG_COMPILER})
endif()

add_library(app_lib
    src/entity.cpp
    src/healer.cpp
    src/cleric.cpp
    src/druid.cpp
    src/paladin.cpp
)

target_include_directories(app_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(app_lib
    PRIVATE
        -Wall
        -Wextra
        -Werror
)

target_compile_options(app_lib
    PRIVATE
        -fsanitize=address
        -fno-omit-frame-pointer
)

target_link_options(app_lib
    PRIVATE
        -fsanitize=address
)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        app_lib
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -Werror
        -fsanitize=address
        -fno-omit-frame-pointer
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        -fsanitize=address
)
