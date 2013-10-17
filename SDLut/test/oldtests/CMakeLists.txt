CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#linking Rage_SDL to all other following executables
LINK_LIBRARIES(Rage_SDL)

#trying to dynamically link opengl
ADD_EXECUTABLE(testdyngl testdyngl.cc)
ADD_DEPENDENCIES(testdyngl Rage_SDL)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(SDLtestInput SDLtestInput.cc)
ADD_DEPENDENCIES(SDLtestInput Rage_SDL)

ADD_EXECUTABLE(checkkeys checkkeys.cc)
ADD_DEPENDENCIES(checkkeys Rage_SDL)

ADD_EXECUTABLE(graywin graywin.cc)
ADD_DEPENDENCIES(graywin Rage_SDL)

ADD_EXECUTABLE(loopwave  loopwave.cc)
ADD_DEPENDENCIES(loopwave Rage_SDL)

ADD_EXECUTABLE(SDLtestVideo SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo Rage_SDL)

ADD_EXECUTABLE(testalpha testalpha.cc)
ADD_DEPENDENCIES(testalpha Rage_SDL)

SET (OLD_INCLUDES ${INCLUDE_DIRECTORIES})
INCLUDE_DIRECTORIES(${Rage_SDL_SOURCE_DIR}/data )
ADD_EXECUTABLE(testbitmap testbitmap.cc)
ADD_DEPENDENCIES(testbitmap Rage_SDL)
SET (INCLUDE_DIRECTORIES ${OLD_INCLUDES})

ADD_EXECUTABLE(testblitspeed testblitspeed.cc)
ADD_DEPENDENCIES(testblitspeed Rage_SDL)

ADD_EXECUTABLE(testcdrom testcdrom.cc)
ADD_DEPENDENCIES(testcdrom Rage_SDL)

ADD_EXECUTABLE(testcpuinfo testcpuinfo.cc)
ADD_DEPENDENCIES(testcpuinfo Rage_SDL)

ADD_EXECUTABLE(testendian testendian.cc)
ADD_DEPENDENCIES(testendian Rage_SDL)

ADD_EXECUTABLE(testerror testerror.cc)
ADD_DEPENDENCIES(testerror Rage_SDL)

ADD_EXECUTABLE(testgamma testgamma.cc)
ADD_DEPENDENCIES(testgamma Rage_SDL)

ADD_EXECUTABLE(testgl testgl.cc)
ADD_DEPENDENCIES(testgl Rage_SDL)

ADD_EXECUTABLE(testthread testthread.cc)
ADD_DEPENDENCIES(testthread Rage_SDL)

ADD_EXECUTABLE(testjoystick testjoystick.cc)
ADD_DEPENDENCIES(testjoystick Rage_SDL)

ADD_EXECUTABLE(testkeys testkeys.cc)
ADD_DEPENDENCIES(testkeys Rage_SDL)

ADD_EXECUTABLE(testlock testlock.cc)
ADD_DEPENDENCIES(testlock Rage_SDL)

ADD_EXECUTABLE(testoverlay2 testoverlay2.cc)
ADD_DEPENDENCIES(testoverlay2 Rage_SDL)

ADD_EXECUTABLE(testoverlay testoverlay.cc)
ADD_DEPENDENCIES(testoverlay Rage_SDL)

ADD_EXECUTABLE(testpalette testpalette.cc)
ADD_DEPENDENCIES(testpalette Rage_SDL)

ADD_EXECUTABLE(testsem testsem.cc)
ADD_DEPENDENCIES(testsem Rage_SDL)

ADD_EXECUTABLE(testsprite testsprite.cc)
ADD_DEPENDENCIES(testsprite Rage_SDL)

ADD_EXECUTABLE(testtimer  testtimer.cc)
ADD_DEPENDENCIES(testtimer Rage_SDL)

ADD_EXECUTABLE(testtypes testtypes.cc)
ADD_DEPENDENCIES(testtypes Rage_SDL)

ADD_EXECUTABLE(testver testver.cc)
ADD_DEPENDENCIES(testver Rage_SDL)

ADD_EXECUTABLE(testvidinfo testvidinfo.cc)
ADD_DEPENDENCIES(testvidinfo Rage_SDL)

ADD_EXECUTABLE(testwin testwin.cc)
ADD_DEPENDENCIES(testwin Rage_SDL)

ADD_EXECUTABLE(testwm testwm.cc)
ADD_DEPENDENCIES(testwm Rage_SDL)

ADD_EXECUTABLE(threadwin threadwin.cc)
ADD_DEPENDENCIES(threadwin Rage_SDL)

ADD_EXECUTABLE(torturethread torturethread.cc)
ADD_DEPENDENCIES(torturethread Rage_SDL)

# SET_TARGET_PROPERTIES ( testdyngl SDLtestInput checkkeys graywin loopwave SDLtestVideo testalpha testbitmap testblitspeed testcdrom testcpuinfo testendian testerror testgamma testgl testthread testjoystick testkeys testlock testoverlay2 testoverlay testpalette testsem testsprite testtimer testtypes testver testvidinfo testwin testwm threadwin torturethread
# 												PROPERTIES WORKING_DIR $(Rage_SDL_SOURCE_DIR) )

# installing tests
INSTALL_TARGETS(/test FILES SDLtestVideo SDLtestInput testdyngl checkkeys graywin loopwave SDLtest testalpha testbitmap testblitspeed testcdrom testcpuinfo testendian testerror testgamma testgl testthread testjoystick testkeys testlock testoverlay2 testoverlay testpalette testsem testsprite testtimer testtypes testver testvidinfo testwin testwm threadwin torturethread)

