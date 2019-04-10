CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(AtlasTest)

SET(sources src/main.c)

add_executable(AtlasTest ${sources})

if(UNIX)
target_link_libraries(AtlasTest ${CMAKE_DL_LIBS})
endif(UNIX)
