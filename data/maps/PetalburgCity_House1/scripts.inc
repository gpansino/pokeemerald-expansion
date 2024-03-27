PetalburgCity_House1_MapScripts::
	.byte 0

PetalburgCity_House1_EventScript_Man::
	msgbox PetalburgCity_House1_Text_TravelingIsWonderful, MSGBOX_NPC
	end

PetalburgCity_House1_EventScript_Woman::
	msgbox PetalburgCity_House1_Text_GoOnAdventure, MSGBOX_NPC
	end

PetalburgCity_House1_EventScript_ReceivePichu::
	setvar VAR_TEMP_1, SPECIES_PICHU
	bufferspeciesname STR_VAR_1, SPECIES_PICHU
	bufferspeciesname STR_VAR_2, SPECIES_PIKACHU
	givemon SPECIES_PICHU, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveElekid::
	setvar VAR_TEMP_1, SPECIES_ELEKID
	bufferspeciesname STR_VAR_1, SPECIES_ELEKID
	bufferspeciesname STR_VAR_2, SPECIES_ELECTABUZZ
	givemon SPECIES_ELEKID, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveRiolu::
	setvar VAR_TEMP_1, SPECIES_RIOLU
	bufferspeciesname STR_VAR_1, SPECIES_RIOLU
	bufferspeciesname STR_VAR_2, SPECIES_LUCARIO
	givemon SPECIES_RIOLU, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveTyrogue::
	setvar VAR_TEMP_1, SPECIES_TYROGUE
	bufferspeciesname STR_VAR_1, SPECIES_TYROGUE
	givemon SPECIES_TYROGUE, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckPartyTyrogue
	end

PetalburgCity_House1_EventScript_ReceiveBudew::
	setvar VAR_TEMP_1, SPECIES_BUDEW
	bufferspeciesname STR_VAR_1, SPECIES_BUDEW
	bufferspeciesname STR_VAR_2, SPECIES_ROSELIA
	givemon SPECIES_BUDEW, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveWynaut::
	setvar VAR_TEMP_1, SPECIES_WYNAUT
	bufferspeciesname STR_VAR_1, SPECIES_WYNAUT
	bufferspeciesname STR_VAR_2, SPECIES_WOBBUFFET
	givemon SPECIES_WYNAUT, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveMunchlax::
	setvar VAR_TEMP_1, SPECIES_MUNCHLAX
	bufferspeciesname STR_VAR_1, SPECIES_MUNCHLAX
	bufferspeciesname STR_VAR_2, SPECIES_SNORLAX
	givemon SPECIES_MUNCHLAX, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveSmoochum::
	setvar VAR_TEMP_1, SPECIES_SMOOCHUM
	bufferspeciesname STR_VAR_1, SPECIES_SMOOCHUM
	bufferspeciesname STR_VAR_2, SPECIES_JYNX
	givemon SPECIES_SMOOCHUM, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveMagby::
	setvar VAR_TEMP_1, SPECIES_MAGBY
	bufferspeciesname STR_VAR_1, SPECIES_MAGBY
	bufferspeciesname STR_VAR_2, SPECIES_MAGMAR
	givemon SPECIES_MAGBY, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveHappiny::
	setvar VAR_TEMP_1, SPECIES_HAPPINY
	bufferspeciesname STR_VAR_1, SPECIES_HAPPINY
	bufferspeciesname STR_VAR_2, SPECIES_CHANSEY
	givemon SPECIES_HAPPINY, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveTogepi::
	setvar VAR_TEMP_1, SPECIES_TOGEPI
	bufferspeciesname STR_VAR_1, SPECIES_TOGEPI
	bufferspeciesname STR_VAR_2, SPECIES_TOGETIC
	givemon SPECIES_TOGEPI, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveChingling::
	setvar VAR_TEMP_1, SPECIES_CHINGLING
	bufferspeciesname STR_VAR_1, SPECIES_CHINGLING
	bufferspeciesname STR_VAR_2, SPECIES_CHIMECHO
	givemon SPECIES_CHINGLING, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveBonsly::
	setvar VAR_TEMP_1, SPECIES_BONSLY
	bufferspeciesname STR_VAR_1, SPECIES_BONSLY
	bufferspeciesname STR_VAR_2, SPECIES_SUDOWOODO
	givemon SPECIES_BONSLY, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveAzurill::
	setvar VAR_TEMP_1, SPECIES_AZURILL
	bufferspeciesname STR_VAR_1, SPECIES_AZURILL
	bufferspeciesname STR_VAR_2, SPECIES_MARILL
	givemon SPECIES_AZURILL, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveCleffa::
	setvar VAR_TEMP_1, SPECIES_CLEFFA
	bufferspeciesname STR_VAR_1, SPECIES_CLEFFA
	bufferspeciesname STR_VAR_2, SPECIES_CLEFAIRY
	givemon SPECIES_CLEFFA, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveMimeJr::
	setvar VAR_TEMP_1, SPECIES_MIME_JR
	bufferspeciesname STR_VAR_1, SPECIES_MIME_JR
	bufferspeciesname STR_VAR_2, SPECIES_MR_MIME
	givemon SPECIES_MIME_JR, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveIgglybuff::
	setvar VAR_TEMP_1, SPECIES_IGGLYBUFF
	bufferspeciesname STR_VAR_1, SPECIES_IGGLYBUFF
	bufferspeciesname STR_VAR_2, SPECIES_JIGGLYPUFF
	givemon SPECIES_IGGLYBUFF, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_ReceiveMantyke::
	setvar VAR_TEMP_1, SPECIES_MANTYKE
	bufferspeciesname STR_VAR_1, SPECIES_MANTYKE
	bufferspeciesname STR_VAR_2, SPECIES_MANTINE
	givemon SPECIES_MANTYKE, 1, ITEM_ORAN_BERRY
	goto PetalburgCity_House1_EventScript_CheckParty
	end

PetalburgCity_House1_EventScript_CheckParty::
	msgbox PetalburgCity_House1_Text_Take, MSGBOX_NPC
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, PetalburgCity_House1_EventScript_ReceiveParty
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, PetalburgCity_House1_EventScript_ReceivePC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

PetalburgCity_House1_EventScript_ReceiveParty::
	call PetalburgCity_House1_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PetalburgCity_House1_EventScript_TakeCare
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto PetalburgCity_House1_EventScript_TakeCare
	end

PetalburgCity_House1_EventScript_ReceivePC::
	call PetalburgCity_House1_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PetalburgCity_House1_EventScript_SendToPC
	call Common_EventScript_NameReceivedBoxMon
	goto PetalburgCity_House1_EventScript_SendToPC
	end

PetalburgCity_House1_EventScript_SendToPC::
	call Common_EventScript_TransferredToPC
	goto PetalburgCity_House1_EventScript_TakeCare
	end

PetalburgCity_House1_EventScript_CheckPartyTyrogue::
	msgbox PetalburgCity_House1_Text_Take, MSGBOX_NPC
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, PetalburgCity_House1_EventScript_ReceivePartyTyrogue
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, PetalburgCity_House1_EventScript_ReceivePCTyrogue
	goto Common_EventScript_NoMoreRoomForPokemon
	end

PetalburgCity_House1_EventScript_ReceivePartyTyrogue::
	call PetalburgCity_House1_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PetalburgCity_House1_EventScript_TakeCareTyrogue
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto PetalburgCity_House1_EventScript_TakeCareTyrogue
	end

PetalburgCity_House1_EventScript_ReceivePCTyrogue::
	call PetalburgCity_House1_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PetalburgCity_House1_EventScript_SendToPCTyrogue
	call Common_EventScript_NameReceivedBoxMon
	goto PetalburgCity_House1_EventScript_SendToPCTyrogue
	end

PetalburgCity_House1_EventScript_SendToPCTyrogue::
	call Common_EventScript_TransferredToPC
	goto PetalburgCity_House1_EventScript_TakeCareTyrogue
	end

PetalburgCity_House1_EventScript_ReceivedFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message PetalburgCity_House1_Text_PlayerReceived
	waitmessage
	waitfanfare
	return

PetalburgCity_House1_EventScript_TakeCare::
	msgbox PetalburgCity_House1_Text_IsBaby, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_BABY
	release
	end

PetalburgCity_House1_EventScript_TakeCareTyrogue::
	msgbox PetalburgCity_House1_Text_TyrogueEvolutions, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_BABY
	release
	end

PetalburgCity_House1_EventScript_StartQuiz::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BABY, PetalburgCity_House1_EventScript_TookBaby
	msgbox PetalburgCity_House1_Text_StartQuiz, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_1, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_Answer_1
	goto PetalburgCity_House1_EventScript_Answer_2
	end

PetalburgCity_House1_EventScript_TookBaby::
	msgbox PetalburgCity_House1_Text_BabyTaken, MSGBOX_NPC
	release
	end

PetalburgCity_House1_EventScript_Answer_1::
	msgbox PetalburgCity_House1_Text_QuizPush, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_2, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_Answer_1_1
	case 1, PetalburgCity_House1_EventScript_Answer_1_2
	goto PetalburgCity_House1_EventScript_Answer_1_3
	end

PetalburgCity_House1_EventScript_Answer_2::
	msgbox PetalburgCity_House1_Text_QuizGentle, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_3, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_Answer_2_1
	case 1, PetalburgCity_House1_EventScript_Answer_2_2
	goto PetalburgCity_House1_EventScript_Answer_2_3
	end

PetalburgCity_House1_EventScript_Answer_1_1::
	msgbox PetalburgCity_House1_Text_QuizGetStrong, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_4, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_ReceiveElekid
	case 1, PetalburgCity_House1_EventScript_ReceiveRiolu
	goto PetalburgCity_House1_EventScript_ReceiveTyrogue
	end

PetalburgCity_House1_EventScript_Answer_1_2::
	msgbox PetalburgCity_House1_Text_QuizFriends, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_5, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_ReceivePichu
	case 1, PetalburgCity_House1_EventScript_ReceiveBudew
	goto PetalburgCity_House1_EventScript_ReceiveWynaut
	end

PetalburgCity_House1_EventScript_Answer_1_3::
	msgbox PetalburgCity_House1_Text_QuizGoodTime, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_6, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_ReceiveMunchlax
	case 1, PetalburgCity_House1_EventScript_ReceiveSmoochum
	goto PetalburgCity_House1_EventScript_ReceiveMagby
	end

PetalburgCity_House1_EventScript_Answer_2_1::
	msgbox PetalburgCity_House1_Text_QuizThoughtful, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_7, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_ReceiveHappiny
	case 1, PetalburgCity_House1_EventScript_ReceiveTogepi
	goto PetalburgCity_House1_EventScript_ReceiveChingling
	end

PetalburgCity_House1_EventScript_Answer_2_2::
	msgbox PetalburgCity_House1_Text_QuizBonds, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_8, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_ReceiveBonsly
	case 1, PetalburgCity_House1_EventScript_ReceiveAzurill
	goto PetalburgCity_House1_EventScript_ReceiveCleffa
	end

PetalburgCity_House1_EventScript_Answer_2_3::
	msgbox PetalburgCity_House1_Text_QuizFun, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_BABY_QUIZ_9, TRUE
	switch VAR_RESULT
	case 0, PetalburgCity_House1_EventScript_ReceiveMimeJr
	case 1, PetalburgCity_House1_EventScript_ReceiveIgglybuff
	goto PetalburgCity_House1_EventScript_ReceiveMantyke
	end

PetalburgCity_House1_Text_TravelingIsWonderful:
	.string "Traveling is wonderful!\p"
	.string "When I was young, I roamed the seas\n"
	.string "and the mountains!$"

PetalburgCity_House1_Text_GoOnAdventure:
	.string "Sigh…\p"
	.string "I wish I could go on an adventure\n"
	.string "with some POKéMON…\p"
	.string "Crawl through some damp grass…\n"
	.string "Climb rocky, rugged mountains…\p"
	.string "Cross the raging seas…\n"
	.string "Wander about in dark caves…\p"
	.string "And, sometimes, even get a little\n"
	.string "homesick…\p"
	.string "It must be fabulous to travel!$"

PetalburgCity_House1_Text_StartQuiz:
	.string "Hey! My grandfather has traveled\n"
	.string "around many regions of the world\p"
	.string "and has quite a large selection\n"
	.string "of POKéMON!\p"
	.string "I've been breeding his POKéMON \n"
	.string "for many years now!\p"
	.string "Hey! I know!...\p"
	.string "Would you like one?\p"
	.string "I'm going to ask you a few short\n"
	.string "questions to determine which\p"
	.string "POKéMON is right for you!\p"
	.string "Question 1:\p"
	.string "How would you train your POKéMON?$"

PetalburgCity_House1_Text_QuizPush:
	.string "Uh huh...\p"
	.string "Question 2:\p"
	.string "What matters most when training?$"

PetalburgCity_House1_Text_QuizGentle:
	.string "Uh huh...\p"
	.string "Question 2:\p"
	.string "What matters most when training?$"

PetalburgCity_House1_Text_QuizGetStrong:
	.string "I see...\p"
	.string "Question 3:\p"
	.string "What makes someone strong?$"

PetalburgCity_House1_Text_QuizFriends:
	.string "I see...\p"
	.string "Question 3:\p"
	.string "What makes you specifically a\n"
	.string "great friend?$"

PetalburgCity_House1_Text_QuizGoodTime:
	.string "I see...\p"
	.string "Question 3:\p"
	.string "What's the key to a good night?$"

PetalburgCity_House1_Text_QuizThoughtful:
	.string "I see...\p"
	.string "Question 3:\p"
	.string "If you had to choose which group\n"
	.string "to help, which matters most?$"

PetalburgCity_House1_Text_QuizBonds:
	.string "I see...\p"
	.string "Question 3:\p"
	.string "What do you think brings people\n"
	.string "together?$"

PetalburgCity_House1_Text_QuizFun:
	.string "I see...\p"
	.string "Question 3:\p"
	.string "Which brings you the most\n"
	.string "enjoyment?$"

PetalburgCity_House1_Text_Take:
	.string "Mmmhm...!!\p"
	.string "That's it!\p"
	.string "I've figured out the perfect\n"
	.string "POKéMON for you!\p"
	.string "And that POKéMON is...\p"
	.string "{STR_VAR_1}!!$"

PetalburgCity_House1_Text_PlayerReceived:
	.string "{PLAYER} received {STR_VAR_1}!$"

PetalburgCity_House1_Text_IsBaby:
	.string "{STR_VAR_1} is a baby POKéMON!\p"
	.string "{STR_VAR_1} is the baby form of\n"
	.string "{STR_VAR_2}!\p"
	.string "Please, take good care of {STR_VAR_1}!$"

PetalburgCity_House1_Text_TyrogueEvolutions:
	.string "TYROGUE is a baby POKéMON!\p"
	.string "TYROGUE is the baby form of\n"
	.string "HITMONCHAN, HITMONLEE, and \p"
	.string "HITMONTOP!\p"
	.string "Please, take good care of TYROGUE!$"

PetalburgCity_House1_Text_BabyTaken:
	.string "Take good care of the POKéMON\n"
	.string "I gave to you!$"

