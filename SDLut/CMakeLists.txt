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

#WkTestBuild ( testScreenClipRect "testScreenClipRect.cc" "TestCommon.hh")

WkTestBuild ( testImageFormat "testImageFormat.cc" "testRendering.hh" "TestCommon.hh" )
WkTestRun   ( SDL_GIF testImageFormat "auto" "data/test/imageformat/ColorTest.gif" )
WkTestRun   ( SDL_JPEG testImageFormat "auto" "data/test/imageformat/ColorTest.jpg" )
WkTestRun   ( SDL_LBM testImageFormat "auto" "data/test/imageformat/ColorTest.lbm" )
WkTestRun   ( SDL_PCX testImageFormat "auto" "data/test/imageformat/ColorTest.pcx" )
WkTestRun   ( SDL_PNG testImageFormat "auto" "data/test/imageformat/ColorTest.png" )
WkTestRun   ( SDL_PNM testImageFormat "auto" "data/test/imageformat/ColorTest.pnm" )
WkTestRun   ( SDL_TGA testImageFormat "auto" "data/test/imageformat/ColorTest.tga" )
WkTestRun   ( SDL_TIFF testImageFormat "auto" "data/test/imageformat/ColorTest.tif" )

WkTestRun   ( OpenGL_GIF testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.gif" )
WkTestRun   ( OpenGL_JPEG testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.jpg" )
WkTestRun   ( OpenGL_LBM testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.lbm" )
WkTestRun   ( OpenGL_PCX testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.pcx" )
WkTestRun   ( OpenGL_PNG testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.png" )
WkTestRun   ( OpenGL_PNM testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.pnm" )
WkTestRun   ( OpenGL_TGA testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.tga" )
WkTestRun   ( OpenGL_TIFF testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.tif" )

WkTestBuild ( testTransparency "testTransparency.cc" "testRendering.hh" "TestCommon.hh")
WkTestRun   ( SDL_Palette_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_Palette_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_32bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_32bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_64bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_64bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16.png" "data/test/transparency/png/stripe.gif")

WkTestRun   ( OpenGL_Palette_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_Palette_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_32bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_32bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_64bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_64bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16.png" "data/test/transparency/png/stripe.gif")

WkTestBuild (testGrayscaleAlphaTransparency "testGrayscaleAlphaTransparency.cc" "testRendering.hh" "TestCommon.hh" )
WkTestRun (SDL_16bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray8a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_16bits_Gray_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray8a.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_32bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray16a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_32bits_Gray_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray16a.png" "data/test/transparency/png/stripe.gif")

WkTestRun (OpenGL_16bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray8a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_16bits_Gray_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray8a.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_32bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray16a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_32bits_Gray_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray16a.png" "data/test/transparency/png/stripe.gif")

WkTestBuild ( SDLtestPixelFormat )
WkTestRun   ( "PixelFormat" SDLtestPixelFormat )

WkTestBuild (SDLtestRefresh)
WkTestData  (SDLtestRefresh smiley.bmp)

WkTestBuild ( SDLtestApp )
WkTestBuild ( SDLtestDumbLoop )
WkTestBuild ( SDLtestver )

WkTestBuild ( SDLtestEvents )
WkTestBuild ( SDLtestManager )

#WkTestBuild ( SDLtestTimer )
#WkTestBuild ( SDLtestStressTimer )
#WkTestBuild ( SDLtestMutex )
#WkTestBuild ( SDLtestThread )
#WkTestBuild ( SDLtestStressThread )

WkTestBuild ( SDLtestVideo )
WkTestBuild ( SDLtestGL )
WkTestBuild ( SDLtestTextInput ) 

WkTestBuild ( SDLtestFont )

