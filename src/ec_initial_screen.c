#include "global.h"
#include "event_data.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "scanline_effect.h"
#include "bg.h"
#include "window.h"
#include "gpu_regs.h"
#include "constants/rgb.h"
#include "international_string_util.h"
#include "tx_randomizer_and_challenges.h"

static void CB2_BuildECInitialScreen(void);
static void VBlankCB(void);
static void Task_BuildECInitialScreen(u8 taskId);
static void InitBuildInfoScreenBgAndWindows(void);

EWRAM_DATA static u8 currentpage = 0;

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    }
};

static const struct WindowTemplate sWindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 3,
        .width = 26,
        .height = 16,
        .paletteNum = 15,
        .baseBlock = 62
    },
    {
        .bg = 0,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 14,
        .baseBlock = 1
    },
    DUMMY_WIN_TEMPLATE
};

#define WIN_CONTENT 0
#define WIN_TOPBAR  1

static const u16 sOptionMenuText_Pal[] = INCBIN_U16("graphics/interface/option_menu_text_custom.gbapal");
static const u16 sTextWindowFrameThin_Pal[] = INCBIN_U16("graphics/text_window/thin.gbapal");
static const u8 sTextWindowFrameThin_Gfx[] = INCBIN_U8("graphics/text_window/thin.4bpp");
static const u16 sBuildMenuBg_Pal[] = {RGB(15, 22, 15)};

const u8 sText_TopBar_Left_1[] = _("PAGE 1/2");
const u8 sText_TopBar_Right_1[] = _("{A_BUTTON} CONTINUE");
const u8 sText_TopBar_Left_2[] = _("PAGE 2/2");
const u8 sText_TopBar_Right_2[] = _("{B_BUTTON} BACK {A_BUTTON} CONTINUE");
const u8 sText_EC_Speech[] = _("Welcome to {COLOR GREEN}Pokémon Emerald Cross{COLOR DARK_GRAY}!\n\n"
                                "This fangame was made with love by\n{COLOR RED}Jaizu{COLOR DARK_GRAY}, please enjoy playing it!\n\n"
                                "Download the latest version on the\nDiscord server:\n{COLOR BLUE}https://jaizu.moe/discord-ec");

const u8 sText_EC_Speech_2[] = _("Next you will be able to set randomizer,\n"
                                    "difficulty and challenge modes.\n\n"
                                    "You {COLOR RED}can't{COLOR DARK_GRAY} change those later!\n\n"
                                    "These settings {COLOR RED}disable{COLOR DARK_GRAY} link features:\nRandomization, nuzlocke, one types,\nstat equalizer and mirror mode.");

void CB2_InitECInitialScreen(void)
{
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);

    DmaClear16(3, PLTT, PLTT_SIZE);
    DmaFillLarge16(3, 0, (u8 *)VRAM, VRAM_SIZE, 0x1000);
    ResetOamRange(0, 128);
    LoadOam();
    ScanlineEffect_Stop();
    ScanlineEffect_Clear();
    ResetSpriteData();
    ResetTasks();
    ResetPaletteFade();
    InitBuildInfoScreenBgAndWindows();
    SetVBlankCallback(VBlankCB);
    SetMainCallback2(CB2_BuildECInitialScreen);
    CreateTask(Task_BuildECInitialScreen, 80);
}

static void InitBuildInfoScreenBgAndWindows(void)
{
    ClearScheduledBgCopiesToVram();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    ScheduleBgCopyTilemapToVram(0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    LoadBgTiles(0, sTextWindowFrameThin_Gfx, 0x120, 532);
    LoadPalette(sOptionMenuText_Pal, 14 * 0x10, sizeof(sOptionMenuText_Pal));
    LoadPalette(sBuildMenuBg_Pal, 0, sizeof(sBuildMenuBg_Pal));
    LoadPalette(sTextWindowFrameThin_Pal, 15 * 0x10, 0x20);
}

static void CB2_BuildECInitialScreen(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    ProcessSpriteCopyRequests();
    LoadOam();
    TransferPlttBuffer();
}

static const u8 colors[3] = {0, 2, 3};
static const u8 color_top[3] = { TEXT_DYNAMIC_COLOR_6, TEXT_COLOR_WHITE, 2 };

static u8 DrawFirstPage(void)
{
    u8 x = GetStringRightAlignXOffset(FONT_SMALL, sText_TopBar_Right_1, 232);

    FillWindowPixelBuffer(WIN_CONTENT, PIXEL_FILL(1));
    FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(15));

    AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 8, 1, color_top, 0, sText_TopBar_Left_1);
    AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, x, 1, color_top, 0, sText_TopBar_Right_1);
    AddTextPrinterParameterized(0, FONT_NORMAL, sText_EC_Speech, 0, 1, TEXT_SKIP_DRAW, 0);

    PutWindowTilemap(WIN_TOPBAR);
    CopyWindowToVram(WIN_TOPBAR, COPYWIN_GFX);
    PutWindowTilemap(WIN_CONTENT);
    CopyWindowToVram(WIN_CONTENT, COPYWIN_GFX);
}

static u8 DrawSecondPage(void)
{
    u8 x = GetStringRightAlignXOffset(FONT_SMALL, sText_TopBar_Right_2, 232);

    FillWindowPixelBuffer(WIN_CONTENT, PIXEL_FILL(1));
    FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(15));

    AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 8, 1, color_top, 0, sText_TopBar_Left_2);
    AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, x, 1, color_top, 0, sText_TopBar_Right_2);
    AddTextPrinterParameterized(WIN_CONTENT, FONT_NORMAL, sText_EC_Speech_2, 0, 1, TEXT_SKIP_DRAW, 0);

    PutWindowTilemap(WIN_TOPBAR);
    CopyWindowToVram(WIN_TOPBAR, COPYWIN_GFX);
    PutWindowTilemap(WIN_CONTENT);
    CopyWindowToVram(WIN_CONTENT, COPYWIN_GFX);
}

#define tState data[0]
#define tSubTaskId data[1]

static void Task_BuildECInitialScreen(u8 taskId)
{
    s16 *data = gTasks[taskId].data;
    u8 x = GetStringRightAlignXOffset(FONT_SMALL, sText_TopBar_Right_1, 232);

    switch (tState)
    {
    case 0:
        if (!gPaletteFade.active)
        {
            DrawStdFrameWithCustomTileAndPalette(0, FALSE, 532, 15);

            FillWindowPixelBuffer(WIN_TOPBAR, PIXEL_FILL(15));
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, 8, 1, color_top, 0, sText_TopBar_Left_1);
            AddTextPrinterParameterized3(WIN_TOPBAR, FONT_SMALL, x, 1, color_top, 0, sText_TopBar_Right_1);
            AddTextPrinterParameterized(WIN_CONTENT, FONT_NORMAL, sText_EC_Speech, 0, 1, TEXT_SKIP_DRAW, 0);

            PutWindowTilemap(WIN_TOPBAR);
            CopyWindowToVram(WIN_TOPBAR, COPYWIN_FULL);
            PutWindowTilemap(WIN_CONTENT);
            CopyWindowToVram(WIN_CONTENT, COPYWIN_FULL);
            ScheduleBgCopyTilemapToVram(0);
            tState = 1;
        }
        break;
    case 1:
        if (JOY_NEW(A_BUTTON))
        {
            if (currentpage == 0)
            {
                DrawSecondPage();
                currentpage++;
                tState = 1;
            }
            else if (currentpage == 1)
            {
                tState = 2;
            }
        }
        else if (JOY_NEW(B_BUTTON))
        {
            if (currentpage == 1)
            {
                DrawFirstPage();
                currentpage--;
                tState = 1;
            }
        }
        break;
    case 2:
        if (!gPaletteFade.active)
        {
            FreeAllWindowBuffers();
            SetMainCallback2(CB2_InitTxRandomizerChallengesMenu);
            DestroyTask(taskId);
        }
    }
}
