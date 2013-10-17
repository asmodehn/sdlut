This is a Developer README for AML

--------------------------
1) Development guideline |
--------------------------

- Code properly, and some coding conventions may arise. Just remember to gather them in a doc.

- Exceptions must be used wisely. Some sort of design pattern using exception to manage C wrapping in C++ has been used in SDLwrap... try to follow the idea. No exception should happen in main part of code. Idealy the core of AML should be fault tolerant ;)

- In the future we want to be able to choose the library we will depend upon. CMake will manage the builds and dependencies checking...

- To test AML, simple little games should be done ( tetris, pacman, invaders, etc. )

- Website : from DocBook only

- Documentation : from Doxygen only

---------------------
2) Development help |
---------------------

- One might consider looking at pygame, the SDL wrapping for python. Good samples of code... 
- check the possiblity to use other existing software output for game contents, like TileStudio, Mappy, etc.

--------------------------
Libraries for the future ?
--------------------------

Considering SDL2.0 docs, there are annex librairies we will have to manage

The SDL Standard libs will be wrapped in the RAGE::SDL part.
The rest of it will be done in AML.

SDL_draw
OpenSceneGraph
OpenInput
ACE
OGRE3D
G3D
NGL/NUI
Cairo/Glitz

TODO : A Poll on the website to prioritise the work.