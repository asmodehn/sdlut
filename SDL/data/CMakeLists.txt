#
#	Library data -> None : should be embedded in the lib.
#


#
# Library tests data
#

IF(BUILD_TESTS)

#temp
CONFIGURE_FILE(SDL_logo.bmp ${EXECUTABLE_OUTPUT_PATH}/data/samplefont.bmp COPYONLY)

#copying data files to use when debugging
CONFIGURE_FILE(SDL_logo.bmp ${EXECUTABLE_OUTPUT_PATH}/data/SDL_logo.bmp COPYONLY)
CONFIGURE_FILE(icon.bmp ${EXECUTABLE_OUTPUT_PATH}/data/icon.bmp COPYONLY)
CONFIGURE_FILE(moose.dat ${EXECUTABLE_OUTPUT_PATH}/data/moose.dat COPYONLY)
CONFIGURE_FILE(picture.xbm ${EXECUTABLE_OUTPUT_PATH}/data/picture.xbm COPYONLY)
CONFIGURE_FILE(sail.bmp ${EXECUTABLE_OUTPUT_PATH}/data/sail.bmp COPYONLY)
CONFIGURE_FILE(sample.bmp ${EXECUTABLE_OUTPUT_PATH}/data/sample.bmp COPYONLY)
CONFIGURE_FILE(sample.wav ${EXECUTABLE_OUTPUT_PATH}/data/sample.wav COPYONLY)
CONFIGURE_FILE(sdl_button.gif ${EXECUTABLE_OUTPUT_PATH}/data/sdl_button.gif COPYONLY)
CONFIGURE_FILE(echelon.ttf ${EXECUTABLE_OUTPUT_PATH}/data/echelon.ttf COPYONLY)

# installing tests data
INSTALL_FILES(/data FILES data/SDL_logo.bmo data/icon.bmp data/moose.dat data/picture.xbm data/sail.bmp data/sample.bmp data/sample.wav data/echelon.ttf)

ENDIF(BUILD_TESTS)
