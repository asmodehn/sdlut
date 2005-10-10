#include "Camera.hh"

std::vector<Camera*> Camera::cameraList;
std::vector<Vector2> Camera::positionList;

Camera::Camera(const Vector2 & position)
{
	cameraList.push_back(this);
	positionList.push_back(position);
	camID=cameraList.size()-1;
	
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
  
//overriding render to handle camera position
void Camera::render(unsigned int myPixCenterX, unsigned int myPixCenterY)
{
	for ( unsigned int i=0;  i<_referee.size(); i++ )
  {
  	Vector2 pos=_position[i];
  	std::cerr << "ref[i] : " <<_referee[i] << std::endl;
  	std::cerr << "pos[i] : " << pos << std::endl;
  	std::cerr << "CameraPos : " << positionList[camID] << std::endl;
    std::cerr << "calling _referee[" << i <<"]->render("<< myPixCenterX-static_cast<int>(pos.x()-positionList[camID].x()) << "," <<myPixCenterY-static_cast<int>(pos.y()-positionList[camID].y())<<")"<<std::endl;
    _referee[i]->render(myPixCenterX-static_cast<int>(pos.x()-positionList[camID].x()),myPixCenterY-static_cast<int>(pos.y()-positionList[camID].y()));
  }
}
