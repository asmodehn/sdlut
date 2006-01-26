#include "Scene.hh"
namespace RAGE
{
    namespace AML
    {
        Scene::Scene()
        {
#ifdef DEBUG
            Log << nl << "Scene::Scene() called ";
#endif
            _sprite=NULL;
            //    Sprite::_display=SDL::App::getInstance().getWindow()->getDisplay();
#ifdef DEBUG
            Log << nl << "Scene::Scene() done ";
#endif

        }

        Scene::~Scene()
        {}

        bool Scene::init (int width, int height)
        {
            return true;
        }

        bool Scene::resize (int width, int height)
        {
            return true;
        }


        void Scene::put(Sprite sprite, int posX, int posY)
        {
#ifdef DEBUG
            Log << nl << "Scene::put() called ... ";
#endif
            _sprite = &sprite;
            _sprite->setPos(posX,posY);
#ifdef DEBUG
            Log << nl << "Scene::put() done. ";
#endif
        }

        bool Scene::render() const
        {
#if (DEBUG == 2)
            Log << nl << "Scene::render() called ..." << std::endl;
#endif
            bool res = false;
            res = _sprite!=NULL && _sprite->render(_screen);

#if (DEBUG == 2)
            Log << nl << "Scene::render() done." << std::endl;
#endif

            return res;
        }

    }
}
