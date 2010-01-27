CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

WkProject ( SDLut CXX)

WkDepends ( Core REQUIRED )
WkDepends ( SDL REQUIRED )
WkDepends ( OpenGL )
WkDepends ( SDL_image)
WkDepends ( SDL_ttf)
WkDepends ( SDL_mixer)
WkDepends ( SDL_net)

WkBuild ( LIBRARY STATIC )

WkDoc()

WkTestBuild ( SDLtestColor )
WkTestRun   ( SDLtestColor )

WkTestBuild (SDLtestRefresh)
WkTestRun   (SDLtestRefresh)

WkTestBuild ( SDLtestApp )
WkTestBuild ( SDLtestDumbLoop )
WkTestBuild ( SDLtestver )

WkTestBuild ( SDLtestEvents )
WkTestBuild ( SDLtestManager )

WkTestBuild ( SDLtestTimer )
WkTestBuild ( SDLtestStressTimer )
WkTestBuild ( SDLtestMutex )
WkTestBuild ( SDLtestThread )
WkTestBuild ( SDLtestStressThread )

WkTestBuild ( SDLtestVideo )
WkTestBuild ( SDLtestGL )
WkTestBuild ( SDLtestTextInput ) 

WkTestBuild ( SDLtestFont )

