MilleniumFestival_MapScripts::
	.byte 0

MilleniumFestival_EventScript_CoasterGirl::
	msgbox MilleniumFestival_Text_CoasterGirl, MSGBOX_NPC
	end

MilleniumFestival_EventScript_CoasterChild::
	msgbox MilleniumFestival_Text_CoasterChild, MSGBOX_NPC
	end

MilleniumFestival_EventScript_CoasterMan::
	msgbox MilleniumFestival_Text_CoasterMan, MSGBOX_NPC
	end

MilleniumFestival_EventScript_CoasterWorker::
	msgbox MilleniumFestival_Text_CoasterWorker, MSGBOX_NPC
	end

MilleniumFestival_EventScript_CometGirl::
	msgbox MilleniumFestival_Text_CometGirl, MSGBOX_NPC
	end

MilleniumFestival_EventScript_FestivalKid::
	msgbox MilleniumFestival_Text_FestivalKid, MSGBOX_NPC
	end

MilleniumFestival_EventScript_AbilityMan::
	msgbox MilleniumFestival_Text_AbilityMan, MSGBOX_NPC
	end

MilleniumFestival_EventScript_TravelerMan::
	msgbox MilleniumFestival_Text_TravelerMan, MSGBOX_NPC
	end

MilleniumFestival_EventScript_EeveeGirl::
	msgbox MilleniumFestival_Text_EeveeGirl, MSGBOX_NPC
	end

MilleniumFestival_EventScript_Artist::
	msgbox MilleniumFestival_Text_Artist, MSGBOX_NPC
	end

MilleniumFestival_EventScript_CharmSeller::
	msgbox MilleniumFestival_Text_CharmSeller, MSGBOX_NPC
	end

MilleniumFestival_EventScript_ClosedShop::
	msgbox MilleniumFestival_Text_ClosedShop, MSGBOX_NPC
	end

MilleniumFestival_EventScript_Horoscope::
	msgbox MilleniumFestival_Text_Horoscope, MSGBOX_NPC
	end


MilleniumFestival_EventScript_JohtoBallClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MilleniumFestival_Pokemart_JohtoBalls
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MilleniumFestival_Pokemart_JohtoBalls:
	.2byte ITEM_FAST_BALL
	.2byte ITEM_LEVEL_BALL
	.2byte ITEM_LURE_BALL
	.2byte ITEM_HEAVY_BALL
	.2byte ITEM_LOVE_BALL
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_MOON_BALL
	.2byte ITEM_NONE
	release
	end

MilleniumFestival_EventScript_TMClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MilleniumFestival_Pokemart_StatDropTMs
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MilleniumFestival_Pokemart_StatDropTMs:
	.2byte ITEM_TM_CHARM
	.2byte ITEM_TM_SCREECH
	.2byte ITEM_TM_EERIE_IMPULSE
	.2byte ITEM_TM_METAL_SOUND
	.2byte ITEM_TM_SCARY_FACE
	.2byte ITEM_NONE
	release
	end

MilleniumFestival_EventScript_CapsuleClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MilleniumFestival_Pokemart_AbilityCapsule
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MilleniumFestival_Pokemart_AbilityCapsule:
	.2byte ITEM_ABILITY_CAPSULE
	.2byte ITEM_NONE
	release
	end

MilleniumFestival_EventScript_ExclusiveMonItemsClerk::
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart MilleniumFestival_Pokemart_ExclusiveMonShop
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
MilleniumFestival_Pokemart_ExclusiveMonShop:
	.2byte ITEM_METAL_POWDER
	.2byte ITEM_LUCKY_PUNCH
	.2byte ITEM_LIGHT_BALL
	.2byte ITEM_THICK_CLUB
	.2byte ITEM_LEEK
	.2byte ITEM_NONE
	release
	end

MilleniumFestival_Text_CoasterGirl:
	.string "The Millenium Festival's coaster is\n"
	.string "the coolest!\p"
	.string "Can you believe they get this whole\n"
	.string "fair up in one night!$"

MilleniumFestival_Text_CoasterChild:
	.string "Do you think if I blend in with the\n"
	.string "crowd they'll let me on the coaster?$"

MilleniumFestival_Text_CoasterMan:
	.string "HEY!\p"
	.string "I've been waiting for this roller\n"
	.string "coaster for so long!\p"
	.string "I don't know how much longer I can\n"
	.string "stand here...\p"
	.string "Ok.. maybe just a little longer...$"

MilleniumFestival_Text_CoasterWorker:
	.string "The Millenium Festival Coaster is\n"
	.string "currently in repair, please wait\l"
	.string "for the maintenance to finish\p"
	.string "(Little do they know, it isn't in\n"
	.string "repair. I just don't want to run\l" 
	.string "it. Hehehehe..)$" 

MilleniumFestival_Text_CometGirl:
	.string "The Millenium Comet comes once\n"
	.string "every 1000 years! It's said to\l"
	.string "bring great luck to everyone it\l"
	.string "passes over.\p"
	.string "It seemed like the perfect time\n"
	.string "to dump my life savings into \l"
	.string "lottery tickets! Wish me luck!$"

MilleniumFestival_Text_FestivalKid:
	.string "My dad told me the festival\n"
	.string "travels with the comet.\p"
	.string "My mom told me the comet\n"
	.string "travels at 32 miles/sec!\p"
	.string "I need to join these guys to\n"
	.string "learn the secrets of their\l"
	.string "speed!$"

MilleniumFestival_Text_AbilityMan:
	.string "Every POKéMON has an ability.\p"
	.string "Some POKéMON only have one \n"
	.string "option for an ability.\p"
	.string "Other POKéMON can have two\n"
	.string "options!\p"
	.string "I heard you can buy something\n"
	.string "to swap between these.$"

MilleniumFestival_Text_TravelerMan:
	.string "This festival is one of the\n"
	.string "the best in the world!\p"
	.string "Weird, its in the middle of\n"
	.string "nowhere right now.\p"
	.string "Come to think of it, how\n"
	.string "did I get here?$"

MilleniumFestival_Text_EeveeGirl:
	.string "I trained with my EEVEE\n"
	.string "every night, but it\l"
	.string "wouldn't evolve.\p"
	.string "Finally, I gave it a special\n"
	.string "stone and it became UMBREON!$"

MilleniumFestival_Text_Artist:
	.string "You and your POKéMON look\n"
	.string "so stunning! Stay right there\l"
	.string "I need to draw you!\p"
	.string "...\p"
	.string "Can you get out from under\n"
	.string "the shade so I can see you.$"

MilleniumFestival_Text_CharmSeller:
	.string "Hey, kid! Want a charm?\p"
	.string "If you wish on a charm \n"
	.string "night of the festival,\l"
	.string "whatever you wish for will\l"
	.string "come true!\p"
	.string "Well, the first night of the\n"
	.string "festival already passed..\p"
	.string "But that just means you can\n"
	.string "buy one for next festival!$"

MilleniumFestival_Text_ClosedShop:
	.string "Sorry, kid! The shop's\n"
	.string "closed for today!\p"
	.string "(Hope they don't find out\n"
	.string "This isn't my booth!..)$"

MilleniumFestival_Text_Horoscope:
	.string "I can sense a great power\n"
	.string "from you!\p"
	.string "Let me read your horoscope.\p"
	.string "...\p"
	.string "I can sense you will become\n"
	.string "powerful and encounter many\l"
	.string "strong POKéMON.\p"
	.string "What?! You say you already\n"
	.string "knew that??$"
