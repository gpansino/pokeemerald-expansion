EventScript_UseSurf::
	checkpartymove MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_UseSurfboard
	goto EventScript_MonUseSurf
	end

EventScript_MonUseSurf::	
	bufferpartymonnick STR_VAR_1, VAR_RESULT
	setfieldeffectargument 0, VAR_RESULT
	setfieldeffectargument 4, 0
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_ReleaseUseSurf
	msgbox gText_PlayerUsedSurf, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
	releaseall
	end

EventScript_UseSurfboard::
	bufferitemname STR_VAR_1, ITEM_SURFBOARD
	setfieldeffectargument 0, 10
	setfieldeffectargument 4, 1
	lockall
	msgbox gText_WantToUseSurf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_ReleaseUseSurf
	msgbox Text_UseHmItem, MSGBOX_DEFAULT
	dofieldeffect FLDEFF_USE_SURF
	releaseall
	end

EventScript_ReleaseUseSurf::
	releaseall
EventScript_EndUseSurf::
	end
