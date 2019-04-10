CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(AtlasSocketApp)

SET(sources src/main.c
            src/internal.h
            src/sockets.c
            src/sockets.h)

add_executable(AtlasSocketApp ${sources})

if(UNIX)
target_link_libraries(AtlasSocketApp ${CMAKE_DL_LIBS})
endif(UNIX)
