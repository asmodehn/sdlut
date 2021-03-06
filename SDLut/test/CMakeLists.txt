CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)

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
CONFIGURE_FILE(data/LS_Initial.png ${SDLut_BINARY_DIR}/test/data/LS_Initial.png COPYONLY)

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

ADD_EXECUTABLE(SDLtestColor SDLtestColor.cc)
ADD_DEPENDENCIES(SDLtestColor SDLut)
ADD_TEST(Test_Color ${EXECUTABLE_OUTPUT_PATH}/SDLtestColor)
ADD_TEST(Test_Color_GL ${EXECUTABLE_OUTPUT_PATH}/SDLtestColor opengl)

ADD_EXECUTABLE(SDLtestDumbLoop SDLtestDumbLoop.cc)
ADD_DEPENDENCIES(SDLtestDumbLoop SDLut)
ADD_TEST(Test_DumbLoop ${EXECUTABLE_OUTPUT_PATH}/SDLtestDumbLoop)

ADD_EXECUTABLE(SDLtestTimer SDLtestTimer.cc)
ADD_DEPENDENCIES(SDLtestTimer SDLut)
ADD_TEST(Timer ${EXECUTABLE_OUTPUT_PATH}/SDLtestTimer)

ADD_EXECUTABLE(SDLtestStressTimer SDLtestStressTimer.cc)
ADD_DEPENDENCIES(SDLtestStressTimer SDLut)
ADD_TEST(Stress_Timer ${EXECUTABLE_OUTPUT_PATH}/SDLtestStressTimer)

ADD_EXECUTABLE(SDLtestThread SDLtestThread.cc)
ADD_DEPENDENCIES(SDLtestThread SDLut)
ADD_TEST(Thread ${EXECUTABLE_OUTPUT_PATH}/SDLtestThread)
ADD_TEST(Thread_wait ${EXECUTABLE_OUTPUT_PATH}/SDLtestThread "wait")

ADD_EXECUTABLE(SDLtestStressThread SDLtestStressThread.cc)
ADD_DEPENDENCIES(SDLtestStressThread SDLut)
ADD_TEST(Stress_Thread ${EXECUTABLE_OUTPUT_PATH}/SDLtestStressThread)

ADD_EXECUTABLE(SDLtestMutex SDLtestMutex.cc)
ADD_DEPENDENCIES(SDLtestMutex SDLut)
ADD_TEST(Thread_Mutex ${EXECUTABLE_OUTPUT_PATH}/SDLtestMutex )

ADD_EXECUTABLE(SDLtestVideo SDLtestVideo.cc)
ADD_DEPENDENCIES(SDLtestVideo SDLut)
ADD_TEST(BMP_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.bmp")
ADD_TEST(PNG_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.png")
ADD_TEST(TIF_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.tif")
ADD_TEST(JPG_Loading ${EXECUTABLE_OUTPUT_PATH}/SDLtestVideo "data/SDLsample.jpg")


ADD_EXECUTABLE(SDLtestScene SDLtestScene.cc)
ADD_DEPENDENCIES(SDLtestScene SDLut)
ADD_TEST(Scene_Test ${EXECUTABLE_OUTPUT_PATH}/SDLtestScene "data/smiley.bmp" )

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

ADD_EXECUTABLE(SDLtestEvents SDLtestEvents.cc)
ADD_DEPENDENCIES(SDLtestEvents SDLut)
ADD_TEST(Events ${EXECUTABLE_OUTPUT_PATH}/SDLtestEvents)

ADD_EXECUTABLE(SDLtestTextInput SDLtestTextInput.cc)
ADD_DEPENDENCIES(SDLtestTextInput SDLut)
ADD_TEST(Text_Input ${EXECUTABLE_OUTPUT_PATH}/SDLtestTextInput)

ADD_EXECUTABLE(SDLtestNet SDLtestNet.cc)
ADD_DEPENDENCIES(SDLtestNet SDLut)

ADD_EXECUTABLE(SDLtestRWCodeDump SDLtestRWCodeDump.cc)
ADD_DEPENDENCIES(SDLtestRWCodeDump SDLut)

ADD_EXECUTABLE(SDLtestLoadingScreen SDLtestLoadingScreen.cc)
ADD_DEPENDENCIES(SDLtestLoadingScreen SDLut)
ADD_TEST(Test_LoadingScreen ${EXECUTABLE_OUTPUT_PATH}/SDLtestLoadingScreen "data/LS_Initial.png")

INSTALL(
TARGETS 
	SDLtestver
	SDLtestTimer
	SDLtestLoadingScreen
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


