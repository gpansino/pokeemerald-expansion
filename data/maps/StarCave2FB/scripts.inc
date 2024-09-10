StarCave2FB_MapScripts::
	.byte 0

StarCave2FB_SetSpawnPoint::
	setvar VAR_0x8006, 1
	releaseall
	end

StarCave2FB_OpenMap::
	goto_if_eq VAR_0x8005, TRUE, StarCave2FB_CloseMap
	lockall
	special DisplayMap
	end

StarCave2FB_CloseMap::
	special DestroyMap
	setvar VAR_0x8005, FALSE 
	releaseall
	end
