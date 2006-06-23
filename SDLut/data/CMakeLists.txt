#
#	Library data -> None : should be embedded in the lib.
#


#
# Library tests data
#

IF(BUILD_TESTS)

#temp
CONFIGURE_FILE(samplefont.bmp ${EXECUTABLE_OUTPUT_PATH}/data/samplefont.bmp COPYONLY)

#copying data files to use when debugging
CONFIGURE_FILE(smiley.bmp ${EXECUTABLE_OUTPUT_PATH}/data/smiley.bmp COPYONLY)
CONFIGURE_FILE(moose.dat ${EXECUTABLE_OUTPUT_PATH}/data/moose.dat COPYONLY)
CONFIGURE_FILE(picture.xbm ${EXECUTABLE_OUTPUT_PATH}/data/picture.xbm COPYONLY)
CONFIGURE_FILE(sail.bmp ${EXECUTABLE_OUTPUT_PATH}/data/sail.bmp COPYONLY)
CONFIGURE_FILE(sample.bmp ${EXECUTABLE_OUTPUT_PATH}/data/sample.bmp COPYONLY)
CONFIGURE_FILE(sample.wav ${EXECUTABLE_OUTPUT_PATH}/data/sample.wav COPYONLY)
CONFIGURE_FILE(ECHELON.TTF ${EXECUTABLE_OUTPUT_PATH}/data/ECHELON.TTF COPYONLY)

# installing tests data
INSTALL_FILES(/data FILES data/icon.bmp data/moose.dat data/picture.xbm data/sail.bmp data/sample.bmp data/sample.wav data/ECHELON.TTF)

ENDIF(BUILD_TESTS)
