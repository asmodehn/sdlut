CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#Project Definition
PROJECT(Rage_SDL)

#
#Checking software dependencies
#

INCLUDE (${CMAKE_ROOT}/Modules/FindSDL.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

#Default Check for SDL
MESSAGE(STATUS "Checking for SDL")
FIND_PACKAGE(SDL REQUIRED)

#If not found ask the user for the location of it
IF ( NOT SDL_FOUND )
	MESSAGE(SEND_ERROR "SDL Not Found - please specify manually")
ENDIF(NOT SDL_FOUND )

#check for openGL
FIND_PACKAGE(OPENGL)
IF ( NOT OPENGL_FOUND )
	MESSAGE(SEND_ERROR "OPENGL Not Found - please specify manually")
ENDIF ( NOT OPENGL_FOUND )


#
#Defining Rules for building Rage_SDL
#

INCLUDE_DIRECTORIES(${Rage_SDL_SOURCE_DIR}/include )
ADD_DEFINITIONS(-DLOGPREFIX=\"Rage_SDL\")

#test for SDL
IF(SDL_FOUND)
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

	
#Compiler Specific rules
IF(CMAKE_CXX_COMPILER STREQUAL "cl")
MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")



#adding definitions for Logs and debug
ADD_DEFINITIONS(-DLOGINDENTLVL=1 -DDEBUG)

INCLUDE_DIRECTORIES(include)
INSTALL_FILES(/include include)
ADD_SUBDIRECTORY(src)

SET(BUILD_TESTS ON CACHE BOOL "Wether or not you want the project to include the tests executables")

ADD_SUBDIRECTORY(data)

IF (BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
ENDIF(BUILD_TESTS)

#defining usefull variables.
#GET_TARGET_PROPERTY(Rage_SDL_LIBRARY Rage_SDL LOCATION)
#SET(Rage_SDL_INCLUDE ${Rage_SDL_SOURCE_DIR}/include)



