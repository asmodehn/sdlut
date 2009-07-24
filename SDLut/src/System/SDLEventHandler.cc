#include "System/SDLEventHandler.hh"
#include "SDLApp.hh" //for default resize

#include "SDLConfig.hh"


namespace RAGE
{
    namespace SDL
	{

    bool DefaultEventHandler::handleActiveEvent(bool gain, bool active, bool inputfocus, bool mousefocus)
    {
        return false;
    }

	bool DefaultEventHandler::handleResizeEvent(int w, int h)
    {
        App::getInstance().getDisplay().resizeDisplay(w,h);
        return true;
    }

    bool DefaultEventHandler::handleExposeEvent()
    {
        return false;
    }

    bool DefaultEventHandler::handleSysWMEvent(void)
    {
        return false;
    }

    bool DefaultEventHandler::handleUserEvent(Event::Type type, int code, void* data1, void* data2)
    {
        return false;
    }

    bool DefaultEventHandler::handleQuitEvent(void)
    {
		App::getInstance().requestTermination();
        return true;
    }

    bool DefaultEventHandler::handleEvent(Event &event)
    {
        return false;
    }






	} //SDL
}//RAGE
