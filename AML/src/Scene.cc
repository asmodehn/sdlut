#include "Scene.hh"
namespace RAGE
{
    namespace AML
    {

        Scene::Scene() : SDL::Engine()
        {
            Log << nl << "Scene::Scene() called ";
            _sprite=NULL;
            //    Sprite::_display=SDL::App::getInstance().getWindow()->getDisplay();
        }

        Scene::~Scene()
        {}

        //bool resize (int width, int height)
        //{
        //}
        //
        //bool setBGColor(const SDL::Color & color)
        //{
        //}

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
}
