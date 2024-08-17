StarCave1FA_MapScripts::
	.byte 0

StarCave1FA_TeleportA::
	lock
	getplayerxy VAR_0x8005, VAR_0x8006
	setmetatile VAR_0x8005, VAR_0x8006, METATILE_StarCave_STARCAVE1FA_Warp, FALSE
	warpteleport MAP_STAR_CAVE1FB, VAR_0x8005, VAR_0x8006
	waitstate
