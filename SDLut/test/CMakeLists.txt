CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#Configuring and building test data
ADD_SUBDIRECTORY(data)

#linking Rage_SDL to all other following executables
LINK_LIBRARIES(SDLut)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(SDLtestver SDLtestver.cc)
ADD_DEPENDENCIES(SDLtestver SDLut)

ADD_EXECUTABLE(SDLtestTimer SDLtestTimer.cc)
ADD_DEPENDENCIES(SDLtestTimer SDLut)

ADD_EXECUTABLE(SDLtestVideo SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo SDLut)
ADD_TEST(BMP_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.bmp")
ADD_TEST(PNG_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.png")
ADD_TEST(TIF_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.tif")
ADD_TEST(JPG_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.jpg")

ADD_EXECUTABLE(SDLtestGL SDLtestGL.cc)
ADD_DEPENDENCIES(SDLtestGL SDLut)

ADD_EXECUTABLE(SDLtestFont SDLtestFont.cc)
ADD_DEPENDENCIES(SDLtestFont SDLut)

ADD_EXECUTABLE(SDLtestNet SDLtestNet.cc)
ADD_DEPENDENCIES(SDLtestNet SDLut)

ADD_EXECUTABLE(SDLtestRWCodeDump SDLtestRWCodeDump.cc)
ADD_DEPENDENCIES(SDLtestRWCodeDump SDLut)


