# Locate Rage::SDLut library
# This module defines
# SDLut_LIBRARY, the name of the library to link against
# SDLut_FOUND, if false, do not try to link to SDL
# SDLut_INCLUDE_DIR, where to find SDL.hh

FIND_PATH(SDLut_INCLUDE_DIR SDL.hh
  $ENV{SDLutDIR}/include
  )
  
FIND_LIBRARY(SDLut_LIBRARY 
    NAMES SDLut
    PATHS
    $ENV{SDLutDIR}/lib
    )
    
SET(SDLut_FOUND "NO")
IF(SDLut_LIBRARY)
	SET(SDLut_FOUND "YES")
ENDIF(SDLut_LIBRARY)
