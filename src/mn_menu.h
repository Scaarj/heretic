#pragma once

#include "doomdef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ITEM_HEIGHT 20

typedef enum { ITT_EMPTY, ITT_EFUNC, ITT_LRFUNC, ITT_SETMENU, ITT_INERT } ItemType_t;

typedef enum {
	MENU_MAIN,
	MENU_EPISODE,
	MENU_SKILL,
	MENU_OPTIONS,
	MENU_OPTIONS2,
	MENU_OPTIONS3,
	MENU_FILES,
	MENU_LOAD,
	MENU_SAVE,
	MENU_NONE
} MenuType_t;

typedef struct {
	ItemType_t type;
	const char* text;
	boolean (*func)(int option);
	int option;
	MenuType_t menu;
} MenuItem_t;

typedef struct {
	int x;
	int y;
	void (*drawFunc)(void);
	int itemCount;
	MenuItem_t* items;
	int oldItPos;
	MenuType_t prevMenu;
	MenuType_t type;
} Menu_t;

extern Menu_t* CurrentMenu;
extern boolean askforquit;

extern int YesButtonX;
extern int NoButtonX;
extern int ConfirmationButtonY;
extern const char* QuitEndMsgAnswer[];

#ifdef __cplusplus
}
#endif
