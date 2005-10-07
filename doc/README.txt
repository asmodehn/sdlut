This is a Developer README for AML

--------------------------
1) Development guideline |
--------------------------

- Code properly, and some coding conventions may arise. Just remember to gather them in a doc.

- Exceptions must be used wisely. Some sort of design pattern using exception to manage C wrapping in C++ has been used in SDLwrap... try to follow the idea. No exception should happen in main part of code. Idealy the core of AML should be fault tolerant ;)

- In the future we want to be able to choose the library we will depend upon. So everything in "depend/[libname]wrap" folder is tied to the library used, and everything in the root folder should be as independant as possible from the library used.

- The wrapping layer for each library should idealy do the same test than the library has, but using the wrap...

- To test AML, simple little games should be done ( tetris, pacman, invaders, etc. )

- Website : from DocBook only

- Documentation : from Doxygen only

--------------------------
Libraries for the future ?
--------------------------

SDL_draw
SDL_ttf
SDL_mixer
OpenSceneGraph
OpenInput
ACE
OGRE3D
G3D
AALIB
NCURSES
NGL/NUI
Cairo/Glitz

TODO : A Poll on the website to prioritise the work.