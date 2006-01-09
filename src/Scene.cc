#include "Scene.hh"

namespace AML
{

Scene::Scene()
{
    Sprite::_display=SDL::App::getInstance().getWindow()->getDisplay();
}

void Scene::put(Sprite sprite, int posX, int posY)
{
    _sprite = &sprite;
    _sprite->setPos(posX,posY);
}

void Scene::render()
{
    _sprite->render();
}

}

