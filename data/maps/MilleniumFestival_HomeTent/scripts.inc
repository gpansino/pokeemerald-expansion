MilleniumFestival_HomeTent_MapScripts::
	.byte 0

MilleniumFestival_EventScript_RelaxingMan::
	msgbox MilleniumFestival_Text_RelaxingMan, MSGBOX_NPC
	end

MilleniumFestival_EventScript_KarateMan::
	msgbox MilleniumFestival_Text_KarateMan, MSGBOX_NPC
	end

MilleniumFestival_Text_RelaxingMan:
	.string "Its nice to take a break\n"
	.string "after a long day of working\l"
	.string "in the festival.\p"
	.string "I just wish the smallest\n"
	.string "tent in the festival wasn't\l"
	.string "our break room.$"

MilleniumFestival_Text_KarateMan:
	.string "You may wonder what\n"
	.string "someone like me does in\l"
	.string "in the circus.\p"
	.string "Hey! Someone has to get\n"
	.string "this place set up!\p"
	.string "What? You didn't say\n"
	.string "anything? Oh...$"
