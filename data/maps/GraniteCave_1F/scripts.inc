GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_FlashlightToo, MSGBOX_DEFAULT
	giveitem ITEM_FLASHLIGHT
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	msgbox GraniteCave_1F_Text_ExplainFlashlight, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Hey, you.\n"
	.string "It gets awfully dark ahead.\l"
	.string "It'll be tough trying to explore.\p"
	.string "That guy who came by earlier…\n"
	.string "STEVEN, I think it was.\p"
	.string "He knew how to use FLASH, so he ought\n"
	.string "to be all right, but…\p"
	.string "Well, for us HIKERS, helping out those\n"
	.string "that we meet is our motto.\p"
	.string "Here you go, I'll pass this on to you.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "Teach that hidden move FLASH to\n"
	.string "a POKéMON and use it.\p"
	.string "It lights up even the inky darkness\n"
	.string "of caves.\p"
	.string "But, to use it, you need the GYM BADGE\n"
	.string "from DEWFORD's POKéMON GYM.$"

GraniteCave_1F_Text_FlashlightToo:
	.string "Here take this too!\p"
	.string "With this, you won't need a specific\n"
	.string "POKéMON to light up dark areas!$"

GraniteCave_1F_Text_ExplainFlashlight:
	.string "Alternatively, you can use the\n"
	.string "FLASHLIGHT to see in dark areas.\p"
	.string "Just use it from the KEY ITEMS\n"
	.string "pocket or register it to use it\l"
	.string "anytime!\p"
	.string "I couldn't get it to work before\n"
	.string "I defeated BRAWLY of DEWFORD GYM,\l"
	.string "though. Not sure what that's about..$"
