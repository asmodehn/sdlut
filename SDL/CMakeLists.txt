CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#Project Definition
PROJECT(Rage_SDL)

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
FIND_PACKAGE(OPENGL)
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
#Defining Rules for building Rage_SDL
#

INCLUDE_DIRECTORIES(${Rage_SDL_SOURCE_DIR}/include )
ADD_DEFINITIONS(-DLOGPREFIX=\"Rage_SDL\")

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
	
#Compiler Specific rules
IF(CMAKE_CXX_COMPILER STREQUAL "cl")
MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")

#to put the SVN Revision number in the build
find_program( SVNVERSION
  svnversion
  /usr/local/bin
  /usr/bin
)

macro( svn_repository_version DESTVAR TOPDIR )
  exec_program( ${SVNVERSION} ${TOPDIR} ARGS "." OUTPUT_VARIABLE ${DESTVAR} )
endmacro( svn_repository_version )

svn_repository_version( SVNREV ${Rage_SDL_SOURCE_DIR} )
#think about where it s better to use SVNREV...

#adding definitions for Logs and debug


ADD_DEFINITIONS(-DLOGINDENTLVL=1)

SET(Custom_Debug_Mode OFF CACHE BOOL "Wether or not you want the project to be build with extra Log output")

IF (Custom_Debug_Mode)
	ADD_DEFINITIONS(-DDEBUG)
ENDIF(Custom_Debug_Mode)



INCLUDE_DIRECTORIES(include)
INSTALL_FILES(/include include)

ADD_SUBDIRECTORY(src)

SET(BUILD_TESTS OFF CACHE BOOL "Wether or not you want the project to include the tests executables")

ADD_SUBDIRECTORY(data)

IF (BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
ENDIF(BUILD_TESTS)

#defining usefull variables.
#GET_TARGET_PROPERTY(Rage_SDL_LIBRARY Rage_SDL LOCATION)
#SET(Rage_SDL_INCLUDE ${Rage_SDL_SOURCE_DIR}/include)
#todo set the dependencies


