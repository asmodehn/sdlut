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

WkTestBuild ( SDLtestImage "SDLtestImage.cc" "testRendering.hh" "TestCommon.hh" )
WkTestRun   ( SDL_GIF SDLtestImage "auto" "data/ColorTest.gif" )
WkTestRun   ( SDL_JPEG SDLtestImage "auto" "data/ColorTest.jpg" )
WkTestRun   ( SDL_LBM SDLtestImage "auto" "data/ColorTest.lbm" )
WkTestRun   ( SDL_PCX SDLtestImage "auto" "data/ColorTest.pcx" )
WkTestRun   ( SDL_PNG SDLtestImage "auto" "data/ColorTest.png" )
WkTestRun   ( SDL_PNM SDLtestImage "auto" "data/ColorTest.pnm" )
WkTestRun   ( SDL_TGA SDLtestImage "auto" "data/ColorTest.tga" )
WkTestRun   ( SDL_TIFF SDLtestImage "auto" "data/ColorTest.tif" )

WkTestRun   ( OpenGL_GIF SDLtestImage "auto" "nogl" "data/ColorTest.gif" )
WkTestRun   ( OpenGL_JPEG SDLtestImage "auto" "nogl" "data/ColorTest.jpg" )
WkTestRun   ( OpenGL_LBM SDLtestImage "auto" "nogl" "data/ColorTest.lbm" )
WkTestRun   ( OpenGL_PCX SDLtestImage "auto" "nogl" "data/ColorTest.pcx" )
WkTestRun   ( OpenGL_PNG SDLtestImage "auto" "nogl" "data/ColorTest.png" )
WkTestRun   ( OpenGL_PNM SDLtestImage "auto" "nogl" "data/ColorTest.pnm" )
WkTestRun   ( OpenGL_TGA SDLtestImage "auto" "nogl" "data/ColorTest.tga" )
WkTestRun   ( OpenGL_TIFF SDLtestImage "auto" "nogl" "data/ColorTest.tif" )

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

