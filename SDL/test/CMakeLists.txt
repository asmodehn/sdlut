CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#linking Rage_SDL to all other following executables
LINK_LIBRARIES(Rage_SDL)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(SDLtestVideo SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo Rage_SDL)
