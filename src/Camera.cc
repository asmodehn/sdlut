#include "Camera.hh"

std::vector<Camera*> Camera::cameraList;

Camera::Camera(void)
{
	cameraList.push_back(this);
}

Camera * Camera::getCamera(unsigned int index)
{
	if ( index < cameraList.size() )
	return cameraList.at(index);
	else return NULL;
}

void Camera::setRenderArea( SDLBaseSurface * render )
{
	_graphic=render;
}
