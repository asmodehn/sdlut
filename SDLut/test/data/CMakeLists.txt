#
# Library tests data set
#

#copying data files to use when debugging
CONFIGURE_FILE(smiley.bmp ${SDLut_BINARY_DIR}/test/data/smiley.bmp COPYONLY)
CONFIGURE_FILE(moose.dat ${SDLut_BINARY_DIR}/test/data/moose.dat COPYONLY)
CONFIGURE_FILE(picture.xbm ${SDLut_BINARY_DIR}/test/data/picture.xbm COPYONLY)
CONFIGURE_FILE(sail.bmp ${SDLut_BINARY_DIR}/test/data/sail.bmp COPYONLY)
CONFIGURE_FILE(SDLsample.bmp ${SDLut_BINARY_DIR}/test/data/SDLsample.bmp COPYONLY)
CONFIGURE_FILE(SDLsample.jpg ${SDLut_BINARY_DIR}/test/data/SDLsample.jpg COPYONLY)
CONFIGURE_FILE(SDLsample.png ${SDLut_BINARY_DIR}/test/data/SDLsample.png COPYONLY)
CONFIGURE_FILE(SDLsample.tif ${SDLut_BINARY_DIR}/test/data/SDLsample.tif COPYONLY)
CONFIGURE_FILE(sample.wav ${SDLut_BINARY_DIR}/test/data/sample.wav COPYONLY)
CONFIGURE_FILE(ECHELON.TTF ${SDLut_BINARY_DIR}/test/data/ECHELON.TTF COPYONLY)

# installing tests data
INSTALL_FILES(/data FILES
		data/icon.bmp
		data/moose.dat
		data/picture.xbm
		data/sail.bmp
		data/sample.bmp
		data/sample.wav
		data/ECHELON.TTF
	     )

