MilleniumFestival_TeachTent_MapScripts::
	.byte 0

	.set TUTOR_PRICE_1000,  1000
	.set TUTOR_PRICE_2000,  2000
	.set TUTOR_PRICE_4000,  4000
	.set TUTOR_PRICE_8000,  8000

MilleniumFestival_EventScript_TeachingEntrance::
	msgbox MilleniumFestival_Text_TeachingEntrance, MSGBOX_NPC
	end


MilleniumFestival_EventScript_EggMovesMan::
	msgbox MilleniumFestival_Text_EggMovesMan, MSGBOX_NPC
	end


MilleniumFestival_EventScript_TeachingDragonDance::
	msgbox MilleniumFestival_Text_TeachingDragonDance, MSGBOX_NPC
	end

MilleniumFestival_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox MilleniumFestival_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MilleniumFestival_EventScript_TutorMan::
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 0
	setvar VAR_TEMP_C, MULTI_MF_MOVE_TUTOR_1
	message MilleniumFestival_Text_TeachWhichMove
	waitmessage
	showmoneybox 0, 0
	multichoice	17, 0, MULTI_MF_MOVE_TUTOR_1, FALSE
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, MilleniumFestival_EventScript_DefenseCurl
	case 1, MilleniumFestival_EventScript_Snore
	case 2, MilleniumFestival_EventScript_MudSlap
	case 3, MilleniumFestival_EventScript_Swift
	case 4, MilleniumFestival_EventScript_Supersonic
	case 5, MilleniumFestival_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, MilleniumFestival_EventScript_ExitTutorMoveSelect
	end

MilleniumFestival_EventScript_TutorWoman::
	setvar VAR_TEMP_FRONTIER_TUTOR_ID, 1
	setvar VAR_TEMP_C, MULTI_MF_MOVE_TUTOR_2
	message MilleniumFestival_Text_TeachWhichMove
	waitmessage
	showmoneybox 0, 0
	multichoice	17, 0, MULTI_MF_MOVE_TUTOR_2, FALSE
	copyvar VAR_TEMP_FRONTIER_TUTOR_SELECTION, VAR_RESULT
	switch VAR_RESULT
	case 0, MilleniumFestival_EventScript_HelpingHand
	case 1, MilleniumFestival_EventScript_Refresh
	case 2, MilleniumFestival_EventScript_Disable
	case 3, MilleniumFestival_EventScript_Smellingsalt
	case 4, MilleniumFestival_EventScript_QuickAttack
	case 5, MilleniumFestival_EventScript_ExitTutorMoveSelect
	case MULTI_B_PRESSED, MilleniumFestival_EventScript_ExitTutorMoveSelect
	end

MilleniumFestival_EventScript_DefenseCurl::
	setvar VAR_0x8008, 1000
	setvar VAR_0x8005, MOVE_DEFENSE_CURL
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_Snore::
	setvar VAR_0x8008, 1000
	setvar VAR_0x8005, MOVE_SNORE
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_MudSlap::
	setvar VAR_0x8008, 4000
	setvar VAR_0x8005, MOVE_MUD_SLAP
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_Swift::
	setvar VAR_0x8008, 4000
	setvar VAR_0x8005, MOVE_SWIFT
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_Supersonic::
	setvar VAR_0x8008, 4000
	setvar VAR_0x8005, MOVE_SUPERSONIC
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_HelpingHand::
	setvar VAR_0x8008, 2000
	setvar VAR_0x8005, MOVE_HELPING_HAND
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_Refresh::
	setvar VAR_0x8008, 2000
	setvar VAR_0x8005, MOVE_REFRESH
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_Disable::
	setvar VAR_0x8008, 4000
	setvar VAR_0x8005, MOVE_DISABLE
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_Smellingsalt::
	setvar VAR_0x8008, 4000
	setvar VAR_0x8005, MOVE_SMELLING_SALTS
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

MilleniumFestival_EventScript_QuickAttack::
	setvar VAR_0x8008, 8000
	setvar VAR_0x8005, MOVE_QUICK_ATTACK
	goto MilleniumFestival_EventScript_ConfirmMoveSelection
	end

@ VAR_0x8008 is the price
@ VAR_TEMP_C is the scroll multichoice ID
@ VAR_TEMP_FRONTIER_TUTOR_SELECTION is the move selection
@ VAR_TEMP_FRONTIER_TUTOR_ID is which move tutor was spoken to
MilleniumFestival_EventScript_ConfirmMoveSelection::
	copyvar VAR_0x800B, VAR_0x8008
	special BufferBattleFrontierTutorMoveName
	buffernumberstring STR_VAR_2, VAR_0x8008
	msgbox MilleniumFestival_Text_MoveWillBeXMoney, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MilleniumFestival_EventScript_ChooseNewMove
	goto_if_eq VAR_0x8008, TUTOR_PRICE_1000, MilleniumFestival_EventScript_CheckMoney1000
	goto_if_eq VAR_0x8008, TUTOR_PRICE_2000, MilleniumFestival_EventScript_CheckMoney2000
	goto_if_eq VAR_0x8008, TUTOR_PRICE_4000, MilleniumFestival_EventScript_CheckMoney4000
	goto_if_eq VAR_0x8008, TUTOR_PRICE_8000, MilleniumFestival_EventScript_CheckMoney8000
	end

MilleniumFestival_EventScript_CheckMoney1000::
	checkmoney TUTOR_PRICE_1000
	goto_if_eq VAR_RESULT, TRUE, MilleniumFestival_EventScript_TeachTutorMove
	goto MilleniumFestival_EventScript_TutorNotEnoughMoney 
	end

MilleniumFestival_EventScript_CheckMoney2000::
	checkmoney TUTOR_PRICE_2000
	goto_if_eq VAR_RESULT, TRUE, MilleniumFestival_EventScript_TeachTutorMove
	goto MilleniumFestival_EventScript_TutorNotEnoughMoney 
	end

MilleniumFestival_EventScript_CheckMoney4000::
	checkmoney TUTOR_PRICE_4000
	goto_if_eq VAR_RESULT, TRUE, MilleniumFestival_EventScript_TeachTutorMove
	goto MilleniumFestival_EventScript_TutorNotEnoughMoney 
	end

MilleniumFestival_EventScript_CheckMoney8000::
	checkmoney TUTOR_PRICE_8000
	goto_if_eq VAR_RESULT, TRUE, MilleniumFestival_EventScript_TeachTutorMove
	goto MilleniumFestival_EventScript_TutorNotEnoughMoney 
	end

MilleniumFestival_EventScript_TutorNotEnoughMoney::
	msgbox gText_YouDontHaveMoney, MSGBOX_DEFAULT
	goto MilleniumFestival_EventScript_ChooseNewMove
	end

MilleniumFestival_EventScript_TeachTutorMove::
	msgbox MilleniumFestival_Text_TeachMoveToWhichMon, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special ChooseMonForMoveTutor
	waitstate
	goto_if_eq VAR_RESULT, FALSE, MilleniumFestival_EventScript_ExitTutorMoveSelect
	msgbox MilleniumFestival_Text_ThankYou, MSGBOX_DEFAULT
	goto_if_eq VAR_0x800B, 1000, MilleniumFestival_EventScript_Remove1000  
	goto_if_eq VAR_0x800B, 2000, MilleniumFestival_EventScript_Remove2000 
	goto_if_eq VAR_0x800B, 4000, MilleniumFestival_EventScript_Remove4000 
	goto_if_eq VAR_0x800B, 8000, MilleniumFestival_EventScript_Remove8000 
	end

MilleniumFestival_EventScript_Remove1000::
	removemoney TUTOR_PRICE_1000
	hidemoneybox
	release
	end

MilleniumFestival_EventScript_Remove2000::
	removemoney TUTOR_PRICE_2000
	hidemoneybox
	release
	end

MilleniumFestival_EventScript_Remove4000::
	removemoney TUTOR_PRICE_4000
	hidemoneybox
	release
	end

MilleniumFestival_EventScript_Remove8000::
	removemoney TUTOR_PRICE_8000
	hidemoneybox
	release
	end

MilleniumFestival_EventScript_ChooseNewMove::
	goto_if_eq VAR_TEMP_FRONTIER_TUTOR_ID, 0, MilleniumFestival_EventScript_TutorMan
	goto MilleniumFestival_EventScript_TutorWoman	
	end


MilleniumFestival_EventScript_ExitTutorMoveSelect::
	msgbox MilleniumFestival_Text_YouDontWantTo, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

MilleniumFestival_Text_TeachWhichMove:
	.string "I'll teach a new move to your\n"
	.string "POKéMON for a small fee.\p"
	.string "Which would you like your\n"
	.string "POKéMON to learn?$"

MilleniumFestival_Text_MoveWillBeXMoney:
	.string "The move {STR_VAR_1}?\n"
	.string "That will be {STR_VAR_2}, okay?$"

MilleniumFestival_Text_YouDontWantTo:
	.string "Oh you don't want to really\n"
	.string "teach a move?$"

MilleniumFestival_Text_TeachMoveToWhichMon:
	.string "Who should learn {STR_VAR_1}?$"

MilleniumFestival_Text_ThankYou:
	.string "Thank you and enjoy your move!$"

MilleniumFestival_Text_TeachingEntrance:
	.string "This tent is home to some of\n"
	.string "the best teachers in the world!\p"
	.string "They can teach your POKéMON new\n"
	.string "moves they can't learn otherwise.$"

MilleniumFestival_Text_EggMovesMan:
	.string "In the daycare, two POKéMON\n"
	.string "can make an egg.\p"
	.string "Sometimes, a POKéMON born from\n"
	.string "one of these eggs will know a\l"
	.string "move their parents learned.\p"
	.string "But only some moves it\n"
	.string "seems. It's very weird.$"

MilleniumFestival_Text_TeachingDragonDance:
	.string "This old man has perfected the\n"
	.string "art of teaching moves to POKéMON\l"
	.string "that don't usually learn it.\p"
	.string "So I've been trying to teach\n"
	.string "DRAGON DANCE to ZIGZAGOON.\p"
	.string "Come on buddy, just a need\n"
	.string "little shimmy shake.$"

MilleniumFestival_Text_Zigzagoon:
	.string "ZIGZAGOON: Goooonn...$"
