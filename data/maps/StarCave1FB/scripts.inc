StarCave1FB_MapScripts::
	.byte 0

StarCave1FB_Teleport::
	lock
	setvar VAR_0x8006, 2
	special TeleportStoneWarp
