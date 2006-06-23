#
# Includes to be copied in the build tree
#

# This file contains the CMake configuration
CONFIGURE_FILE(SDLConfig.hh ${SDLut_BINARY_DIR}/include/SDLConfig.hh )

# The other files shouldnt be changed
CONFIGURE_FILE(SDL.hh ${SDLut_BINARY_DIR}/include/SDL.hh COPYONLY)
CONFIGURE_FILE(SDLColor.hh ${SDLut_BINARY_DIR}/include/SDLColor.hh COPYONLY)
CONFIGURE_FILE(SDLEngine.hh ${SDLut_BINARY_DIR}/include/SDLEngine.hh COPYONLY)
CONFIGURE_FILE(SDLApp.hh ${SDLut_BINARY_DIR}/include/SDLApp.hh COPYONLY)
CONFIGURE_FILE(SDLBaseSurface.hh ${SDLut_BINARY_DIR}/include/SDLBaseSurface.hh COPYONLY)
CONFIGURE_FILE(SDLCDRom.hh ${SDLut_BINARY_DIR}/include/SDLCDRom.hh COPYONLY)
CONFIGURE_FILE(SDLCursor.hh ${SDLut_BINARY_DIR}/include/SDLCursor.hh COPYONLY)
CONFIGURE_FILE(SDLVideoSurface.hh ${SDLut_BINARY_DIR}/include/SDLVideoSurface.hh COPYONLY)
CONFIGURE_FILE(SDLCriticalEvent.hh ${SDLut_BINARY_DIR}/include/SDLCriticalEvent.hh COPYONLY)
CONFIGURE_FILE(SDLEvent.hh ${SDLut_BINARY_DIR}/include/SDLEvent.hh COPYONLY)
CONFIGURE_FILE(SDLEventManager.hh ${SDLut_BINARY_DIR}/include/SDLEventManager.hh COPYONLY)
CONFIGURE_FILE(SDLKeyboard.hh ${SDLut_BINARY_DIR}/include/SDLKeyboard.hh COPYONLY)
CONFIGURE_FILE(SDLMouse.hh ${SDLut_BINARY_DIR}/include/SDLMouse.hh COPYONLY)
CONFIGURE_FILE(SDLJoystick.hh ${SDLut_BINARY_DIR}/include/SDLJoystick.hh COPYONLY)
CONFIGURE_FILE(SDLGLManager.hh ${SDLut_BINARY_DIR}/include/SDLGLManager.hh COPYONLY)
CONFIGURE_FILE(SDLManager.hh ${SDLut_BINARY_DIR}/include/SDLManager.hh COPYONLY)
CONFIGURE_FILE(SDLOverlay.hh ${SDLut_BINARY_DIR}/include/SDLOverlay.hh COPYONLY)
CONFIGURE_FILE(SDLPixelFormat.hh ${SDLut_BINARY_DIR}/include/SDLPixelFormat.hh COPYONLY)
CONFIGURE_FILE(SDLPoint.hh ${SDLut_BINARY_DIR}/include/SDLPoint.hh COPYONLY)
CONFIGURE_FILE(SDLRect.hh ${SDLut_BINARY_DIR}/include/SDLRect.hh COPYONLY)
CONFIGURE_FILE(SDLRGBSurface.hh ${SDLut_BINARY_DIR}/include/SDLRGBSurface.hh COPYONLY)
CONFIGURE_FILE(SDLVideoInfo.hh ${SDLut_BINARY_DIR}/include/SDLVideoInfo.hh COPYONLY)
CONFIGURE_FILE(SDLWindow.hh ${SDLut_BINARY_DIR}/include/SDLWindow.hh COPYONLY)
CONFIGURE_FILE(SDLRWOps.hh ${SDLut_BINARY_DIR}/include/SDLRWOps.hh COPYONLY)
CONFIGURE_FILE(SDLFont.hh ${SDLut_BINARY_DIR}/include/SDLFont.hh COPYONLY)
CONFIGURE_FILE(SDLTimer.hh ${SDLut_BINARY_DIR}/include/SDLTimer.hh COPYONLY)

# install include files
# NB : SDLConfig.hh shouldnt be copied, it is not aimed to be use by the user.
#
INSTALL_FILES(/include FILES
		include/SDL.hh
		include/SDLColor.hh
		include/SDLEngine.hh
		include/SDLApp.hh
		include/SDLBaseSurface.hh
		include/SDLCDRom.hh
		include/SDLCursor.hh
		include/SDLVideoSurface.hh
		include/SDLEvent.hh
		include/SDLEventManager.hh
		include/SDLKeyboard.hh
		include/SDLMouse.hh
		include/SDLJoystick.hh
		include/SDLGLManager.hh
		include/SDLManager.hh
		include/SDLOverlay.hh
		include/SDLPixelFormat.hh
		include/SDLPoint.hh
		include/SDLRect.hh
		include/SDLRGBSurface.hh
		include/SDLVideoInfo.hh
		include/SDLWindow.hh
		include/SDLRWOps.hh
		include/SDLFont.hh
		include/SDLTimer.hh
	     )
