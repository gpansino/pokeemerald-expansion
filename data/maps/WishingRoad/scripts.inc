WishingRoad_MapScripts::
	.byte 0

WishingRoad_EventScript_TRAINER1::
	trainerbattle_single TRAINER_WISHROAD1_1, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER2::
	trainerbattle_single TRAINER_WISHROAD1_2, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER3::
	trainerbattle_single TRAINER_WISHROAD1_3, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_Leah::
	trainerbattle_single TRAINER_LEAH2, WishingRoad_Text_LeahIntro, WishingRoad_Text_LeahDefeated
	msgbox WishingRoad_Text_LeahPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER5::
	trainerbattle_single TRAINER_WISHROAD1_5, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER6::
	trainerbattle_single TRAINER_WISHROAD1_6, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER7::
	trainerbattle_single TRAINER_WISHROAD1_7, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER8::
	trainerbattle_single TRAINER_WISHROAD1_8, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER9::
	trainerbattle_single TRAINER_WISHROAD1_9, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_Pyro::
	trainerbattle_single TRAINER_PYRO, WishingRoad_Text_PyroIntro, WishingRoad_Text_PyroDefeated
	msgbox WishingRoad_Text_PyroPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER11::
	trainerbattle_single TRAINER_WISHROAD1_11, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_Marcus::
	trainerbattle_single TRAINER_MARCUS, WishingRoad_Text_MarcusIntro, WishingRoad_Text_MarcusDefeated
	msgbox WishingRoad_Text_MarcusPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_TRAINER13::
	trainerbattle_single TRAINER_WISHROAD1_13, WishingRoad_Text_GenericIntro, WishingRoad_Text_GenericDefeated
	msgbox WishingRoad_Text_GenericPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_JT::
	trainerbattle_single TRAINER_JT, WishingRoad_Text_JTIntro, WishingRoad_Text_JTDefeated
	msgbox WishingRoad_Text_JTPostBattle, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_GuestPokemon::
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_ne VAR_RESULT, PARTY_SIZE, WishingRoad_EventScript_ReceivedGuest
	fadescreen FADE_TO_BLACK
	special ChooseMonSendToPC
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, WishingRoad_EventScript_DeniedGuest
	specialvar VAR_0x8005, GetSelectedMonNicknameAndSpecies
	goto_if_eq VAR_0x8004, PARTY_IS_GUEST, WishingRoad_EventScript_SendingGuest
	special SendMonToPC
	msgbox WishingRoad_Text_SendMonToPC, MSGBOX_DEFAULT
	goto WishingRoad_EventScript_ReceivedGuest
	end

WishingRoad_EventScript_SendingGuest::
	msgbox WishingRoad_Text_CannotSendGuest, MSGBOX_DEFAULT
	goto WishingRoad_EventScript_GuestPokemon
	end

WishingRoad_EventScript_DeniedGuest::
	bufferspeciesname STR_VAR_1, SPECIES_ABSOL
	msgbox WishingRoad_Text_DeniedGuest, MSGBOX_DEFAULT
	release
	end

WishingRoad_EventScript_ReceivedGuest::
	bufferspeciesname STR_VAR_1, SPECIES_ABSOL
	givemon SPECIES_ABSOL, 28, ITEM_NONE, move1=MOVE_NIGHT_SLASH, move2=MOVE_SWORDS_DANCE, move3=MOVE_RAZOR_WIND, move4=MOVE_BITE, isGuest=TRUE 
	playfanfare MUS_OBTAIN_ITEM
	msgbox WishingRoad_Text_ReceivedGuest, MSGBOX_DEFAULT
	waitmessage
	waitfanfare
	release 
	end

WishingRoad_Text_SendMonToPC:
	.string "{STR_VAR_1} was sent to the PC!$"

WishingRoad_Text_DeniedGuest:
	.string "Decided to not travel with {STR_VAR_1}!$"

WishingRoad_Text_ReceivedGuest:
	.string "{STR_VAR_1} has joined your team!$"

WishingRoad_Text_CannotSendGuest:
	.string "{STR_VAR_1} cannot be sent to the PC!$"

WishingRoad_Text_GenericIntro:
	.string "Generic Intro Message !!!!!!!!!!!!!!$"

WishingRoad_Text_GenericDefeated:
	.string "Generic Defeated Message !!!!!!!!!!!!!!$"

WishingRoad_Text_GenericPostBattle:
	.string "Generic Post Text !!!!!!!!!!!!!!!!!!!!!$"

WishingRoad_Text_LeahIntro:
	.string "HEY!! WANNA SEE MY COOL BUG?!$"

WishingRoad_Text_LeahDefeated:
	.string "What did you think of my little bug?\l"
	.string "Pretty cool, right?$"

WishingRoad_Text_LeahPostBattle:
	.string "I love my little bug c:\p"
	.string "I'm not sure why but he makes tiny\n"
	.string "zapping sounds...\p"
	.string "I think I'm gonna take him to the\n"
	.string "POKéMON CENTER...$"

WishingRoad_Text_PyroIntro:
	.string "Oh, so when my GROWLITHE uses \n"
	.string "FLAMETHROWER they're a “great\p"
	.string "special attacker”, but when I do it,\n"
	.string "I'm “an arsonist” and “not allowed\l"
	.string "in the park anymore”?$"

WishingRoad_Text_PyroDefeated:
	.string "And apparently it's 'illegal' to use\n"
	.string "homemade napalm on citizens.\l"
	.string "This country, man...$"

WishingRoad_Text_PyroPostBattle:
	.string "POKéMON always look like theyre having\n"
	.string "so much fun. I wish I had someone to\l"
	.string "be my trainer and tell me I'm doing a\l"
	.string "good job.$"

WishingRoad_Text_MarcusIntro:
	.string "What does my POKéMON team say about me?$"

WishingRoad_Text_MarcusDefeated:
	.string "It says I'm a seal-y goose.$"

WishingRoad_Text_MarcusPostBattle:
	.string "Alright, that was pretty bad.\n"
	.string "How about this one?\p"
	.string "A seal walks into a club.$"

WishingRoad_Text_JTIntro:
	.string "CLAMPERL, MACHOKE, AIPOMs?\l"
	.string "You want it?\p"
	.string "It's yours, my friend.\n"
	.string "As long as you have enough EEVEEs.$"

WishingRoad_Text_JTDefeated:
	.string "Sorry, {PLAYER}!\n"
	.string "I can't give credit!\p"
	.string "Come back when you're a little\l"
	.string "MMMMM.. WHISMUR.$"

WishingRoad_Text_JTPostBattle:
	.string "Would you rather have unlimited\n"
	.string "games or unlimited BAGON?$"
