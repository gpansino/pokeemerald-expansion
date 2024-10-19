MilleniumFestival_GlassTent_MapScripts::
	.byte 0

MilleniumFestival_EventScript_GlassEntrance::
	msgbox MilleniumFestival_Text_GlassEntrance, MSGBOX_NPC
	end


MilleniumFestival_EventScript_GlassFinish::
	lock 
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_MIRROR_COAT, MilleniumFestival_EventScript_GlassGotMirrorCoat
	applymovement LOCALID_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox MilleniumFestival_Text_GlassFinish, MSGBOX_NPC
	giveitem ITEM_TM_MIRROR_COAT
	goto_if_eq VAR_RESULT, 0, MilleniumFestival_EventScript_NoRoomForMirrorCoat
	setflag FLAG_RECEIVED_TM_MIRROR_COAT
	goto MilleniumFestival_EventScript_GlassGotMirrorCoat

MilleniumFestival_EventScript_GlassGotMirrorCoat::
	msgbox MilleniumFestival_Text_MirrorCoatExplain, MSGBOX_DEFAULT
	release
	end

MilleniumFestival_EventScript_NoRoomForMirrorCoat::
	msgbox MilleniumFestival_Text_NoRoomMirrorCoat, MSGBOX_DEFAULT
	release
	end

MilleniumFestival_Text_GlassEntrance:
	.string "Welcome to the Glass Tent!\p"
	.string "It's a never-ending maze\n"
	.string "of solid glass walls!\p"
	.string "If you can find your way\n"
	.string "to the end, you'll get\l"
	.string "a prize!\p"
	.string "Up to the challenge?$"

MilleniumFestival_Text_GlassFinish:
	.string "Wow! I can't believe you\n"
	.string "made it here!\p"
	.string "Most people just get\n"
	.string "turned around and leave.\p"
	.string "Well, here's your prize!$"
	
MilleniumFestival_Text_MirrorCoatExplain:
	.string "This TM contains\n"
	.string "MIRROR COAT!\p"
	.string "You can take the damage\n"
	.string "enemies do to you and turn\l"
	.string "it around on 'em!\p"
	.string "Just make sure it's a\n"
	.string "SPECIAL move you reflect!!$"

MilleniumFestival_Text_NoRoomMirrorCoat:
	.string "Oh.. You have no room..\p"
	.string "I guess you really do\n"
	.string "have to turn around.$"
