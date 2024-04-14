#include "global.h"
#include "event_data.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "fldeff.h"
#include "party_menu.h"
#include "script.h"
#include "string_util.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"

// static functions
static void FieldCallback_Strength(void);
static void StartStrengthFieldEffect(void);

// text
bool8 SetUpFieldMove_Strength(void)
{
    if (CheckObjectGraphicsInFrontOfPlayer(OBJ_EVENT_GFX_PUSHABLE_BOULDER) == TRUE)
    {
        if(gFieldEffectArguments[4] == 0){
            gSpecialVar_Result = GetCursorSelectionMonId();
            gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
            gPostMenuFieldCallback = FieldCallback_Strength;
        }
        else { 
            gSpecialVar_Result = 9;
            FieldCallback_Strength();
        }
        return TRUE;
    }
    return FALSE;
}

bool8 FieldMove_Strength_Mon(void){
    gFieldEffectArguments[4] = 0;
    return SetUpFieldMove_Strength();
}

bool8 FieldMove_Strength_Item(void){
    gFieldEffectArguments[4] = 1;
    return SetUpFieldMove_Strength();
}

static void FieldCallback_Strength(void)
{
    if(gFieldEffectArguments[4] == 0)
        gFieldEffectArguments[0] = GetCursorSelectionMonId();//reference mon sprite
    else    
        gFieldEffectArguments[0] = 9;//reference force palms
    ScriptContext_SetupScript(EventScript_UseStrength);
}

bool8 FldEff_UseStrength(void)
{
    u8 taskId = CreateFieldMoveTask();
    gTasks[taskId].data[8] = (u32)StartStrengthFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartStrengthFieldEffect;
    GetMonNickname(&gPlayerParty[gFieldEffectArguments[0]], gStringVar1);
    return FALSE;
}

// Just passes control back to EventScript_UseStrength
static void StartStrengthFieldEffect(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_STRENGTH);
    ScriptContext_Enable();
}
