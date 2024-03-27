.set LOCALID_STEVEN, 1

GraniteCave_StevensRoom_MapScripts::
	.byte 0

GraniteCave_StevensRoom_EventScript_StevenBegin::
	lock
	faceplayer
	msgbox GraniteCave_StevensRoom_Text_ImSteven, MSGBOX_DEFAULT
	copyvar VAR_0x8004, VAR_FACING
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_QuestionMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	delay 30
	msgbox GraniteCave_StevensRoom_Text_Explain, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_StevenSpeech1South
	goto GraniteCave_StevensRoom_EventScript_StevenSpeech1Else
	release
	end

GraniteCave_StevensRoom_EventScript_StevenSpeech1South::
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenLeftNorth
	goto GraniteCave_StevensRoom_EventScript_StevenSpeech2
	end

GraniteCave_StevensRoom_EventScript_StevenSpeech1Else::
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenNorthLeft
	goto GraniteCave_StevensRoom_EventScript_StevenSpeech2
	end

GraniteCave_StevensRoom_EventScript_StevenSpeech2::
	delay 20
	call_if_ne VAR_0x8004, DIR_WEST, GraniteCave_StevensRoom_EventScript_FaceStevenWest
	waitmovement 0 
	msgbox GraniteCave_StevensRoom_Text_HoennPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenWalk2
	delay 40
	call_if_eq VAR_0x8004, DIR_NORTH, GraniteCave_StevensRoom_EventScript_FaceStevenNorth
	call_if_eq VAR_0x8004, DIR_WEST, GraniteCave_StevensRoom_EventScript_FaceStevenNorth
	call_if_eq VAR_0x8004, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_FaceStevenEast
	call_if_eq VAR_0x8004, DIR_EAST, GraniteCave_StevensRoom_EventScript_FaceStevenEast
	waitmovement 0 
	msgbox GraniteCave_StevensRoom_Text_EvilOrganizations, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenWalk3
	delay 20
	call_if_eq VAR_0x8004, DIR_NORTH, GraniteCave_StevensRoom_EventScript_FaceStevenEast
	call_if_eq VAR_0x8004, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_FaceStevenSouth
	call_if_eq VAR_0x8004, DIR_WEST, GraniteCave_StevensRoom_EventScript_FaceStevenEast
	call_if_eq VAR_0x8004, DIR_EAST, GraniteCave_StevensRoom_EventScript_FaceStevenEast
	waitmovement 0
	msgbox GraniteCave_StevensRoom_Text_StrongestTrainer, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, GraniteCave_StevensRoom_EventScript_StevenSpeech3North
	goto GraniteCave_StevensRoom_EventScript_StevenSpeech3Else
	end

GraniteCave_StevensRoom_EventScript_StevenSpeech3North::
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_Steven4NorthLeft
	waitmovement 0
	goto GraniteCave_StevensRoom_EventScript_StevenBattle
	end

GraniteCave_StevensRoom_EventScript_StevenSpeech3Else::
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_Steven4LeftNorth
	waitmovement 0 
	goto GraniteCave_StevensRoom_EventScript_StevenBattle
	end

GraniteCave_StevensRoom_EventScript_StevenBattle::
	call_if_eq VAR_0x8004, DIR_NORTH, GraniteCave_StevensRoom_EventScript_FaceStevenNorth
	call_if_eq VAR_0x8004, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_FaceStevenSouth
	call_if_eq VAR_0x8004, DIR_EAST, GraniteCave_StevensRoom_EventScript_FaceStevenEast
	call_if_eq VAR_0x8004, DIR_WEST, GraniteCave_StevensRoom_EventScript_FaceStevenWest
	waitmovement 0
	faceplayer
	msgbox GraniteCave_StevensRoom_Text_ToughTrainer, MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_CHAMPION, TRUE
	delay 30
	msgbox GraniteCave_StevensRoom_Text_BattleSteven, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN_GRANITECAVE, GraniteCave_StevensRoom_Text_StevenDefeated
	goto GraniteCave_StevensRoom_EventScript_StevenRegisterAndLeave
	end

GraniteCave_StevensRoom_EventScript_FaceStevenNorth:
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_FaceUp
	return

GraniteCave_StevensRoom_EventScript_FaceStevenSouth:
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_FaceDown
	return

GraniteCave_StevensRoom_EventScript_FaceStevenWest:
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_FaceLeft
	return

GraniteCave_StevensRoom_EventScript_FaceStevenEast:
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_FaceRight
	return

GraniteCave_StevensRoom_EventScript_StevenRegisterAndLeave::
	fadedefaultbgm
	msgbox GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox GraniteCave_StevensRoom_Text_RegisteredSteven, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_REGISTERED_STEVEN_POKENAV
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_QuestionMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	delay 10
	msgbox GraniteCave_StevensRoom_Text_GiveLetter
	setvar VAR_0x8004, ITEM_LETTER
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_DELIVERED_STEVEN_LETTER
	msgbox GraniteCave_StevensRoom_Text_ThankYouTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM47
	call_if_eq VAR_RESULT, FALSE, GraniteCave_StevensRoom_EventScript_BagFull
	msgbox GraniteCave_StevensRoom_Text_IveGotToHurryAlong, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, GraniteCave_StevensRoom_EventScript_StevenExitNorth
	call_if_eq VAR_FACING, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_StevenExitSouth
	call_if_eq VAR_FACING, DIR_WEST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	call_if_eq VAR_FACING, DIR_EAST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
	playse SE_EXIT
	removeobject LOCALID_STEVEN
	release
	end

GraniteCave_StevensRoom_EventScript_StevenExitNorth::
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitWestEast::
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_StevenExitSouth::
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExitSouth
	waitmovement 0
	return

GraniteCave_StevensRoom_EventScript_BagFull::
	msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
	return

GraniteCave_StevensRoom_Movement_StevenExit:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit:
	delay_16
	delay_16
	delay_16
	walk_in_place_faster_up
	step_end

GraniteCave_StevensRoom_Movement_StevenExitSouth:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	delay_8
	step_end

GraniteCave_StevensRoom_Movement_StevenNorthLeft:
	walk_up
	walk_left
	walk_left
	step_end

GraniteCave_StevensRoom_Movement_StevenLeftNorth:
	walk_left
	walk_up
	walk_left
	step_end

GraniteCave_StevensRoom_Movement_StevenWalk2:
	walk_up
	walk_right	
	walk_right
	walk_right
	step_end

GraniteCave_StevensRoom_Movement_StevenWalk3:
	walk_down
	walk_right
	walk_down
	walk_down
	step_end

GraniteCave_StevensRoom_Movement_Steven4LeftNorth:
	walk_left
	walk_left
	walk_up
	step_end

GraniteCave_StevensRoom_Movement_Steven4NorthLeft:
	walk_left
	walk_up
	walk_left	
	step_end

GraniteCave_StevensRoom_Movement_FaceLeft:
	walk_in_place_faster_left
	step_end

GraniteCave_StevensRoom_Movement_FaceRight:
	walk_in_place_faster_right
	step_end

GraniteCave_StevensRoom_Movement_FaceUp:
	walk_in_place_faster_up
	step_end

GraniteCave_StevensRoom_Movement_FaceDown:
	walk_in_place_faster_down
	step_end

GraniteCave_StevensRoom_Text_ImSteven:
	.string "My name is STEVEN.\p"
	.string "I'm interested in rare stones,\n"
	.string "so I travel here and there.$"

GraniteCave_StevensRoom_Text_GiveLetter:
	.string "Oh?\n"
	.string "My bad. Do you have a LETTER\l"
	.string "for me?$"

GraniteCave_StevensRoom_Text_ThankYouTakeThis:
	.string "STEVEN: Okay, thank you.\p"
	.string "You went through all this trouble to\n"
	.string "deliver that. I need to thank you.\p"
	.string "Let me see…\n"
	.string "I'll give you this TM.\p"
	.string "It contains my favorite move,\n"
	.string "STEEL WING.$"

GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister:
	.string "STEVEN: Your POKéMON appear quite\n"
	.string "capable.\p"
	.string "If you keep training, you could even\n"
	.string "become the CHAMPION of the POKéMON\l"
	.string "LEAGUE one day. That's what I think.\l"
	.string "Just as long as its after I retire, haha.\p"
	.string "I know, since we've gotten to know each\n"
	.string "other, let's register one another in\l"
	.string "our POKéNAVS.\p"
	.string "… … … … … …$"

GraniteCave_StevensRoom_Text_RegisteredSteven:
	.string "Registered STEVEN\n"
	.string "in the POKéNAV.$"

GraniteCave_StevensRoom_Text_IveGotToHurryAlong:
	.string "Now, I've got to hurry along.$"

GraniteCave_StevensRoom_Text_OhBagIsFull:
	.string "Oh, your BAG is full…\n"
	.string "That's too bad, then.$"

GraniteCave_StevensRoom_Text_Explain:
	.string "Hm?\p"
	.string "Oh, you're wondering what I'm doing\n"
	.string "all the way down here? Let me explain.$"

GraniteCave_StevensRoom_Text_HoennPokemon:
	.string "You see the HOENN region is home to\n"
	.string "many powerful POKéMON...\p"
	.string "Some strong POKéMON you can\n"
	.string "encounter everyday. Others you must\l"
	.string "evolve to see.\p"
	.string "However, some POKéMON are so powerful\n"
	.string "they have been sealed away and have\l"
	.string "fallen into legend.$"

GraniteCave_StevensRoom_Text_EvilOrganizations:
	.string "Some humans seek to obtain this\n"
	.string "power to use for their own evil devices.\p"
	.string "Does this power exist? I'm not sure...\p"
	.string "But I'm here as an archeologist to find\n"
	.string "out that question for myself.\p"
	.string "If such a power exists, I will personally\n"
	.string "take it as my responsibility to prevent\l"
	.string "anybody from awakening that power.$"

GraniteCave_StevensRoom_Text_StrongestTrainer:
	.string "After all, it is said that if anyone is\n"
	.string "able to reawaken those beasts,\l"
	.string "it would take the strongest POKéMON\l"
	.string "in the world just to have a chance\l"
	.string "at stopping a single one.\p"
	.string "...\l"
	.string "The thought of such a power terrifies\n"
	.string "me.$" 

GraniteCave_StevensRoom_Text_ToughTrainer:
	.string "But! I do consider myself a tough \n"
	.string "trainer.\p"
	.string "Hey, if you got all the way down here, you\n"
	.string "must be no slouch yourself!\p"
	.string "Oh, and youre a gym battle veteran!\n"
	.string "Not bad.\p"
	.string "Why don't we have a little battle\n"
	.string "while we're down here?\l"
	.string "I love testing out new trainers to see\l"
	.string "how strong they really are.\p"
	.string "People said I was powerful when I was\n"
	.string "young so I never want to underestimate\l"
	.string "new talent.$"

GraniteCave_StevensRoom_Text_BattleSteven:
	.string "So believe me, I won't be\n" 
	.string "underestimating you.$"

GraniteCave_StevensRoom_Text_StevenDefeated:
	.string "!!\p"
	.string "It seems like you have already\n"
	.string "built up great strength!\p"
	.string "I was not expecting that amount of\n"
	.string "power!$"