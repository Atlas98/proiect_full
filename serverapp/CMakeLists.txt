CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(ServerApp)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(SOURCES src/main.c
            src/libutils.h
            src/libutils.c
            src/structs.h

            src/message_handler.c
            src/message_handler.h

            src/networking/networking_interface.c
            src/networking/networking_interface.h

            src/networking/sockets/sockets_linux.c
            src/networking/sockets/sock_internal.h
            src/networking/sockets/sockets.h)

add_executable(ServerApp ${SOURCES})

if(UNIX) 
target_link_libraries(ServerApp ${CMAKE_DL_LIBS} pthread)
endif(UNIX)