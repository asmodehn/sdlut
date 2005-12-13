#Project Definition
PROJECT(SDLWrap)

INCLUDE (${CMAKE_ROOT}/Modules/FindSDL.cmake)

#Checking for SDL
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
	IF ( NOT DEPEND_SDL )
		MESSAGE(STATUS "Custom Install of SDL found in "${DEPEND_SDL})
	ENDIF ( NOT DEPEND_SDL )
	
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

INCLUDE_DIRECTORIES(SDLWrap_INCLUDES_FILES ${SDLWrap_SOURCE_DIR}/include ${SDLWrap_SOURCE_DIR}/../Common/include ${SDL_INCLUDE_DIR})

LINK_LIBRARIES (${SDLMAIN_LIBRARY} ${SDL_LIBRARY})
ADD_LIBRARY(SDLWrap ../Common/src/Logger.cc src/Interface3D.cc src/SDLBaseSurface.cc src/SDLCDRom.cc src/SDLConfig.cc src/SDLCursor.cc src/SDLDisplaySurface.cc src/SDLEvent.cc src/SDLEventHandler.cc src/SDLGLManager.cc src/SDLGLWindow.cc src/SDLManager.cc src/SDLOverlay.cc src/SDLPixelFormat.cc src/SDLPoint.cc src/SDLRect.cc src/SDLRGBSurface.cc src/SDLSurfaceFactory.cc src/SDLVideoInfo.cc src/SDLWindow.cc)


