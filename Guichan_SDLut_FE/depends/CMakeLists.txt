CMAKE_MINIMUM_REQUIRED ( VERSION 2.6) 
 
INCLUDE ( CMake/WkCMake.cmake ) 
WkCMakeDir ( CMake ) 

WkSrcDir ( "guichan-0.8.2/src" )
WkIncludeDir ( "guichan-0.8.2/include" )
WkLibDir ( "guichan-0.8.2_build/" )
 
WkProject ( Guichan CXX) 
 
WkBuild ( LIBRARY STATIC )
 