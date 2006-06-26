#
# Includes to be copied in the build tree
#

# This file contains the CMake build configuration
CONFIGURE_FILE(CMakeConfig.hh ${SDLut_BINARY_DIR}/include/CMakeConfig.hh )

# install include files
# NB : CMakeConfig.hh should be installed as well to indicate which options have been used to build the library, and use them
#
INSTALL_FILES(/include FILES
		CMakeConfig.hh
		../include/SDL.hh
		../include/SDLConfig.hh
		../include/SDLColor.hh
		../include/SDLEngine.hh
		../include/SDLApp.hh
		../include/SDLBaseSurface.hh
		../include/SDLCDRom.hh
		../include/SDLCursor.hh
		../include/SDLVideoSurface.hh
		../include/SDLEvent.hh
		../include/SDLEventManager.hh
		../include/SDLKeyboard.hh
		../include/SDLMouse.hh
		../include/SDLJoystick.hh
		../include/SDLGLManager.hh
		../include/SDLManager.hh
		../include/SDLOverlay.hh
		../include/SDLPixelFormat.hh
		../include/SDLPoint.hh
		../include/SDLRect.hh
		../include/SDLRGBSurface.hh
		../include/SDLVideoInfo.hh
		../include/SDLWindow.hh
		../include/SDLRWOps.hh
		../include/SDLFont.hh
		../include/SDLTimer.hh
	     )
