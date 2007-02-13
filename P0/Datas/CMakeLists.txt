#copying Datas (useful when debugging)

	#Battlefield
CONFIGURE_FILE(	Battlefield/BackGround_Map.txt ${Project_0_BINARY_DIR}/Datas/Battlefield/BackGround_Map.txt COPYONLY)
CONFIGURE_FILE(	Battlefield/Environment_Map.txt ${Project_0_BINARY_DIR}/Datas/Battlefield/Environment_Map.txt COPYONLY)
CONFIGURE_FILE(	Battlefield/Grass.png ${Project_0_BINARY_DIR}/Datas/Battlefield/Grass.png COPYONLY)
CONFIGURE_FILE(	"Battlefield/Houses Tileset.png" "${Project_0_BINARY_DIR}/Datas/Battlefield/Houses Tileset.png" COPYONLY)
CONFIGURE_FILE(	Battlefield/Rock.png ${Project_0_BINARY_DIR}/Datas/Battlefield/Rock.png COPYONLY)
CONFIGURE_FILE(	"Battlefield/Sand Tileset.png" "${Project_0_BINARY_DIR}/Datas/Battlefield/Sand Tileset.png" COPYONLY)
CONFIGURE_FILE(	"Battlefield/tankbrigade.bmp" "${Project_0_BINARY_DIR}/Datas/Battlefield/tankbrigade.bmp" COPYONLY)
CONFIGURE_FILE(	"Battlefield/Trees Tileset.png" "${Project_0_BINARY_DIR}/Datas/Battlefield/Trees Tileset.png" COPYONLY)
CONFIGURE_FILE(	Battlefield/Wall.png ${Project_0_BINARY_DIR}/Datas/Battlefield/Wall.png COPYONLY)
CONFIGURE_FILE(	Battlefield/Water.png ${Project_0_BINARY_DIR}/Datas/Battlefield/Water.png COPYONLY)

	#Characters
CONFIGURE_FILE(	Characters/Character_Archer.png ${Project_0_BINARY_DIR}/Datas/Characters/Character_Archer.png COPYONLY)
CONFIGURE_FILE(	Characters/Character_Fighter.png ${Project_0_BINARY_DIR}/Datas/Characters/Character_Fighter.png COPYONLY)
CONFIGURE_FILE(	"Characters/Life Bar Tile.bmp" "${Project_0_BINARY_DIR}/DatasCharacters/Life Bar Tile.bmp" COPYONLY)
CONFIGURE_FILE(	"Characters/Skeletons Tile.bmp" "${Project_0_BINARY_DIR}/Datas/Characters/Skeletons Tile.bmp" COPYONLY)
CONFIGURE_FILE(	"Characters/Skeletons.ini" "${Project_0_BINARY_DIR}/Datas/Characters/Skeletons.ini" COPYONLY)
CONFIGURE_FILE(	"Characters/Worms Tile.bmp" "${Project_0_BINARY_DIR}/Datas/Characters/Worms Tile.bmp" COPYONLY)
CONFIGURE_FILE(	"Characters/Worms.ini" "${Project_0_BINARY_DIR}/Datas/Characters/Worms.ini" COPYONLY)

	#Fonts
CONFIGURE_FILE(	Fonts/SlimSansSerif.ttf ${Project_0_BINARY_DIR}/Datas/Fonts/SlimSansSerif.ttf COPYONLY)

	#Interface
CONFIGURE_FILE(	Interface/LeaveMenu_NoSelected.png ${Project_0_BINARY_DIR}/Datas/Interface/LeaveMenu_NoSelected.png COPYONLY)
CONFIGURE_FILE(	Interface/LeaveMenu_YesSelected.png ${Project_0_BINARY_DIR}/Datas/Interface/LeaveMenu_YesSelected.png COPYONLY)
CONFIGURE_FILE(	"Interface/Victory Screen.png" "${Project_0_BINARY_DIR}/Datas/Interface/Victory Screen.png" COPYONLY)

	#Items
CONFIGURE_FILE( Items/Arrow.png "${Project_0_BINARY_DIR}/Datas/Items/Arrow.png")
#!!!!! Cmake BUG on copying Arrow.png file: copy failed, dest file 1k instead of src 4k => dest completly unusable   !!!!!

	#Movies


	#Musics
CONFIGURE_FILE(	"Musics/Temple.wav" "${Project_0_BINARY_DIR}/Datas/Musics/Temple.wav" COPYONLY)

	#SFXs
CONFIGURE_FILE(	SFXs/esc_menu_sound.wav ${Project_0_BINARY_DIR}/Datas/SFXs/esc_menu_sound.wav COPYONLY)
CONFIGURE_FILE(	SFXs/null.wav ${Project_0_BINARY_DIR}/Datas/SFXs/null.wav COPYONLY)

