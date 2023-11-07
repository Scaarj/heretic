
/* MN_menu.c */

#include "mn_menu.h"
#include "doomdef.h"
#include "p_local.h"
#include "r_local.h"
#include "soundst.h"
#include <ctype.h>

#include <QDateTime>

/* Macros */
#ifdef __cplusplus
extern "C" {
#endif

#define LEFT_DIR 0
#define RIGHT_DIR 1
#define ITEM_HEIGHT 20
#define SELECTOR_XOFFSET (-28)
#define SELECTOR_YOFFSET (-1)
#define SLOTTEXTLEN 20
#define ASCII_CURSOR '['

/* Types */

/* Private Functions */

static void InitFonts(void);
static void SetMenu(MenuType_t menu);
static boolean SCNetCheck(int option);
static boolean SCQuitGame(int option);
static boolean SCEpisode(int option);
static boolean SCSkill(int option);
static boolean SCMouseXSensi(int option);
static boolean SCMouseYSensi(int option);
static boolean SCMouseLook(int option);
static boolean SCMouseInvert(int option);
static boolean SCSfxVolume(int option);
static boolean SCMusicVolume(int option);
static boolean SCScreenSize(int option);
static boolean SCLoadGame(int option);
static boolean SCSaveGame(int option);
static boolean SCMessages(int option);
static boolean SCEndGame(int option);
static boolean SCInfo(int option);
static void DrawMainMenu(void);
static void DrawEpisodeMenu(void);
static void DrawSkillMenu(void);
static void DrawOptionsMenu(void);
static void DrawOptions2Menu(void);
static void DrawOptions3Menu(void);
static void DrawFileSlots(Menu_t* menu);
static void DrawFilesMenu(void);
static void MN_DrawInfo(void);
static void DrawLoadMenu(void);
static void DrawSaveMenu(void);
static void DrawSlider(Menu_t* menu, int item, int width, int slot);
void MN_LoadSlotText(void);

/* External Data */

extern int detailLevel;
extern long screenblocks;
extern int maxblocks;
extern int minblocks;

extern char* homedir;

/* Public Data */

boolean MenuActive;
int InfoType;
boolean messageson;
int FontBBaseLump;
int CurrentItPos;
Menu_t* CurrentMenu;
boolean askforquit;

int YesButtonX;
int NoButtonX;
int ConfirmationButtonY;

/* Private Data */

static int FontABaseLump;
static int SkullBaseLump;
static int MenuEpisode;
static int MenuTime;
static boolean soundchanged;

int typeofask;
boolean FileMenuKeySteal;
static boolean slottextloaded;
static char SlotText[6][SLOTTEXTLEN + 2];
static char oldSlotText[SLOTTEXTLEN + 2];
static int SlotStatus[6];
static int slotptr;
static int currentSlot;
static int quicksave;
static int quickload;

static MenuItem_t MainItems[] = {{ITT_EFUNC, "NEW GAME", SCNetCheck, 1, MENU_EPISODE},
	{ITT_SETMENU, "OPTIONS", NULL, 0, MENU_OPTIONS}, {ITT_SETMENU, "GAME FILES", NULL, 0, MENU_FILES},
	{ITT_EFUNC, "INFO", SCInfo, 0, MENU_NONE}, {ITT_EFUNC, "QUIT GAME", SCQuitGame, 0, MENU_NONE}};

static Menu_t MainMenu = {110, 56, DrawMainMenu, 5, MainItems, 0, MENU_NONE, MENU_MAIN};

static MenuItem_t EpisodeItems[] = {{ITT_EFUNC, "CITY OF THE DAMNED", SCEpisode, 1, MENU_NONE},
	{ITT_EFUNC, "HELL'S MAW", SCEpisode, 2, MENU_NONE}, {ITT_EFUNC, "THE DOME OF D'SPARIL", SCEpisode, 3, MENU_NONE},
	{ITT_EFUNC, "THE OSSUARY", SCEpisode, 4, MENU_NONE}, {ITT_EFUNC, "THE STAGNANT DEMESNE", SCEpisode, 5, MENU_NONE}};

static Menu_t EpisodeMenu = {80, 50, DrawEpisodeMenu, 3, EpisodeItems, 0, MENU_MAIN, MENU_EPISODE};

static MenuItem_t FilesItems[] = {
	{ITT_EFUNC, "LOAD GAME", SCNetCheck, 2, MENU_LOAD}, {ITT_SETMENU, "SAVE GAME", NULL, 0, MENU_SAVE}};

static Menu_t FilesMenu = {110, 60, DrawFilesMenu, 2, FilesItems, 0, MENU_MAIN, MENU_FILES};

static MenuItem_t LoadItems[] = {{ITT_EFUNC, NULL, SCLoadGame, 0, MENU_NONE},
	{ITT_EFUNC, NULL, SCLoadGame, 1, MENU_NONE}, {ITT_EFUNC, NULL, SCLoadGame, 2, MENU_NONE},
	{ITT_EFUNC, NULL, SCLoadGame, 3, MENU_NONE}, {ITT_EFUNC, NULL, SCLoadGame, 4, MENU_NONE},
	{ITT_EFUNC, NULL, SCLoadGame, 5, MENU_NONE}};

static Menu_t LoadMenu = {70, 30, DrawLoadMenu, 6, LoadItems, 0, MENU_FILES, MENU_SAVE};

static MenuItem_t SaveItems[] = {{ITT_EFUNC, NULL, SCSaveGame, 0, MENU_NONE},
	{ITT_EFUNC, NULL, SCSaveGame, 1, MENU_NONE}, {ITT_EFUNC, NULL, SCSaveGame, 2, MENU_NONE},
	{ITT_EFUNC, NULL, SCSaveGame, 3, MENU_NONE}, {ITT_EFUNC, NULL, SCSaveGame, 4, MENU_NONE},
	{ITT_EFUNC, NULL, SCSaveGame, 5, MENU_NONE}};

static Menu_t SaveMenu = {70, 30, DrawSaveMenu, 6, SaveItems, 0, MENU_FILES, MENU_SAVE};

static MenuItem_t SkillItems[] = {{ITT_EFUNC, "THOU NEEDETH A WET-NURSE", SCSkill, sk_baby, MENU_NONE},
	{ITT_EFUNC, "YELLOWBELLIES-R-US", SCSkill, sk_easy, MENU_NONE},
	{ITT_EFUNC, "BRINGEST THEM ONETH", SCSkill, sk_medium, MENU_NONE},
	{ITT_EFUNC, "THOU ART A SMITE-MEISTER", SCSkill, sk_hard, MENU_NONE},
	{ITT_EFUNC, "BLACK PLAGUE POSSESSES THEE", SCSkill, sk_nightmare, MENU_NONE}};

static Menu_t SkillMenu = {38, 30, DrawSkillMenu, 5, SkillItems, 2, MENU_EPISODE, MENU_SKILL};

static MenuItem_t OptionsItems[] = {{ITT_EFUNC, "END GAME", SCEndGame, 0, MENU_NONE},
	{ITT_EFUNC, "MESSAGES : ", SCMessages, 0, MENU_NONE}, {ITT_SETMENU, "EFFECTS...", NULL, 0, MENU_OPTIONS2},
	{ITT_SETMENU, "CONTROLS...", NULL, 0, MENU_OPTIONS3}};

static Menu_t OptionsMenu = {88, 30, DrawOptionsMenu, 4, OptionsItems, 0, MENU_MAIN, MENU_OPTIONS};

static MenuItem_t Options2Items[] = {{ITT_LRFUNC, "SCREEN SIZE", SCScreenSize, 0, MENU_NONE},
	{ITT_EMPTY, NULL, NULL, 0, MENU_NONE}, {ITT_LRFUNC, "SFX VOLUME", SCSfxVolume, 0, MENU_NONE},
	{ITT_EMPTY, NULL, NULL, 0, MENU_NONE}, {ITT_LRFUNC, "MUSIC VOLUME", SCMusicVolume, 0, MENU_NONE},
	{ITT_EMPTY, NULL, NULL, 0, MENU_NONE}};

static Menu_t Options2Menu = {90, 20, DrawOptions2Menu, 6, Options2Items, 0, MENU_OPTIONS, MENU_OPTIONS2};

static MenuItem_t Options3Items[] = {
	{ITT_EFUNC, "MOUSE LOOK : ", SCMouseLook, 0, MENU_NONE},
	{ITT_EFUNC, "MOUSE INVERT Y : ", SCMouseInvert, 0, MENU_NONE},
	{ITT_LRFUNC, "MOUSE X-SENSITIVITY", SCMouseXSensi, 0, MENU_NONE},
	{ITT_EMPTY, NULL, NULL, 0, MENU_NONE},
	{ITT_LRFUNC, "MOUSE Y-SENSITIVITY", SCMouseYSensi, 0, MENU_NONE},
	{ITT_EMPTY, NULL, NULL, 0, MENU_NONE},
};

static Menu_t Options3Menu = {88, 30, DrawOptions3Menu, 6, Options3Items, 0, MENU_OPTIONS, MENU_OPTIONS3};

static Menu_t* Menus[] = {
	&MainMenu, &EpisodeMenu, &SkillMenu, &OptionsMenu, &Options2Menu, &Options3Menu, &FilesMenu, &LoadMenu, &SaveMenu};

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_Init
  //
  //---------------------------------------------------------------------------
*/
void MN_Init(void) {
	InitFonts();
	MenuActive = false;
	messageson = true;
	mouseLook = true;
	mouseInvert = true;
	SkullBaseLump = W_GetNumForName("M_SKL00");
	if (ExtendedWAD) { /* Add episodes 4 and 5 to the menu */
		EpisodeMenu.itemCount = 5;
		EpisodeMenu.y -= ITEM_HEIGHT;
	}
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC InitFonts
  //
  //---------------------------------------------------------------------------
*/
static void InitFonts(void) {
	FontABaseLump = W_GetNumForName("FONTA_S") + 1;
	FontBBaseLump = W_GetNumForName("FONTB_S") + 1;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_DrTextA
  //
  // Draw text using font A.
  //
  //---------------------------------------------------------------------------
*/
void MN_DrTextA(const char* text, int x, int y) {
	char c;
	patch_t* p;

	while ((c = *text++) != 0) {
		if (c < 33) {
			x += 5;
		} else {
			p = static_cast<patch_t*>(W_CacheLumpNum(FontABaseLump + c - 33, PU_CACHE));
			V_DrawPatch(x, y, p);
			x += SHORT(p->width) - 1;
		}
	}
}

/*
  //---------------------------------------------------------------------------
  //
  // FUNC MN_TextAWidth
  //
  // Returns the pixel width of a string using font A.
  //
  //---------------------------------------------------------------------------
*/
int MN_TextAWidth(const char* text) {
	char c;
	int width;
	patch_t* p;

	width = 0;
	while ((c = *text++) != 0) {
		if (c < 33) {
			width += 5;
		} else {
			p = static_cast<patch_t*>(W_CacheLumpNum(FontABaseLump + c - 33, PU_CACHE));
			width += SHORT(p->width) - 1;
		}
	}
	return (width);
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_DrTextB
  //
  // Draw text using font B.
  //
  //---------------------------------------------------------------------------
*/
void MN_DrTextB(const char* text, int x, int y) {
	char c;
	patch_t* p;

	while ((c = *text++) != 0) {
		if (c < 33) {
			x += 8;
		} else {
			p = static_cast<patch_t*>(W_CacheLumpNum(FontBBaseLump + c - 33, PU_CACHE));
			V_DrawPatch(x, y, p);
			x += SHORT(p->width) - 1;
		}
	}
}

/*
  //---------------------------------------------------------------------------
  //
  // FUNC MN_TextBWidth
  //
  // Returns the pixel width of a string using font B.
  //
  //---------------------------------------------------------------------------
*/
int MN_TextBWidth(const char* text) {
	char c;
	int width;
	patch_t* p;

	width = 0;
	while ((c = *text++) != 0) {
		if (c < 33) {
			width += 5;
		} else {
			p = static_cast<patch_t*>(W_CacheLumpNum(FontBBaseLump + c - 33, PU_CACHE));
			width += SHORT(p->width) - 1;
		}
	}
	return (width);
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_Ticker
  //
  //---------------------------------------------------------------------------
*/
void MN_Ticker(void) {
	if (MenuActive == false) {
		return;
	}
	MenuTime++;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_Drawer
  //
  //---------------------------------------------------------------------------
*/
const char* QuitEndMsg[] = {"ARE YOU SURE YOU WANT TO QUIT?", "ARE YOU SURE YOU WANT TO END THE GAME?",
	"DO YOU WANT TO QUICKSAVE THE GAME NAMED", "DO YOU WANT TO QUICKLOAD THE GAME NAMED"};
const char* QuitEndMsgAnswer[] = {"YES", "NO"};

void MN_Drawer(void) {
	int i;
	int x;
	int y;
	MenuItem_t* item;
	char* selName;

	if (MenuActive == false) {
		if (askforquit) {
			MN_DrTextA(QuitEndMsg[typeofask - 1], 160 - MN_TextAWidth(QuitEndMsg[typeofask - 1]) / 2, Y_DISP + 80);
			if (typeofask == 3) {
				MN_DrTextA(SlotText[quicksave - 1], 160 - MN_TextAWidth(SlotText[quicksave - 1]) / 2, Y_DISP + 90);
				MN_DrTextA("?", 160 + MN_TextAWidth(SlotText[quicksave - 1]) / 2, Y_DISP + 90);
			}
			if (typeofask == 4) {
				MN_DrTextA(SlotText[quickload - 1], 160 - MN_TextAWidth(SlotText[quickload - 1]) / 2, Y_DISP + 90);
				MN_DrTextA("?", 160 + MN_TextAWidth(SlotText[quickload - 1]) / 2, Y_DISP + 90);
			}
			MN_DrTextB(QuitEndMsgAnswer[0], YesButtonX, ConfirmationButtonY);
			MN_DrTextB(QuitEndMsgAnswer[1], NoButtonX, ConfirmationButtonY);
			/* UpdateState |= I_FULLSCRN; */
		}
		return;
	} else {
		/* UpdateState |= I_FULLSCRN; */
		if (InfoType) {
			MN_DrawInfo();
			return;
		}
		if (screenblocks < maxblocks - 1) {
			BorderNeedRefresh = true;
		}

		if (CurrentMenu->drawFunc != NULL) {
			CurrentMenu->drawFunc();
		}
		x = CurrentMenu->x;
		y = CurrentMenu->y;
		item = CurrentMenu->items;
		for (i = 0; i < CurrentMenu->itemCount; i++) {
			if (item->type != ITT_EMPTY && item->text) {
				MN_DrTextB(item->text, x, Y_DISP + y);
			}
			y += ITEM_HEIGHT;
			item++;
		}
		y = CurrentMenu->y + (CurrentItPos * ITEM_HEIGHT) + SELECTOR_YOFFSET;
		selName = MenuTime & 16 ? const_cast<char*>("M_SLCTR1") : const_cast<char*>("M_SLCTR2");

		V_DrawPatch(x + SELECTOR_XOFFSET, Y_DISP + y, static_cast<patch_t*>(W_CacheLumpName(selName, PU_CACHE)));
	}
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawMainMenu
  //
  //---------------------------------------------------------------------------
*/
static void DrawMainMenu(void) {
	int frame;

	frame = (MenuTime / 3) % 18;
	V_DrawPatch(88, Y_DISP + 0, static_cast<patch_t*>(W_CacheLumpName("M_HTIC", PU_CACHE)));
	V_DrawPatch(40, Y_DISP + 10, static_cast<patch_t*>(W_CacheLumpNum(SkullBaseLump + (17 - frame), PU_CACHE)));
	V_DrawPatch(232, Y_DISP + 10, static_cast<patch_t*>(W_CacheLumpNum(SkullBaseLump + frame, PU_CACHE)));
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawEpisodeMenu
  //
  //---------------------------------------------------------------------------
*/
static void DrawEpisodeMenu(void) {
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawSkillMenu
  //
  //---------------------------------------------------------------------------
*/
static void DrawSkillMenu(void) {
}

//---------------------------------------------------------------------------
//
// PROC DrawFilesMenu
//
//---------------------------------------------------------------------------

static void DrawFilesMenu(void) {
	/* clear out the quicksave/quickload stuff */
	quicksave = 0;
	quickload = 0;
	players[consoleplayer].message = NULL;
	players[consoleplayer].messageTics = 1;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawLoadMenu
  //
  //---------------------------------------------------------------------------
*/
static void DrawLoadMenu(void) {
	MN_DrTextB("LOAD GAME", 160 - MN_TextBWidth("LOAD GAME") / 2, Y_DISP + 10);
	if (!slottextloaded) {
		MN_LoadSlotText();
	}
	DrawFileSlots(&LoadMenu);
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawSaveMenu
  //
  //---------------------------------------------------------------------------
*/
static void DrawSaveMenu(void) {
	MN_DrTextB("SAVE GAME", 160 - MN_TextBWidth("SAVE GAME") / 2, Y_DISP + 10);
	if (!slottextloaded) {
		MN_LoadSlotText();
	}
	DrawFileSlots(&SaveMenu);
}

/*
  //===========================================================================
  //
  // MN_LoadSlotText
  //
  //              Loads in the text message for each slot
  //===========================================================================
*/
void MN_LoadSlotText(void) {
	FILE* fp;
	[[maybe_unused]] int count;
	int i;
	char name[256];

	for (i = 0; i < 6; i++) {
		if (cdrom) {
			sprintf(name, SAVEGAMENAMECD "%d.hsg", i);
		} else {
			sprintf(name, "%s" SAVEGAMENAME "%d.hsg", homedir, i);
		}
		fp = fopen(name, "rb+");
		if (!fp) {
			SlotText[i][0] = 0; /* empty the string */
			SlotStatus[i] = 0;
			continue;
		}
		count = fread(&SlotText[i], SLOTTEXTLEN, 1, fp);
		fclose(fp);
		SlotStatus[i] = 1;
	}
	slottextloaded = true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawFileSlots
  //
  //---------------------------------------------------------------------------
*/
static void DrawFileSlots(Menu_t* menu) {
	int i;
	int x;
	int y;

	x = menu->x;
	y = menu->y;
	for (i = 0; i < 6; i++) {
		V_DrawPatch(x, Y_DISP + y, static_cast<patch_t*>(W_CacheLumpName("M_FSLOT", PU_CACHE)));
		if (SlotStatus[i]) {
			MN_DrTextA(SlotText[i], x + 5, Y_DISP + y + 5);
		}
		y += ITEM_HEIGHT;
	}
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawOptionsMenu
  //
  //---------------------------------------------------------------------------
*/
static void DrawOptionsMenu(void) {
	if (messageson) {
		MN_DrTextB("ON", 196, Y_DISP + 50);
	} else {
		MN_DrTextB("OFF", 196, Y_DISP + 50);
	}
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawOptions2Menu
  //
  //---------------------------------------------------------------------------
*/
static void DrawOptions2Menu(void) {
	int diff = minblocks - 1;
	DrawSlider(&Options2Menu, 1, maxblocks - (diff), screenblocks - (diff + 1));
	DrawSlider(&Options2Menu, 3, 16, snd_SfxVolume);
	DrawSlider(&Options2Menu, 5, 16, snd_MusicVolume);
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawOptions3Menu
  //
  //---------------------------------------------------------------------------
*/
static void DrawOptions3Menu(void) {
	if (mouseLook) {
		MN_DrTextB("ON", 216, Y_DISP + 30);
	} else {
		MN_DrTextB("OFF", 216, Y_DISP + 30);
	}
	if (mouseInvert) {
		MN_DrTextB("ON", 240, Y_DISP + 50);
	} else {
		MN_DrTextB("OFF", 240, Y_DISP + 50);
	}
	DrawSlider(&OptionsMenu, 3, 10, mouseXSensitivity);
	DrawSlider(&OptionsMenu, 5, 10, mouseYSensitivity);
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCNetCheck
  //
  //---------------------------------------------------------------------------
*/
static boolean SCNetCheck(int option) {
	if (!netgame) { /* okay to go into the menu */
		return true;
	}
	switch (option) {
		case 1: P_SetMessage(&players[consoleplayer], "YOU CAN'T START A NEW GAME IN NETPLAY!", true); break;
		case 2: P_SetMessage(&players[consoleplayer], "YOU CAN'T LOAD A GAME IN NETPLAY!", true); break;
		default: break;
	}
	MenuActive = false;
	return false;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCQuitGame
  //
  //---------------------------------------------------------------------------
*/
static boolean SCQuitGame([[maybe_unused]] int option) {
	MenuActive = false;
	askforquit = true;
	typeofask = 1; /* quit game */
	if (!netgame && !demoplayback) {
		paused = true;
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCEndGame
  //
  //---------------------------------------------------------------------------
*/
static boolean SCEndGame([[maybe_unused]] int option) {
	if (demoplayback || netgame) {
		return false;
	}
	MenuActive = false;
	askforquit = true;
	typeofask = 2; /* endgame */
	if (!netgame && !demoplayback) {
		paused = true;
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCMessages
  //
  //---------------------------------------------------------------------------
*/
static boolean SCMessages([[maybe_unused]] int option) {
	messageson ^= 1;
	if (messageson) {
		P_SetMessage(&players[consoleplayer], "MESSAGES ON", true);
	} else {
		P_SetMessage(&players[consoleplayer], "MESSAGES OFF", true);
	}
	S_StartSound(NULL, sfx_chat);
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCMessages
  //
  //---------------------------------------------------------------------------
*/
static boolean SCMouseLook([[maybe_unused]] int option) {
	mouseLook ^= 1;
	if (mouseLook) {
		P_SetMessage(&players[consoleplayer], "MOUSELOOK ON", true);
	} else {
		P_SetMessage(&players[consoleplayer], "MOUSELOOK OFF", true);
	}
	S_StartSound(NULL, sfx_chat);
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCMessages
  //
  //---------------------------------------------------------------------------
*/
static boolean SCMouseInvert([[maybe_unused]] int option) {
	mouseInvert ^= 1;
	if (mouseInvert) {
		P_SetMessage(&players[consoleplayer], "MOUSEINVERT ON", true);
	} else {
		P_SetMessage(&players[consoleplayer], "MOUSEINVERT OFF", true);
	}
	S_StartSound(NULL, sfx_chat);
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCLoadGame
  //
  //---------------------------------------------------------------------------
*/
static boolean SCLoadGame(int option) {
	char name[256];

	if (!SlotStatus[option]) { /* slot's empty...don't try and load */
		return false;
	}
	if (cdrom) {
		sprintf(name, SAVEGAMENAMECD "%d.hsg", option);
	} else {
		sprintf(name, "%s" SAVEGAMENAME "%d.hsg", homedir, option);
	}
	G_LoadGame(name);
	MN_DeactivateMenu();
	BorderNeedRefresh = true;
	if (quickload == -1) {
		quickload = option + 1;
		players[consoleplayer].message = NULL;
		players[consoleplayer].messageTics = 1;
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCSaveGame
  //
  //---------------------------------------------------------------------------
*/
static boolean SCSaveGame(int option) {
	char* ptr;

	if (!FileMenuKeySteal) {
		FileMenuKeySteal = true;
		memset(SlotText[option], 0, sizeof(SlotText[option]) / sizeof(char));
		auto datetime = QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss");
		strncpy(SlotText[option], datetime.toStdString().c_str(), datetime.size());

		ptr = SlotText[option];
		while (*ptr) {
			ptr++;
		}
		*ptr = '[';
		*(ptr + 1) = 0;
		SlotStatus[option]++;
		currentSlot = option;
		slotptr = ptr - SlotText[option];
		return false;
	} else {
		G_SaveGame(option, SlotText[option]);
		FileMenuKeySteal = false;
		MN_DeactivateMenu();
	}
	BorderNeedRefresh = true;
	if (quicksave == -1) {
		quicksave = option + 1;
		players[consoleplayer].message = NULL;
		players[consoleplayer].messageTics = 1;
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCEpisode
  //
  //---------------------------------------------------------------------------
*/
static boolean SCEpisode(int option) {
	if (shareware && (option > 1)) {
		P_SetMessage(&players[consoleplayer], "ONLY AVAILABLE IN THE REGISTERED VERSION", true);
	} else {
		MenuEpisode = option;
		SetMenu(MENU_SKILL);
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCSkill
  //
  //---------------------------------------------------------------------------
*/
static boolean SCSkill(int option) {
	G_DeferedInitNew(static_cast<skill_t>(option), MenuEpisode, 1);
	MN_DeactivateMenu();
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCMouseXSensi
  //
  //---------------------------------------------------------------------------
*/
static boolean SCMouseXSensi(int option) {
	if (option == RIGHT_DIR) {
		if (mouseXSensitivity < 9) {
			mouseXSensitivity++;
		}
	} else if (mouseXSensitivity) {
		mouseXSensitivity--;
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCMouseYSensi
  //
  //---------------------------------------------------------------------------
*/
static boolean SCMouseYSensi(int option) {
	if (option == RIGHT_DIR) {
		if (mouseYSensitivity < 9) {
			mouseYSensitivity++;
		}
	} else if (mouseYSensitivity) {
		mouseYSensitivity--;
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCSfxVolume
  //
  //---------------------------------------------------------------------------
*/
static boolean SCSfxVolume(int option) {
	if (option == RIGHT_DIR) {
		if (snd_SfxVolume < 15) {
			snd_SfxVolume++;
		}
	} else if (snd_SfxVolume) {
		snd_SfxVolume--;
	}
	S_SetSfxVolume(snd_SfxVolume); /* don't recalc the sound curve, yet */
	/* soundchanged = true; */ /* we'll set it when we leave the menu */
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCMusicVolume
  //
  //---------------------------------------------------------------------------
*/
static boolean SCMusicVolume(int option) {
	if (option == RIGHT_DIR) {
		if (snd_MusicVolume < 15) {
			snd_MusicVolume++;
		}
	} else if (snd_MusicVolume) {
		snd_MusicVolume--;
	}
	S_SetMusicVolume(snd_MusicVolume);
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCScreenSize
  //
  //---------------------------------------------------------------------------
*/
static boolean SCScreenSize(int option) {
	if (option == RIGHT_DIR) {
		if (screenblocks < maxblocks) {
			screenblocks++;
		}
	} else if (screenblocks > minblocks) {
		screenblocks--;
	}
	R_SetViewSize(screenblocks, detailLevel);
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SCInfo
  //
  //---------------------------------------------------------------------------
*/
static boolean SCInfo([[maybe_unused]] int option) {
	InfoType = 1;
	S_StartSound(NULL, sfx_dorcls);
	if (!netgame && !demoplayback) {
		paused = true;
	}
	return true;
}

/*
  //---------------------------------------------------------------------------
  //
  // FUNC MN_Responder
  //
  //---------------------------------------------------------------------------
*/
boolean MN_Responder(event_t* event) {
	int key;
	int i;
	MenuItem_t* item;
	extern boolean automapactive;
	static boolean shiftdown;
	extern void D_StartTitle(void);
	extern boolean G_CheckDemoStatus(void);
	char* textBuffer;

	if (event->data1 == KEY_RSHIFT) {
		shiftdown = (event->type == ev_keydown);
	}
	if (event->type != ev_keydown) {
		return (false);
	}
	key = event->data1;
	if (InfoType) {
		if (shareware) {
			InfoType = (InfoType + 1) % 5;
		} else {
			InfoType = (InfoType + 1) % 4;
		}
		if (key == KEY_ESCAPE) {
			InfoType = 0;
		}
		if (!InfoType) {
			paused = false;
			MN_DeactivateMenu();
			SB_state = -1; /* refresh the statbar */
			BorderNeedRefresh = true;
		}
		S_StartSound(NULL, sfx_dorcls);
		return (true); /* make the info screen eat the keypress */
	}

	if (ravpic && key == KEY_F1) {
		G_ScreenShot();
		return (true);
	}

	if (askforquit) {
		switch (key) {
			case 'y':
				if (askforquit) {
					switch (typeofask) {
						case 1:
							G_CheckDemoStatus();
							I_Quit();
							break;
						case 2:
							players[consoleplayer].messageTics = 0;
							/* set the msg to be cleared */
							players[consoleplayer].message = NULL;
							typeofask = 0;
							askforquit = false;
							paused = false;
							I_SetPalette(static_cast<byte*>(W_CacheLumpName("PLAYPAL", PU_CACHE)));
							D_StartTitle(); /* go to intro/demo mode. */
							break;
						case 3:
							P_SetMessage(&players[consoleplayer], "QUICKSAVING....", false);
							FileMenuKeySteal = true;
							SCSaveGame(quicksave - 1);
							askforquit = false;
							typeofask = 0;
							BorderNeedRefresh = true;
							return true;
						case 4:
							P_SetMessage(&players[consoleplayer], "QUICKLOADING....", false);
							SCLoadGame(quickload - 1);
							askforquit = false;
							typeofask = 0;
							BorderNeedRefresh = true;
							return true;
						default: return true; /* eat the 'y' keypress */
					}
				}
				return false;
			case 'n':
			case KEY_ESCAPE:
				if (askforquit) {
					players[consoleplayer].messageTics = 1; /* set the msg to be cleared */
					askforquit = false;
					typeofask = 0;
					paused = false;
					/* UpdateState |= I_FULLSCRN; */
					BorderNeedRefresh = true;
					return true;
				}
				return false;
		}
		return false; /* don't let the keys filter thru */
	}
	if (MenuActive == false && !chatmodeon) {
		switch (key) {
			case KEY_MINUS:
				if (automapactive) { /* Don't screen size in automap */
					return (false);
				}
				SCScreenSize(LEFT_DIR);
				S_StartSound(NULL, sfx_keyup);
				BorderNeedRefresh = true;
				/* UpdateState |= I_FULLSCRN; */
				return (true);
			case KEY_EQUALS:
				if (automapactive) { /* Don't screen size in automap */
					return (false);
				}
				SCScreenSize(RIGHT_DIR);
				S_StartSound(NULL, sfx_keyup);
				BorderNeedRefresh = true;
				/* UpdateState |= I_FULLSCRN; */
				return (true);
#ifndef __NeXT__
			case KEY_F1: /* help screen */
				SCInfo(0); /* start up info screens */
				MenuActive = true;
				return (true);
			case KEY_F2: /* save game */
				if (gamestate == GS_LEVEL && !demoplayback) {
					MenuActive = true;
					FileMenuKeySteal = false;
					MenuTime = 0;
					CurrentMenu = &SaveMenu;
					CurrentItPos = CurrentMenu->oldItPos;
					if (!netgame && !demoplayback) {
						paused = true;
					}
					S_StartSound(NULL, sfx_dorcls);
					slottextloaded = false; /* reload the slot text, when needed */
				}
				return true;
			case KEY_F3: /* load game */
				if (SCNetCheck(2)) {
					MenuActive = true;
					FileMenuKeySteal = false;
					MenuTime = 0;
					CurrentMenu = &LoadMenu;
					CurrentItPos = CurrentMenu->oldItPos;
					if (!netgame && !demoplayback) {
						paused = true;
					}
					S_StartSound(NULL, sfx_dorcls);
					slottextloaded = false; /* reload the slot text, when needed */
				}
				return true;
			case KEY_F4: /* volume */
				MenuActive = true;
				FileMenuKeySteal = false;
				MenuTime = 0;
				CurrentMenu = &Options2Menu;
				CurrentItPos = CurrentMenu->oldItPos;
				if (!netgame && !demoplayback) {
					paused = true;
				}
				S_StartSound(NULL, sfx_dorcls);
				slottextloaded = false; /* reload the slot text, when needed */
				return true;
			case KEY_F5: /* F5 isn't used in Heretic. (detail level) */ return true;
			case KEY_F6: /* quicksave */
				if (gamestate == GS_LEVEL && !demoplayback) {
					if (!quicksave || quicksave == -1) {
						MenuActive = true;
						FileMenuKeySteal = false;
						MenuTime = 0;
						CurrentMenu = &SaveMenu;
						CurrentItPos = CurrentMenu->oldItPos;
						if (!netgame && !demoplayback) {
							paused = true;
						}
						S_StartSound(NULL, sfx_dorcls);
						slottextloaded = false; /* reload the slot text, when needed */
						quicksave = -1;
						P_SetMessage(&players[consoleplayer], "CHOOSE A QUICKSAVE SLOT", true);
					} else {
						askforquit = true;
						typeofask = 3;
						if (!netgame && !demoplayback) {
							paused = true;
						}
						S_StartSound(NULL, sfx_chat);
					}
				}
				return true;
			case KEY_F7: /* endgame */
				if (gamestate == GS_LEVEL && !demoplayback) {
					S_StartSound(NULL, sfx_chat);
					SCEndGame(0);
				}
				return true;
			case KEY_F8: /* toggle messages */ SCMessages(0); return true;
			case KEY_F9: /* quickload */
				if (!quickload || quickload == -1) {
					MenuActive = true;
					FileMenuKeySteal = false;
					MenuTime = 0;
					CurrentMenu = &LoadMenu;
					CurrentItPos = CurrentMenu->oldItPos;
					if (!netgame && !demoplayback) {
						paused = true;
					}
					S_StartSound(NULL, sfx_dorcls);
					slottextloaded = false; /* reload the slot text, when needed */
					quickload = -1;
					P_SetMessage(&players[consoleplayer], "CHOOSE A QUICKLOAD SLOT", true);
				} else {
					askforquit = true;
					if (!netgame && !demoplayback) {
						paused = true;
					}
					typeofask = 4;
					S_StartSound(NULL, sfx_chat);
				}
				return true;
			case KEY_F10: /* quit */
				if (gamestate == GS_LEVEL) {
					SCQuitGame(0);
					S_StartSound(NULL, sfx_chat);
				}
				return true;
			case KEY_F11: /* F11 - gamma mode correction */
				usegamma++;
				if (usegamma > 4) {
					usegamma = 0;
				}
				I_SetPalette((byte*) W_CacheLumpName("PLAYPAL", PU_CACHE));
				return true;
#endif
		}
	}

	if (MenuActive == false) {
		if (key == KEY_ESCAPE) {
			MN_ActivateMenu();
			return (true);
		}
		return (false);
	}
	if (!FileMenuKeySteal) {
		item = &CurrentMenu->items[CurrentItPos];
		switch (key) {
			case KEY_DOWNARROW:
				do {
					if (CurrentItPos + 1 > CurrentMenu->itemCount - 1) {
						CurrentItPos = 0;
					} else {
						CurrentItPos++;
					}
				} while (CurrentMenu->items[CurrentItPos].type == ITT_EMPTY);
				S_StartSound(NULL, sfx_switch);
				return (true);
				break;
			case KEY_UPARROW:
				do {
					if (CurrentItPos == 0) {
						CurrentItPos = CurrentMenu->itemCount - 1;
					} else {
						CurrentItPos--;
					}
				} while (CurrentMenu->items[CurrentItPos].type == ITT_EMPTY);
				S_StartSound(NULL, sfx_switch);
				return (true);
				break;
			case KEY_LEFTARROW:
				if (item->type == ITT_LRFUNC && item->func != NULL) {
					item->func(LEFT_DIR);
					S_StartSound(NULL, sfx_keyup);
				}
				return (true);
				break;
			case KEY_RIGHTARROW:
				if (item->type == ITT_LRFUNC && item->func != NULL) {
					item->func(RIGHT_DIR);
					S_StartSound(NULL, sfx_keyup);
				}
				return (true);
				break;
			case KEY_ENTER:
				if (item->type == ITT_SETMENU) {
					SetMenu(item->menu);
				} else if (item->func != NULL) {
					CurrentMenu->oldItPos = CurrentItPos;
					if (item->type == ITT_LRFUNC) {
						item->func(RIGHT_DIR);
					} else if (item->type == ITT_EFUNC) {
						if (item->func(item->option)) {
							if (item->menu != MENU_NONE) {
								SetMenu(item->menu);
							}
						}
					}
				}
				S_StartSound(NULL, sfx_dorcls);
				return (true);
				break;
			case KEY_ESCAPE: MN_DeactivateMenu(); return (true);
			case KEY_BACKSPACE:
				S_StartSound(NULL, sfx_switch);
				if (CurrentMenu->prevMenu == MENU_NONE) {
					MN_DeactivateMenu();
				} else {
					SetMenu(CurrentMenu->prevMenu);
				}
				return (true);
			default:
				for (i = 0; i < CurrentMenu->itemCount; i++) {
					if (CurrentMenu->items[i].text) {
						if (toupper(key) == toupper(CurrentMenu->items[i].text[0])) {
							CurrentItPos = i;
							return (true);
						}
					}
				}
				break;
		}
		return (false);
	} else { /* Editing file names */
		textBuffer = &SlotText[currentSlot][slotptr];
		if (key == KEY_BACKSPACE) {
			if (slotptr) {
				*textBuffer-- = 0;
				*textBuffer = ASCII_CURSOR;
				slotptr--;
			}
			return (true);
		}
		if (key == KEY_ESCAPE) {
			memset(SlotText[currentSlot], 0, SLOTTEXTLEN + 2);
			strncpy(SlotText[currentSlot], oldSlotText, sizeof(SlotText[currentSlot]) / sizeof(char));
			SlotStatus[currentSlot]--;
			MN_DeactivateMenu();
			return (true);
		}
		if (key == KEY_ENTER) {
			SlotText[currentSlot][slotptr] = 0; /* clear the cursor */
			item = &CurrentMenu->items[CurrentItPos];
			CurrentMenu->oldItPos = CurrentItPos;
			if (item->type == ITT_EFUNC) {
				item->func(item->option);
				if (item->menu != MENU_NONE) {
					SetMenu(item->menu);
				}
			}
			return (true);
		}
		if (slotptr < SLOTTEXTLEN && key != KEY_BACKSPACE) {
			if ((key >= 'a' && key <= 'z')) {
				*textBuffer++ = key - 32;
				*textBuffer = ASCII_CURSOR;
				slotptr++;
				return (true);
			}
			if (((key >= '0' && key <= '9') || key == ' ' || key == ',' || key == '.' || key == '-') && !shiftdown) {
				*textBuffer++ = key;
				*textBuffer = ASCII_CURSOR;
				slotptr++;
				return (true);
			}
			if (shiftdown && key == '1') {
				*textBuffer++ = '!';
				*textBuffer = ASCII_CURSOR;
				slotptr++;
				return (true);
			}
		}
		return (true);
	}
	return (false);
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_ActivateMenu
  //
  //---------------------------------------------------------------------------
*/
void MN_ActivateMenu(void) {
	if (MenuActive) {
		return;
	}
	if (paused) {
		S_ResumeSound();
	}
	MenuActive = true;
	FileMenuKeySteal = false;
	MenuTime = 0;
	CurrentMenu = &MainMenu;
	CurrentItPos = CurrentMenu->oldItPos;
	if (!netgame && !demoplayback) {
		paused = true;
	}
	S_StartSound(NULL, sfx_dorcls);
	slottextloaded = false; /* reload the slot text, when needed */
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_DeactivateMenu
  //
  //---------------------------------------------------------------------------
*/
void MN_DeactivateMenu(void) {
	if (CurrentMenu)
		CurrentMenu->oldItPos = CurrentItPos;
	MenuActive = false;
	if (!netgame) {
		paused = false;
	}
	S_StartSound(NULL, sfx_dorcls);
	if (soundchanged) {
		/* S_SetSfxVolume(true); */ /* recalc the sound curve */
		/* S_SetSfxVolume(snd_SfxVolume); */
#ifdef USE_GSI
		soundchanged = false;
#endif
	}
	players[consoleplayer].message = NULL;
	players[consoleplayer].messageTics = 1;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC MN_DrawInfo
  //
  //---------------------------------------------------------------------------
*/
void MN_DrawInfo(void) {
	I_SetPalette(static_cast<byte*>(W_CacheLumpName("PLAYPAL", PU_CACHE)));

	V_DrawRawScreen((byte*) W_CacheLumpNum(W_GetNumForName("TITLE") + InfoType, PU_CACHE));
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC SetMenu
  //
  //---------------------------------------------------------------------------
*/
static void SetMenu(MenuType_t menu) {
	CurrentMenu->oldItPos = CurrentItPos;
	CurrentMenu->type = menu;
	CurrentMenu = Menus[menu];
	CurrentItPos = CurrentMenu->oldItPos;
}

/*
  //---------------------------------------------------------------------------
  //
  // PROC DrawSlider
  //
  //---------------------------------------------------------------------------
*/
static void DrawSlider(Menu_t* menu, int item, int width, int slot) {
	int x;
	int y;
	int x2;
	int count;

	x = menu->x + 24;
	y = menu->y + 2 + (item * ITEM_HEIGHT) + Y_DISP;
	V_DrawPatch(x - 32, y, static_cast<patch_t*>(W_CacheLumpName("M_SLDLT", PU_CACHE)));
	for (x2 = x, count = width; count--; x2 += 8) {
		V_DrawPatch(x2, y,
			static_cast<patch_t*>(
				W_CacheLumpName(count & 1 ? const_cast<char*>("M_SLDMD1") : const_cast<char*>("M_SLDMD2"), PU_CACHE)));
	}
	V_DrawPatch(x2, y, static_cast<patch_t*>(W_CacheLumpName("M_SLDRT", PU_CACHE)));
	V_DrawPatch(x + 4 + slot * 8, y + 7, static_cast<patch_t*>(W_CacheLumpName("M_SLDKB", PU_CACHE)));
}

#ifdef __cplusplus
}
#endif
