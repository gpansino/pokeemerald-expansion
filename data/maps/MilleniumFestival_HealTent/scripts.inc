.set LOCALID_NURSE, 1


MilleniumFestival_HealTent_MapScripts::
	.byte 0


MilleniumFestival_EventScript_Zomnbie::
	msgbox MilleniumFestival_Text_Zombie, MSGBOX_NPC
	end

MilleniumFestival_EventScript_MegasGirl::
	msgbox MilleniumFestival_Text_MegasGirl, MSGBOX_NPC
	end

MilleniumFestival_EventScript_PassiveGirl::
	msgbox MilleniumFestival_Text_PassiveGirl, MSGBOX_NPC
	end

MilleniumFestival_EventScript_ManMadePokemon::
	msgbox MilleniumFestival_Text_ManMadePokemon, MSGBOX_NPC
	end

MilleniumFestival_EventScript_Skitty::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SKITTY, CRY_MODE_NORMAL
	msgbox MilleniumFestival_Text_Skitty, MSGBOX_DEFAULT
	waitmoncry
	release
	end

MilleniumFestival_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	msgbox MilleniumFestival_Text_Nurse, MSGBOX_DEFAULT
	waitbuttonpress
	call Common_EventScript_OutOfCenterPartyHeal
	applymovement VAR_0x800B, Movement_PkmnCenterNurse_Bow
	waitmovement 0
	msgbox MilleniumFestival_Text_NurseGoodbye, MSGBOX_DEFAULT
	release
	end

MilleniumFestival_EventScript_MartClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MilleniumFestival_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MilleniumFestival_Mart_Pokemart:
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_POKE_DOLL
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_DREAM_MAIL
	.2byte ITEM_NONE
	release
	end

MilleniumFestival_Text_Zombie:
	.string "Raaahhhh...\p"
	.string "BRRAAIINNNSSS...\p"
	.string "Oh sorry, I forgot\n"
	.string "I'm on break!$"

MilleniumFestival_Text_MegasGirl:
	.string "I heard if you have a very\n"
	.string "strong bond with your POKéMON,\p"
	.string "they can unlock a new level\n"
	.string "power!\p"
	.string "It's just a rumor, though.\p"
	.string "I wonder if anyone out there\n"
	.string "knows more..$"

MilleniumFestival_Text_PassiveGirl:
	.string "Oh SKITTY! You're so so\n"
	.string "SO adorable! <3\p"
	.string "You're always so cute\n"
	.string "and perfect\l"
	.string "even when smelly, strange\l"
	.string "people try to talk to us!\p"
	.string "Like right now!\p"
	.string "My tiny SKITTY, promise to\n"
	.string "never leave me alone with\l"
	.string "these weird, ugly people! <3$"

MilleniumFestival_Text_ManMadePokemon:
	.string "Have you heard? Scientists\n"
	.string "have made their own unique\l"
	.string "POKéMON!\p"
	.string "I wonder, is this POKéMON\n"
	.string "truly alive?\p"
	.string "Or do we have the ability\n"
	.string "to artificially create life!\p"
	.string "...\p"
	.string "I'm gonna stop eating this\n"
	.string "candy given to me by random\l"
	.string "people at the festival..$"

MilleniumFestival_Text_Skitty:
	.string "SKITTY: ...$"

MilleniumFestival_Text_Nurse:
	.string "We're set up as a portable POKéMON\n"
	.string "for the festival!\p"
	.string "Here let me heal your POKéMON.$"

MilleniumFestival_Text_NurseGoodbye:
	.string "We hope you enjoy the festival!$"
