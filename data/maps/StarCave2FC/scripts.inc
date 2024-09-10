StarCave2FC_MapScripts::
	.byte 0

StarCave2FC_SetSpawnPoint::
	setvar VAR_0x8006, 2
	releaseall
	end

StarCave2FC_OpenMap::
	goto_if_eq VAR_0x8005, TRUE, StarCave2FC_CloseMap
	lockall
	special DisplayMap
	end

StarCave2FC_CloseMap::
	special DestroyMap
	setvar VAR_0x8005, FALSE 
	releaseall
	end
