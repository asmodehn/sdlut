#include "Scene.hh"

namespace AML
{

Scene::Scene() : SDL::Engine()
{
    _sprite=NULL;
//    Sprite::_display=SDL::App::getInstance().getWindow()->getDisplay();
}

void Scene::put(Sprite sprite, int posX, int posY)
{
    _sprite = &sprite;
    _sprite->setPos(posX,posY);
}

bool Scene::render()
{
    Log << nl << Scene::render() << std::endl;
    return _sprite=NULL && _sprite->render(_screen);
}

}

