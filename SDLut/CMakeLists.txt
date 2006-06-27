CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)

#Project Definition
PROJECT(SDLut)


INCLUDE(../RageCommon.cmake)


#
#Checking software dependencies
#

#Default Check for SDL
MESSAGE(STATUS "Checking for SDL")
FIND_PACKAGE(SDL REQUIRED)

#If not found ask the user for the location of it
IF ( NOT SDL_FOUND )
	MESSAGE(SEND_ERROR "SDL Not Found - please specify manually")
ENDIF(NOT SDL_FOUND )

#check for openGL
FIND_PACKAGE(OpenGL)
#opengl optional

#check for sdl_image
FIND_PACKAGE(SDL_image)
#sdl_image optional

#check for sdl_ttf
FIND_PACKAGE(SDL_ttf)
#sdl_ttf optional

#check for sdl_mixer
FIND_PACKAGE(SDL_mixer)
#sdl_mixer optional

#check for sdl_net
FIND_PACKAGE(SDL_net)
#sdl_net optional

#
#Defining Rules for building SDL Utility Toolkit
#

# this should be a dependency
INCLUDE_DIRECTORIES(${SDLut_SOURCE_DIR}/../Core/include )

#test for SDL
IF(SDL_FOUND)
	MESSAGE (STATUS "SDL found, adjusting build options..." )
	#adding SDL includes to the build
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
	#adding SDL libraries to the link
	LINK_LIBRARIES (${SDL_LIBRARY})
ENDIF(SDL_FOUND)

#test for openGL
IF(OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_OPENGL)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE (OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL not found." )
ENDIF(OPENGL_FOUND)
#linking late to test dynamic linking of opengl libs

#test for sdl_image
IF(SDLIMAGE_FOUND)
	MESSAGE (STATUS "SDL_image found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLIMAGE)
	INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLIMAGE_LIBRARY})
ELSE (SDLIMAGE_FOUND)
	MESSAGE (STATUS "SDL_image not found." )
ENDIF(SDLIMAGE_FOUND)
	
#test for sdl_ttf
IF(SDLTTF_FOUND)
	MESSAGE (STATUS "SDL_ttf found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLTTF)
	INCLUDE_DIRECTORIES(${SDLTTF_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLTTF_LIBRARY})
ELSE (SDLTTF_FOUND)
	MESSAGE (STATUS "SDL_ttf not found." )
ENDIF(SDLTTF_FOUND)

#test for sdl_mixer
IF(SDLMIXER_FOUND)
	MESSAGE (STATUS "SDL_mixer found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLMIXER)
	INCLUDE_DIRECTORIES(${SDLMIXER_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLMIXER_LIBRARY})
ELSE (SDLMIXER_FOUND)
	MESSAGE (STATUS "SDL_mixer not found." )
ENDIF(SDLMIXER_FOUND)

#test for sdl_net
IF(SDLNET_FOUND)
	MESSAGE (STATUS "SDL_Net found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLNET)
	INCLUDE_DIRECTORIES(${SDLNET_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLNET_LIBRARY})
ELSE (SDLNET_FOUND)
	MESSAGE (STATUS "SDL_Net not found." )
ENDIF(SDLNET_FOUND)	
	
#
# Definining what to build depending on options
#

SET(BUILD_TESTS OFF CACHE BOOL "Wether or not you want the project to include the tests executables")


#
# Configure and Build process
#

#Include Files are copied in the binary tree once configured
#those configured include files, are the ones who will be installed.
ADD_SUBDIRECTORY(include)
#Including configured headers (binary for the configured header, source for the unmodified ones
INCLUDE_DIRECTORIES( ${SDLut_BINARY_DIR}/include ${SDLut_SOURCE_DIR}/include )

#Defining target
ADD_SUBDIRECTORY(src)

IF (BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
ENDIF(BUILD_TESTS)

#defining usefull variables.
#GET_TARGET_PROPERTY(SDLut_LIBRARY SDLut LOCATION)
#SET(SDLut_INCLUDE ${SDLut_SOURCE_DIR}/include)
#todo set the dependencies


