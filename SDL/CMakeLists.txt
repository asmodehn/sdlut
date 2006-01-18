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

#If not found try to get a custom one (default on Windows)
IF ( NOT SDL_FOUND )
	MESSAGE(STATUS "SDL Not Found as a package - checking custom install in " ${Rage_SDL_SOURCE_DIR}/depend/SDL-*)
	
	#to handle a specific variable used byt the cmake default module (doesnt work ??)
	IF (NOT SDL_LIBRARY_TEMP)
		SET(SDL_LIBRARY_TEMP "Unused - SDL Not found using the default FindSDL.cmake Module")
	ENDIF (NOT SDL_LIBRARY_TEMP)

	FILE(GLOB DEPEND_SDL ${Rage_SDL_SOURCE_DIR}/depend/SDL-*)
	IF ( DEPEND_SDL )
		MESSAGE(STATUS "Custom Install of SDL found in "${DEPEND_SDL})
	ENDIF ( DEPEND_SDL )
	
	FIND_PATH(SDL_INCLUDE_DIR SDL.h ${DEPEND_SDL}/include )
	FIND_LIBRARY(SDL_LIBRARY NAMES SDL PATHS ${DEPEND_SDL} ${DEPEND_SDL}/lib ${DEPEND_SDL}/src/.libs)
	FIND_LIBRARY(SDLMAIN_LIBRARY NAMES SDLmain PATHS ${DEPEND_SDL} ${DEPEND_SDL}/lib ${DEPEND_SDL}/src/main)
	
	IF ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
		MESSAGE( FATAL_ERROR "SDL Not Found ! - Please copy SDL built libraries under ${Rage_SDL_SOURCE_DIR}/depend/SDL-*" )
	ELSE ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
		SET(SDL_FOUND "YES")
		MESSAGE( STATUS "SDL Found !")
	ENDIF ( NOT SDL_INCLUDE_DIR OR NOT SDL_LIBRARY OR NOT SDLMAIN_LIBRARY )
	
ENDIF(NOT SDL_FOUND )

#check for openGL
FIND_PACKAGE(OPENGL)


#
#Defining Rules for building Rage_SDL
#

INCLUDE_DIRECTORIES(${Rage_SDL_SOURCE_DIR}/include )

#test for SDL
IF(SDL_FOUND)
	#adding SDL includes to the build
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
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
ADD_LIBRARY(	Rage_SDL
		include/SDL.hh
		include/SDLConfig.hh src/SDLConfig.cc
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

#copying data files to use when debugging
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/SDL_icon.bmp ${Rage_SDL_BINARY_DIR}/data/SDL_icon.bmp COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/SDL_logo.bmp ${Rage_SDL_BINARY_DIR}/data/SDL_logo.bmp COPYONLY)

#defining usefull variables to be used by dependant projects.
SET (Rage_SDL_INCLUDE_DIR ${Rage_SDL_SOURCE_DIR}/include)
GET_TARGET_PROPERTY(Rage_SDL_LIBRARY Rage_SDL LOCATION)

#Copying dependencies if needed for debug
IF(DEPEND_SDL)
	IF (WIN32)
		GET_FILENAME_COMPONENT(DEBUG_DIR ${Rage_SDL_LIBRARY} PATH)
		ADD_CUSTOM_COMMAND(TARGET Rage_SDL POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different ${DEPEND_SDL}/lib/SDL.dll ${DEBUG_DIR})
	ENDIF (WIN32)
ENDIF(DEPEND_SDL)

#
#Adding targets for tests
#Not in a subdir, because of the actual dependency being the other way around than the directory hierarchy
#
#TODO : add custom build command to move the needed files for testing (without installing)...

#linking Rage_SDL to all other following executables
LINK_LIBRARIES(Rage_SDL)

# TODO : Still need to copy test data for following tests... temporary, while the test still uses raw SDL.
# Goal : having test using only data/* files...

#trying to dynamically link opengl
ADD_EXECUTABLE(testdyngl  include/SDL.hh test/testdyngl.cc)
ADD_DEPENDENCIES(testdyngl Rage_SDL)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(SDLtestInput include/SDL.hh test/SDLtestInput.cc)
ADD_DEPENDENCIES(SDLtestInput Rage_SDL)

ADD_EXECUTABLE(checkkeys  include/SDL.hh test/checkkeys.cc)
ADD_DEPENDENCIES(checkkeys Rage_SDL)

ADD_EXECUTABLE(graywin  include/SDL.hh test/graywin.cc)
ADD_DEPENDENCIES(graywin Rage_SDL)

ADD_EXECUTABLE(loopwave  include/SDL.hh test/loopwave.cc)
ADD_DEPENDENCIES(loopwave Rage_SDL)

ADD_EXECUTABLE(SDLtestVideo  include/SDL.hh test/SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo Rage_SDL)

ADD_EXECUTABLE(testalpha  include/SDL.hh test/testalpha.cc)
ADD_DEPENDENCIES(testalpha Rage_SDL)

ADD_EXECUTABLE(testbitmap  include/SDL.hh test/testbitmap.cc)
ADD_DEPENDENCIES(testbitmap Rage_SDL)

ADD_EXECUTABLE(testblitspeed include/SDL.hh  test/testblitspeed.cc)
ADD_DEPENDENCIES(testblitspeed Rage_SDL)

ADD_EXECUTABLE(testcdrom include/SDL.hh  test/testcdrom.cc)
ADD_DEPENDENCIES(testcdrom Rage_SDL)

ADD_EXECUTABLE(testcpuinfo  include/SDL.hh test/testcpuinfo.cc)
ADD_DEPENDENCIES(testcpuinfo Rage_SDL)

ADD_EXECUTABLE(testendian  include/SDL.hh test/testendian.cc)
ADD_DEPENDENCIES(testendian Rage_SDL)

ADD_EXECUTABLE(testerror  include/SDL.hh test/testerror.cc)
ADD_DEPENDENCIES(testerror Rage_SDL)

ADD_EXECUTABLE(testgamma  include/SDL.hh test/testgamma.cc)
ADD_DEPENDENCIES(testgamma Rage_SDL)

ADD_EXECUTABLE(testgl  include/SDL.hh test/testgl.cc)
ADD_DEPENDENCIES(testgl Rage_SDL)

ADD_EXECUTABLE(testthread  include/SDL.hh test/testthread.cc)
ADD_DEPENDENCIES(testthread Rage_SDL)

ADD_EXECUTABLE(testjoystick  include/SDL.hh test/testjoystick.cc)
ADD_DEPENDENCIES(testjoystick Rage_SDL)

ADD_EXECUTABLE(testkeys include/SDL.hh  test/testkeys.cc)
ADD_DEPENDENCIES(testkeys Rage_SDL)

ADD_EXECUTABLE(testlock include/SDL.hh  test/testlock.cc)
ADD_DEPENDENCIES(testlock Rage_SDL)

ADD_EXECUTABLE(testoverlay2  include/SDL.hh test/testoverlay2.cc)
ADD_DEPENDENCIES(testoverlay2 Rage_SDL)

ADD_EXECUTABLE(testoverlay  include/SDL.hh test/testoverlay.cc)
ADD_DEPENDENCIES(testoverlay Rage_SDL)

ADD_EXECUTABLE(testpalette include/SDL.hh  test/testpalette.cc)
ADD_DEPENDENCIES(testpalette Rage_SDL)

ADD_EXECUTABLE(testsem include/SDL.hh  test/testsem.cc)
ADD_DEPENDENCIES(testsem Rage_SDL)

ADD_EXECUTABLE(testsprite include/SDL.hh  test/testsprite.cc)
ADD_DEPENDENCIES(testsprite Rage_SDL)

ADD_EXECUTABLE(testtimer  include/SDL.hh test/testtimer.cc)
ADD_DEPENDENCIES(testtimer Rage_SDL)

ADD_EXECUTABLE(testtypes include/SDL.hh  test/testtypes.cc)
ADD_DEPENDENCIES(testtypes Rage_SDL)

ADD_EXECUTABLE(testver  include/SDL.hh test/testver.cc)
ADD_DEPENDENCIES(testver Rage_SDL)

ADD_EXECUTABLE(testvidinfo  include/SDL.hh test/testvidinfo.cc)
ADD_DEPENDENCIES(testvidinfo Rage_SDL)

ADD_EXECUTABLE(testwin include/SDL.hh  test/testwin.cc)
ADD_DEPENDENCIES(testwin Rage_SDL)

ADD_EXECUTABLE(testwm include/SDL.hh  test/testwm.cc)
ADD_DEPENDENCIES(testwm Rage_SDL)

ADD_EXECUTABLE(threadwin  include/SDL.hh test/threadwin.cc)
ADD_DEPENDENCIES(threadwin Rage_SDL)

ADD_EXECUTABLE(torturethread include/SDL.hh  test/torturethread.cc)
ADD_DEPENDENCIES(torturethread Rage_SDL)





#
#Adding rules for installation
#

# installing main library
INSTALL_TARGETS(/. FILES Rage_SDL)
INSTALL_FILES(/include FILES
#"^include/*.hh$")
		include/SDL.hh
		include/SDLConfig.hh
		include/Logger.hh
		include/SDLApp.hh
		include/SDLWindow.hh
		include/SDLEngine.hh
		include/SDLBaseSurface.hh
		include/SDLCDRom.hh
		include/SDLCursor.hh
		include/SDLVideoSurface.hh
		include/SDLCriticalEvent.hh
		include/SDLEvent.hh
		include/SDLEventManager.hh
		include/SDLKeyboard.hh
		include/SDLMouse.hh
		include/SDLJoystick.hh
		include/SDLGLManager.hh
		include/SDLGLSurface.hh
		include/SDLManager.hh
		include/SDLOverlay.hh
		include/SDLPixelFormat.hh
		include/SDLPoint.hh
		include/SDLRect.hh
		include/SDLRGBSurface.hh
		include/SDLVideoInfo.hh)

# installing custom dependencies if needed
IF(DEPEND_SDL)
	IF (WIN32)
	INSTALL_FILES(/. FILES ${DEPEND_SDL}/lib/SDL.dll)
	INSTALL_FILES(/test FILES ${DEPEND_SDL}/lib/SDL.dll)
	ELSE (WIN32)
	INSTALL_FILES(/. FILES ${DEPEND_SDL}/lib/SDL.so)
	INSTALL_FILES(/test FILES ${DEPEND_SDL}/lib/SDL.so)
	ENDIF (WIN32)
ENDIF(DEPEND_SDL)

# installing main shared data
INSTALL_FILES(/data FILES data/SDL_icon.bmp data/SDL_logo.bmp )
#  data/sdl_button.gif 

# installing tests
INSTALL_TARGETS(/test FILES SDLtestVideo SDLtestInput testdyngl checkkeys graywin loopwave SDLtest testalpha testbitmap testblitspeed testcdrom testcpuinfo testendian testerror testgamma testgl testthread testjoystick testkeys testlock testoverlay2 testoverlay testpalette testsem testsprite testtimer testtypes testver testvidinfo testwin testwm threadwin torturethread)

# installing tests data
INSTALL_FILES(/test FILES test/icon.bmp test/moose.dat test/picture.xbm test/sail.bmp test/sample.bmp test/sample.wav)

