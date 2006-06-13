CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#linking Rage_SDL to all other following executables
LINK_LIBRARIES(Rage_SDL)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(SDLtestver SDLtestver.cc)
ADD_DEPENDENCIES(SDLtestver Rage_SDL)

ADD_EXECUTABLE(SDLtestTimer SDLtestTimer.cc)
ADD_DEPENDENCIES(SDLtestTimer Rage_SDL)

ADD_EXECUTABLE(SDLtestVideo SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo Rage_SDL)

ADD_EXECUTABLE(SDLtestGL SDLtestGL.cc)
ADD_DEPENDENCIES(SDLtestGL Rage_SDL)

ADD_EXECUTABLE(SDLtestFont SDLtestFont.cc)
ADD_DEPENDENCIES(SDLtestFont Rage_SDL)

ADD_EXECUTABLE(SDLtestNet SDLtestNet.cc)
ADD_DEPENDENCIES(SDLtestNet Rage_SDL)

ADD_EXECUTABLE(SDLtestRWCodeDump SDLtestRWCodeDump.cc)
ADD_DEPENDENCIES(SDLtestRWCodeDump Rage_SDL)


