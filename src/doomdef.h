
#ifndef __DOOMDEF__
#define __DOOMDEF__

#include "doomtype.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* all external data is defined here */
#include "doomdata.h"

/* all important printed strings */
#include "dstrings.h"

/* header generated by multigen utility */
#include "info.h"

#ifdef __cplusplus
extern "C" {
#endif

/* PC direct to screen pointers (should be unused!) */
extern byte *destview, *destscreen;

/*
* Global parameters/defines.
*
* Heretiv version
*/
#define VERSION 130
#define VERSION_TEXT "v1.3"

/*
* most key data are simple ascii (lowercased)
*/
#define KEY_RIGHTARROW 0xae
#define KEY_LEFTARROW 0xac
#define KEY_UPARROW 0xad
#define KEY_DOWNARROW 0xaf
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_TAB 9
#define KEY_F1 (0x80 + 0x3b)
#define KEY_F2 (0x80 + 0x3c)
#define KEY_F3 (0x80 + 0x3d)
#define KEY_F4 (0x80 + 0x3e)
#define KEY_F5 (0x80 + 0x3f)
#define KEY_F6 (0x80 + 0x40)
#define KEY_F7 (0x80 + 0x41)
#define KEY_F8 (0x80 + 0x42)
#define KEY_F9 (0x80 + 0x43)
#define KEY_F10 (0x80 + 0x44)
#define KEY_F11 (0x80 + 0x57)
#define KEY_F12 (0x80 + 0x58)

#define KEY_INSERT (0x80 + 0x59)
#define KEY_DELETE (0x80 + 0x5a)
#define KEY_HOME (0x80 + 0x5b)
#define KEY_END (0x80 + 0x5c)
#define KEY_PAGEUP (0x80 + 0x5d)
#define KEY_PAGEDOWN (0x80 + 0x5f)

#define KEY_BACKSPACE 127
#define KEY_PAUSE 0xff

#define KEY_EQUALS 0x3d
#define KEY_MINUS 0x2d

#define KEY_RSHIFT (0x80 + 0x36)
#define KEY_RCTRL (0x80 + 0x1d)
#define KEY_RALT (0x80 + 0x38)

#define KEY_LALT KEY_RALT

#define FINEANGLES 8192
#define FINEMASK (FINEANGLES - 1)
#define ANGLETOFINESHIFT 19 /* 0x100000000 to 0x2000 */

#define SAVEGAMENAME "hticsav"
#define SAVEGAMENAMECD "hticsav.cd"

/* The home-directory of the user */

void I_GetHomeDirectory(void);

/*
* Mission packs - might be useful for TC stuff?
*/
typedef enum {
	heretic, /* Heretic */
	none
} GameMission_t;

/*
* Identify language to use, software localization.
*/
typedef enum { english, french, german, unknown } Language_t;

/*
* if rangecheck is undefined, most parameter validation debugging code
* will not be compiled
*
*/
#define RANGECHECK

/* Used for centering */
#define X_DISP ((screenwidth - 320) / 2)
#define Y_DISP ((screenheight - 200) / 2)
/* Used for bottom align. */
#define Y_BOTTOM (screenheight - 200)

/* The maximum number of players, multiplayer/networking. */
#define MAXPLAYERS 4

/* State updates, number of tics / second. */
#define TICRATE 35
#define TICSPERSEC 35
#define NUMARTIFCTS 28
#define MAXPLAYERS 4

#define FRACBITS 16
#define FRACUNIT (1 << FRACBITS)
typedef int fixed_t;

#define ANGLE_1 0x01000000
#define ANGLE_45 0x20000000
#define ANGLE_90 0x40000000
#define ANGLE_180 0x80000000
#define ANGLE_MAX 0xffffffff

#define ANG45 0x20000000
#define ANG90 0x40000000
#define ANG180 0x80000000
#define ANG270 0xc0000000

typedef unsigned int angle_t;

#define BT_ATTACK 1
#define BT_USE 2
#define BT_CHANGE 4 /* if true, the next 3 bits hold weapon num */
#define BT_WEAPONMASK (8 + 16 + 32)
#define BT_WEAPONSHIFT 3

#define BT_SPECIAL 128 /* game events, not really buttons */
#define BTS_SAVEMASK (4 + 8 + 16)
#define BTS_SAVESHIFT 2
#define BT_SPECIALMASK 3
#define BTS_PAUSE 1 /* pause the game */
#define BTS_SAVEGAME 2 /* save the game at each console */
/* savegame slot numbers occupy the second byte of buttons */

typedef enum { ev_keydown, ev_keyup, ev_mouse, ev_joystick } evtype_t;

typedef struct {
	evtype_t type;
	int data1 __PACKED__; /* keys / mouse/joystick buttons */
	int data2 __PACKED__; /* mouse/joystick x move */
	int data3 __PACKED__; /* mouse/joystick y move */
} __PACKED__ event_t;

typedef struct {
	signed char forwardmove; /* *2048 for move */
	signed char sidemove __PACKED__; /* *2048 for move */
	short angleturn __PACKED__; /* <<16 for angle delta */
	short consistancy __PACKED__; /* checks for net game */
	byte chatchar __PACKED__;
	byte buttons __PACKED__;
	byte lookfly __PACKED__; /* look/fly up/down/centering */
	byte arti __PACKED__; /* artitype_t to use */
} __PACKED__ ticcmd_t;

/*
* The current state of the game: whether we are
* playing, gazing at the intermission screen,
* the game final animation, or a demo.
*/
typedef enum { GS_LEVEL, GS_INTERMISSION, GS_FINALE, GS_DEMOSCREEN } gamestate_t;

typedef enum {
	ga_nothing,
	ga_loadlevel,
	ga_newgame,
	ga_loadgame,
	ga_savegame,
	ga_playdemo,
	ga_completed,
	ga_victory,
	ga_worlddone,
	ga_screenshot
} gameaction_t;

typedef enum { wipe_0, wipe_1, wipe_2, wipe_3, wipe_4, NUMWIPES, wipe_random } wipe_t;

/*
* Difficulty/skill settings/filters.
*/

/* Skill flags. */
#define MTF_EASY 1
#define MTF_NORMAL 2
#define MTF_HARD 4

/* Deaf monsters/do not react to sound. */
#define MTF_AMBUSH 8

typedef enum : int { sk_baby, sk_easy, sk_medium, sk_hard, sk_nightmare } skill_t;

/*
* Key cards.
*/
typedef enum { key_yellow, key_green, key_blue, NUMKEYS } keytype_t;

/* The defined weapons,
*  including a marker indicating
*  user has not changed weapon.
*/
typedef enum : int {
	wp_staff,
	wp_goldwand,
	wp_crossbow,
	wp_blaster,
	wp_skullrod,
	wp_phoenixrod,
	wp_mace,
	wp_gauntlets,
	wp_beak,
	NUMWEAPONS,
	/* No pending weapon change. */
	wp_nochange
} weapontype_t;

#define AMMO_GWND_WIMPY 10
#define AMMO_GWND_HEFTY 50
#define AMMO_CBOW_WIMPY 5
#define AMMO_CBOW_HEFTY 20
#define AMMO_BLSR_WIMPY 10
#define AMMO_BLSR_HEFTY 25
#define AMMO_SKRD_WIMPY 20
#define AMMO_SKRD_HEFTY 100
#define AMMO_PHRD_WIMPY 1
#define AMMO_PHRD_HEFTY 10
#define AMMO_MACE_WIMPY 20
#define AMMO_MACE_HEFTY 100

/* Ammunition types defined. */
typedef enum {
	am_goldwand,
	am_crossbow,
	am_blaster,
	am_skullrod,
	am_phoenixrod,
	am_mace,
	NUMAMMO,
	am_noammo /* staff, gauntlets */
} ammotype_t;

typedef struct {
	ammotype_t ammo;
	int upstate __PACKED__;
	int downstate __PACKED__;
	int readystate __PACKED__;
	int atkstate __PACKED__;
	int holdatkstate __PACKED__;
	int flashstate __PACKED__;
} __PACKED__ weaponinfo_t;

extern weaponinfo_t wpnlev1info[NUMWEAPONS];
extern weaponinfo_t wpnlev2info[NUMWEAPONS];

/* Power up artifacts. */
typedef enum : int {
	pw_None,
	pw_invulnerability,
	pw_invisibility,
	pw_allmap,
	pw_infrared,
	pw_weaponlevel2,
	pw_flight,
	pw_shield,
	pw_health2,
	NUMPOWERS
} powertype_t;

typedef enum : int {
	arti_none,
	arti_invulnerability,
	arti_invisibility,
	arti_health,
	arti_superhealth,
	arti_tomeofpower,
	arti_torch,
	arti_firebomb,
	arti_egg,
	arti_fly,
	arti_teleport,
	NUMARTIFACTS
} artitype_t;

#define INVULNTICS (30 * 35)
#define INVISTICS (60 * 35)
#define INFRATICS (120 * 35)
#define IRONTICS (60 * 35)
#define WPNLEV2TICS (40 * 35)
#define FLIGHTTICS (60 * 35)

#define CHICKENTICS (40 * 35)

#define MESSAGETICS (4 * 35)
#define BLINKTHRESHOLD (4 * 32)

#define NUMINVENTORYSLOTS 14

typedef struct {
	int type;
	int count;
} __PACKED__ inventory_t;

/*
===============================================================================

MAPOBJ DATA
	
	===============================================================================
		*/

/*
* Experimental stuff.
* To compile this as "ANSI C with classes"
*  we will need to handle the various
*  action functions cleanly.
*/
typedef void (*actionf_v)(void);
typedef void (*actionf_p1)(void*);
typedef void (*actionf_p2)(void*, void*);

typedef union {
	actionf_p1 acp1;
	actionf_v acv;
	actionf_p2 acp2;

} actionf_t;

typedef struct {
	spritenum_t sprite;
	long frame __PACKED__;
	long tics __PACKED__;

	actionf_t action __PACKED__;
	statenum_t nextstate __PACKED__;
	long misc1 __PACKED__, misc2 __PACKED__;
} __PACKED__ state_t;

extern state_t states[NUMSTATES];
extern const char* sprnames[NUMSPRITES];

/* think_t is a function pointer to a routine to handle an actor. */
typedef actionf_t think_t;

typedef struct thinker_s {
	struct thinker_s *prev, *next __PACKED__;
	think_t function __PACKED__;
} __PACKED__ thinker_t;

struct player_s;

typedef struct mobj_s {
	thinker_t thinker; /* thinker links */

	/* info for drawing */
	fixed_t x __PACKED__, y __PACKED__, z __PACKED__;
	struct mobj_s *snext __PACKED__, *sprev __PACKED__; /* links in sector (if needed) */
	angle_t angle __PACKED__;
	spritenum_t sprite __PACKED__; /* used to find patch_t and flip value */
	int frame __PACKED__; /*  might be ord with FF_FULLBRIGHT */

	/* interaction info */
	struct mobj_s *bnext __PACKED__, *bprev __PACKED__; /* links in blocks (if needed) */
	struct subsector_s* subsector __PACKED__;
	fixed_t floorz __PACKED__, ceilingz __PACKED__; /* closest together of contacted secs */
	fixed_t radius __PACKED__, height __PACKED__; /* for movement checking */
	fixed_t momx __PACKED__, momy __PACKED__, momz __PACKED__; /* momentums */

	int validcount __PACKED__; /* if == validcount, already checked */

	mobjtype_t type __PACKED__;
	mobjinfo_t* info __PACKED__; /* &mobjinfo[mobj->type] */
	int tics __PACKED__; /* state tic counter */
	state_t* state __PACKED__;
	int damage __PACKED__; /* For missiles */
	int flags __PACKED__;
	int flags2 __PACKED__; /* Heretic flags */
	int special1 __PACKED__; /* Special info */
	int special2 __PACKED__; /* Special info */
	int health __PACKED__;
	int movedir __PACKED__; /* 0-7 */
	int movecount __PACKED__; /* when 0, select a new dir */
	struct mobj_s* target __PACKED__; /* thing being chased/attacked (or NULL) */
	/* also the originator for missiles */
	int reactiontime __PACKED__; /* if non 0, don't attack yet */
	/* used by player to freeze a bit after */
	/* teleporting */
	int threshold __PACKED__; /* if >0, the target will be chased */
	/* no matter what (even if shot) */
	struct player_s* player __PACKED__; /* only valid if type == MT_PLAYER */
	int lastlook __PACKED__; /* player number last looked for */

	mapthing_t spawnpoint __PACKED__; /* for nightmare respawn */
} __PACKED__ mobj_t;

/* each sector has a degenmobj_t in it's center for sound origin purposes */
typedef struct {
	thinker_t thinker; /* not used for anything */
	fixed_t x __PACKED__, y __PACKED__, z __PACKED__;
} __PACKED__ degenmobj_t;

/* Most damage defined using HITDICE */
#define HITDICE(a) ((1 + (P_Random() & 7)) * a)

/*
* frame flags
*/
#define FF_FULLBRIGHT 0x8000 /* flag in thing->frame */
#define FF_FRAMEMASK 0x7fff

/* --- mobj.flags --- */

#define MF_SPECIAL 1 /* call P_SpecialThing when touched */
#define MF_SOLID 2
#define MF_SHOOTABLE 4
#define MF_NOSECTOR 8 /* don't use the sector links */
/* (invisible but touchable) */
#define MF_NOBLOCKMAP 16 /* don't use the blocklinks */
/* (inert but displayable) */
#define MF_AMBUSH 32
#define MF_JUSTHIT 64 /* try to attack right back */
#define MF_JUSTATTACKED 128 /* take at least one step before attacking */
#define MF_SPAWNCEILING 256 /* hang from ceiling instead of floor */
#define MF_NOGRAVITY 512 /* don't apply gravity every tic */

/* movement flags */
#define MF_DROPOFF 0x400 /* allow jumps from high places */
#define MF_PICKUP 0x800 /* for players to pick up items */
#define MF_NOCLIP 0x1000 /* player cheat */
#define MF_SLIDE 0x2000 /* keep info about sliding along walls */
#define MF_FLOAT 0x4000 /* allow moves to any height, no gravity */
#define MF_TELEPORT 0x8000 /* don't cross lines or look at heights */
#define MF_MISSILE 0x10000 /* don't hit same species, explode on block */

#define MF_DROPPED 0x20000 /* dropped by a demon, not level spawned */
#define MF_SHADOW 0x40000 /* use fuzzy draw (shadow demons / invis) */
#define MF_NOBLOOD 0x80000 /* don't bleed when shot (use puff) */
#define MF_CORPSE 0x100000 /* don't stop moving halfway off a step */
#define MF_INFLOAT 0x200000 /* floating to a height for a move, don't */
/* auto float to target's height */

#define MF_COUNTKILL 0x400000 /* count towards intermission kill total */
#define MF_COUNTITEM 0x800000 /* count towards intermission item total */

#define MF_SKULLFLY 0x1000000 /* skull in flight */
#define MF_NOTDMATCH 0x2000000 /* don't spawn in death match (key cards) */

#define MF_TRANSLATION 0xc000000 /* if 0x4 0x8 or 0xc, use a translation */
#define MF_TRANSSHIFT 26 /* table for player colormaps */

/* --- mobj.flags2 --- */

#define MF2_LOGRAV 0x00000001 /* alternate gravity setting */
#define MF2_WINDTHRUST 0x00000002 /* gets pushed around by the wind */
/* specials */
#define MF2_FLOORBOUNCE 0x00000004 /* bounces off the floor */
#define MF2_THRUGHOST 0x00000008 /* missile will pass through ghosts */
#define MF2_FLY 0x00000010 /* fly mode is active */
#define MF2_FOOTCLIP 0x00000020 /* if feet are allowed to be clipped */
#define MF2_SPAWNFLOAT 0x00000040 /* spawn random float z */
#define MF2_NOTELEPORT 0x00000080 /* does not teleport */
#define MF2_RIP 0x00000100 /* missile rips through solid */
/* targets */
#define MF2_PUSHABLE 0x00000200 /* can be pushed by other moving */
/* mobjs */
#define MF2_SLIDE 0x00000400 /* slides against walls */
#define MF2_ONMOBJ 0x00000800 /* mobj is resting on top of another */
/* mobj */
#define MF2_PASSMOBJ 0x00001000 /* Enable z block checking.  If on, */
/* this flag will allow the mobj to */
/* pass over/under other mobjs. */
#define MF2_CANNOTPUSH 0x00002000 /* cannot push other pushable mobjs */
#define MF2_FEETARECLIPPED 0x00004000 /* a mobj's feet are now being cut */
#define MF2_BOSS 0x00008000 /* mobj is a major boss */
#define MF2_FIREDAMAGE 0x00010000 /* does fire damage */
#define MF2_NODMGTHRUST 0x00020000 /* does not thrust target when */
/* damaging */
#define MF2_TELESTOMP 0x00040000 /* mobj can stomp another */
#define MF2_FLOATBOB 0x00080000 /* use float bobbing z movement */
#define MF2_DONTDRAW 0X00100000 /* don't generate a vissprite */

//=============================================================================

typedef enum {
	PST_LIVE, /* playing */
	PST_DEAD, /* dead on the ground */
	PST_REBORN /* ready to restart */
} playerstate_t;

/*
* psprites are scaled shapes directly on the view screen
* coordinates are given for a 320*200 view screen
*/
typedef enum { ps_weapon, ps_flash, NUMPSPRITES } psprnum_t;

typedef struct {
	state_t* state; /* a NULL state means not active */
	int tics __PACKED__;
	fixed_t sx __PACKED__, sy __PACKED__;
} __PACKED__ pspdef_t;

/*
================
=
= player_t
=
================
*/

typedef struct player_s {
	mobj_t* mo;
	playerstate_t playerstate __PACKED__;
	ticcmd_t cmd __PACKED__;

	fixed_t viewz __PACKED__; /* focal origin above r.z */
	fixed_t viewheight __PACKED__; /* base height above floor for viewz */
	fixed_t deltaviewheight __PACKED__; /* squat speed */
	fixed_t bob __PACKED__; /* bounded/scaled total momentum */

	int flyheight __PACKED__;
	int lookdir __PACKED__;
	boolean centering __PACKED__;
	int health __PACKED__; /* only used between levels, mo->health */
	/* is used during levels */
	int armorpoints __PACKED__, armortype __PACKED__; /* armor type is 0-2 */

	inventory_t inventory[NUMINVENTORYSLOTS] __PACKED__;
	artitype_t readyArtifact __PACKED__;
	int artifactCount __PACKED__;
	int inventorySlotNum __PACKED__;
	int powers[NUMPOWERS] __PACKED__;
	boolean keys[NUMKEYS] __PACKED__;
	boolean backpack __PACKED__;
	signed int frags[MAXPLAYERS] __PACKED__; /* kills of other players */
	weapontype_t readyweapon __PACKED__;
	weapontype_t pendingweapon __PACKED__; /* wp_nochange if not changing */
	boolean weaponowned[NUMWEAPONS] __PACKED__;
	int ammo[NUMAMMO] __PACKED__;
	int maxammo[NUMAMMO] __PACKED__;
	int attackdown __PACKED__, usedown __PACKED__; /* true if button down last tic */
	int cheats __PACKED__; /* bit flags */

	int refire __PACKED__; /* refired shots are less accurate */

	int killcount __PACKED__, itemcount __PACKED__, secretcount __PACKED__; /* for intermission */
	const char* message __PACKED__; /* hint messages */
	int messageTics __PACKED__; /* counter for showing messages */
	int damagecount __PACKED__, bonuscount __PACKED__; /* for screen flashing */
	int flamecount __PACKED__; /* for flame thrower duration */
	mobj_t* attacker __PACKED__; /* who did damage (NULL for floors) */
	int extralight __PACKED__; /* so gun flashes light up areas */
	int fixedcolormap __PACKED__; /* can be set to REDCOLORMAP, etc */
	int colormap __PACKED__; /* 0-3 for which color to draw player */
	pspdef_t psprites[NUMPSPRITES] __PACKED__; /* view sprites (gun, etc) */
	boolean didsecret __PACKED__; /* true if secret level has been done */
	int chickenTics __PACKED__; /* player is a chicken if > 0 */
	int chickenPeck __PACKED__; /* chicken peck countdown */
	mobj_t* rain1 __PACKED__; /* active rain maker 1 */
	mobj_t* rain2 __PACKED__; /* active rain maker 2 */
} __PACKED__ player_t;

#define CF_NOCLIP 1
#define CF_GODMODE 2
#define CF_NOMOMENTUM 4 /* not really a cheat, just a debug aid */

#define BACKUPTICS 12 /* CHANGED FROM 12 !?!? */

typedef struct {
	unsigned checksum; /* high bit is retransmit request */
	byte retransmitfrom __PACKED__; /* only valid if NCMD_RETRANSMIT */
	byte starttic __PACKED__;
	byte player __PACKED__, numtics __PACKED__;
	ticcmd_t cmds[BACKUPTICS] __PACKED__;
} __PACKED__ doomdata_t;

typedef struct {
	long id;
	short intnum __PACKED__; /* DOOM executes an int to execute commands */

	/* communication between DOOM and the driver */
	short command __PACKED__; /* CMD_SEND or CMD_GET */
	short remotenode __PACKED__; /* dest for send, set by get (-1 = no packet) */
	short datalength __PACKED__; /* bytes in doomdata to be sent */

	/* info common to all nodes */
	short numnodes __PACKED__; /* console is allways node 0 */
	short ticdup __PACKED__; /* 1 = no duplication, 2-5 = dup for slow nets */
	short extratics __PACKED__; /* 1 = send a backup tic in every packet */
	short deathmatch __PACKED__; /* 1 = deathmatch */
	short savegame __PACKED__; /* -1 = new game, 0-5 = load savegame */
	short episode __PACKED__; /* 1-3 */
	short map __PACKED__; /* 1-9 */
	short skill __PACKED__; /* 1-5 */

	/* info specific to this node */
	short consoleplayer __PACKED__;
	short numplayers __PACKED__;
	short angleoffset __PACKED__; /* 1 = left, 0 = center, -1 = right */
	short drone __PACKED__; /* 1 = drone */

	/* packet data to be sent */
	doomdata_t data __PACKED__;
} __PACKED__ doomcom_t;

#define DOOMCOM_ID 0x12345678l

extern doomcom_t* doomcom;
extern doomdata_t* netbuffer; /* points inside doomcom */

#define MAXNETNODES 8 /* max computers in a game */

#define CMD_SEND 1
#define CMD_GET 2

#define SBARHEIGHT 42 /* status bar height at bottom of screen */

/*
===============================================================================

GLOBAL VARIABLES
	
	===============================================================================
		*/

#define TELEFOGHEIGHT (32 * FRACUNIT)

#define MAXEVENTS 64

extern event_t events[MAXEVENTS];
extern int eventhead;
extern int eventtail;

extern fixed_t finesine[5 * FINEANGLES / 4];
extern fixed_t* finecosine;

extern gameaction_t gameaction;

extern boolean paused;

extern boolean shareware; /* true if main WAD is the shareware version */
extern boolean ExtendedWAD; /* true if main WAD is the extended version */

extern boolean nomonsters; /* checkparm of -nomonsters */

extern boolean respawnparm; /* checkparm of -respawn */

extern boolean debugmode; /* checkparm of -debug */

extern boolean usergame; /* ok to save / end game */

extern boolean ravpic; /* checkparm of -ravpic */

extern boolean altpal; /* checkparm to use an alternate palette routine */

extern boolean cdrom; /* true if cd-rom mode active ("-cdrom") */

extern boolean deathmatch; /* only if started as net death */

extern boolean netgame; /* only true if >1 player */

extern boolean playeringame[MAXPLAYERS];

extern int consoleplayer; /* player taking events and displaying */

extern int displayplayer;

extern int viewangleoffset; /* ANG90 = left side, ANG270 = right */

extern player_t players[MAXPLAYERS];

extern boolean singletics; /* debug flag to cancel adaptiveness */

extern boolean DebugSound; /* debug flag for displaying sound info */

extern int maxammo[NUMAMMO];

extern boolean demoplayback;
extern boolean advancedemo;
extern int skytexture;

extern gamestate_t gamestate;
extern skill_t gameskill;
extern boolean respawnmonsters;
extern int gameepisode;
extern int gamemap;
extern int prevmap;
extern int totalkills, totalitems, totalsecret; /* for intermission */
extern int levelstarttic; /* gametic at level start */
extern int leveltime; /* tics in game play for par */

extern ticcmd_t netcmds[MAXPLAYERS][BACKUPTICS];
extern int ticdup;

#define MAXNETNODES 8
extern ticcmd_t localcmds[BACKUPTICS];
extern int rndindex;
extern int gametic, maketic;
extern int nettics[MAXNETNODES];

#define SAVEGAMESIZE 0x30000
#define SAVESTRINGSIZE 24
extern byte* savebuffer;
extern byte* save_p;

extern mapthing_t* deathmatch_p;
extern mapthing_t deathmatchstarts[10];
extern mapthing_t playerstarts[MAXPLAYERS];

extern int viewwindowx;
extern int viewwindowy;
extern int viewwidth;
extern int scaledviewwidth;
extern int viewheight;

/* rhandeev: differentiated mouse X and Y sensitivity */
extern long mouseXSensitivity;
extern long mouseYSensitivity;

/* rhandeev: added mouse invert and mouse look features */
extern boolean mouseInvert;
extern boolean mouseLook;

extern boolean precache; /* if true, load all graphics at level load */

extern byte* screen; /* off screen work buffer, from V_video.c */

extern boolean singledemo; /* quit after playing a demo from cmdline */

extern FILE* debugfile;
extern int bodyqueslot;
extern skill_t startskill;
extern int startepisode;
extern int startmap;
extern boolean autostart;
extern int demosequence;

/*
===============================================================================

GLOBAL FUNCTIONS
	
	===============================================================================
		*/

fixed_t FixedMul(fixed_t a, fixed_t b);
fixed_t FixedDiv(fixed_t a, fixed_t b);
fixed_t FixedDiv2(fixed_t a, fixed_t b);

#ifdef __BIG_ENDIAN__

	#define SHORT(x)                                                         \
		((short) ((((unsigned short) (x) & (unsigned short) 0x00ffU) << 8) | \
			(((unsigned short) (x) & (unsigned short) 0xff00U) >> 8)))

	#define LONG(x)                                                          \
		((int) ((((unsigned int) (x) & (unsigned int) 0x000000ffUL) << 24) | \
			(((unsigned int) (x) & (unsigned int) 0x0000ff00UL) << 8) |      \
			(((unsigned int) (x) & (unsigned int) 0x00ff0000UL) >> 8) |      \
			(((unsigned int) (x) & (unsigned int) 0xff000000UL) >> 24)))

#else
	#define SHORT(x) (x)
	#define LONG(x) (x)
#endif

/*
* -----------
* MEMORY ZONE
* -----------
* tags < 100 are not overwritten until freed
*/
#define PU_STATIC 1 /* static entire execution time */
#define PU_SOUND 2 /* static while playing */
#define PU_MUSIC 3 /* static while playing */
#define PU_DAVE 4 /* anything else Dave wants static */
#define PU_LEVEL 50 /* static until level exited */
#define PU_LEVSPEC 51 /* a special thinker in a level */
/* tags >= 100 are purgable whenever needed. */
#define PU_PURGELEVEL 100
#define PU_CACHE 101

void Z_Init(void);
void* Z_Malloc(size_t size, int tag, void* ptr);
void Z_Free(void* ptr);
void Z_FreeTags(int lowtag, int hightag);
void Z_DumpHeap(int lowtag, int hightag);
void Z_FileDumpHeap(FILE* f);
void Z_CheckHeap(void);
void Z_ChangeTag2(void* ptr, int tag);
int Z_FreeMemory(void);

extern boolean MallocFailureOk;

typedef struct memblock_s {
	size_t size; /* including the header and possibly tiny fragments */
	void** user __PACKED__; /* NULL if a free block */
	int tag __PACKED__; /* purgelevel */
	int id __PACKED__; /* should be ZONEID */
	struct memblock_s *next __PACKED__, *prev __PACKED__;
} __PACKED__ memblock_t;

void Z_ChangeTag(byte* p, unsigned char t);

/*
#define Z_ChangeTag(p, t)                                                       \
	{                                                                           \
		if (((memblock_t*) ((byte*) (p) - sizeof(memblock_t)))->id != 0x1d4a11) \
			I_Error(                                                            \
				"Z_CT at "__FILE__                                              \
				":%i",                                                          \
				__LINE__);                                                      \
		Z_ChangeTag2(p, t);                                                     \
	};
*/

//-------
//WADFILE
//-------
typedef struct {
	char name[8];
	int handle __PACKED__, position __PACKED__, size __PACKED__;
} __PACKED__ lumpinfo_t;

extern lumpinfo_t* lumpinfo;
extern int numlumps;

void W_InitMultipleFiles(const char** filenames);

int W_CheckNumForName(const char* name);
int W_GetNumForName(const char* name);

int W_LumpLength(int lump);
void W_ReadLump(int lump, void* dest);

void* W_CacheLumpNum(int lump, int tag);
void* W_CacheLumpName(const char* name, int tag);

int wadopen(const char* fileName);

/*
* ----------
* BASE LEVEL
* ----------
*/
void D_DoomMain(void);

/*
void IncThermo(void);
void InitThermo(int max);
void tprintf(char *string, int initflag);
*/

/*
* not a globally visible function, just included for source reference
* calls all startup code
* parses command line options
* if not overrided, calls N_AdvanceDemo
*/

void D_PrepareDoomLoop(void);

void D_DoomLoop(void);
/*
* not a globally visible function, just included for source reference
* called by D_DoomMain, never exits
* manages timing and IO
* calls all ?_Responder, ?_Ticker, and ?_Drawer functions
* calls I_GetTime, I_StartFrame, and I_StartTic
*/

void D_PostEvent(event_t ev);
/* called by IO functions when input is detected */

void NetUpdate(void);
/* create any new ticcmds and broadcast to other players */

void D_QuitNetGame(void);
/* broadcasts special packets to other players to notify of game exit */

void TryRunTics(void);

/*
* ---------
* SYSTEM IO
* ---------
*/

/*
* Do or do not use external soundserver.
* The sndserver binary to be run separately
*  has been introduced by Dave Taylor.
* The integrated sound support is experimental,
*  and unfinished. Default is synchronous.
* Experimental asynchronous timer based is
*  handled by SNDINTR.
*#define SNDSERV  1
*#define SNDINTR  1
*/

/*
* This one switches between MIT SHM (no proper mouse)
* and XFree86 DGA (mickey sampling). The original
* linuxdoom used SHM, which is default.
*#define X11_DGA		1
*/

/*
* For resize of screen, at start of game.
* It will not work dynamically, see visplanes.
*/
#define BASE_WIDTH 320

/*
* It is educational but futile to change this
*  scaling e.g. to 2. Drawing of status bar,
*  menues etc. is tied to the scale implied
*  by the graphics.
*/
#define SCREEN_MUL 1
#define INV_ASPECT_RATIO 0.625 /* 0.75, ideally */

/*
* So there.
*/
#define SCREENWIDTH 320
/* SCREEN_MUL*BASE_WIDTH */
#define SCREENHEIGHT 200
/* (int)(SCREEN_MUL*BASE_WIDTH*INV_ASPECT_RATIO) */

extern int screenwidth;
extern int screenheight;
#define MAXSCREENWIDTH 1024
#define MAXSCREENHEIGHT 768

/*
* Added for use with SVGALIB(inits some things); dummy for X11 and GGI Targets */
void InitGraphLib(void);

/* Added for a clean exit... */
void I_ShutdownGraphics(void);

/* Checks the resolution via the modules rend_svga, rend_x11 or rend_ggi */
void I_CheckRes(void);

byte* I_ZoneBase(size_t* size);
/*
* called by startup code to get the ammount of memory to malloc
* for the zone management
*/

int I_GetTime(void);
/*
* called by D_DoomLoop
* returns current time in tics
*/

void I_StartFrame(void);
/*
* called by D_DoomLoop
* called before processing any tics in a frame (just after displaying a frame)
* time consuming syncronous operations are performed here (joystick reading)
* can call D_PostEvent
*/

void I_StartTic(void);
/*
* called by D_DoomLoop
* called before processing each tic in a frame
* quick syncronous operations are performed here
* can call D_PostEvent
*
* asyncronous interrupt functions should maintain private ques that are
* read by the syncronous functions to be converted into events
*/

void I_Init(void);
/*
* called by D_DoomMain
* determines the hardware configuration and sets up the video mode
*/

void I_InitGraphics(void);

void I_InitNetwork(void);
void I_NetCmd(void);

void I_Error(const char* error, ...);
/*
* called by anything that can generate a terminal error
* bad exit with diagnostic message
*/

void I_Quit(void);
/*
* called by M_Responder when quit is selected
* clean exit, displays sell blurb
*/

void I_SetPalette(byte* palette);
/* takes full 8 bit values */

void I_FinishUpdate(void);
/* Copy buffer to video */

void I_WipeUpdate(wipe_t wipe);
/* Copy buffer to video with wipe effect */

void I_WaitVBL(int count);
/* wait for vertical retrace or pause a bit */

void I_BeginRead(void);
void I_EndRead(void);

byte* I_AllocLow(int length);
/* allocates from low memory under dos, just mallocs under unix */

void I_Tactile(int on, int off, int total);

/*
* ----
* GAME
* ----
*/

void G_DeathMatchSpawnPlayer(int playernum);

void G_InitNew(skill_t skill, int episode, int map);

void G_DeferedInitNew(skill_t skill, int episode, int map);
/*
* can be called by the startup code or M_Responder
* a normal game starts at map 1, but a warp test can start elsewhere
*/

void G_DeferedPlayDemo(const char* demo);

void G_LoadGame(char* name);
/*
* can be called by the startup code or M_Responder
* calls P_SetupLevel or W_EnterWorld
*/
void G_DoLoadGame(void);

void G_SaveGame(int slot, char* description);
/*
* called by M_Responder
*
* Support routines for saving games
*/
void SV_Open(char* fileName);
void SV_Close(char* fileName);
void SV_Write(void* buffer, size_t size);
void SV_WriteByte(byte val);
void SV_WriteWord(unsigned short val);
void SV_WriteLong(unsigned int val);

void G_RecordDemo(skill_t skill, int numplayers, int episode, int map, char* name);
/* only called by startup code */

void G_PlayDemo(char* name);
void G_TimeDemo(char* name);

boolean G_CheckDemoStatus(void);

void G_ExitLevel(void);
void G_SecretExitLevel(void);

void G_WorldDone(void);

void G_Ticker(void);
boolean G_Responder(event_t* ev);

void G_ScreenShot(void);

/*
* -----
* PLAY
* -----
*/

void P_Ticker(void);
/*
* called by C_Ticker
* can call G_PlayerExited
* carries out all thinking of monsters and players
*/

void P_SetupLevel(int episode, int map, int playermask, skill_t skill);
/* called by W_Ticker */

void P_Init(void);
/* called by startup code */

void P_ArchivePlayers(void);
void P_UnArchivePlayers(void);
void P_ArchiveWorld(void);
void P_UnArchiveWorld(void);
void P_ArchiveThinkers(void);
void P_UnArchiveThinkers(void);
void P_ArchiveSpecials(void);
void P_UnArchiveSpecials(void);
/* load / save game routines */

/*
* -------
* REFRESH
* -------
*/

extern boolean setsizeneeded;

extern boolean BorderNeedRefresh;
extern boolean BorderTopRefresh;

extern int UpdateState;
/* define the different areas for the dirty map */
#define I_NOUPDATE 0
#define I_FULLVIEW 1
#define I_STATBAR 2
#define I_MESSAGES 4
#define I_FULLSCRN 8

void R_RenderPlayerView(player_t* player);
/* called by G_Drawer */

void R_Init(void);
/* called by startup code */

void R_DrawViewBorder(void);
void R_DrawTopBorder(void);
/* if the view size is not full screen, draws a border around it */

void R_SetViewSize(int blocks, int detail);
/* called by M_Responder */

int R_FlatNumForName(const char* name);

int R_TextureNumForName(const char* name);
int R_CheckTextureNumForName(const char* name);
/*
* called by P_Ticker for switches and animations
* returns the texture number for the texture name
*/

/*
* ----
* MISC
* ----
*/

extern int myargc;
extern char** myargv;

int M_CheckParm(const char* check);
/* returns the position of the given parameter in the arg list (0 if not found) */

boolean M_ValidEpisodeMap(int episode, int map);
/*
* returns true if the episode/map combo is valid for the current
* game configuration
*/

void M_ForceUppercase(char* text);
/* Changes a string to uppercase */

int M_Random(void);
/* returns a number from 0 to 255 */

int P_Random(void);
/* as M_Random, but used only by the play simulation */

void M_ClearRandom(void);
/* fix randoms for demos */

void M_FindResponseFile(void);

void M_ClearBox(fixed_t* box);
void M_AddToBox(fixed_t* box, fixed_t x, fixed_t y);
/* bounding box functions */

boolean M_WriteFile(char const* name, void* source, int length);
int M_ReadFile(char const* name, byte** buffer);

void M_ScreenShot(void);

void M_LoadDefaults(void);

void M_SaveDefaults(void);

int M_DrawText(int x, int y, boolean direct, char* string);

/*
* ----------------------
*  Interlude (IN_lude.c)
* ----------------------
*/

extern boolean intermission;

void IN_Start(void);
void IN_Ticker(void);
void IN_Drawer(void);

/*
* ----------------------
*  Chat mode (CT_chat.c)
* ----------------------
*/

void CT_Init(void);
void CT_Drawer(void);
boolean CT_Responder(event_t* ev);
void CT_Ticker(void);
char CT_dequeueChatChar(void);

extern boolean chatmodeon;
extern boolean ultimatemsg;

/*
* --------------------
*  Finale (F_finale.c)
* --------------------
*/

void F_Drawer(void);
void F_Ticker(void);
void F_StartFinale(void);

/*
* ----------------------
*  STATUS BAR (SB_bar.c)
* ----------------------
*/

extern int SB_state;
void SB_Init(void);
boolean SB_Responder(event_t* event);
void SB_Ticker(void);
void SB_Drawer(void);

/*
* -----------------
*  MENU (MN_menu.c)
* -----------------
*/

void MN_Init(void);
void MN_ActivateMenu(void);
void MN_DeactivateMenu(void);
boolean MN_Responder(event_t* event);
void MN_Ticker(void);
void MN_Drawer(void);
void MN_DrTextA(const char* text, int x, int y);
int MN_TextAWidth(const char* text);
void MN_DrTextB(const char* text, int x, int y);
int MN_TextBWidth(const char* text);

/*
* ------
*  VIDEO
* ------
*/
extern byte* screens[5];
extern int dirtybox[4];
extern byte gammatable[5][256];
extern long usegamma;
extern int bilifilter;
extern int lifilter;

/*
* ------
*  GAME EVENT
* ------
*/
extern boolean sendpause; /* send a pause event next tic */

void V_Init(void); /* Allocates buffer screens, call before R_Init */
void V_DrawPatch(int x, int y, patch_t* patch);
void V_DrawFuzzPatch(int x, int y, patch_t* patch);
void V_DrawShadowedPatch(int x, int y, patch_t* patch);
void V_DrawRawScreen(byte* raw);
void V_Filter_Screen_linear(byte* screenp);
void V_Filter_Screen_bilinear(byte* screenp);

#include "sounds.h"

#ifdef __cplusplus
}
#endif

#endif /* __DOOMDEF__ */
