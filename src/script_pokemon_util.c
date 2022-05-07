#include "global.h"
#include "battle.h"
#include "battle_gfx_sfx_util.h"
#include "battle_setup.h" //tx_randomizer_and_challenges
#include "berry.h"
#include "data.h"
#include "daycare.h"
#include "decompress.h"
#include "event_data.h"
#include "international_string_util.h"
#include "item.h" //tx_randomizer_and_challenges
#include "link.h"
#include "link_rfu.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"
#include "sprite.h"
#include "string_util.h"
#include "tv.h"
#include "constants/items.h"
#include "constants/battle_frontier.h"
#include "tx_randomizer_and_challenges.h"

static void CB2_ReturnFromChooseHalfParty(void);
static void CB2_ReturnFromChooseBattleFrontierParty(void);

void HealPlayerParty(void)
{
    u8 i, j;
    u8 ppBonuses;
    u8 arg[4];

    // restore HP.
    for(i = 0; i < gPlayerPartyCount; i++)
    {
        u16 maxHP = GetMonData(&gPlayerParty[i], MON_DATA_MAX_HP);
        arg[0] = maxHP;
        arg[1] = maxHP >> 8;
        SetMonData(&gPlayerParty[i], MON_DATA_HP, arg);
        ppBonuses = GetMonData(&gPlayerParty[i], MON_DATA_PP_BONUSES);

        // restore PP.
        for(j = 0; j < MAX_MON_MOVES; j++)
        {
            arg[0] = CalculatePPWithBonus(GetMonData(&gPlayerParty[i], MON_DATA_MOVE1 + j), ppBonuses, j);
            SetMonData(&gPlayerParty[i], MON_DATA_PP1 + j, arg);
        }

        // since status is u32, the four 0 assignments here are probably for safety to prevent undefined data from reaching SetMonData.
        arg[0] = 0;
        arg[1] = 0;
        arg[2] = 0;
        arg[3] = 0;
        SetMonData(&gPlayerParty[i], MON_DATA_STATUS, arg);
    }
}

u8 ScriptGiveMon(u16 species, u8 level, u16 item, u32 unused1, u32 unused2, u8 unused3)
{
    u16 nationalDexNum;
    int sentToPc;
    u8 heldItem[2];
    struct Pokemon mon;

    CreateMon(&mon, species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    heldItem[0] = item;
    heldItem[1] = item >> 8;
    SetMonData(&mon, MON_DATA_HELD_ITEM, heldItem);
    sentToPc = GiveMonToPlayer(&mon, FALSE);
    nationalDexNum = SpeciesToNationalPokedexNum(species);

    // Don't set Pokédex flag for MON_CANT_GIVE
    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
        break;
    }
    return sentToPc;
}

u8 ScriptGiveBeldum()
{
    u16 nationalDexNum;
    int sentToPc;
    struct Pokemon mon;
	u8 otGender = MALE;
	u32 otId = 61266;
	u8 otName[PLAYER_NAME_LENGTH + 1] = _("STEVEN");

	CreateMon(&mon, SPECIES_BELDUM, 5, USE_RANDOM_IVS, FALSE, 0, OT_ID_PRESET, otId);
	SetMonData(&mon, MON_DATA_OT_NAME, &otName);
	SetMonData(&mon, MON_DATA_OT_GENDER, &otGender);
    sentToPc = GiveMonToPlayer(&mon, TRUE);
    nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_BELDUM);

    // Don't set Pokédex flag for MON_CANT_GIVE
    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
        break;
    }
    return sentToPc;
}

#define gcnLCGa 0x000343FDu
#define gcnLCGc 0x00269EC3u

u8 ScriptGiveGligar(void)
{
    struct Pokemon mon;
	u32 personality, gcnRng, otId;
	u16 iv, iv1, iv2, hId, lId, tid, sid, nationalDexNum, item;
	u8 otGender, sentToPc, version, language, location;
    bool8 nationalRibbon;
    u8 otName[] = _("JAIZU");
	
    gcnRng = Random();
    iv1 = gcnRng >> 16;
    gcnRng = gcnRng * gcnLCGa + gcnLCGc;
    iv2 = gcnRng >> 16;
    gcnRng = gcnRng * gcnLCGa + gcnLCGc;
    gcnRng = gcnRng * gcnLCGa + gcnLCGc;
    hId = gcnRng >> 16;
    gcnRng = gcnRng * gcnLCGa + gcnLCGc;
    lId = gcnRng >> 16;
    gcnRng = gcnRng * gcnLCGa + gcnLCGc;
	personality = (hId << 16) | lId;
	otGender = MALE;
    tid = 00000;
    sid = 00000;
	otId = (sid << 16) | tid;
	language = LANGUAGE_ENGLISH;
	location = 133;
	item = ITEM_SALAC_BERRY;
	version = VERSION_GAMECUBE;
    nationalRibbon = TRUE;

	CreateMon(&mon, SPECIES_GLIGAR, 43, 32, TRUE, personality, OT_ID_PRESET, otId);
	SetMonData(&mon, MON_DATA_MET_GAME, &version);
	SetMonData(&mon, MON_DATA_OT_NAME, &otName);
	SetMonData(&mon, MON_DATA_OT_GENDER, &otGender);
	SetMonData(&mon, MON_DATA_LANGUAGE, &language);
	SetMonData(&mon, MON_DATA_MET_LOCATION, &location);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    iv = iv1 & MAX_IV_MASK;
    SetMonData(&mon, MON_DATA_HP_IV, &iv);
    iv = (iv1 & (MAX_IV_MASK << 5)) >> 5;
    SetMonData(&mon, MON_DATA_ATK_IV, &iv);
    iv = (iv1 & (MAX_IV_MASK << 10)) >> 10;
    SetMonData(&mon, MON_DATA_DEF_IV, &iv);
    iv = iv2 & MAX_IV_MASK;
    SetMonData(&mon, MON_DATA_SPEED_IV, &iv);
    iv = (iv2 & (MAX_IV_MASK << 5)) >> 5;
    SetMonData(&mon, MON_DATA_SPATK_IV, &iv);
    iv = (iv2 & (MAX_IV_MASK << 10)) >> 10;
    SetMonData(&mon, MON_DATA_SPDEF_IV, &iv);
    SetMonData(&mon, MON_DATA_NATIONAL_RIBBON, &nationalRibbon);
    SetMonMoveSlot(&mon, MOVE_FAINT_ATTACK, 0);
    SetMonMoveSlot(&mon, MOVE_SAND_ATTACK, 1);
    SetMonMoveSlot(&mon, MOVE_POISON_STING, 2);
    SetMonMoveSlot(&mon, MOVE_SLASH, 3);
    CalculateMonStats(&mon);
    sentToPc = GiveMonToPlayer(&mon, TRUE);
    nationalDexNum = SpeciesToNationalPokedexNum(SPECIES_GLIGAR);

    // Don't set Pokédex flag for MON_CANT_GIVE
    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
        break;
    }
    return sentToPc;
}

u8 ScriptGiveEgg(u16 species)
{
    struct Pokemon mon;
    u8 isEgg;

    CreateEgg(&mon, species, TRUE);
    isEgg = TRUE;
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);

    return GiveMonToPlayer(&mon, FALSE);
}

void HasEnoughMonsForDoubleBattle(void)
{
    switch (GetMonsStateToDoubles())
    {
    case PLAYER_HAS_TWO_USABLE_MONS:
        gSpecialVar_Result = PLAYER_HAS_TWO_USABLE_MONS;
        break;
    case PLAYER_HAS_ONE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_MON;
        break;
    case PLAYER_HAS_ONE_USABLE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_USABLE_MON;
        break;
    }
}

static bool8 CheckPartyMonHasHeldItem(u16 item)
{
    int i;

    for(i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2);
        if (species != SPECIES_NONE && species != SPECIES_EGG && GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    return FALSE;
}

bool8 DoesPartyHaveEnigmaBerry(void)
{
    bool8 hasItem = CheckPartyMonHasHeldItem(ITEM_ENIGMA_BERRY);
    if (hasItem == TRUE)
        GetBerryNameByBerryType(ItemIdToBerryType(ITEM_ENIGMA_BERRY), gStringVar1);

    return hasItem;
}

void CreateScriptedWildMon(u16 species, u8 level, u16 item)
{
    u8 heldItem[2];

    //tx_randomizer_and_challenges
    if (gSaveBlock1Ptr->tx_Random_Static)
        species = GetSpeciesRandomSeeded(species, TX_RANDOM_T_STATIC);
    if (gSaveBlock1Ptr->tx_Random_Items)
        item = RandomItemId(item);

    ZeroEnemyPartyMons();
    CreateMon(&gEnemyParty[0], species, level, USE_RANDOM_IVS, 0, 0, OT_ID_PLAYER_ID, 0);
    if (item)
    {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, heldItem);
    }

    SetNuzlockeChecks(); //tx_randomizer_and_challenges
}

void ScriptSetMonMoveSlot(u8 monIndex, u16 move, u8 slot)
{
// Allows monIndex to go out of bounds of gPlayerParty. Doesn't occur in vanilla
#ifdef BUGFIX
    if (monIndex >= PARTY_SIZE)
#else
    if (monIndex > PARTY_SIZE)
#endif
        monIndex = gPlayerPartyCount - 1;

    SetMonMoveSlot(&gPlayerParty[monIndex], move, slot);
}

// Note: When control returns to the event script, gSpecialVar_Result will be
// TRUE if the party selection was successful.
void ChooseHalfPartyForBattle(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseHalfParty;
    VarSet(VAR_FRONTIER_FACILITY, FACILITY_MULTI_OR_EREADER);
    InitChooseHalfPartyForBattle(0);
}

static void CB2_ReturnFromChooseHalfParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ChoosePartyForBattleFrontier(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseBattleFrontierParty;
    InitChooseHalfPartyForBattle(gSpecialVar_0x8004 + 1);
}

static void CB2_ReturnFromChooseBattleFrontierParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ReducePlayerPartyToSelectedMons(void)
{
    struct Pokemon party[MAX_FRONTIER_PARTY_SIZE];
    int i;

    CpuFill32(0, party, sizeof party);

    // copy the selected pokemon according to the order.
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
            party[i] = gPlayerParty[gSelectedOrderFromParty[i] - 1]; // index is 0 based, not literal

    CpuFill32(0, gPlayerParty, sizeof gPlayerParty);

    // overwrite the first 4 with the order copied to.
    for (i = 0; i < MAX_FRONTIER_PARTY_SIZE; i++)
        gPlayerParty[i] = party[i];

    CalculatePlayerPartyCount();
}
