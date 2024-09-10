StarCave2FA_MapScripts::
	.byte 0

StarCave2FA_SetSpawnPoint::
	setvar VAR_0x8006, 0
	releaseall
	end

StarCave2FA_OpenMap::
	goto_if_eq VAR_0x8005, TRUE, StarCave2FA_CloseMap
	lockall
	special DisplayMap
	end

StarCave2FA_CloseMap::
	special DestroyMap
	setvar VAR_0x8005, FALSE 
	releaseall
	end
