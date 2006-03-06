#
#	Library data
#

#copying data files to use when debugging
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/SDL_icon.bmp ${Rage_SDL_BINARY_DIR}/data/SDL_icon.bmp COPYONLY)
# we wil get rid of this when we will have the RWOps wrapped so we can embed that in the source code :)

# installing main shared data
INSTALL_FILES(/data FILES data/SDL_icon.bmp )

#
# Library tests data
#

IF(BUILD_TESTS)

#copying data files to use when debugging
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/SDL_logo.bmp ${Rage_SDL_BINARY_DIR}/test/data/SDL_logo.bmp COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/icon.bmp ${Rage_SDL_BINARY_DIR}/test/data/icon.bmp COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/moose.dat ${Rage_SDL_BINARY_DIR}/test/data/moose.dat COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/picture.xbm ${Rage_SDL_BINARY_DIR}/test/data/picture.xbm COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/sail.bmp ${Rage_SDL_BINARY_DIR}/test/data/sail.bmp COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/sample.bmp ${Rage_SDL_BINARY_DIR}/test/data/sample.bmp COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/sample.wav ${Rage_SDL_BINARY_DIR}/test/data/sample.wav COPYONLY)
CONFIGURE_FILE(${Rage_SDL_SOURCE_DIR}/data/sdl_button.gif ${Rage_SDL_BINARY_DIR}/test/data/sdl_button.gif COPYONLY)

# installing tests data
INSTALL_FILES(/data FILES data/SDL_logo.bmo data/icon.bmp data/moose.dat data/picture.xbm data/sail.bmp data/sample.bmp data/sample.wav)

ENDIF(BUILD_TESTS)
