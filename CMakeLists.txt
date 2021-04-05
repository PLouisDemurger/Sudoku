cmake_minimum_required(VERSION 3.17)
project(Sudoku C)

set(CMAKE_C_STANDARD 99)

#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32”)
#set(CMAKE_EXE_LINKER_FLAGS “-static-libgcc -static-libstdc++”)

######################################################################
#          CREATION DES EDITIONS DE LIEN POUR SDL                    #
######################################################################
set(SDL2_BASE C:/SDL/)
set(SDL2_CMAKE_64_DIR ${SDL2_BASE}/SDL2-2.0.14/x86_64-w64-mingw32)
set(SDL2_CMAKE_32_DIR ${SDL2_BASE}/SDL2-2.0.14/i686-w64-mingw32)
set(SDL2_INCLUDE_DIR ${SDL2_CMAKE_64_DIR}/include/SDL2)
set(SDL2_LIB_DIR ${SDL2_CMAKE_64_DIR}/lib)

set(SDL2_BASE C:/SDL/)

######################################################################
#          CREATION DES EDITIONS DE LIEN POUR SDL TTF                #
######################################################################
set(SDL2_TTF_CMAKE_64_DIR ${SDL2_BASE}/SDL2_ttf-2.0.15/x86_64-w64-mingw32)
set(SDL2_TTF_CMAKE_32_DIR ${SDL2_BASE}/SDL2_ttf-2.0.15/i686-w64-mingw32)

######################################################################
#        CREATION DES EDITIONS DE LIEN POUR SDL IMAGE                #
######################################################################
set(SDL2_IMAGE_CMAKE_64_DIR ${SDL2_BASE}/SDL2_image-2.0.5/x86_64-w64-mingw32)
set(SDL2_IMAGE_CMAKE_32_DIR ${SDL2_BASE}/SDL2_image-2.0.5/i686-w64-mingw32)

######################################################################
#          CREATION DES EDITIONS DE LIEN POUR SDL                    #
######################################################################
set(SDL2_CMAKE_64_DIR ${SDL2_BASE}/SDL2-2.0.14/x86_64-w64-mingw32)
set(SDL2_CMAKE_32_DIR ${SDL2_BASE}/SDL2-2.0.14/i686-w64-mingw32)
set(SDL2_INCLUDE_DIR ${SDL2_CMAKE_64_DIR}/include/SDL2 ${SDL2_TTF_CMAKE_64_DIR}/include/SDL2 ${SDL2_IMAGE_CMAKE_64_DIR}/include/SDL2)
set(SDL2_LIB_DIR ${SDL2_CMAKE_64_DIR}/lib ${SDL2_TTF_CMAKE_64_DIR}/lib ${SDL2_IMAGE_CMAKE_64_DIR}/lib)

#set(SDL2_DIR ${SDL2_CMAKE_DIR}/lib/cmake/SDL2)
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}+${SDL2_INCLUDE_DIR}/lib/SDL2)

set(SOURCE_FILE lib/)
set(HEADER_FILE include/)

set(FILE_EXE main.c
        ${SOURCE_FILE}sudokuFunction.c ${SOURCE_FILE}SudokuGraphic.c
        ${HEADER_FILE}sudokuFunction.h ${HEADER_FILE}SudokuGraphic.h)

#find_package(SDL2 REQUIRED)
#find_package(SDL_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

#include_directories(${SDL_TTF_INCLUDE_DIRS})
#link_directories(${SDL_TTF_LIBRARIES})



add_executable(Sudoku ${FILE_EXE})

target_link_libraries(Sudoku SDL2main SDL2 SDL2_ttf SDL2_image)