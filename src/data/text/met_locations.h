#define REGION_UNKNOWN	0
#define REGION_KANTO	1
#define REGION_HOENN	2
#define REGION_ORRE		3

static const u8 sRegionName_Unknown[] = _("");
static const u8 sRegionName_Kanto[] = _(", Kanto");
static const u8 sRegionName_Hoenn[] = _("");
static const u8 sRegionName_Orre[] = _(", Orre");

const u8 *const gRegionStringPointers[] =
{
	[REGION_UNKNOWN] = sRegionName_Unknown,
	[REGION_KANTO]   = sRegionName_Kanto,
	[REGION_HOENN]   = sRegionName_Hoenn,
	[REGION_ORRE]    = sRegionName_Orre,
};

static const u8 sGameName_Unknown[] = _("");
static const u8 sGameName_Sapphire[] = _("Traded from SAPPHIRE");
static const u8 sGameName_Ruby[] = _("Traded from RUBY");
static const u8 sGameName_Emerald[] = _("");
static const u8 sGameName_FireRed[] = _("Traded from FIRERED");
static const u8 sGameName_LeafGreen[] = _("Traded from LEAFGREEN");
static const u8 sGameName_Colosseum[] = _("Traded from COLOSSEUM");
static const u8 sGameName_XD[] = _("Traded from XD: GALE OF DARKNESS");	//Probably too long

const u8 *const gGameStringPointers[] =
{
	[0] = sGameName_Unknown,
	[VERSION_SAPPHIRE]     = sGameName_Sapphire,
	[VERSION_RUBY]         = sGameName_Ruby,
	[VERSION_EMERALD]      = sGameName_Emerald,
	[VERSION_FIRE_RED]     = sGameName_FireRed,
	[VERSION_LEAF_GREEN]   = sGameName_LeafGreen,
	[6]                    = sGameName_Unknown,
	[7]                    = sGameName_Unknown,
	[8]                    = sGameName_Unknown,
	[9]                    = sGameName_Unknown,
	[10]                   = sGameName_Unknown,
	[11]                   = sGameName_Unknown,
	[12]                   = sGameName_Unknown,
	[13]                   = sGameName_Unknown,
	[14]                   = sGameName_Unknown,
	[VERSION_GAMECUBE]     = sGameName_Colosseum,
	[VERSION_GAMECUBE + 1] = sGameName_XD,
};

const u8 gText_TrainerMemo_Standard[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature.\n{DYNAMIC 8}\n{DYNAMIC 0}{DYNAMIC 4}{DYNAMIC 5}{DYNAMIC 1}\nMet at {LV_2}{DYNAMIC 3}.\n\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_Hatched[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature.\n{DYNAMIC 8}\n{DYNAMIC 0}{DYNAMIC 4}{DYNAMIC 5}{DYNAMIC 1}\nHatched at {LV_2}{DYNAMIC 3}.\n\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_Trade[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature.\n\nObtained in {DYNAMIC 0}a trade{DYNAMIC 1}.\n\n\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_Fateful[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature.\n{DYNAMIC 8}\nObtained in a\n{DYNAMIC 0}fateful encounter{DYNAMIC 1} at {LV_2}{DYNAMIC 3}.\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_Untrusted[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature.\n{DYNAMIC 8}\n{DYNAMIC 0}{DYNAMIC 4}{DYNAMIC 5}{DYNAMIC 1}\nApparently met at {LV_2}{DYNAMIC 3}.\n\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_HatchedUntrusted[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature.\n{DYNAMIC 8}\n{DYNAMIC 0}{DYNAMIC 4}{DYNAMIC 5}{DYNAMIC 1}\nApparently hatched at {LV_2}{DYNAMIC 3}.\n\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_EggFromDayCare[] = _("An odd POKéMON EGG found\nby {DYNAMIC 0}the DAY CARE couple{DYNAMIC 1}.\n\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_EggTraded[] = _("An peculiar POKéMON EGG\nobtained in a trade.\n\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_EggFateful[] = _("A peculiar POKéMON EGG\nobtained at {DYNAMIC 0}a nice place{DYNAMIC 1}.\n\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_EggFatefulTraded[] = _("A peculiar POKéMON EGG\nobtained in a trade.\n\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_EggFromHotSprings[] = _("A POKéMON EGG obtained\nat {DYNAMIC 0}the hot springs{DYNAMIC 1}.\n\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_EggFromTraveler[] = _("An odd POKéMON EGG\nobtained from {DYNAMIC 0}a traveler{DYNAMIC 1}.\n\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_EggFromKanto[] = _("An odd POKéMON EGG found\nby {DYNAMIC 0}the DAY CARE couple{DYNAMIC 1}\nin the {DYNAMIC 0}KANTO{DYNAMIC 1} region.\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_BadEgg[] = _("A very mysterious\nPOKéMON EGG.\n\n\n“The Egg Watch”\n{DYNAMIC 2}");
const u8 gText_TrainerMemo_OldFriend[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature,\n\n{DYNAMIC 0}{DYNAMIC 4}{DYNAMIC 1}'s old friend\nfrom {DYNAMIC 0}ORRE{DYNAMIC 1}.\n\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_ReceivedFrom[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature,\n\nreceived from {DYNAMIC 0}{DYNAMIC 4}{DYNAMIC 1}\nin {DYNAMIC 0}ORRE{DYNAMIC 1}.\n\n{DYNAMIC 6}\n{DYNAMIC 7}");
const u8 gText_TrainerMemo_ObtainedFromDad[] = _("{DYNAMIC 0}{DYNAMIC 2}{DYNAMIC 1} nature,\n\ngiven to {DYNAMIC 0}{DYNAMIC 4}{DYNAMIC 1} by his dad\nin {DYNAMIC 0}ORRE{DYNAMIC 1}.\n\n{DYNAMIC 6}\n{DYNAMIC 7}");

//Battle Tower from Ruby/Sapphire
const u8 gMapName_BattleTower[] = _("BATTLE TOWER");

//Orre met locations
static const u8 sMapName_DistantLand[] = _("A DISTANT LAND");
static const u8 sMapName_OutskirtStand[] = _("OUTSKIRT STAND");
static const u8 sMapName_PhenacCity[] = _("PHENAC CITY");
static const u8 sMapName_MayorsHouse[] = _("MAYOR'S HOUSE");
static const u8 sMapName_PreGym[] = _("PRE GYM");
static const u8 sMapName_PhenacStadium[] = _("PHENAC STADIUM");
static const u8 sMapName_PyriteTown[] = _("PYRITE TOWN");
static const u8 sMapName_PyriteBldg[] = _("PYRITE BLDG");
static const u8 sMapName_PyriteCave[] = _("PYRITE CAVE");
static const u8 sMapName_MirorsHideout[] = _("MIROR'S HIDEOUT");
static const u8 sMapName_PyriteColosseum[] = _("PYRITE COLOSSEUM");
static const u8 sMapName_AgateVillage[] = _("AGATE VILLAGE");
static const u8 sMapName_RelicCave[] = _("RELIC CAVE");
static const u8 sMapName_TheUnder[] = _("THE UNDER");
static const u8 sMapName_TheUnderSubway[] = _("THE UNDER SUBWAY");
static const u8 sMapName_UnderColosseum[] = _("UNDER COLOSSEUM");
static const u8 sMapName_DeepColosseum[] = _("DEEP COLOSSEUM");
static const u8 sMapName_FrontOfLab[] = _("FRONT OF LAB");
static const u8 sMapName_Laboratory[] = _("LABORATORY");
static const u8 sMapName_MtBattle[] = _("MT. BATTLE");
static const u8 sMapName_MtBtlColosseum[] = _("MT.BTL COLOSSEUM");
static const u8 sMapName_RealgamTower[] = _("REALGAM TOWER");
static const u8 sMapName_RealgamTwrDome[] = _("REALGAMTWR DOME");
static const u8 sMapName_RealgamTwrLobby[] = _("REALGAMTWR LOBBY");
static const u8 sMapName_TowerColosseum[] = _("TOWER COLOSSEUM");
static const u8 sMapName_OrreColosseum[] = _("ORRE COLOSSEUM");
static const u8 sMapName_SnagemHideout[] = _("SNAGEM HIDEOUT");
static const u8 sMapName_RealgamTower2F[] = _("REALGAM TOWER 2F");
static const u8 sMapName_CipherLab[] = _("CIPHER LAB");
static const u8 sMapName_SSLibra[] = _("S.S. LIBRA");
static const u8 sMapName_CipherKeyLair[] = _("CIPHER KEY LAIR");
static const u8 sMapName_CitadarkIsle[] = _("CITADARK ISLE");
static const u8 sMapName_Rock[] = _("ROCK");
static const u8 sMapName_Oasis[] = _("OASIS");
static const u8 sMapName_Cave[] = _("CAVE");
static const u8 sMapName_PokemonHQLab[] = _("POKéMON HQ LAB");
static const u8 sMapName_GateonPort[] = _("GATEON PORT");
static const u8 sMapName_KaminkosHouse[] = _("KAMINKO'S HOUSE");

const u8 *const gOrreMapNamePointers[] =
{
	[MAPSEC_DISTANT_LAND]               = sMapName_DistantLand,
	[MAPSEC_OUTSKIRT_STAND]             = sMapName_OutskirtStand,
	[MAPSEC_PHENAC_CITY]                = sMapName_PhenacCity,
	[MAPSEC_MAYORS_HOUSE]               = sMapName_MayorsHouse,
	[MAPSEC_PRE_GYM]                    = sMapName_PreGym,
	[MAPSEC_PHENAC_STADIUM]             = sMapName_PhenacStadium,
	[MAPSEC_PYRITE_TOWN]                = sMapName_PyriteTown,
	[MAPSEC_PYRITE_BLDG]                = sMapName_PyriteBldg,
	[MAPSEC_PYRITE_CAVE]                = sMapName_PyriteCave,
	[MAPSEC_MIRORS_HIDEOUT]             = sMapName_MirorsHideout,
	[MAPSEC_PYRITE_COLOSSEUM]           = sMapName_PyriteColosseum,
	[MAPSEC_AGATE_VILLAGE]              = sMapName_AgateVillage,
	[MAPSEC_RELIC_CAVE]                 = sMapName_RelicCave,
	[MAPSEC_THE_UNDER]                  = sMapName_TheUnder,
	[MAPSEC_THE_UNDER_SUBWAY]           = sMapName_TheUnderSubway,
	[MAPSEC_UNDER_COLOSSEUM]            = sMapName_UnderColosseum,
	[MAPSEC_DEEP_COLOSSEUM]             = sMapName_DeepColosseum,
	[MAPSEC_FRONT_OF_LAB]               = sMapName_FrontOfLab,
	[MAPSEC_LABORATORY]                 = sMapName_Laboratory,
	[MAPSEC_MT_BATTLE]                  = sMapName_MtBattle,
	[MAPSEC_MTBTL_COLOSSEUM]            = sMapName_MtBtlColosseum,
	[MAPSEC_REALGAM_TOWER]              = sMapName_RealgamTower,
	[MAPSEC_REALGAMTWR_DOME]            = sMapName_RealgamTwrDome,
	[MAPSEC_REALGAMTWR_LOBBY]           = sMapName_RealgamTwrLobby,
	[MAPSEC_TOWER_COLOSSEUM]            = sMapName_TowerColosseum,
	[MAPSEC_ORRE_COLOSSEUM]             = sMapName_OrreColosseum,
	[MAPSEC_SNAGEM_HIDEOUT]             = sMapName_SnagemHideout,
	[MAPSEC_REALGAM_TOWER_2F]           = sMapName_RealgamTower2F,
	[MAPSEC_CIPHER_LAB]                 = sMapName_CipherLab,
	[MAPSEC_S_S_LIBRA]                  = sMapName_SSLibra,
	[MAPSEC_CIPHER_KEY_LAIR]            = sMapName_CipherKeyLair,
	[MAPSEC_CITADARK_ISLE]              = sMapName_CitadarkIsle,
	[MAPSEC_ROCK]                       = sMapName_Rock,
	[MAPSEC_OASIS]                      = sMapName_Oasis,
	[MAPSEC_CAVE]                       = sMapName_Cave,
	[MAPSEC_POKEMON_HQ_LAB]             = sMapName_PokemonHQLab,
	[MAPSEC_GATEON_PORT]                = sMapName_GateonPort,
	[MAPSEC_KAMINKOS_HOUSE]             = sMapName_KaminkosHouse
};
