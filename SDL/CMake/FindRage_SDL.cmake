# Locate Rage::SDL library
# This module defines
# RAGE_SDL_LIBRARY, the name of the library to link against
# RAGE_SDL_FOUND, if false, do not try to link to SDL
# RAGE_SDL_INCLUDE_DIR, where to find SDL.hh

FIND_PATH(RAGE_SDL_INCLUDE_DIR SDL.hh
  $ENV{RAGESDLDIR}/include

#also detecting non installed library
  include
  SDL/include
  ../SDL/include
  )
  
FIND_LIBRARY(RAGE_SDL_LIBRARY 
    NAMES Rage_SDL
    PATHS
    $ENV{RAGESDLDIR}/lib
    
#also detecting non installed library
		src/debug
		SDL/src/debug
		../SDL/src/debug
    )
    
SET(RAGE_SDL_FOUND "NO")
IF(RAGE_SDL_LIBRARY)
	SET(RAGE_SDL_FOUND "YES")
ENDIF(RAGE_SDL_LIBRARY)
