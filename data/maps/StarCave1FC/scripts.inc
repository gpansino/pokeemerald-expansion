StarCave1FC_MapScripts::
	.byte 0

StarCave1FC_Teleport::
	lock
	setvar VAR_0x8006, 0
	special TeleportStoneWarp
