StarCave1FC_MapScripts::
	.byte 0

StarCave1FC_TeleportC::
	lock
	getplayerxy VAR_0x8005, VAR_0x8006
	setmetatile VAR_0x8005, VAR_0x8006, METATILE_StarCave_STARCAVE1FC_Warp , FALSE
	warpteleport MAP_STAR_CAVE1FA, VAR_0x8005, VAR_0x8006
	waitstate
