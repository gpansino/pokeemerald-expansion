#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "pokemon.h"

void SetCap(void){
    u8 trainerNum = gSpecialVar_0x8004;
    struct Trainer capTrainer = gTrainers[0];
    u8 cap = 100;

    switch(trainerNum){
        case 0: // rival route 103
            capTrainer = gTrainers[TRAINER_MAY_ROUTE_103_MUDKIP];
            break;
        case 1: // roxanne
            capTrainer = gTrainers[TRAINER_ROXANNE_1];
            break; 
        case 2: // brawly
            capTrainer = gTrainers[TRAINER_BRAWLY_1];
            break;
        case 3: // rival route 110
            capTrainer = gTrainers[TRAINER_MAY_ROUTE_110_MUDKIP];
            break;
        case 4: // wattson
            capTrainer = gTrainers[TRAINER_WATTSON_1];
            break;
        case 5: // flannery
            capTrainer = gTrainers[TRAINER_FLANNERY_1];
            break;
        case 6: // norman
            capTrainer = gTrainers[TRAINER_NORMAN_1];
            break;
        case 7: // rival route 119
            capTrainer = gTrainers[TRAINER_MAY_ROUTE_119_MUDKIP];
            break;
        case 8: // winona
            capTrainer = gTrainers[TRAINER_WINONA_1];
            break;
        case 9: // maxie magma hideout  
            capTrainer = gTrainers[TRAINER_MAXIE_MAGMA_HIDEOUT];
            break;
        case 10: // tate and liza
            capTrainer = gTrainers[TRAINER_TATE_AND_LIZA_1];
            break;
        case 11: // archie seafloor cavern
            capTrainer = gTrainers[TRAINER_ARCHIE];
            break;
        case 12: // juan/wallace
            capTrainer = gTrainers[TRAINER_JUAN_1];
            break;
        case 13: // champion 
            capTrainer = gTrainers[TRAINER_WALLACE];
            break;
        case 14: // no cap
            break;
    }

    if(capTrainer.trainerName != gTrainers[0].trainerName)
        cap = GetAce(capTrainer);
    *GetVarPointer(VAR_LEVEL_CAP) = cap;
}

int GetAce(struct Trainer capTrainer){
    int i;
    struct TrainerMon ace;

    ace.lvl = 0;
    for (i = 0; i < capTrainer.partySize; i++){
        if(capTrainer.party[i].lvl > ace.lvl){
            ace = capTrainer.party[i];
        }
    }
    return ace.lvl;
}

u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 19},
        {FLAG_BADGE03_GET, 24},
        {FLAG_BADGE04_GET, 29},
        {FLAG_BADGE05_GET, 31},
        {FLAG_BADGE06_GET, 33},
        {FLAG_BADGE07_GET, 42},
        {FLAG_BADGE08_GET, 46},
        {FLAG_IS_CHAMPION, 58},
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (B_LEVEL_CAP_EXP_UP && level < currentLevelCap)
    {
        levelDifference = currentLevelCap - level;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown))
            return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingDown) - 1]);
        else
            return expValue + (expValue / sExpScalingUp[levelDifference]);
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT && level >= currentLevelCap)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown))
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else if (level < currentLevelCap)
    {
       return expValue;
    }
    else
    {
        return 0;
    }

}
