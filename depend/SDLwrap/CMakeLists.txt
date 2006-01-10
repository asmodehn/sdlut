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
	FIND_LIBRARY(SDLMAIN_LIBRARY NAMES SDLmain PATHS ${DEPEND_SDL} ${DEPEND_SDL}/lib ${DEPEND_SDL}/src/main)
	
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
	MESSAGE (STATUS "OpenGL found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_OPENGL)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	ADD_DEFINITIONS(-DLOGPREFIX=\"SDLwrap\")
ELSE (OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL not found." )
	ADD_DEFINITIONS(-DLOGPREFIX=\"SDLwrap.noGL\")
ENDIF(OPENGL_FOUND)

#Compiler Specific rules


IF(CMAKE_CXX_COMPILER STREQUAL "cl")
MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")



#adding definitions for Logs and debug
ADD_DEFINITIONS(-DLOGINDENTLVL=1 -DDEBUG)

#listing headers as well to have them easily accessible in many IDE, not sure about the effect on the make build...
ADD_LIBRARY(	SDLWrap 
		include/SDLWrap.hh
		include/SDLConfig.hh
		include/Logger.hh src/Logger.cc
		include/SDLApp.hh src/SDLApp.cc
		include/SDLWindow.hh src/SDLWindow.cc
		include/SDLEngine.hh src/SDLEngine.cc
		include/SDLBaseSurface.hh src/SDLBaseSurface.cc
		include/SDLCDRom.hh src/SDLCDRom.cc
		include/SDLCursor.hh src/SDLCursor.cc
		include/SDLVideoSurface.hh src/SDLVideoSurface.cc
		include/SDLCriticalEvent.hh src/SDLCriticalEvent.cc
		include/SDLEvent.hh src/SDLEvent.cc
		include/SDLEventManager.hh src/SDLEventManager.cc
		include/SDLKeyboard.hh src/SDLKeyboard.cc
		include/SDLMouse.hh src/SDLMouse.cc
		include/SDLJoystick.hh src/SDLJoystick.cc
		include/SDLGLManager.hh src/SDLGLManager.cc
		include/SDLGLSurface.hh src/SDLGLSurface.cc
		include/SDLManager.hh src/SDLManager.cc
		include/SDLOverlay.hh src/SDLOverlay.cc
		include/SDLPixelFormat.hh src/SDLPixelFormat.cc
		include/SDLPoint.hh src/SDLPoint.cc
		include/SDLRect.hh src/SDLRect.cc
		include/SDLRGBSurface.hh src/SDLRGBSurface.cc
		include/SDLVideoInfo.hh src/SDLVideoInfo.cc
	)

#
#Adding targets for tests
#Not in a subdir, because of the actual dependency being the other way around than the directory hierarchy
#
#TODO : add custom build command to move the needed files for testing (without installing)...

#linking SDLWrap to all other following libraries
LINK_LIBRARIES(SDLWrap)

#trying to dynamically link opengl
ADD_EXECUTABLE(testdyngl  include/SDLWrap.hh test/testdyngl.cc)
ADD_DEPENDENCIES(testdyngl SDLWrap)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(SDLtestInput include/SDLWrap.hh test/SDLtestInput.cc)
ADD_DEPENDENCIES(SDLtestInput SDLWrap)

ADD_EXECUTABLE(checkkeys  include/SDLWrap.hh test/checkkeys.cc)
ADD_DEPENDENCIES(checkkeys SDLWrap)

ADD_EXECUTABLE(graywin  include/SDLWrap.hh test/graywin.cc)
ADD_DEPENDENCIES(graywin SDLWrap)

ADD_EXECUTABLE(loopwave  include/SDLWrap.hh test/loopwave.cc)
ADD_DEPENDENCIES(loopwave SDLWrap)

ADD_EXECUTABLE(SDLtestVideo  include/SDLWrap.hh test/SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo SDLWrap)

ADD_EXECUTABLE(testalpha  include/SDLWrap.hh test/testalpha.cc)
ADD_DEPENDENCIES(testalpha SDLWrap)

ADD_EXECUTABLE(testbitmap  include/SDLWrap.hh test/testbitmap.cc)
ADD_DEPENDENCIES(testbitmap SDLWrap)

ADD_EXECUTABLE(testblitspeed include/SDLWrap.hh  test/testblitspeed.cc)
ADD_DEPENDENCIES(testblitspeed SDLWrap)

ADD_EXECUTABLE(testcdrom include/SDLWrap.hh  test/testcdrom.cc)
ADD_DEPENDENCIES(testcdrom SDLWrap)

ADD_EXECUTABLE(testcpuinfo  include/SDLWrap.hh test/testcpuinfo.cc)
ADD_DEPENDENCIES(testcpuinfo SDLWrap)

ADD_EXECUTABLE(testendian  include/SDLWrap.hh test/testendian.cc)
ADD_DEPENDENCIES(testendian SDLWrap)

ADD_EXECUTABLE(testerror  include/SDLWrap.hh test/testerror.cc)
ADD_DEPENDENCIES(testerror SDLWrap)

ADD_EXECUTABLE(testgamma  include/SDLWrap.hh test/testgamma.cc)
ADD_DEPENDENCIES(testgamma SDLWrap)

ADD_EXECUTABLE(testgl  include/SDLWrap.hh test/testgl.cc)
ADD_DEPENDENCIES(testgl SDLWrap)

ADD_EXECUTABLE(testthread  include/SDLWrap.hh test/testthread.cc)
ADD_DEPENDENCIES(testthread SDLWrap)

ADD_EXECUTABLE(testjoystick  include/SDLWrap.hh test/testjoystick.cc)
ADD_DEPENDENCIES(testjoystick SDLWrap)

ADD_EXECUTABLE(testkeys include/SDLWrap.hh  test/testkeys.cc)
ADD_DEPENDENCIES(testkeys SDLWrap)

ADD_EXECUTABLE(testlock include/SDLWrap.hh  test/testlock.cc)
ADD_DEPENDENCIES(testlock SDLWrap)

ADD_EXECUTABLE(testoverlay2  include/SDLWrap.hh test/testoverlay2.cc)
ADD_DEPENDENCIES(testoverlay2 SDLWrap)

ADD_EXECUTABLE(testoverlay  include/SDLWrap.hh test/testoverlay.cc)
ADD_DEPENDENCIES(testoverlay SDLWrap)

ADD_EXECUTABLE(testpalette include/SDLWrap.hh  test/testpalette.cc)
ADD_DEPENDENCIES(testpalette SDLWrap)

ADD_EXECUTABLE(testsem include/SDLWrap.hh  test/testsem.cc)
ADD_DEPENDENCIES(testsem SDLWrap)

ADD_EXECUTABLE(testsprite include/SDLWrap.hh  test/testsprite.cc)
ADD_DEPENDENCIES(testsprite SDLWrap)

ADD_EXECUTABLE(testtimer  include/SDLWrap.hh test/testtimer.cc)
ADD_DEPENDENCIES(testtimer SDLWrap)

ADD_EXECUTABLE(testtypes include/SDLWrap.hh  test/testtypes.cc)
ADD_DEPENDENCIES(testtypes SDLWrap)

ADD_EXECUTABLE(testver  include/SDLWrap.hh test/testver.cc)
ADD_DEPENDENCIES(testver SDLWrap)

ADD_EXECUTABLE(testvidinfo  include/SDLWrap.hh test/testvidinfo.cc)
ADD_DEPENDENCIES(testvidinfo SDLWrap)

ADD_EXECUTABLE(testwin include/SDLWrap.hh  test/testwin.cc)
ADD_DEPENDENCIES(testwin SDLWrap)

ADD_EXECUTABLE(testwm include/SDLWrap.hh  test/testwm.cc)
ADD_DEPENDENCIES(testwm SDLWrap)

ADD_EXECUTABLE(threadwin  include/SDLWrap.hh test/threadwin.cc)
ADD_DEPENDENCIES(threadwin SDLWrap)

ADD_EXECUTABLE(torturethread include/SDLWrap.hh  test/torturethread.cc)
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
INSTALL_FILES(/data FILES data/SDL_ico.bmp data/sdl_button.gif data/SDL_logo.bmp)

# installing tests
INSTALL_TARGETS(/test FILES testdyngl checkkeys graywin loopwave SDLtest testalpha testbitmap testblitspeed testcdrom testcpuinfo testendian testerror testgamma testgl testthread testjoystick testkeys testlock testoverlay2 testoverlay testpalette testsem testsprite testtimer testtypes testver testvidinfo testwin testwm threadwin torturethread)

# installing tests data
INSTALL_FILES(/test FILES test/icon.bmp test/moose.dat test/picture.xbm test/sail.bmp test/sample.bmp test/sample.wav)
