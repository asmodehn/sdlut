#include "Camera.hh"

std::vector<Camera*> Camera::cameraList;
std::vector<Vector2> Camera::positionList;

Camera::Camera(const Vector2 & position)
{
	cameraList.push_back(this);
	camID=cameraList.size()-1;
	positionList.push_back(position);
}

Camera * Camera::getCamera(unsigned int index)
{
	if ( index < cameraList.size() )
	return cameraList.at(index);
	else return NULL;
}


//overriding move : The Camera manage his own position
bool Camera::move(const Vector2& deltap)
{
  positionList[camID]+=deltap;
  return true;
}
  
//overriding render to handl camera position
//camera usually in the midle of the screen
void Camera::render(unsigned int myPixCenterX, unsigned int myPixCenterY)
{
	for ( unsigned int i=0;  i<_referee.size(); i++ )
  {
    Vector2 pos=_position[i];
    _referee[i]->render(static_cast<int>(pos.x()-positionList[camID].x())-myPixCenterX,static_cast<int>(pos.y()-positionList[camID].y())-myPixCenterY);
  }
}
