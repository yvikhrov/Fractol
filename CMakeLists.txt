cmake_minimum_required( VERSION 3.5 FATAL_ERROR )

project( Fractol )

FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

set ( SOURCE_PATH ${FULL_PATH}/src/ )
set ( SOURCEFILES	color.c
						image.c
						init.c
						loop.c
						main.c
						parsing.c
						timer.c
						clamp.c
						handle_input.c
						mix.c
						vec2i.c
						utility.c
						cl.c)
PREPEND( SOURCES ${SOURCE_PATH} ${SOURCEFILES} )

set( PROJECT_SOURCES    ${SOURCES} )
set( PROJECT_INCLUDES   ${FULL_PATH}/include
                        ${FULL_PATH}/libft/include
                        ${FULL_PATH}/libmlx/include )

add_subdirectory(libft)

include_directories( ${PROJECT_INCLUDES} )
ADD_EXECUTABLE( fractol ${PROJECT_SOURCES} buildXcode/Debug/kernel.cl )

TARGET_LINK_LIBRARIES( fractol	libft
							${FULL_PATH}/libmlx/libmlx.a
							"-framework OpenGL"
							"-framework OpenCL"
							"-framework Foundation"
							"-framework CoreFoundation"
							"-framework AppKit")

