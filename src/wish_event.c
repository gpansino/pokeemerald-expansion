#include "global.h"
#include "malloc.h"
#include "decompress.h"
#include "event_data.h"
#include "field_control_avatar.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "graphics.h"
#include "main.h"
#include "map_name_popup.h"
#include "fieldmap.h"
#include "overworld.h"
#include "palette.h"
#include "script.h"
#include "task.h"
#include "fieldmap.h"

#define TAG_MAPB0 0xABE3
#define TAG_MAPPal 0xABE7
#define TAG_MAPB1 0xABEB
#define TAG_MAPB2 0xABEF
#define TAG_MAPB3 0xABF3
#define TAG_MAPA0 0xABF7
#define TAG_MAPA1 0xABFB
#define TAG_MAPA2 0xABFF
#define TAG_MAPA3 0xAC03
#define TAG_MAPC0 0xAC07
#define TAG_MAPC1 0xAC0B
#define TAG_MAPC2 0xAC0F
#define TAG_MAPC3 0xAC13

const u32 gPic_MapA0[] = INCBIN_U32("graphics/star_cave_maps/CaveMapA-0.4bpp.lz");
const u32 gPic_MapA1[] = INCBIN_U32("graphics/star_cave_maps/CaveMapA-1.4bpp.lz");
const u32 gPic_MapA2[] = INCBIN_U32("graphics/star_cave_maps/CaveMapA-2.4bpp.lz");
const u32 gPic_MapA3[] = INCBIN_U32("graphics/star_cave_maps/CaveMapA-3.4bpp.lz");
const u32 gPic_MapB0[] = INCBIN_U32("graphics/star_cave_maps/CaveMapB-0.4bpp.lz");
const u32 gPic_MapB1[] = INCBIN_U32("graphics/star_cave_maps/CaveMapB-1.4bpp.lz");
const u32 gPic_MapB2[] = INCBIN_U32("graphics/star_cave_maps/CaveMapB-2.4bpp.lz");
const u32 gPic_MapB3[] = INCBIN_U32("graphics/star_cave_maps/CaveMapB-3.4bpp.lz");
const u32 gPic_MapC0[] = INCBIN_U32("graphics/star_cave_maps/CaveMapC-0.4bpp.lz");
const u32 gPic_MapC1[] = INCBIN_U32("graphics/star_cave_maps/CaveMapC-1.4bpp.lz");
const u32 gPic_MapC2[] = INCBIN_U32("graphics/star_cave_maps/CaveMapC-2.4bpp.lz");
const u32 gPic_MapC3[] = INCBIN_U32("graphics/star_cave_maps/CaveMapC-3.4bpp.lz");
const u16 gPal_MapPal[] = INCBIN_U16("graphics/star_cave_maps/maps.gbapal");

static const struct OamData sOam_64x64 =
{
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .priority = 2,
};

struct StarCaveMap {
    int Part1;
    int Part2;
    int Part3;
    int Part4;
};


EWRAM_DATA void * gStarCaveSubstructPtr = NULL;

static const struct SpritePalette sSpritePal_MapB=
{
    .data = gPal_MapPal, 
    .tag = TAG_MAPPal,
};

static const struct CompressedSpriteSheet sSpriteSheet_MapA0[]=
{
    {
        .data = gPic_MapA0, 
        .size = 0x1000, 
        .tag = TAG_MAPA0,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapA1[]=
{
    {
        .data = gPic_MapA1, 
        .size = 0x1000, 
        .tag = TAG_MAPA1,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapA2[]=
{
    {
        .data = gPic_MapA2, 
        .size = 0x1000, 
        .tag = TAG_MAPA2,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapA3[]=
{
    {
        .data = gPic_MapA3, 
        .size = 0x1000, 
        .tag = TAG_MAPA3,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapB0[]=
{
    {
        .data = gPic_MapB0, 
        .size = 0x1000, 
        .tag = TAG_MAPB0,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapB1[]=
{
    {
        .data = gPic_MapB1, 
        .size = 0x1000, 
        .tag = TAG_MAPB1,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapB2[]=
{
    {
        .data = gPic_MapB2, 
        .size = 0x1000, 
        .tag = TAG_MAPB2,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapB3[]=
{
    {
        .data = gPic_MapB3, 
        .size = 0x1000, 
        .tag = TAG_MAPB3,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapC0[]=
{
    {
        .data = gPic_MapC0, 
        .size = 0x1000, 
        .tag = TAG_MAPC0,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapC1[]=
{
    {
        .data = gPic_MapC1, 
        .size = 0x1000, 
        .tag = TAG_MAPC1,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapC2[]=
{
    {
        .data = gPic_MapC2, 
        .size = 0x1000, 
        .tag = TAG_MAPC2,
    }
};
static const struct CompressedSpriteSheet sSpriteSheet_MapC3[]=
{
    {
        .data = gPic_MapC3, 
        .size = 0x1000, 
        .tag = TAG_MAPC3,
    }
};

const struct SpriteFrameImage sPicTable_MapA0[] = {
    overworld_frame(gPic_MapA0, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapA1[] = {
    overworld_frame(gPic_MapA1, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapA2[] = {
    overworld_frame(gPic_MapA2, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapA3[] = {
    overworld_frame(gPic_MapA3, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapB0[] = {
    overworld_frame(gPic_MapB0, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapB1[] = {
    overworld_frame(gPic_MapB1, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapB2[] = {
    overworld_frame(gPic_MapB2, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapB3[] = {
    overworld_frame(gPic_MapB3, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapC0[] = {
    overworld_frame(gPic_MapC0, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapC1[] = {
    overworld_frame(gPic_MapC1, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapC2[] = {
    overworld_frame(gPic_MapC2, 8, 8, 0),
};
const struct SpriteFrameImage sPicTable_MapC3[] = {
    overworld_frame(gPic_MapC3, 8, 8, 0),
};

static const union AnimCmd sAnim_StayStill[] =
{
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_FRAME(0, 8),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sAnimTable_Inanimate[] = {
    sAnim_StayStill,
};

const struct SpriteTemplate SpriteTemplate_MapA0 =
{
    .tileTag = TAG_MAPA0,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapA0,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapA1 =
{
    .tileTag = TAG_MAPA1,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapA1,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapA2 =
{
    .tileTag = TAG_MAPA2,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapA2,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapA3 =
{
    .tileTag = TAG_MAPA3,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapA3,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapB0 =
{
    .tileTag = TAG_MAPB0,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapB0,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapB1 =
{
    .tileTag = TAG_MAPB1,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapB1,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapB2 =
{
    .tileTag = TAG_MAPB2,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapB2,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapB3 =
{
    .tileTag = TAG_MAPB3,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapB3,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapC0 =
{
    .tileTag = TAG_MAPC0,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapC0,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapC1 =
{
    .tileTag = TAG_MAPC1,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapC1,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapC2 =
{
    .tileTag = TAG_MAPC2,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapC2,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};
const struct SpriteTemplate SpriteTemplate_MapC3 =
{
    .tileTag = TAG_MAPC3,
    .paletteTag = TAG_MAPPal,  
    .oam = &sOam_64x64,
    .anims = sAnimTable_Inanimate,
    .images = sPicTable_MapC3,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

void FallWarpStarCave(void)
{
    switch(gSpecialVar_0x8006){
        default:
            SetWarpDestination(MAP_GROUP(STAR_CAVE2FA), MAP_NUM(STAR_CAVE2FA), WARP_ID_NONE, 16, 29);
            break;
        case 1:
            SetWarpDestination(MAP_GROUP(STAR_CAVE2FB), MAP_NUM(STAR_CAVE2FB), WARP_ID_NONE, 16, 32);
            break;
        case 2: 
            SetWarpDestination(MAP_GROUP(STAR_CAVE2FC), MAP_NUM(STAR_CAVE2FC), WARP_ID_NONE, 16, 33);
            break;
    }
    DoStarCaveHoleWarp();
    ResetInitialPlayerAvatarState();
}

void DisplayMap(void){
    u8 spriteId;
    struct StarCaveMap *map;

    LockPlayerFieldControls();
    gSpecialVar_0x8005 = TRUE;
    LoadPalette(&gPal_MapPal, OBJ_PLTT_ID(4), PLTT_SIZEOF(5));
    gStarCaveSubstructPtr = Alloc(sizeof(struct StarCaveMap));
    map = gStarCaveSubstructPtr;

    switch(gSpecialVar_0x8006){
        case 1:
            LoadCompressedSpriteSheet(&sSpriteSheet_MapB0[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapB0, 88, 50, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part1 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapB1[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapB1, 152, 50, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part2 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapB2[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapB2, 88, 114, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part3 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapB3[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapB3, 152, 114, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part4 = spriteId;
            break;
        case 2:
            LoadCompressedSpriteSheet(&sSpriteSheet_MapC0[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapC0, 88, 50, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part1 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapC1[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapC1, 152, 50, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part2 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapC2[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapC2, 88, 114, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part3 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapC3[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapC3, 152, 114, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part4 = spriteId;
            break;
        default:
            LoadCompressedSpriteSheet(&sSpriteSheet_MapA0[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapA0, 88, 50, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part1 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapA1[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapA1, 152, 50, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part2 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapA2[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapA2, 88, 114, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part3 = spriteId;

            LoadCompressedSpriteSheet(&sSpriteSheet_MapA3[0]);
            spriteId = CreateSprite(&SpriteTemplate_MapA3, 152, 114, 0);
            gSprites[spriteId].oam.paletteNum = 4;
            map->Part4 = spriteId;
    }
}

void DestroyMap(void){
    struct StarCaveMap *map;
    map = gStarCaveSubstructPtr;
    //while(map->Part1.template->tileTag == TAG_MAPA0){}

    DestroySprite(&gSprites[map->Part1]);
    DestroySprite(&gSprites[map->Part2]);
    DestroySprite(&gSprites[map->Part3]);
    DestroySprite(&gSprites[map->Part4]);

    UnlockPlayerFieldControls();
}

