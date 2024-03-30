#include "global.h"
#include "berry.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_control_avatar.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "item.h"
#include "item_menu.h"
#include "main.h"
#include "random.h"
#include "script_pokemon_util.h"
#include "string_util.h"
#include "text.h"
#include "constants/event_object_movement.h"
#include "constants/items.h"

static u16 BerryTypeToItemId(u16 berry);
static u8 BerryTreeGetNumStagesWatered(struct BerryTree *tree);
static u8 GetNumStagesWateredByBerryTreeId(u8 id);
static u8 CalcBerryYieldInternal(u16 max, u16 min, u8 water);
static u8 CalcBerryYield(struct BerryTree *tree);
static u8 GetBerryCountByBerryTreeId(u8 id);
static u16 GetStageDurationByBerryType(u8);
//static u8 GetDrainRateByBerryType(u8);
//static u8 GetWaterBonusByBerryType(u8);
//static u8 GetWeedingBonusByBerryType(u8);
//static u8 GetPestsBonusByBerryType(u8);
//static void SetTreeMutations(u8 id, u8 berry);
//static u8 GetTreeMutationValue(u8 id);
//static u16 GetBerryPestSpecies(u8 berryId);
//static void TryForWeeds(struct BerryTree *tree);
//static void TryForPests(struct BerryTree *tree);
//static void AddTreeBonus(struct BerryTree *tree, u8 bonus);

// Check include/config/overworld.h configs and throw an error if illegal
#if OW_BERRY_GROWTH_RATE < GEN_3 || (OW_BERRY_GROWTH_RATE > GEN_7 && OW_BERRY_GROWTH_RATE != GEN_6_ORAS)
#error "OW_BERRY_GROWTH_RATE must be between GEN_3 and GEN_7!"
#endif

#if OW_BERRY_YIELD_RATE < GEN_3 || (OW_BERRY_YIELD_RATE > GEN_6 && OW_BERRY_YIELD_RATE != GEN_6_ORAS)
#error "OW_BERRY_YIELD_RATE must be between GEN_3 and GEN_6!"
#elif OW_BERRY_YIELD_RATE == GEN_5
#error "OW_BERRY_YIELD_RATE can not be GEN_5!"
#endif

#if OW_BERRY_MOISTURE && OW_BERRY_DRAIN_RATE != GEN_4 && OW_BERRY_DRAIN_RATE != GEN_6_XY && OW_BERRY_DRAIN_RATE != GEN_6_ORAS
#error "OW_BERRY_DRAIN_RATE must be GEN_5, GEN_6_XY or GEN_6_ORAS!"
#endif

#define GROWTH_DURATION(g3, g4, g5, xy, oras, g7) OW_BERRY_GROWTH_RATE == GEN_3 ? g3 : OW_BERRY_GROWTH_RATE == GEN_4 ? g4 : OW_BERRY_GROWTH_RATE == GEN_5 ? g5 : OW_BERRY_GROWTH_RATE == GEN_6_XY ? xy : OW_BERRY_GROWTH_RATE == GEN_6_ORAS ? oras : g7
#define YIELD_RATE(g3, g4, xy, oras) OW_BERRY_YIELD_RATE == GEN_3 ? g3 : OW_BERRY_YIELD_RATE == GEN_4 ? g4 : OW_BERRY_YIELD_RATE == GEN_6_XY ? xy : oras

const struct Berry gBerries[] =
{
    [ITEM_CHERI_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("CHERI"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_RED,
        .size = 20,
        .maxYield = YIELD_RATE(3, 5, 15, 20),
        .minYield = YIELD_RATE(2, 2, 4, 4),
        .description1 = COMPOUND_STRING("Blooms with delicate pretty flowers."),
        .description2 = COMPOUND_STRING("The bright red Berry is very spicy."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 15,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_CHESTO_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("CHESTO"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_PURPLE,
        .size = 80,
        .maxYield = YIELD_RATE(3, 5, 15, 20),
        .minYield = YIELD_RATE(2, 2, 4, 4),
        .description1 = COMPOUND_STRING("The Berry's thick skin and fruit are"),
        .description2 = COMPOUND_STRING("very tough. It is dry-tasting all over."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 15,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_PECHA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("PECHA"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_PINK,
        .size = 40,
        .maxYield = YIELD_RATE(3, 5, 15, 20),
        .minYield = YIELD_RATE(2, 2, 4, 4),
        .description1 = COMPOUND_STRING("Very sweet and delicious."),
        .description2 = COMPOUND_STRING("Also very tender - handle with care."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 15,
        .waterBonus = 10,
        .weedsBonus = 4,
        .pestsBonus = 6,
    },

    [ITEM_RAWST_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("RAWST"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 32,
        .maxYield = YIELD_RATE(3, 5, 15, 20),
        .minYield = YIELD_RATE(2, 2, 4, 4),
        .description1 = COMPOUND_STRING("If the leaves grow long and curly,"),
        .description2 = COMPOUND_STRING("the Berry seems to grow very bitter."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 10,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 15,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_ASPEAR_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("ASPEAR"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_YELLOW,
        .size = 50,
        .maxYield = YIELD_RATE(3, 5, 15, 20),
        .minYield = YIELD_RATE(2, 2, 4, 4),
        .description1 = COMPOUND_STRING("The hard Berry is dense with a rich"),
        .description2 = COMPOUND_STRING("juice. It is quite sour."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 10,
        .smoothness = 25,
        .drainRate = 15,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_LEPPA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("LEPPA"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_RED,
        .size = 28,
        .maxYield = YIELD_RATE(3, 5, 15, 22),
        .minYield = YIELD_RATE(2, 2, 2, 2),
        .description1 = COMPOUND_STRING("Grows slower than Cheri and others."),
        .description2 = COMPOUND_STRING("The smaller the Berry, the tastier."),
        .stageDuration = 4,
        .spicy = 10,
        .dry = 0,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 15,
        .waterBonus = 15,
        .weedsBonus = 3,
        .pestsBonus = 6,
    },

    [ITEM_ORAN_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("ORAN"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_BLUE,
        .size = 35,
        .maxYield = YIELD_RATE(3, 5, 15, 20),
        .minYield = YIELD_RATE(2, 2, 4, 4),
        .description1 = COMPOUND_STRING("A peculiar Berry with a mix of flavors."),
        .description2 = COMPOUND_STRING("Berries grow in half a day."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 10,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 15,
        .waterBonus = 10,
        .weedsBonus = 4,
        .pestsBonus = 6,
    },

    [ITEM_PERSIM_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("PERSIM"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PINK,
        .size = 47,
        .maxYield = YIELD_RATE(3, 5, 15, 20),
        .minYield = YIELD_RATE(2, 2, 4, 4),
        .description1 = COMPOUND_STRING("Loves sunlight. The Berry's color"),
        .description2 = COMPOUND_STRING("grows vivid when exposed to the sun."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 10,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 15,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_LUM_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("LUM"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 34,
        .maxYield = YIELD_RATE(2, 5, 20, 18),
        .minYield = YIELD_RATE(1, 2, 3, 2),
        .description1 = COMPOUND_STRING("Slow to grow. If raised with loving"),
        .description2 = COMPOUND_STRING("care, it may grow two Berries."),
        .stageDuration = 12,
        .spicy = 10,
        .dry = 10,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 8,
        .waterBonus = 12,
        .weedsBonus = 1,
        .pestsBonus = 6,
    },

    [ITEM_SITRUS_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("SITRUS"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_YELLOW,
        .size = 95,
        .maxYield = YIELD_RATE(3, 5, 20, 27),
        .minYield = YIELD_RATE(2, 2, 3, 3),
        .description1 = COMPOUND_STRING("Closely related to Oran. The large"),
        .description2 = COMPOUND_STRING("Berry has a well-rounded flavor."),
        .stageDuration = 6,
        .spicy = 10,
        .dry = 10,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 7,
        .waterBonus = 12,
        .weedsBonus = 1,
        .pestsBonus = 6,
    },

    [ITEM_FIGY_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("FIGY"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_RED,
        .size = 100,
        .maxYield = YIELD_RATE(3, 5, 15, 15),
        .minYield = YIELD_RATE(2, 1, 3, 3),
        .description1 = COMPOUND_STRING("The Berry, which looks chewed up,"),
        .description2 = COMPOUND_STRING("brims with spicy substances."),
        .stageDuration = 6,
        .spicy = 10,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 10,
        .waterBonus = 15,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_WIKI_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("WIKI"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PURPLE,
        .size = 115,
        .maxYield = YIELD_RATE(3, 5, 15, 15),
        .minYield = YIELD_RATE(2, 1, 3, 3),
        .description1 = COMPOUND_STRING("The Berry is said to have grown lumpy"),
        .description2 = COMPOUND_STRING("to help Pokémon grip it."),
        .stageDuration = 6,
        .spicy = 0,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 10,
        .waterBonus = 15,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_MAGO_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("MAGO"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PINK,
        .size = 126,
        .maxYield = YIELD_RATE(3, 5, 15, 15),
        .minYield = YIELD_RATE(2, 1, 3, 3),
        .description1 = COMPOUND_STRING("The Berry turns curvy as it grows."),
        .description2 = COMPOUND_STRING("The curvier, the sweeter and tastier."),
        .stageDuration = 6,
        .spicy = 0,
        .dry = 0,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 10,
        .waterBonus = 15,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_AGUAV_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("AGUAV"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 64,
        .maxYield = YIELD_RATE(3, 5, 15, 15),
        .minYield = YIELD_RATE(2, 1, 3, 3),
        .description1 = COMPOUND_STRING("The flower is dainty. It is rare in its"),
        .description2 = COMPOUND_STRING("ability to grow without light."),
        .stageDuration = 6,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 10,
        .sour = 0,
        .smoothness = 25,
        .drainRate = 10,
        .waterBonus = 15,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_IAPAPA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("IAPAPA"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_YELLOW,
        .size = 223,
        .maxYield = YIELD_RATE(3, 5, 15, 15),
        .minYield = YIELD_RATE(2, 1, 3, 3),
        .description1 = COMPOUND_STRING("The Berry is very big and sour."),
        .description2 = COMPOUND_STRING("It takes at least a day to grow."),
        .stageDuration = 6,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 10,
        .smoothness = 25,
        .drainRate = 10,
        .waterBonus = 15,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_RAZZ_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("RAZZ"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_RED,
        .size = 120,
        .maxYield = YIELD_RATE(6, 10, 15, 20),
        .minYield = YIELD_RATE(3, 2, 3, 4),
        .description1 = COMPOUND_STRING("The red Berry tastes slightly spicy."),
        .description2 = COMPOUND_STRING("It grows quickly in just four hours."),
                .stageDuration = 1,
        .spicy = 10,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 20,
        .drainRate = 35,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_BLUK_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("BLUK"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_PURPLE,
        .size = 108,
        .maxYield = YIELD_RATE(6, 10, 15, 20),
        .minYield = YIELD_RATE(3, 2, 3, 4),
        .description1 = COMPOUND_STRING("The Berry is blue on the outside, but"),
        .description2 = COMPOUND_STRING("it blackens the mouth when eaten."),
        .stageDuration = 1,
        .spicy = 0,
        .dry = 10,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 20,
        .drainRate = 35,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_NANAB_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("NANAB"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_PINK,
        .size = 77,
        .maxYield = YIELD_RATE(6, 10, 15, 20),
        .minYield = YIELD_RATE(3, 2, 3, 4),
        .description1 = COMPOUND_STRING("This Berry was the seventh"),
        .description2 = COMPOUND_STRING("discovered in the world. It is sweet."),
        .stageDuration = 1,
        .spicy = 0,
        .dry = 0,
        .sweet = 10,
        .bitter = 10,
        .sour = 0,
        .smoothness = 20,
        .drainRate = 35,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_WEPEAR_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("WEPEAR"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 74,
        .maxYield = YIELD_RATE(6, 10, 15, 20),
        .minYield = YIELD_RATE(3, 2, 3, 4),
        .description1 = COMPOUND_STRING("The flower is small and white. It has a"),
        .description2 = COMPOUND_STRING("delicate balance of bitter and sour."),
        .stageDuration = 1,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 10,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 35,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_PINAP_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("PINAP"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_YELLOW,
        .size = 80,
        .maxYield = YIELD_RATE(6, 10, 15, 20),
        .minYield = YIELD_RATE(3, 2, 3, 4),
        .description1 = COMPOUND_STRING("Weak against wind and cold."),
        .description2 = COMPOUND_STRING("The fruit is spicy and the skin, sour."),
        .stageDuration = 1,
        .spicy = 10,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 35,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_POMEG_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("POMEG"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_RED,
        .size = 135,
        .maxYield = YIELD_RATE(6, 5, 20, 26),
        .minYield = YIELD_RATE(2, 1, 1, 2),
        .description1 = COMPOUND_STRING("However much it is watered,"),
        .description2 = COMPOUND_STRING("it only grows up to six Berries."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 0,
        .sweet = 10,
        .bitter = 10,
        .sour = 0,
        .smoothness = 20,
        .drainRate = 8,
        .waterBonus = 5,
        .weedsBonus = 3,
        .pestsBonus = 6,
    },

    [ITEM_KELPSY_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("KELPSY"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_BLUE,
        .size = 150,
        .maxYield = YIELD_RATE(6, 5, 20, 26),
        .minYield = YIELD_RATE(2, 1, 1, 2),
        .description1 = COMPOUND_STRING("A rare variety shaped like a root."),
        .description2 = COMPOUND_STRING("Grows a very large flower."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 10,
        .sweet = 0,
        .bitter = 10,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 8,
        .waterBonus = 5,
        .weedsBonus = 3,
        .pestsBonus = 6,
    },

    [ITEM_QUALOT_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("QUALOT"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_YELLOW,
        .size = 110,
        .maxYield = YIELD_RATE(6, 5, 20, 26),
        .minYield = YIELD_RATE(2, 1, 1, 2),
        .description1 = COMPOUND_STRING("Loves water. Grows strong even in"),
        .description2 = COMPOUND_STRING("locations with constant rainfall."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 0,
        .sweet = 10,
        .bitter = 0,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 8,
        .waterBonus = 5,
        .weedsBonus = 3,
        .pestsBonus = 6,
    },

    [ITEM_HONDEW_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("HONDEW"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 162,
        .maxYield = YIELD_RATE(6, 5, 20, 26),
        .minYield = YIELD_RATE(2, 1, 1, 2),
        .description1 = COMPOUND_STRING("A Berry that is very valuable and"),
        .description2 = COMPOUND_STRING("rarely seen. It is very delicious."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 10,
        .sweet = 0,
        .bitter = 10,
        .sour = 0,
        .smoothness = 20,
        .drainRate = 8,
        .waterBonus = 5,
        .weedsBonus = 3,
        .pestsBonus = 6,
    },

    [ITEM_GREPA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("GREPA"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_YELLOW,
        .size = 149,
        .maxYield = YIELD_RATE(6, 5, 20, 26),
        .minYield = YIELD_RATE(2, 1, 1, 2),
        .description1 = COMPOUND_STRING("Despite its tenderness and round"),
        .description2 = COMPOUND_STRING("shape, the Berry is unimaginably sour."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 10,
        .sweet = 10,
        .bitter = 0,
        .sour = 10,
        .smoothness = 20,
        .drainRate = 8,
        .waterBonus = 5,
        .weedsBonus = 3,
        .pestsBonus = 6,
    },

    [ITEM_TAMATO_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("TAMATO"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_RED,
        .size = 200,
        .maxYield = YIELD_RATE(4, 5, 20, 26),
        .minYield = YIELD_RATE(2, 1, 1, 2),
        .description1 = COMPOUND_STRING("The Berry is lip-bendingly spicy."),
        .description2 = COMPOUND_STRING("It takes time to grow."),
        .stageDuration = 6,
        .spicy = 20,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 8,
        .waterBonus = 5,
        .weedsBonus = 3,
        .pestsBonus = 6,
    },

    [ITEM_CORNN_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("CORNN"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PURPLE,
        .size = 75,
        .maxYield = YIELD_RATE(4, 10, 15, 15),
        .minYield = YIELD_RATE(2, 2, 3, 3),
        .description1 = COMPOUND_STRING("A Berry from an ancient era. May not"),
        .description2 = COMPOUND_STRING("grow unless planted in quantity."),
        .stageDuration = 6,
        .spicy = 0,
        .dry = 20,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 10,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_MAGOST_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("MAGOST"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PINK,
        .size = 140,
        .maxYield = YIELD_RATE(4, 10, 15, 15),
        .minYield = YIELD_RATE(2, 2, 3, 3),
        .description1 = COMPOUND_STRING("A Berry that is widely said to have"),
        .description2 = COMPOUND_STRING("a finely balanced flavor."),
        .stageDuration = 6,
        .spicy = 0,
        .dry = 0,
        .sweet = 20,
        .bitter = 10,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 10,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_RABUTA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("RABUTA"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_GREEN,
        .size = 226,
        .maxYield = YIELD_RATE(4, 10, 15, 15),
        .minYield = YIELD_RATE(2, 2, 3, 3),
        .description1 = COMPOUND_STRING("A rare variety that is overgrown with"),
        .description2 = COMPOUND_STRING("hair. It is quite bitter."),
        .stageDuration = 6,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 20,
        .sour = 10,
        .smoothness = 30,
        .drainRate = 10,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_NOMEL_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("NOMEL"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_YELLOW,
        .size = 285,
        .maxYield = YIELD_RATE(4, 10, 15, 15),
        .minYield = YIELD_RATE(2, 2, 3, 3),
        .description1 = COMPOUND_STRING("Quite sour. Just one bite makes it"),
        .description2 = COMPOUND_STRING("impossible to taste for three days."),
        .stageDuration = 6,
        .spicy = 10,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 20,
        .smoothness = 30,
        .drainRate = 10,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_SPELON_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("SPELON"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_RED,
        .size = 133,
        .maxYield = YIELD_RATE(2, 15, 15, 15),
        .minYield = YIELD_RATE(1, 2, 3, 3),
        .description1 = COMPOUND_STRING("The vividly red Berry is very spicy."),
        .description2 = COMPOUND_STRING("Its warts secrete a spicy substance."),
        .stageDuration = 8,
        .spicy = 40,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 70,
        .drainRate = 8,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_PAMTRE_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("PAMTRE"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_PURPLE,
        .size = 244,
        .maxYield = YIELD_RATE(2, 15, 15, 15),
        .minYield = YIELD_RATE(1, 3, 3, 3),
        .description1 = COMPOUND_STRING("Drifts on the sea from somewhere."),
        .description2 = COMPOUND_STRING("It is thought to grow elsewhere."),
        .stageDuration = 8,
        .spicy = 0,
        .dry = 40,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 70,
        .drainRate = 8,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_WATMEL_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("WATMEL"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_PINK,
        .size = 250,
        .maxYield = YIELD_RATE(2, 15, 15, 15),
        .minYield = YIELD_RATE(1, 2, 3, 3),
        .description1 = COMPOUND_STRING("A huge Berry, with some over 20"),
        .description2 = COMPOUND_STRING("inches discovered. Exceedingly sweet."),
        .stageDuration = 8,
        .spicy = 0,
        .dry = 0,
        .sweet = 40,
        .bitter = 10,
        .sour = 0,
        .smoothness = 70,
        .drainRate = 8,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_DURIN_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("DURIN"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 280,
        .maxYield = YIELD_RATE(2, 15, 15, 15),
        .minYield = YIELD_RATE(1, 3, 3, 3),
        .description1 = COMPOUND_STRING("Bitter to even look at. It is so"),
        .description2 = COMPOUND_STRING("bitter, no one has ever eaten it as is."),
        .stageDuration = 8,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 40,
        .sour = 10,
        .smoothness = 70,
        .drainRate = 8,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_BELUE_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("BELUE"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_PURPLE,
        .size = 300,
        .maxYield = YIELD_RATE(2, 15, 15, 15),
        .minYield = YIELD_RATE(1, 2, 3, 3),
        .description1 = COMPOUND_STRING("It is glossy and looks delicious, but"),
        .description2 = COMPOUND_STRING("it is awfully sour. Takes time to grow."),
        .stageDuration = 8,
        .spicy = 10,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 40,
        .smoothness = 70,
        .drainRate = 8,
        .waterBonus = 10,
        .weedsBonus = 2,
        .pestsBonus = 6,
    },

    [ITEM_CHILAN_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("CHILAN"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_YELLOW,
        .size = 34,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("It can be made into a whistle that"),
        .description2 = COMPOUND_STRING("produces an indescribable sound."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 25,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_OCCA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("OCCA"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_RED,
        .size = 90,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Said to grow in the tropics once,"),
        .description2 = COMPOUND_STRING("it boasts an intensely hot spiciness."),
        .stageDuration = 3,
        .spicy = 15,
        .dry = 0,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_PASSHO_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("PASSHO"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_BLUE,
        .size = 33,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Its flesh is dotted with many tiny"),
        .description2 = COMPOUND_STRING("bubbles that keep it afloat in water."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 15,
        .sweet = 0,
        .bitter = 10,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_WACAN_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("WACAN"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_YELLOW,
        .size = 250,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Energy drawn from lightning strikes"),
        .description2 = COMPOUND_STRING("makes this Berry grow big and rich."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 15,
        .bitter = 0,
        .sour = 10,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_RINDO_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("RINDO"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_GREEN,
        .size = 156,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("This berry has a vegetable-like flavor,"),
        .description2 = COMPOUND_STRING("but is rich in health-promoting fiber."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 0,
        .sweet = 0,
        .bitter = 15,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_YACHE_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("YACHE"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_BLUE,
        .size = 135,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("This Berry has a refreshing dry and"),
        .description2 = COMPOUND_STRING("sour flavor. Tastes better chilled."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 15,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_CHOPLE_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("CHOPLE"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_RED,
        .size = 77,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Contains a substance that generates"),
        .description2 = COMPOUND_STRING("heat. Can even fire up a chilly heart."),
        .stageDuration = 3,
        .spicy = 15,
        .dry = 0,
        .sweet = 0,
        .bitter = 10,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_KEBIA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("KEBIA"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 90,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Brilliant green on the outside, inside"),
        .description2 = COMPOUND_STRING("it is packed with black-colored flesh."),
         .stageDuration = 3,
        .spicy = 0,
        .dry = 15,
        .sweet = 0,
        .bitter = 0,
        .sour = 10,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_SHUCA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("SHUCA"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_YELLOW,
        .size = 42,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("The sweet pulp has just the hint of a"),
        .description2 = COMPOUND_STRING("a hard-edged and fragrant bite to it."),
         .stageDuration = 3,
        .spicy = 10,
        .dry = 0,
        .sweet = 15,
        .bitter = 0,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_COBA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("COBA"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_BLUE,
        .size = 278,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("This Berry is said to be a cross of"),
        .description2 = COMPOUND_STRING("two Berries blown in from far away."),
          .stageDuration = 3,
        .spicy = 0,
        .dry = 10,
        .sweet = 0,
        .bitter = 15,
        .sour = 0,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_PAYAPA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("PAYAPA"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_PURPLE,
        .size = 252,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Said to sense human emotions, it swells"),
        .description2 = COMPOUND_STRING("roundly when a person approaches."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 10,
        .bitter = 0,
        .sour = 15,
        .smoothness = 30,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_TANGA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("TANGA"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_GREEN,
        .size = 42,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("It grows a flower at the tip that lures"),
        .description2 = COMPOUND_STRING("Bug Pokémon with its stringy petals."),
        .stageDuration = 3,
        .spicy = 20,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 10,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_CHARTI_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("CHARTI"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_YELLOW,
        .size = 28,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Often used for pickles because of its"),
        .description2 = COMPOUND_STRING("dry flavor. Sometimes eaten raw."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 20,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_KASIB_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("KASIB"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PURPLE,
        .size = 144,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Old superstitions say it has an odd"),
        .description2 = COMPOUND_STRING("power. A popular good-luck charm."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 10,
        .sweet = 20,
        .bitter = 0,
        .sour = 0,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_HABAN_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("HABAN"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_RED,
        .size = 23,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Less bitter if enough of this Berry"),
        .description2 = COMPOUND_STRING("is boiled down. Makes a good jam."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 10,
        .bitter = 20,
        .sour = 0,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_COLBUR_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("COLBUR"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_PURPLE,
        .size = 39,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Tiny hooks on the surface latch onto"),
        .description2 = COMPOUND_STRING("Pokémon to reach far-off places."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 10,
        .sour = 20,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_BABIRI_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("BABIRI"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 265,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("Very tough with a strong flavor. It"),
        .description2 = COMPOUND_STRING("was used to make medicine in the past."),
        .stageDuration = 3,
        .spicy = 25,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_ROSELI_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("ROSELI"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PINK,
        .size = 35,
        .maxYield = YIELD_RATE(5, 5, 20, 10),
        .minYield = YIELD_RATE(2, 1, 3, 2),
        .description1 = COMPOUND_STRING("In nature, they grow in wide rings"),
        .description2 = COMPOUND_STRING("for reasons that are still unknown."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 25,
        .bitter = 10,
        .sour = 0,
        .smoothness = 35,
        .drainRate = 6,
        .waterBonus = 10,
        .weedsBonus = 1,
        .pestsBonus = 4,
    },

    [ITEM_LIECHI_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("LIECHI"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_RED,
        .size = 111,
        .maxYield = YIELD_RATE(2, 5, 10, 13),
        .minYield = YIELD_RATE(1, 1, 1, 2),
        .description1 = COMPOUND_STRING("A mysterious Berry. It is rumored to"),
        .description2 = COMPOUND_STRING("contain the power of the sea."),
        .stageDuration = 12,
        .spicy = 40,
        .dry = 0,
        .sweet = 40,
        .bitter = 0,
        .sour = 10,
        .smoothness = 80,
        .drainRate = 4,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 2,
    },

    [ITEM_GANLON_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("GANLON"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_PURPLE,
        .size = 33,
        .maxYield = YIELD_RATE(2, 5, 10, 13),
        .minYield = YIELD_RATE(1, 1, 1, 2),
        .description1 = COMPOUND_STRING("A mysterious Berry. It is rumored to"),
        .description2 = COMPOUND_STRING("contain the power of the land."),
        .stageDuration = 12,
        .spicy = 0,
        .dry = 40,
        .sweet = 0,
        .bitter = 40,
        .sour = 0,
        .smoothness = 80,
        .drainRate = 4,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 2,
    },

    [ITEM_SALAC_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("SALAC"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 95,
        .maxYield = YIELD_RATE(2, 5, 10, 13),
        .minYield = YIELD_RATE(1, 1, 1, 2),
        .description1 = COMPOUND_STRING("A mysterious Berry. It is rumored to"),
        .description2 = COMPOUND_STRING("contain the power of the sky."),
        .stageDuration = 12,
        .spicy = 0,
        .dry = 0,
        .sweet = 40,
        .bitter = 0,
        .sour = 40,
        .smoothness = 80,
        .drainRate = 4,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 2,
    },

    [ITEM_PETAYA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("PETAYA"),
        .firmness = BERRY_FIRMNESS_VERY_HARD,
        .color = BERRY_COLOR_PINK,
        .size = 237,
        .maxYield = YIELD_RATE(2, 5, 10, 13),
        .minYield = YIELD_RATE(1, 1, 1, 2),
        .description1 = COMPOUND_STRING("A mysterious Berry. It is rumored to"),
        .description2 = COMPOUND_STRING("contain the power of all living things."),
        .stageDuration = 12,
        .spicy = 40,
        .dry = 0,
        .sweet = 0,
        .bitter = 40,
        .sour = 0,
        .smoothness = 80,
        .drainRate = 4,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 2,
    },

    [ITEM_APICOT_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("APICOT"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_BLUE,
        .size = 75,
        .maxYield = YIELD_RATE(2, 5, 10, 13),
        .minYield = YIELD_RATE(1, 1, 1, 2),
        .description1 = COMPOUND_STRING("A very mystifying Berry. No telling"),
        .description2 = COMPOUND_STRING("what may happen or how it can be used."),
        .stageDuration =12,
        .spicy = 0,
        .dry = 40,
        .sweet = 0,
        .bitter = 0,
        .sour = 40,
        .smoothness = 80,
        .drainRate = 4,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 2,
    },

    [ITEM_LANSAT_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("LANSAT"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_RED,
        .size = 97,
        .maxYield = YIELD_RATE(2, 5, 5, 7),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("Said to be a legendary Berry."),
        .description2 = COMPOUND_STRING("Holding it supposedly brings joy."),
        .stageDuration = 12,
        .spicy = 10,
        .dry = 10,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 30,
        .drainRate = 4,
        .waterBonus = 1,
        .weedsBonus = 0,
        .pestsBonus = 1,
    },

    [ITEM_STARF_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("STARF"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_GREEN,
        .size = 153,
        .maxYield = YIELD_RATE(2, 5, 5, 7),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("So strong, it was abandoned at the"),
        .description2 = COMPOUND_STRING("world's edge. Considered a mirage."),
        .stageDuration = 12,
        .spicy = 10,
        .dry = 10,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 30,
        .drainRate = 4,
        .waterBonus = 1,
        .weedsBonus = 0,
        .pestsBonus = 1,
    },

    [ITEM_ENIGMA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("ENIGMA"),
        .firmness = BERRY_FIRMNESS_HARD,
        .color = BERRY_COLOR_PURPLE,
        .size = 155,
        .maxYield = YIELD_RATE(2, 5, 5, 13),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("A completely enigmatic Berry."),
        .description2 = COMPOUND_STRING("Appears to have the power of stars."),
        .stageDuration = 12,
        .spicy = 40,
        .dry = 10,
        .sweet = 0,
        .bitter = 0,
        .sour = 0,
        .smoothness = 60,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 0,
    },

    [ITEM_MICLE_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("MICLE"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_GREEN,
        .size = 41,
        .maxYield = YIELD_RATE(2, 5, 5, 13),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("It makes other food eaten at the"),
        .description2 = COMPOUND_STRING("same time taste sweet."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 40,
        .sweet = 10,
        .bitter = 0,
        .sour = 0,
        .smoothness = 60,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 0,
    },

    [ITEM_CUSTAP_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("CUSTAP"),
        .firmness = BERRY_FIRMNESS_SUPER_HARD,
        .color = BERRY_COLOR_RED,
        .size = 267,
        .maxYield = YIELD_RATE(2, 5, 5, 13),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("The flesh underneath the Custap"),
        .description2 = COMPOUND_STRING("Berry's skin is sweet and creamy soft."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 40,
        .bitter = 10,
        .sour = 0,
        .smoothness = 60,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 0,
    },

    [ITEM_JABOCA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("JABOCA"),
        .firmness = BERRY_FIRMNESS_SOFT,
        .color = BERRY_COLOR_YELLOW,
        .size = 33,
        .maxYield = YIELD_RATE(2, 5, 5, 13),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("The drupelets that make up this berry"),
        .description2 = COMPOUND_STRING("pop rythmically if handled roughly."),
        .stageDuration = 3,
        .spicy = 0,
        .dry = 0,
        .sweet = 0,
        .bitter = 40,
        .sour = 10,
        .smoothness = 60,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 0,
    },

    [ITEM_ROWAP_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("ROWAP"),
        .firmness = BERRY_FIRMNESS_VERY_SOFT,
        .color = BERRY_COLOR_BLUE,
        .size = 52,
        .maxYield = YIELD_RATE(2, 5, 5, 13),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("People once worked top-shaped pieces"),
        .description2 = COMPOUND_STRING("of this berry free to use as toys."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 0,
        .sweet = 0,
        .bitter = 0,
        .sour = 40,
        .smoothness = 60,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 0,
    },

    [ITEM_KEE_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("KEE"),
        .firmness = BERRY_FIRMNESS_UNKNOWN,
        .color = BERRY_COLOR_YELLOW,
        .size = 0,
        .maxYield = YIELD_RATE(2, 5, 10, 13),
        .minYield = YIELD_RATE(1, 1, 1, 2),
        .description1 = COMPOUND_STRING("A berry that is incredibly spicy at"),
        .description2 = COMPOUND_STRING("first, then extremely bitter."),
        .stageDuration = 3,
        .spicy = 30,
        .dry = 30,
        .sweet = 10,
        .bitter = 10,
        .sour = 10,
        .smoothness = 60,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 2,
    },

    [ITEM_MARANGA_BERRY - FIRST_BERRY_INDEX] =
    {
        .name = _("MARNGA"), // "Maranga" is too long
        .firmness = BERRY_FIRMNESS_UNKNOWN,
        .color = BERRY_COLOR_BLUE,
        .size = 0,
        .maxYield = YIELD_RATE(2, 5, 10, 13),
        .minYield = YIELD_RATE(1, 1, 1, 2),
        .description1 = COMPOUND_STRING("Its outside is very bitter, but its"),
        .description2 = COMPOUND_STRING("inside tastes like a sweet drink."),
        .stageDuration = 3,
        .spicy = 10,
        .dry = 10,
        .sweet = 30,
        .bitter = 30,
        .sour = 10,
        .smoothness = 60,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 2,
    },

    [ITEM_ENIGMA_BERRY_E_READER - FIRST_BERRY_INDEX] =
    {
        .name = _("ENIGMA"),
        .firmness = BERRY_FIRMNESS_UNKNOWN,
        .color = BERRY_COLOR_PURPLE,
        .size = 0,
        .maxYield = YIELD_RATE(2, 5, 5, 13),
        .minYield = YIELD_RATE(1, 1, 1, 1),
        .description1 = COMPOUND_STRING("A completely enigmatic Berry."),
        .description2 = COMPOUND_STRING("Appears to have the power of stars."),
        .stageDuration = 3,
        .spicy = 40,
        .dry = 40,
        .sweet = 40,
        .bitter = 40,
        .sour = 40,
        .smoothness = 40,
        .drainRate = 7,
        .waterBonus = 2,
        .weedsBonus = 0,
        .pestsBonus = 0,
    },
};

const struct BerryCrushBerryData gBerryCrush_BerryData[] = {
    [ITEM_CHERI_BERRY - FIRST_BERRY_INDEX]           = {.difficulty =  50, .powder =  20},
    [ITEM_CHESTO_BERRY - FIRST_BERRY_INDEX]          = {.difficulty =  50, .powder =  20},
    [ITEM_PECHA_BERRY - FIRST_BERRY_INDEX]           = {.difficulty =  50, .powder =  20},
    [ITEM_RAWST_BERRY - FIRST_BERRY_INDEX]           = {.difficulty =  50, .powder =  20},
    [ITEM_ASPEAR_BERRY - FIRST_BERRY_INDEX]          = {.difficulty =  50, .powder =  20},
    [ITEM_LEPPA_BERRY - FIRST_BERRY_INDEX]           = {.difficulty =  50, .powder =  30},
    [ITEM_ORAN_BERRY - FIRST_BERRY_INDEX]            = {.difficulty =  50, .powder =  30},
    [ITEM_PERSIM_BERRY - FIRST_BERRY_INDEX]          = {.difficulty =  50, .powder =  30},
    [ITEM_LUM_BERRY - FIRST_BERRY_INDEX]             = {.difficulty =  50, .powder =  30},
    [ITEM_SITRUS_BERRY - FIRST_BERRY_INDEX]          = {.difficulty =  50, .powder =  30},
    [ITEM_FIGY_BERRY - FIRST_BERRY_INDEX]            = {.difficulty =  60, .powder =  50},
    [ITEM_WIKI_BERRY - FIRST_BERRY_INDEX]            = {.difficulty =  60, .powder =  50},
    [ITEM_MAGO_BERRY - FIRST_BERRY_INDEX]            = {.difficulty =  60, .powder =  50},
    [ITEM_AGUAV_BERRY - FIRST_BERRY_INDEX]           = {.difficulty =  60, .powder =  50},
    [ITEM_IAPAPA_BERRY - FIRST_BERRY_INDEX]          = {.difficulty =  60, .powder =  50},
    [ITEM_RAZZ_BERRY - FIRST_BERRY_INDEX]            = {.difficulty =  80, .powder =  70},
    [ITEM_BLUK_BERRY - FIRST_BERRY_INDEX]            = {.difficulty =  80, .powder =  70},
    [ITEM_NANAB_BERRY - FIRST_BERRY_INDEX]           = {.difficulty =  80, .powder =  70},
    [ITEM_WEPEAR_BERRY - FIRST_BERRY_INDEX]          = {.difficulty =  80, .powder =  70},
    [ITEM_PINAP_BERRY - FIRST_BERRY_INDEX]           = {.difficulty =  80, .powder =  70},
    [ITEM_POMEG_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 100, .powder = 100},
    [ITEM_KELPSY_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 100, .powder = 100},
    [ITEM_QUALOT_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 100, .powder = 100},
    [ITEM_HONDEW_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 100, .powder = 100},
    [ITEM_GREPA_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 100, .powder = 100},
    [ITEM_TAMATO_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 130, .powder = 150},
    [ITEM_CORNN_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 130, .powder = 150},
    [ITEM_MAGOST_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 130, .powder = 150},
    [ITEM_RABUTA_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 130, .powder = 150},
    [ITEM_NOMEL_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 130, .powder = 150},
    [ITEM_SPELON_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 160, .powder = 250},
    [ITEM_PAMTRE_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 160, .powder = 250},
    [ITEM_WATMEL_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 160, .powder = 250},
    [ITEM_DURIN_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 160, .powder = 250},
    [ITEM_BELUE_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 160, .powder = 250},
    [ITEM_LIECHI_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 180, .powder = 500},
    [ITEM_GANLON_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 180, .powder = 500},
    [ITEM_SALAC_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 180, .powder = 500},
    [ITEM_PETAYA_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 180, .powder = 500},
    [ITEM_APICOT_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 180, .powder = 500},
    [ITEM_LANSAT_BERRY - FIRST_BERRY_INDEX]          = {.difficulty = 200, .powder = 750},
    [ITEM_STARF_BERRY - FIRST_BERRY_INDEX]           = {.difficulty = 200, .powder = 750},
    [ITEM_ENIGMA_BERRY_E_READER - FIRST_BERRY_INDEX] = {.difficulty = 150, .powder = 200}
};

const struct BerryTree gBlankBerryTree = {};

void SetEnigmaBerry(u8 *src)
{
#if FREE_ENIGMA_BERRY == FALSE
    u32 i;
    u8 *dest = (u8 *)&gSaveBlock1Ptr->enigmaBerry;

    for (i = 0; i < sizeof(gSaveBlock1Ptr->enigmaBerry); i++)
        dest[i] = src[i];
#endif //FREE_ENIGMA_BERRY
}

#if FREE_ENIGMA_BERRY == FALSE
static u32 GetEnigmaBerryChecksum(struct EnigmaBerry *enigmaBerry)
{
    u32 i;
    u32 checksum;
    u8 *dest;

    dest = (u8 *)enigmaBerry;
    checksum = 0;
    for (i = 0; i < sizeof(gSaveBlock1Ptr->enigmaBerry) - sizeof(gSaveBlock1Ptr->enigmaBerry.checksum); i++)
        checksum += dest[i];

    return checksum;
}
#endif //FREE_ENIGMA_BERRY

bool32 IsEnigmaBerryValid(void)
{
#if FREE_ENIGMA_BERRY == FALSE
    if (!gSaveBlock1Ptr->enigmaBerry.berry.growthDuration)
        return FALSE;
    if (!gSaveBlock1Ptr->enigmaBerry.berry.maxYield)
        return FALSE;
    if (GetEnigmaBerryChecksum(&gSaveBlock1Ptr->enigmaBerry) != gSaveBlock1Ptr->enigmaBerry.checksum)
        return FALSE;
    return TRUE;
#else
    return FALSE;
#endif //FREE_ENIGMA_BERRY
}

const struct Berry *GetBerryInfo(u8 berry)
{
    if (berry == ITEM_TO_BERRY(ITEM_ENIGMA_BERRY_E_READER) && IsEnigmaBerryValid())
    #if FREE_ENIGMA_BERRY == FALSE
        return (struct Berry *)(&gSaveBlock1Ptr->enigmaBerry.berry);
    #else
        return &gBerries[0];    //never reached, but will appease the compiler gods
    #endif //FREE_ENIGMA_BERRY
    else
    {
        if (berry == BERRY_NONE || berry > ITEM_TO_BERRY(LAST_BERRY_INDEX))
            berry = ITEM_TO_BERRY(FIRST_BERRY_INDEX);
        return &gBerries[berry - 1];
    }
}

struct BerryTree *GetBerryTreeInfo(u8 id)
{
    return &gSaveBlock1Ptr->berryTrees[id];
}

bool32 ObjectEventInteractionWaterBerryTree(void)
{
    struct BerryTree *tree = GetBerryTreeInfo(GetObjectEventBerryTreeId(gSelectedObjectEvent));
    const struct Berry *berry = GetBerryInfo(tree->berry);

    switch (tree->stage)
    {
    case BERRY_STAGE_PLANTED:
        tree->watered1 += 1;
        if(tree->watered1 >= berry->stageDuration)
            BerryTreeGrow(tree);
        break;
    case BERRY_STAGE_SPROUTED:
        tree->watered2 += 1;
        if(tree->watered2 >= berry->stageDuration)
            BerryTreeGrow(tree);
        break;
    case BERRY_STAGE_TALLER:
        tree->watered3 += 1;
        if(tree->watered3 >= berry->stageDuration)
            BerryTreeGrow(tree);
        break;
    case BERRY_STAGE_FLOWERING:
        tree->watered4 += 1;
        if(tree->watered4 >= berry->stageDuration)
            BerryTreeGrow(tree);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

bool8 IsPlayerFacingEmptyBerryTreePatch(void)
{
    if (GetObjectEventScriptPointerPlayerFacing() == BerryTreeScript
     && GetStageByBerryTreeId(GetObjectEventBerryTreeId(gSelectedObjectEvent)) == BERRY_STAGE_NO_BERRY)
        return TRUE;
    else
        return FALSE;
}

bool8 TryToWaterBerryTree(void)
{
    if (GetObjectEventScriptPointerPlayerFacing() != BerryTreeScript)
        return FALSE;
    else
        return ObjectEventInteractionWaterBerryTree();
}

void ClearBerryTrees(void)
{
    int i;

    for (i = 0; i < BERRY_TREES_COUNT; i++)
        gSaveBlock1Ptr->berryTrees[i] = gBlankBerryTree;
}

bool32 BerryTreeGrow(struct BerryTree *tree)
{
    if (tree->stopGrowth)
        return FALSE;

    switch (tree->stage)
    {
    case BERRY_STAGE_NO_BERRY:
        return FALSE;
    case BERRY_STAGE_FLOWERING:
        tree->berryYield = CalcBerryYield(tree);
    case BERRY_STAGE_PLANTED:
    case BERRY_STAGE_SPROUTED:
    //case BERRY_STAGE_TRUNK:
        tree->stage++;
        break;
    case BERRY_STAGE_TALLER:
        if (OW_BERRY_SIX_STAGES)
            tree->stage = BERRY_STAGE_TRUNK;
        else
            tree->stage++;
        break;
    /*case BERRY_STAGE_BUDDING:
        tree->berryYield = CalcBerryYield(tree);
        tree->stage = BERRY_STAGE_BERRIES;
        break; */
    case BERRY_STAGE_BERRIES:
        tree->watered1 = 0;
        tree->watered2 = 0;
        tree->watered3 = 0;
        tree->watered4 = 0;
        tree->berryYield = 0;
        tree->stage = BERRY_STAGE_SPROUTED;
        //tree->moistureLevel = 100;
        if (++tree->regrowthCount == ((tree->mulch == ITEM_TO_MULCH(ITEM_GOOEY_MULCH)) ? 15 : 10))
            *tree = gBlankBerryTree;
        break;
    }
    return TRUE;
}

/* static u16 GetMulchAffectedGrowthRate(u16 berryDuration, u8 mulch, u8 stage)
{
    if (stage == BERRY_STAGE_BERRIES)
        return berryDuration;
    if (mulch == ITEM_TO_MULCH(ITEM_GROWTH_MULCH))
        return berryDuration / 4 * 3;
    if (mulch == ITEM_TO_MULCH(ITEM_DAMP_MULCH))
        return berryDuration / 2 * 3;
    return berryDuration;
} */

void BerryTreeTimeUpdate(s32 minutes)
{
    int i;
    //u8 drainVal;
    struct BerryTree *tree;

    for (i = 0; i < BERRY_TREES_COUNT; i++)
    {
        tree = &gSaveBlock1Ptr->berryTrees[i];

        if (tree->berry && tree->stage && !tree->stopGrowth)
        {
            if (minutes >= GetStageDurationByBerryType(tree->berry) * 4260)
            {
                *tree = gBlankBerryTree;
            }
            else
            {
                s32 time = minutes;

                // Check moisture gradient, pests and weeds
                /* while (time > 0 && tree->stage != BERRY_STAGE_BERRIES)
                {
                    tree->moistureClock += 1;
                    time -= 1;
                    if (tree->moistureClock % 60 == 0)
                    {
                        if (OW_BERRY_MOISTURE)
                        {
                            drainVal = (OW_BERRY_DRAIN_RATE == GEN_4) ? GetDrainRateByBerryType(tree->berry) : (OW_BERRY_DRAIN_RATE == GEN_6_XY) ? 4 : 25;
                            if (OW_BERRY_MULCH_USAGE)
                            {
                                if (tree->mulch == ITEM_TO_MULCH(ITEM_GROWTH_MULCH))
                                    drainVal *= 2;
                                if (tree->mulch == ITEM_TO_MULCH(ITEM_DAMP_MULCH))
                                    drainVal /= 2;
                                if (tree->mulch == ITEM_TO_MULCH(ITEM_BOOST_MULCH) || tree->mulch == ITEM_TO_MULCH(ITEM_AMAZE_MULCH))
                                    drainVal = 25;
                            }
                            if (OW_BERRY_ALWAYS_WATERABLE && tree->moistureLevel == 0)
                            {
                                if (tree->berryYield > GetBerryInfo(tree->berry)->minYield + GetBerryInfo(tree->berry)->maxYield / 5)
                                    tree->berryYield -= GetBerryInfo(tree->berry)->maxYield / 5;
                                else
                                    tree->berryYield = GetBerryInfo(tree->berry)->minYield;
                            }
                            else if (tree->moistureLevel <= drainVal)
                                tree->moistureLevel = 0;
                            else
                                tree->moistureLevel -= drainVal;
                            if (OW_BERRY_DRAIN_RATE == GEN_6_XY && tree->moistureLevel <= 4) // Without variable drain rate (and without mulches), this needs to trigger after 24 hours, hence the extra check
                                tree->moistureLevel = 0;
                        }
                        if (tree->moistureClock == 120)
                        {
                            TryForWeeds(tree);
                            TryForPests(tree); 
                            tree->moistureClock = 0;
                        } 
                    }
                }
 */
                // Check Berry growth
                time = minutes;

                while (time != 0)
                {
                    if (tree->minutesUntilNextStage > time)
                    {
                        tree->minutesUntilNextStage -= time;
                        break;
                    }
                    time -= tree->minutesUntilNextStage;
                    tree->minutesUntilNextStage = GetStageDurationByBerryType(tree->berry) * 60;
                    if(tree->minutesUntilNextStage <= 0){
                        if (!BerryTreeGrow(tree))
                        break;
                    }
                    if (tree->stage == BERRY_STAGE_BERRIES)
                        tree->minutesUntilNextStage = GetStageDurationByBerryType(tree->berry) * ((tree->mulch == ITEM_TO_MULCH(ITEM_STABLE_MULCH)) ? 6 : 4);
                }
            }
        }
    }
}

void PlantBerryTree(u8 id, u8 berry, u8 stage, bool8 allowGrowth)
{
    struct BerryTree *tree = GetBerryTreeInfo(id);

    tree->berry = berry;
    tree->minutesUntilNextStage = GetStageDurationByBerryType(berry) * 60;
    tree->stage = stage;
    //tree->moistureLevel = 100;
    if (OW_BERRY_ALWAYS_WATERABLE)
        tree->berryYield = GetBerryInfo(berry)->maxYield;
    if (stage == BERRY_STAGE_BERRIES)
    {
        tree->berryYield = CalcBerryYield(tree);
        tree->minutesUntilNextStage *= ((tree->mulch == ITEM_TO_MULCH(ITEM_STABLE_MULCH)) ? 6 : 4);
    }

    // Stop growth, to keep tree at this stage until the player has seen it
    // allowGrowth is always true for berry trees the player has planted
    if (!allowGrowth)
        tree->stopGrowth = TRUE;

    //SetTreeMutations(id, berry);
}

void RemoveBerryTree(u8 id)
{
    gSaveBlock1Ptr->berryTrees[id] = gBlankBerryTree;
}

u8 GetBerryTypeByBerryTreeId(u8 id)
{
    return gSaveBlock1Ptr->berryTrees[id].berry;
}

u8 GetStageByBerryTreeId(u8 id)
{
    return gSaveBlock1Ptr->berryTrees[id].stage;
}

u8 GetMulchByBerryTreeId(u8 id)
{
    return gSaveBlock1Ptr->berryTrees[id].mulch;
}

u8 ItemIdToBerryType(u16 item)
{
    u16 berry = item - FIRST_BERRY_INDEX;

    if (berry > LAST_BERRY_INDEX - FIRST_BERRY_INDEX)
        return ITEM_TO_BERRY(FIRST_BERRY_INDEX);
    else
        return ITEM_TO_BERRY(item);
}

static u16 BerryTypeToItemId(u16 berry)
{
    u16 item = berry - 1;

    if (item > LAST_BERRY_INDEX - FIRST_BERRY_INDEX)
        return FIRST_BERRY_INDEX;
    else
        return berry + FIRST_BERRY_INDEX - 1;
}

void GetBerryNameByBerryType(u8 berry, u8 *string)
{
    memcpy(string, GetBerryInfo(berry)->name, BERRY_NAME_LENGTH);
    string[BERRY_NAME_LENGTH] = EOS;
}

void AllowBerryTreeGrowth(u8 id)
{
    GetBerryTreeInfo(id)->stopGrowth = FALSE;
}

static u8 BerryTreeGetNumStagesWatered(struct BerryTree *tree)
{
    u8 count = 0;

    if (tree->watered1 > 0)
        count++;
    if (tree->watered2 > 0)
        count++;
    if (tree->watered3 > 0)
        count++;
    if (tree->watered4 > 0)
        count++;
    return count;
}

static u8 GetNumStagesWateredByBerryTreeId(u8 id)
{
    return BerryTreeGetNumStagesWatered(GetBerryTreeInfo(id));
}

// Berries can be watered at 4 stages of growth. This function is likely meant
// to divide the berry yield range equally into quartiles. If you watered the
// tree n times, your yield is a random number in the nth quartile.
//
// However, this function actually skews towards higher berry yields, because
// it rounds `extraYield` to the nearest whole number.
//
// See resulting yields: https://gist.github.com/hondew/2a099dbe54aa91414decdbfaa524327d,
// and bug fix: https://gist.github.com/hondew/0f0164e5b9dadfd72d24f30f2c049a0b.
static u8 CalcBerryYieldInternal(u16 max, u16 min, u8 water)
{
    u32 randMin;
    u32 randMax;
    u32 rand;
    u32 extraYield;

    if (water == 0 || OW_BERRY_MOISTURE)
        return min;
    else
    {
        randMin = (max - min) * (water - 1);
        randMax = (max - min) * (water);
        rand = randMin + Random() % (randMax - randMin + 1);

        // Round upwards
        if ((rand % NUM_WATER_STAGES) >= NUM_WATER_STAGES / 2)
            extraYield = rand / NUM_WATER_STAGES + 1;
        else
            extraYield = rand / NUM_WATER_STAGES;
        return extraYield + min;
    }
}

static u8 CalcBerryYield(struct BerryTree *tree)
{
    const struct Berry *berry = GetBerryInfo(tree->berry);
    u8 min = tree->berryYield;
    u8 max = berry->maxYield;
    u8 result;
    if (OW_BERRY_MULCH_USAGE && (tree->mulch == ITEM_TO_MULCH(ITEM_RICH_MULCH) || tree->mulch == ITEM_TO_MULCH(ITEM_AMAZE_MULCH)))
        min += 2;
    if (!(OW_BERRY_MOISTURE && OW_BERRY_ALWAYS_WATERABLE))
        min += berry->minYield;
    if (min >= max)
        result = max;
    else
        result = CalcBerryYieldInternal(max, min, BerryTreeGetNumStagesWatered(tree));

    return result;
}

static u8 GetBerryCountByBerryTreeId(u8 id)
{
    return gSaveBlock1Ptr->berryTrees[id].berryYield;
}

static u16 GetStageDurationByBerryType(u8 berry)
{
    return GetBerryInfo(berry)->stageDuration;
}

void ObjectEventInteractionGetBerryTreeData(void)
{
    u8 id;
    u8 berry;
    u8 localId;
    u8 group;
    u8 num;

    id = GetObjectEventBerryTreeId(gSelectedObjectEvent);
    berry = GetBerryTypeByBerryTreeId(id);
    AllowBerryTreeGrowth(id);
    localId = gSpecialVar_LastTalked;
    num = gSaveBlock1Ptr->location.mapNum;
    group = gSaveBlock1Ptr->location.mapGroup;
    if (IsBerryTreeSparkling(localId, num, group))
        gSpecialVar_0x8004 = BERRY_STAGE_SPARKLING;
    else
        gSpecialVar_0x8004 = GetStageByBerryTreeId(id);
    gSpecialVar_0x8005 = GetNumStagesWateredByBerryTreeId(id);
    gSpecialVar_0x8006 = GetBerryCountByBerryTreeId(id);
    CopyItemNameHandlePlural(BerryTypeToItemId(berry), gStringVar1, gSpecialVar_0x8006);
}

void ObjectEventInteractionGetBerryName(void)
{
    u8 berryType = GetBerryTypeByBerryTreeId(GetObjectEventBerryTreeId(gSelectedObjectEvent));
    GetBerryNameByBerryType(berryType, gStringVar1);
}

void ObjectEventInteractionGetBerryCountString(void)
{
    u8 treeId = GetObjectEventBerryTreeId(gSelectedObjectEvent);
    u8 berry = GetBerryTypeByBerryTreeId(treeId);
    u8 count = GetBerryCountByBerryTreeId(treeId);
    CopyItemNameHandlePlural(BerryTypeToItemId(berry), gStringVar1, count);
    //berry = GetTreeMutationValue(treeId);
    if (berry > 0)
    {
        count = 1;
        CopyItemNameHandlePlural(BerryTypeToItemId(berry), gStringVar3, count);
        gSpecialVar_Result = TRUE;
    }
    else
        gSpecialVar_Result = FALSE;
}

void Bag_ChooseBerry(void)
{
    SetMainCallback2(CB2_ChooseBerry);
}

void Bag_ChooseMulch(void)
{
    SetMainCallback2(CB2_ChooseMulch);
}

void ObjectEventInteractionPlantBerryTree(void)
{
    u8 berry = ItemIdToBerryType(gSpecialVar_ItemId);

    PlantBerryTree(GetObjectEventBerryTreeId(gSelectedObjectEvent), berry, BERRY_STAGE_PLANTED, TRUE);
    ObjectEventInteractionGetBerryTreeData();
}

void ObjectEventInteractionApplyMulch(void)
{
    u8 mulch = ITEM_TO_MULCH(gSpecialVar_ItemId);

    gSaveBlock1Ptr->berryTrees[GetObjectEventBerryTreeId(gSelectedObjectEvent)].mulch = mulch;
    StringExpandPlaceholders(gStringVar1, gItemsInfo[gSpecialVar_ItemId].name);
}

void ObjectEventInteractionPickBerryTree(void)
{
    u8 id = GetObjectEventBerryTreeId(gSelectedObjectEvent);
    u8 berry = GetBerryTypeByBerryTreeId(id);
    //u8 mutation = GetTreeMutationValue(id);

     if (!OW_BERRY_MUTATIONS)
    {
        gSpecialVar_0x8004 = AddBagItem(BerryTypeToItemId(berry), GetBerryCountByBerryTreeId(id));
        return;
    } 
    //gSpecialVar_0x8004 = (CheckBagHasSpace(BerryTypeToItemId(berry), GetBerryCountByBerryTreeId(id)) && CheckBagHasSpace(BerryTypeToItemId(mutation), 1)) + 2;
/*     if (gSpecialVar_0x8004 == 3)
    {
        AddBagItem(BerryTypeToItemId(berry), GetBerryCountByBerryTreeId(id));
        AddBagItem(BerryTypeToItemId(mutation), 1);
    } */
}

void ObjectEventInteractionRemoveBerryTree(void)
{
    RemoveBerryTree(GetObjectEventBerryTreeId(gSelectedObjectEvent));
    SetBerryTreeJustPicked(gSpecialVar_LastTalked, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
}

void ObjectEventInteractionPullBerryWeed(void)
{
    struct BerryTree *tree = GetBerryTreeInfo(GetObjectEventBerryTreeId(gSelectedObjectEvent));
    tree->weeds = FALSE;
    //AddTreeBonus(tree, GetWeedingBonusByBerryType(tree->berry));
}

void ObjectEventInteractionClearBerryPests(void)
{
    struct BerryTree *tree = GetBerryTreeInfo(GetObjectEventBerryTreeId(gSelectedObjectEvent));
    tree->pests = FALSE;
    //AddTreeBonus(tree, GetPestsBonusByBerryType(tree->berry));
}

bool8 PlayerHasBerries(void)
{
    return IsBagPocketNonEmpty(POCKET_BERRIES);
}

bool8 ObjectEventInteractionBerryHasWeed(void)
{
    return gSaveBlock1Ptr->berryTrees[GetObjectEventBerryTreeId(gSelectedObjectEvent)].weeds;
}

/* bool8 ObjectEventInteractionBerryHasPests(void)
{
    u16 species;
    if (!OW_BERRY_PESTS || !gSaveBlock1Ptr->berryTrees[GetObjectEventBerryTreeId(gSelectedObjectEvent)].pests)
        return FALSE;
    species = GetBerryPestSpecies(gSaveBlock1Ptr->berryTrees[GetObjectEventBerryTreeId(gSelectedObjectEvent)].berry);
    if (species == SPECIES_NONE)
        return FALSE;
    CreateScriptedWildMon(species, 14 + Random() % 3, ITEM_NONE);
    gSaveBlock1Ptr->berryTrees[GetObjectEventBerryTreeId(gSelectedObjectEvent)].pests = FALSE;
    return TRUE;
} */

// Berry tree growth is frozen at their initial stage (usually, fully grown) until the player has seen the tree
// For all berry trees on screen, allow normal growth
void SetBerryTreesSeen(void)
{
    u16 cam_left;
    u16 cam_top;
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
    int i;

    GetCameraCoords(&cam_left, &cam_top);
    left = cam_left;
    top = cam_top + 3;
    right = cam_left + 14;
    bottom = top + 8;
    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].active && gObjectEvents[i].movementType == MOVEMENT_TYPE_BERRY_TREE_GROWTH)
        {
            s16 x = gObjectEvents[i].currentCoords.x;
            s16 y = gObjectEvents[i].currentCoords.y;
            if (left <= x && x <= right && top <= y && y <= bottom)
                AllowBerryTreeGrowth(gObjectEvents[i].trainerRange_berryTreeId);
        }
    }
}

void DecrementWaterPail(void)
{
    if(gSaveBlock1Ptr->pailWater > 0){
        gSaveBlock1Ptr->pailWater -= 1;
        gSpecialVar_Result = gSaveBlock1Ptr->pailWater;
    }
    else {
        gSpecialVar_Result = 0;
    }
    return;
}

void GetWaterInPail(void)
{
    if(gSaveBlock1Ptr->pailWater > 0){
        gSpecialVar_Result = gSaveBlock1Ptr->pailWater - 1;
    }
    else {
        gSpecialVar_Result = 0;
    }
    return;
}

void FillPail(void)
{
    gSaveBlock1Ptr->pailWater = 4;
}

bool8 TryToFillWater(void)
{
    if (IsPlayerFacingSurfableFishableWater())
        return TRUE;
    else
        return FALSE;
}
