#copying Data (useful when debugging)
#WARNING: Only uncapitalled extensions are copied on nux OS

	#Data Images
FILE(GLOB_RECURSE IMAGES RELATIVE ${CMAKE_SOURCE_DIR}/Data/ *.png *.bmp *.tif *.tiff *.jpg *.jpeg *.ico)
FOREACH(ELMT ${IMAGES} )
	CONFIGURE_FILE( ${ELMT} ${Project_0_BINARY_DIR}/Data/${ELMT} COPYONLY )
ENDFOREACH(ELMT ${IMAGES} )

	#Data Txts
FILE(GLOB_RECURSE TXTS RELATIVE ${CMAKE_SOURCE_DIR}/Data/ *.txt *.ini *.xml *.dtd)
FOREACH(ELMT ${TXTS} )
	CONFIGURE_FILE( ${ELMT} ${Project_0_BINARY_DIR}/Data/${ELMT} COPYONLY )
ENDFOREACH(ELMT ${TXTS} )

	#Data Fonts
FILE(GLOB_RECURSE FONTS RELATIVE ${CMAKE_SOURCE_DIR}/Data/ *.ttf *.fon)
FOREACH(ELMT ${FONTS} )
	CONFIGURE_FILE( ${ELMT} ${Project_0_BINARY_DIR}/Data/${ELMT} COPYONLY )
ENDFOREACH(ELMT ${FONTS} )

	#Data Audios
FILE(GLOB_RECURSE AUDIOS RELATIVE ${CMAKE_SOURCE_DIR}/Data/ *.wav *.mp3 *.ogg *.aac *.mid)
FOREACH(ELMT ${AUDIOS} )
	CONFIGURE_FILE( ${ELMT} ${Project_0_BINARY_DIR}/Data/${ELMT} COPYONLY )
ENDFOREACH(ELMT ${AUDIOS} )

	#Data Videos
FILE(GLOB_RECURSE VIDEOS RELATIVE ${CMAKE_SOURCE_DIR}/Data/ *.avi *.ogm *.mkv *.bik *.mp4)
FOREACH(ELMT ${VIDEOS} )
	CONFIGURE_FILE( ${ELMT} ${Project_0_BINARY_DIR}/Data/${ELMT} COPYONLY )
ENDFOREACH(ELMT ${VIDEOS} )


