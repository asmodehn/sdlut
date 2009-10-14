CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

WkProject ( Core CXX)

#Optional for now... Functor implements whats needed so far as well
#WkDependsInclude ( SigC++ )

WkBuild ( LIBRARY STATIC )

#WkDependsLink ( SigC++ )
WkLink()

WkDoc()

