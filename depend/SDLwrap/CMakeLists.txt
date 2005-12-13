#Project Definition
PROJECT(SDLWrap)

INCLUDE (${CMAKE_ROOT}/Modules/FindSDL.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

#Default Check for SDL
MESSAGE(STATUS "Checking for SDL")
FIND_PACKAGE(SDL REQUIRED)

#If not found try to get a custom one (default on Windows)
IF (SDL_FOUND STREQUAL "NO")
	MESSAGE(STATUS "SDL Not Found as a package - checking custom install in " ${SDLWrap_SOURCE_DIR}/depend/SDL-*)
	
	#to handle a specific variable used byt the cmake default module (doesnt work ??)
	IF (NOT SDL_LIBRARY_TEMP)
		SET(SDL_LIBRARY_TEMP "Unused - SDL Not found using the default CMake Module")
	ENDIF (NOT SDL_LIBRARY_TEMP)
	
	FILE(GLOB DEPEND_SDL ${SDLWrap_SOURCE_DIR}/depend/SDL-*)
	IF ( DEPEND_SDL )
		MESSAGE(STATUS "Custom Install of SDL found in "${DEPEND_SDL})
	ENDIF ( DEPEND_SDL )
	
	FIND_PATH(SDL_INCLUDE_DIR SDL.h ${DEPEND_SDL}/include )
	FIND_LIBRARY(SDL_LIBRARY SDL ${DEPEND_SDL}/lib)
	FIND_LIBRARY(SDLMAIN_LIBRARY SDLmain ${DEPEND_SDL}/lib)
	
	IF ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
		MESSAGE( FATAL_ERROR "SDL Not Found ! - Please install SDL under ${SDLWrap_SOURCE_DIR}/depend/SDL-*" )
	ELSE ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
		SET(SDL_FOUND "YES")
		MESSAGE( STATUS "SDL Found !")
	ENDIF ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
	
ENDIF(SDL_FOUND STREQUAL "NO")

#check for SDL
IF(SDL_FOUND)
	#adding SDL includes to the build
	INCLUDE_DIRECTORIES(SDLWrap_INCLUDES_FILES ${SDLWrap_SOURCE_DIR}/include ${SDLWrap_SOURCE_DIR}/../Common/include ${SDL_INCLUDE_DIR})
	#adding SDL libraries to the link
	LINK_LIBRARIES (${SDLMAIN_LIBRARY} ${SDL_LIBRARY})
ENDIF(SDL_FOUND)

#check for openGL
FIND_PACKAGE(OPENGL)
IF(OPENGL_FOUND)
	ADD_DEFINITIONS(-DHAVE_OPENGL)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
	ADD_DEFINITIONS(-DLOGPREFIX=\"SDLwrap\")
ELSE (OPENGL_FOUND)
	ADD_DEFINITIONS(-DLOGPREFIX=\"SDLwrap.noGL\")
ENDIF(OPENGL_FOUND)
	
#adding definitions for Logs

ADD_DEFINITIONS(-DLOGINDENTLVL=1)

ADD_LIBRARY(bin/SDLWrap ../Common/src/Logger.cc src/Interface3D.cc src/SDLBaseSurface.cc src/SDLCDRom.cc src/SDLConfig.cc src/SDLCursor.cc src/SDLDisplaySurface.cc src/SDLEvent.cc src/SDLEventHandler.cc src/SDLGLManager.cc src/SDLGLWindow.cc src/SDLManager.cc src/SDLOverlay.cc src/SDLPixelFormat.cc src/SDLPoint.cc src/SDLRect.cc src/SDLRGBSurface.cc src/SDLSurfaceFactory.cc src/SDLVideoInfo.cc src/SDLWindow.cc)

#adding subdirectory for tests
ADD_SUBDIRECTORY(test EXCLUDE_FROM_ALL)


