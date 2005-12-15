CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#Project Definition
PROJECT(SDLWrap)

#
#Checking software dependencies
#

INCLUDE (${CMAKE_ROOT}/Modules/FindSDL.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

#Default Check for SDL
MESSAGE(STATUS "Checking for SDL")
FIND_PACKAGE(SDL REQUIRED)

#If not found try to get a custom one (default on Windows)
IF ( NOT SDL_FOUND )
	MESSAGE(STATUS "SDL Not Found as a package - checking custom install in " ${SDLWrap_SOURCE_DIR}/depend/SDL-*)
	
	#to handle a specific variable used byt the cmake default module (doesnt work ??)
	IF (NOT SDL_LIBRARY_TEMP)
		SET(SDL_LIBRARY_TEMP "Unused - SDL Not found using the default FindSDL.cmake Module")
	ENDIF (NOT SDL_LIBRARY_TEMP)
	

	FILE(GLOB DEPEND_SDL ${SDLWrap_SOURCE_DIR}/depend/SDL-*)
	IF ( DEPEND_SDL )
		MESSAGE(STATUS "Custom Install of SDL found in "${DEPEND_SDL})
	ENDIF ( DEPEND_SDL )
	
	FIND_PATH(SDL_INCLUDE_DIR SDL.h ${DEPEND_SDL}/include )
	FIND_LIBRARY(SDL_LIBRARY NAMES SDL PATHS ${DEPEND_SDL} ${DEPEND_SDL}/lib ${DEPEND_SDL}/src/.libs)
	FIND_LIBRARY(SDLMAIN_LIBRARY NAMES SDLmain PATHS ${DEPEND_SDL} ${DEPEND_SDL}/lib ${DEPEND_SDL}/main)
	
	IF ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
		MESSAGE( FATAL_ERROR "SDL Not Found ! - Please copy SDL built libraries under ${SDLWrap_SOURCE_DIR}/depend/SDL-*" )
	ELSE ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
		SET(SDL_FOUND "YES")
		MESSAGE( STATUS "SDL Found !")
	ENDIF ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
	
ENDIF(NOT SDL_FOUND )

#check for openGL
FIND_PACKAGE(OPENGL)


#
#Defining Rules for building SDLWrap
#

#test for SDL
IF(SDL_FOUND)
	#adding SDL includes to the build
	INCLUDE_DIRECTORIES(SDLWrap_INCLUDES_FILES ${SDLWrap_SOURCE_DIR}/include ${SDLWrap_SOURCE_DIR}/../Common/include ${SDL_INCLUDE_DIR})
	#adding SDL libraries to the link
	LINK_LIBRARIES (${SDLMAIN_LIBRARY} ${SDL_LIBRARY})
ENDIF(SDL_FOUND)

#test for openGL
IF(OPENGL_FOUND)
	ADD_DEFINITIONS(-DHAVE_OPENGL)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	ADD_DEFINITIONS(-DLOGPREFIX=\"SDLwrap\")
ELSE (OPENGL_FOUND)
	ADD_DEFINITIONS(-DLOGPREFIX=\"SDLwrap.noGL\")
ENDIF(OPENGL_FOUND)


#adding definitions for Logs
ADD_DEFINITIONS(-DLOGINDENTLVL=1)

#setting up flags depending on platform
IF(WIN32)
#TODO : disable the warning in VS about exception specifications.
ENDIF(WIN32)

ADD_LIBRARY(SDLWrap ../Common/src/Logger.cc src/Interface3D.cc src/SDLBaseSurface.cc src/SDLCDRom.cc src/SDLConfig.cc src/SDLCursor.cc src/SDLDisplaySurface.cc src/SDLEvent.cc src/SDLEventHandler.cc src/SDLGLManager.cc src/SDLGLWindow.cc src/SDLManager.cc src/SDLOverlay.cc src/SDLPixelFormat.cc src/SDLPoint.cc src/SDLRect.cc src/SDLRGBSurface.cc src/SDLSurfaceFactory.cc src/SDLVideoInfo.cc src/SDLWindow.cc)

#
#Adding targets for tests
#Not in a subdir, because of the actual dependency being the other way around than the directory hierarchy
#

#linking SDLWrap to all other following libraries
LINK_LIBRARIES(SDLWrap)

#trying to dynamiccaly link opengl
ADD_EXECUTABLE(testdyngl test/testdyngl.cc)
ADD_DEPENDENCIES(testdyngl SDLWrap)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(checkkeys test/checkkeys.cc)
ADD_DEPENDENCIES(checkkeys SDLWrap)

ADD_EXECUTABLE(graywin test/graywin.cc)
ADD_DEPENDENCIES(graywin SDLWrap)

ADD_EXECUTABLE(loopwave test/loopwave.cc)
ADD_DEPENDENCIES(loopwave SDLWrap)

ADD_EXECUTABLE(SDLtest test/SDLtest.cc)
ADD_DEPENDENCIES(SDLtest SDLWrap)

ADD_EXECUTABLE(testalpha test/testalpha.cc)
ADD_DEPENDENCIES(testalpha SDLWrap)

ADD_EXECUTABLE(testbitmap test/testbitmap.cc)
ADD_DEPENDENCIES(testbitmap SDLWrap)

ADD_EXECUTABLE(testblitspeed test/testblitspeed.cc)
ADD_DEPENDENCIES(testblitspeed SDLWrap)

ADD_EXECUTABLE(testcdrom test/testcdrom.cc)
ADD_DEPENDENCIES(testcdrom SDLWrap)

ADD_EXECUTABLE(testcpuinfo test/testcpuinfo.cc)
ADD_DEPENDENCIES(testcpuinfo SDLWrap)

ADD_EXECUTABLE(testendian test/testendian.cc)
ADD_DEPENDENCIES(testendian SDLWrap)

ADD_EXECUTABLE(testerror test/testerror.cc)
ADD_DEPENDENCIES(testerror SDLWrap)

ADD_EXECUTABLE(testgamma test/testgamma.cc)
ADD_DEPENDENCIES(testgamma SDLWrap)

ADD_EXECUTABLE(testgl test/testgl.cc)
ADD_DEPENDENCIES(testgl SDLWrap)

ADD_EXECUTABLE(testthread test/testthread.cc)
ADD_DEPENDENCIES(testthread SDLWrap)

ADD_EXECUTABLE(testjoystick test/testjoystick.cc)
ADD_DEPENDENCIES(testjoystick SDLWrap)

ADD_EXECUTABLE(testkeys test/testkeys.cc)
ADD_DEPENDENCIES(testkeys SDLWrap)

ADD_EXECUTABLE(testlock test/testlock.cc)
ADD_DEPENDENCIES(testlock SDLWrap)

ADD_EXECUTABLE(testoverlay2 test/testoverlay2.cc)
ADD_DEPENDENCIES(testoverlay2 SDLWrap)

ADD_EXECUTABLE(testoverlay test/testoverlay.cc)
ADD_DEPENDENCIES(testoverlay SDLWrap)

ADD_EXECUTABLE(testpalette test/testpalette.cc)
ADD_DEPENDENCIES(testpalette SDLWrap)

ADD_EXECUTABLE(testsem test/testsem.cc)
ADD_DEPENDENCIES(testsem SDLWrap)

ADD_EXECUTABLE(testsprite test/testsprite.cc)
ADD_DEPENDENCIES(testsprite SDLWrap)

ADD_EXECUTABLE(testtimer test/testtimer.cc)
ADD_DEPENDENCIES(testtimer SDLWrap)

ADD_EXECUTABLE(testtypes test/testtypes.cc)
ADD_DEPENDENCIES(testtypes SDLWrap)

ADD_EXECUTABLE(testver test/testver.cc)
ADD_DEPENDENCIES(testver SDLWrap)

ADD_EXECUTABLE(testvidinfo test/testvidinfo.cc)
ADD_DEPENDENCIES(testvidinfo SDLWrap)

ADD_EXECUTABLE(testwin test/testwin.cc)
ADD_DEPENDENCIES(testwin SDLWrap)

ADD_EXECUTABLE(testwm test/testwm.cc)
ADD_DEPENDENCIES(testwm SDLWrap)

ADD_EXECUTABLE(threadwin test/threadwin.cc)
ADD_DEPENDENCIES(threadwin SDLWrap)

ADD_EXECUTABLE(torturethread test/torturethread.cc)
ADD_DEPENDENCIES(torturethread SDLWrap)
 
#
#Adding rules for installation
#

# installing main library
INSTALL_TARGETS(/. FILES SDLWrap)
INSTALL_FILES(/include FILES "^include/*.hh$")

# installing dependency if needed
#IF(DEPEND_SDL)
#	INSTALL_FILES(/. FILES ${DEPEND_SDL}/lib/SDL.dll ${DEPEND_SDL}/lib/SDL.so)
#ENDIF(DEPEND_SDL)

# installing main shared data
INSTALL_FILES(/data FILES data/SDL.ico data/sdl_button.gif data/SDL_logo.bmp)

# installing tests
INSTALL_TARGETS(/test FILES testdyngl checkkeys graywin loopwave SDLtest testalpha testbitmap testblitspeed testcdrom testcpuinfo testendian testerror testgamma testgl testthread testjoystick testkeys testlock testoverlay2 testoverlay testpalette testsem testsprite testtimer testtypes testver testvidinfo testwin testwm threadwin torturethread)

# installing tests data
INSTALL_FILES(/test FILES test/icon.bmp test/moose.dat test/picture.xbm test/sail.bmp test/sample.bmp test/sample.wav)
