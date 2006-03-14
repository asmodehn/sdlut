#adding with headers just to have them in generated projects
ADD_LIBRARY(	Rage_AML ../include/AML.hh ../include/Math2D.hh
		Config.cc ../include/Config.hh
		Camera.cc ../include/Camera.hh
		Image.cc ../include/Image.hh
		Layer.cc ../include/Layer.hh
		Scene.cc ../include/Scene.hh
		Sprite.cc ../include/Sprite.hh
		Window.cc ../include/Window.hh
	)


# installing main library
INSTALL_TARGETS(/. FILES Rage_AML)
