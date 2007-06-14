CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

# Library tests data set

#copying data files to use when debugging
CONFIGURE_FILE(data/smiley.bmp ${SDLut_BINARY_DIR}/test/data/smiley.bmp COPYONLY)
CONFIGURE_FILE(data/moose.dat ${SDLut_BINARY_DIR}/test/data/moose.dat COPYONLY)
CONFIGURE_FILE(data/picture.xbm ${SDLut_BINARY_DIR}/test/data/picture.xbm COPYONLY)
CONFIGURE_FILE(data/sail.bmp ${SDLut_BINARY_DIR}/test/data/sail.bmp COPYONLY)
CONFIGURE_FILE(data/SDLsample.bmp ${SDLut_BINARY_DIR}/test/data/SDLsample.bmp COPYONLY)
CONFIGURE_FILE(data/SDLsample.jpg ${SDLut_BINARY_DIR}/test/data/SDLsample.jpg COPYONLY)
CONFIGURE_FILE(data/SDLsample.png ${SDLut_BINARY_DIR}/test/data/SDLsample.png COPYONLY)
CONFIGURE_FILE(data/SDLsample.tif ${SDLut_BINARY_DIR}/test/data/SDLsample.tif COPYONLY)
CONFIGURE_FILE(data/sample.wav ${SDLut_BINARY_DIR}/test/data/sample.wav COPYONLY)
CONFIGURE_FILE(data/null.wav ${SDLut_BINARY_DIR}/test/data/null.wav COPYONLY)
CONFIGURE_FILE(data/soundSample.wav ${SDLut_BINARY_DIR}/test/data/soundSample.wav COPYONLY)
CONFIGURE_FILE(data/soundSample.ogg ${SDLut_BINARY_DIR}/test/data/soundSample.ogg COPYONLY)
CONFIGURE_FILE(data/musicSample.wav ${SDLut_BINARY_DIR}/test/data/musicSample.wav COPYONLY)
CONFIGURE_FILE(data/musicSample.ogg ${SDLut_BINARY_DIR}/test/data/musicSample.ogg COPYONLY)
CONFIGURE_FILE(data/musicSample.mp3 ${SDLut_BINARY_DIR}/test/data/musicSample.mp3 COPYONLY)
CONFIGURE_FILE(data/ECHELON.TTF ${SDLut_BINARY_DIR}/test/data/ECHELON.TTF COPYONLY)

#linking Rage_SDL to all other following executables
LINK_LIBRARIES(SDLut)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(SDLtestver SDLtestver.cc)
ADD_DEPENDENCIES(SDLtestver SDLut)
ADD_TEST(Version ${EXECUTABLE_OUTPUT_PATH}/SDLtestver)

ADD_EXECUTABLE(SDLtestManager SDLtestManager.cc)
ADD_DEPENDENCIES(SDLtestManager SDLut)
ADD_TEST(Test_Manager ${EXECUTABLE_OUTPUT_PATH}/SDLtestManager)

ADD_EXECUTABLE(SDLtestApp SDLtestApp.cc)
ADD_DEPENDENCIES(SDLtestApp SDLut)
ADD_TEST(Test_App ${EXECUTABLE_OUTPUT_PATH}/SDLtestApp)

ADD_EXECUTABLE(SDLtestDumbLoop SDLtestDumbLoop.cc)
ADD_DEPENDENCIES(SDLtestDumbLoop SDLut)
ADD_TEST(Test_App ${EXECUTABLE_OUTPUT_PATH}/SDLtestDumbLoop)

ADD_EXECUTABLE(SDLtestTimer SDLtestTimer.cc)
ADD_DEPENDENCIES(SDLtestTimer SDLut)
ADD_TEST(Timing ${EXECUTABLE_OUTPUT_PATH}/SDLtestTimer)

ADD_EXECUTABLE(SDLtestThread SDLtestThread.cc)
ADD_DEPENDENCIES(SDLtestThread SDLut)
ADD_TEST(Timing ${EXECUTABLE_OUTPUT_PATH}/SDLtestThread)

ADD_EXECUTABLE(SDLtestVideo SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo SDLut)
ADD_TEST(BMP_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.bmp")
ADD_TEST(PNG_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.png")
ADD_TEST(TIF_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.tif")
ADD_TEST(JPG_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.jpg")

ADD_EXECUTABLE(SDLtestAudioChannel SDLtestAudioChannel.cc)
ADD_DEPENDENCIES(SDLtestAudioChannel SDLut)
ADD_TEST(WAV_Sound ${EXECUTABLE_OUTPUT_PATH}/SDLtestAudioChannel "data/soundSample.wav")
ADD_TEST(OGG_Sound ${EXECUTABLE_OUTPUT_PATH}/SDLtestAudioChannel "data/soundSample.ogg")

ADD_EXECUTABLE(SDLtestAudioMusic SDLtestAudioMusic.cc)
ADD_DEPENDENCIES(SDLtestAudioMusic SDLut)
ADD_TEST(WAV_Music ${EXECUTABLE_OUTPUT_PATH}/SDLtestAudioMusic "data/musicSample.wav")
ADD_TEST(OGG_Music ${EXECUTABLE_OUTPUT_PATH}/SDLtestAudioMusic "data/musicSample.ogg")
ADD_TEST(MP3_Music ${EXECUTABLE_OUTPUT_PATH}/SDLtestAudioMusic "data/musicSample.mp3")

ADD_EXECUTABLE(SDLtestGL SDLtestGL.cc)
ADD_DEPENDENCIES(SDLtestGL SDLut)
ADD_TEST(OpenGL_Display ${EXECUTABLE_OUTPUT_PATH}/SDLtestGL)

ADD_EXECUTABLE(SDLtestFont SDLtestFont.cc)
ADD_DEPENDENCIES(SDLtestFont SDLut)
ADD_TEST(Default_Font ${EXECUTABLE_OUTPUT_PATH}/SDLtestFont)
ADD_TEST(TTF_Font ${EXECUTABLE_OUTPUT_PATH}/SDLtestFont "data/ECHELON.TTF")

ADD_EXECUTABLE(SDLtestNet SDLtestNet.cc)
ADD_DEPENDENCIES(SDLtestNet SDLut)

ADD_EXECUTABLE(SDLtestRWCodeDump SDLtestRWCodeDump.cc)
ADD_DEPENDENCIES(SDLtestRWCodeDump SDLut)

INSTALL(
TARGETS 
	SDLtestver
	SDLtestTimer
	SDLtestVideo
	SDLtestGL
	SDLtestFont
	SDLtestNet
	SDLtestRWCodeDump
	SDLtestAudioChannel
	SDLtestAudioMusic
DESTINATION
	${VERSION}/test
)

# installing tests data
INSTALL(
FILES
	data/smiley.bmp
	data/moose.dat
	data/picture.xbm
	data/sail.bmp
	data/SDLsample.bmp
	data/SDLsample.jpg
	data/SDLsample.png
	data/SDLsample.tif
	data/sample.wav
	data/ECHELON.TTF
DESTINATION
	${VERSION}/test/data
)


