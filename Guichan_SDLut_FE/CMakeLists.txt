CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

WkProject ( Guichan_SDLut_FE CXX)

WkDepends ( SDLut REQUIRED )
WkDepends ( Guichan REQUIRED )

WkBuild ( LIBRARY STATIC )

WkDoc()

WkTestBuild(sdlutaction action.hpp sdlutaction.cpp)
WkTestData(sdlutaction fixedfont.bmp )

WkTestBuild(sdluthelloworld helloworld.hpp sdluthelloworld.cpp)
WkTestData(sdluthelloworld fixedfont.bmp )

WkTestBuild(sdlutwidgets widgets.hpp sdlutwidgets.cpp)
WkTestData(sdlutwidgets fixedfont.bmp gui-chan.bmp darkbitslogo_by_haiko.bmp)
