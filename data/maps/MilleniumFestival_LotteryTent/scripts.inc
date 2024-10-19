MilleniumFestival_LotteryTent_MapScripts::
	.byte 0

MilleniumFestival_EventScript_LotteryEntrance::
	msgbox MilleniumFestival_Text_LotteryEntrance, MSGBOX_NPC
	end

MilleniumFestival_EventScript_BadLuck::
	msgbox MilleniumFestival_Text_BadLuck, MSGBOX_NPC
	end

MilleniumFestival_EventScript_Lottery::
	lock
	faceplayer
	showmoneybox 0, 0
	msgbox MilleniumFestival_Text_Lottery, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MilleniumFestival_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, MilleniumFestival_EventScript_DeclineTrade
	copyvar VAR_0x800A, VAR_0x8004
	special GetTradeRandom
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special DoInGameTradeScene
	removemoney 1000
	waitstate
	goto MilleniumFestival_EventScript_DeclineTrade
	end

MilleniumFestival_EventScript_DeclineTrade::
	
	msgbox MilleniumFestival_Text_LotteryGoodbye, MSGBOX_DEFAULT
	release
	end

MilleniumFestival_Text_LotteryEntrance:
	.string "Step right up, kid! Welcome\n"
	.string "to the TRADE LOTTERY!!!\p"
	.string "You give us just one of your\n"
	.string "well-loved POKéMON and we\l"
	.string "will trade it for another\l"
	.string "one, entirely at random!\p"
	.string "The THRILS! The CHILLS! \n"
	.string "  The SUSPENSE! (Wow!)  \p"
	.string "Try us out today!\p"
	.string "(TradeLotteryIsNotResponsible\n"
	.string "ForTheQualityOfNewPOKéMON)$"

MilleniumFestival_Text_BadLuck:
	.string "I traded my strong MACHOP\n"
	.string "and only got a wimpy\l"
	.string "little CATERPIE! Grrr..\p"
	.string "... At least this little\n"
	.string "guy is cute...$"

MilleniumFestival_Text_Lottery:
	.string "Hello, and welcome to the\n"
	.string "Trade Lottery!\p"
	.string "Just give us one of your\n"
	.string "POKéMON and we will trade\l"
	.string "you another at random.\p"
	.string "..At the small fee of\n"
	.string "1000$, of course...\p"
	.string "Would you like to use\n"
	.string "the trade lottery?$"

MilleniumFestival_Text_LotteryGoodbye:
	.string "We hope you will use the\n"
	.string "the Trade Lottery again.$" 
