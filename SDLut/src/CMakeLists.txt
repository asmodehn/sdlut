#adding with headers just to have them in generated projects
ADD_LIBRARY(	Rage_SDL
		SDLEngine.cc
		SDLConfig.cc
		Logger.cc
		SDLApp.cc
		SDLBaseSurface.cc
		SDLCDRom.cc
		SDLCursor.cc
		SDLVideoSurface.cc
		SDLCriticalEvent.cc
		SDLEvent.cc
		SDLEventManager.cc
		SDLKeyboard.cc
		SDLMouse.cc
		SDLJoystick.cc
		SDLGLManager.cc
		SDLManager.cc
		SDLOverlay.cc
		SDLPixelFormat.cc
		SDLPoint.cc
		SDLRect.cc
		SDLRGBSurface.cc
		SDLVideoInfo.cc
		SDLWindow.cc
		SDLRWOps.cc
		SDLFont.cc
		SDLTimer.cc
		SDLResources.inc
	)


# installing main library
INSTALL_TARGETS(/. Rage_SDL)
