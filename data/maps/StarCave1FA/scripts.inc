StarCave1FA_MapScripts::
	.byte 0

StarCave1FA_Teleport::
	lock
	setvar VAR_0x8006, 1
	special TeleportStoneWarp
