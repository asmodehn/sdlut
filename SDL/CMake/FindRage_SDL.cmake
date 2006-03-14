# Locate Rage::SDL library
# This module defines
# Rage_SDL_LIBRARY, the name of the library to link against
# Rage_SDL_FOUND, if false, do not try to link to SDL
# Rage_SDL_INCLUDE_DIR, where to find SDL.hh

FIND_PATH(Rage_SDL_INCLUDE_DIR SDL.hh
  $ENV{Rage_SDL_DIR}/include

#also detecting non installed library -> temporary, should be done manually later
  include
  SDL/include
  ../SDL/include
  )
  
FIND_LIBRARY(Rage_SDL_LIBRARY 
    NAMES Rage_SDL
    PATHS
    $ENV{Rage_SDL_DIR}/lib
    
#also detecting non installed library -> temporary, should be done manually later
		src/debug
		SDL/src/debug
		../SDL/src/debug
    )
    
SET(Rage_SDL_FOUND "NO")
IF(Rage_SDL_LIBRARY)
	SET(Rage_SDL_FOUND "YES")
ENDIF(Rage_SDL_LIBRARY)
