CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(AtlasOM)
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(testapp)

include_directories(${PROJECT_SOURCE_DIR}/src)


SET(sources src/structs.h
            src/exports.h
            src/internal.h
            src/data/data.h
            src/console_interface.h
            src/data/anexe/anexe.h
            
            src/testing/test.h
            src/testing/test_anexe.c

            src/data/anexe/anexa9.c
            src/data/anexe/anexa8.c
	        src/data/anexe/anexa7.c
	        src/data/anexe/anexa6.c
            src/data/anexe/anexa5.c
            src/data/anexe/anexa4.c
            src/data/anexe/anexa3.c
            src/data/anexe/anexa2.c
            src/console_interface.c
            src/internal.c

			src/java_interface.c
            src/data/data.c
            src/data/base_values.c
            src/data/capitol_1.c
            src/data/capitol_2.c
            src/data/capitol_3.c
            src/data/capitol_4.c
            src/data/capitol_5.c
            src/data/capitol_6.c

            src/autocad/autocad.h
            src/autocad/autocad.c
            src/autocad/desen_final.c
			)


add_library(AtlasOM SHARED ${sources})

if(UNIX)
target_link_libraries(AtlasOM m pthread)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wmissing-field-initializers -fexceptions") 
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra") 

set(CMAKE_C_FLAGS_DEBUG "")
set(CMAKE_C_FLAGS_RELEASE "-O3")

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-ident -fmerge-all-constants -fno-unroll-loops -fno-math-errno -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-stack-protector -fomit-frame-pointer -ffunction-sections -fdata-sections") # FULL SIZE OPTIMIZATIONS

endif(UNIX)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
