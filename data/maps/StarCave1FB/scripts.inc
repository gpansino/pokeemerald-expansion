StarCave1FB_MapScripts::
	.byte 0

StarCave1FB_TeleportB::
	lock
	getplayerxy VAR_0x8005, VAR_0x8006
	setmetatile VAR_0x8005, VAR_0x8006, METATILE_StarCave_StarCave1FB_Warp, FALSE
	warpteleport MAP_STAR_CAVE1FC, VAR_0x8005, VAR_0x8006
	waitstate
