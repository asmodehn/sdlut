#adding with headers to have them in generated projects
#ADD_LIBRARY(
ADD_EXECUTABLE(
		Project_0
		Project0.cpp ../include/Project0.hh 
		Base.cpp ../include/Base.hh 
		BattleField.cpp ../include/BattleField.hh
		Character_Base.cpp ../include/Character_Base.hh
		Daemons.cpp ../include/Daemons.hh
		Input_Management.cpp ../include/Input_Management.hh
		Menus.cpp ../include/Menus.hh
		Monster_Base.cpp ../include/Monster_Base.hh
		Monster_Factory.cpp ../include/Monster_Factory.hh
		Monsters.cpp ../include/Monsters.hh
		Render_Engine.cpp ../include/Render_Engine.hh

#adding data  to have them in generated projects
		../data/Arrow.bmp
		../data/BackGround_Map.txt
		../data/Character_Archer.bmp
		../data/Character_Fighter.bmp
		../data/ECHELON.TTF
		../data/Environment_Map.txt
		../data/Grass.png
		"../data/Houses Tileset.png"
		../data/LeaveMenu_NoSelected.png
		../data/LeaveMenu_YesSelected.png
		../data/Monsters5.bmp
		../data/Rock.png
		"../data/Sand Tileset.png"
		"../data/Trees Tileset.png"
		../data/Wall.png
		../data/Water.png

#adding spec to have it in generated projects
		"../Specifs/2D/2D Design v0.02.odt"
	)