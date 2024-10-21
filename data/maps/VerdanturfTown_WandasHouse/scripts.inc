.set LOCALID_WALLY, 1
.set LOCALID_UNCLE, 3
.set LOCALID_RIVAL, 6

VerdanturfTown_WandasHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VerdanturfTown_WandasHouse_OnTransition
	.byte 0

VerdanturfTown_WandasHouse_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WISHEVENT_COMPLETE, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_WishEventTrigger, MSGBOX_YESNO
	switch VAR_RESULT
	case YES, VerdanturfTown_WandasHouse_EventScript_ExitToWishEvent
	msgbox VerdanturfTown_WandasHouse_Text_WallyDeclineWish, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_Rival::
	lock
	faceplayer
	msgbox VerdanturfTown_WandasHouse_Text_RivalPreWish, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_ExitToWishEvent:
	msgbox VerdanturfTown_WandasHouse_Text_WallyBeginWishEvent, MSGBOX_DEFAULT
	waitmessage
	applymovement LOCALID_RIVAL, Common_Movement_FaceOriginalDirection
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitse
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	msgbox VerdanturfTown_WandasHouse_Text_RivalWishEvent, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_UNCLE, VerdanturfTown_WandasHouse_Movement_UncleBeginWish
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_FaceLeft
	applymovement LOCALID_WALLY, Common_Movement_FaceLeft
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox VerdanturfTown_WandasHouse_Text_UncleWishEvent, MSGBOX_DEFAULT
	playse SE_TRUCK_MOVE
	@fadescreen FADE_TO_BLACK
	@delay 40
	warp MAP_MILLENIUM_FESTIVAL, 34, 39
	waitstate
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Movement_UncleBeginWish:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
	.string "WALLY: I lost to you, {PLAYER}, but I'm\n"
	.string "not feeling down anymore.\p"
	.string "Because I have a new purpose in life.\n"
	.string "Together with my RALTS, I'm going\l"
	.string "to challenge POKéMON GYMS and become\l"
	.string "a great TRAINER.\p"
	.string "Please watch me, {PLAYER}.\n"
	.string "I'm going to be stronger than you.\p"
	.string "When I do, I'm going to challenge you\n"
	.string "to another battle.$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
	.string "WALLY: Please watch me, {PLAYER}.\n"
	.string "I'm going to get stronger than you.\p"
	.string "When I do, I'm going to challenge you\n"
	.string "to another battle.$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
	.string "UNCLE: Oh! {PLAYER}{KUN}!\n"
	.string "WALLY's next door.\p"
	.string "But, boy, there's something I have to\n"
	.string "tell you.\p"
	.string "This natural environment is doing\n"
	.string "wonders for WALLY's health.\p"
	.string "Maybe it's not just the environment.\n"
	.string "It could be POKéMON that are giving\l"
	.string "the boy hope.$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
	.string "WALLY's gone away…\n"
	.string "He slipped off on his own…$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
	.string "UNCLE: Is that right?\n"
	.string "WALLY's gone away that far all by\l"
	.string "himself…\p"
	.string "Well, I have to give him credit--he is\n"
	.string "my little brother's son.$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
	.string "WANDA: You are?\n"
	.string "Oh, right, I get it!\p"
	.string "You're the {PLAYER} who WALLY was\n"
	.string "telling me about.\p"
	.string "I'm WALLY's cousin.\n"
	.string "Glad to meet you!\p"
	.string "I think WALLY's become a lot more lively\n"
	.string "and healthy since he came here.$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
	.string "WANDA: Don't worry about WALLY.\n"
	.string "He'll be just fine.\p"
	.string "I know my little cousin, and he has\n"
	.string "POKéMON with him, too.$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
	.string "Thanks to you, I can see my girlfriend\n"
	.string "every day.\l"
	.string "Happy? You bet I am!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
	.string "My daughter's boyfriend is a very\n"
	.string "driven and passionate sort of person.\p"
	.string "He's been digging a tunnel nonstop\n"
	.string "just so he can see my daughter.\p"
	.string "My daughter's a little concerned,\n"
	.string "so she goes out to the tunnel a lot.$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
	.string "It's amazing. My daughter's boyfriend\n"
	.string "was digging the tunnel by hand!\p"
	.string "It's so incredible!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
	.string "If anything were to happen to WALLY,\n"
	.string "I would never be able to look his\l"
	.string "parents in PETALBURG in the eye…$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
	.string "WALLY was in EVER GRANDE?\p"
	.string "His parents in PETALBURG would be\n"
	.string "astonished to hear that!$"

VerdanturfTown_WandasHouse_Text_WishEventTrigger:
	.string "WALLY: Hey, {PLAYER}!\p"
	.string "My cousin DIANE invited us to visit\n"
	.string "her at the MILLENIUM FESTIVAL.\p"
	.string "We're leaving soon!\n"
	.string "Are you ready?$"

VerdanturfTown_WandasHouse_Text_WallyDeclineWish:
	.string "Oh, ok.\p"
	.string "Don't take too long though.\n"
	.string "The MILLENIUM COMET is only around\l"
	.string "for so long!$"

VerdanturfTown_WandasHouse_Text_RivalPreWish:
	.string "WOOOOOOOO!!!!\p"
	.string "{PLAYER}, are you as excited as me\n"
	.string "to see the MILLENIUM COMET?!\p"
	.string "All of our wishes will come true!\p"
	.string "Actually, I think its just one wish.\p"
	.string "MAN! I gotta think long and hard\n"
	.string "about what my one wish will be!$"

VerdanturfTown_WandasHouse_Text_WallyBeginWishEvent:
	.string "WALLY: Awesome! We can get going!\p"
	.string "Y'know, {PLAYER}, I was pretty\n"
	.string "bummed when you beat me.\p"
	.string "It really highlighted just how much\n"
	.string "stronger you were than me..\p"
	.string "And it just looked impossible; how\n"
	.string "could I get as strong as you?\p"
	.string "I think that's what my wish will\n"
	.string "be on the MILLENIUM COMET.\p"
	.string "Then, I'll be the strongest trainer\n"
	.string "in the world!$"

VerdanturfTown_WandasHouse_Text_RivalWishEvent:
	.string "{RIVAL}: OH! Are we talking about\n"
	.string "wishes over here, eh?\p"
	.string "{PLAYER}, what are you gonna wish\n"
	.string "for on the MILLENIUM COMET?\p"
	.string "Better yet, what am I gonna\n"
	.string "wish for? Heheheh....\p"
	.string "I just can't wait! If you're both\n"
	.string "ready, let's go right now!$"

VerdanturfTown_WandasHouse_Text_UncleWishEvent:
	.string "Sounds like we've got a lot of\n"
	.string "commotion over here!\p"
	.string "You kids ready to go the\n"
	.string "MILLENIUM FESTIVAL?\p"
	.string "We'll take my truck!\n"
	.string "Hop in everyone!$"
