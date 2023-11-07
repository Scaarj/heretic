
/* sounds.c */

#include "doomdef.h"
#include "sounds.h"

/* Music info */

musicinfo_t S_music[] = {{"MUS_E1M1", 0, nullptr, 0}, /* 1-1 */
	{"MUS_E1M2", 0, nullptr, 0}, {"MUS_E1M3", 0, nullptr, 0}, {"MUS_E1M4", 0, nullptr, 0}, {"MUS_E1M5", 0, nullptr, 0},
	{"MUS_E1M6", 0, nullptr, 0}, {"MUS_E1M7", 0, nullptr, 0}, {"MUS_E1M8", 0, nullptr, 0}, {"MUS_E1M9", 0, nullptr, 0},

	{"MUS_E2M1", 0, nullptr, 0}, /* 2-1 */
	{"MUS_E2M2", 0, nullptr, 0}, {"MUS_E2M3", 0, nullptr, 0}, {"MUS_E2M4", 0, nullptr, 0}, {"MUS_E1M4", 0, nullptr, 0},
	{"MUS_E2M6", 0, nullptr, 0}, {"MUS_E2M7", 0, nullptr, 0}, {"MUS_E2M8", 0, nullptr, 0}, {"MUS_E2M9", 0, nullptr, 0},

	{"MUS_E1M1", 0, nullptr, 0}, /* 3-1 */
	{"MUS_E3M2", 0, nullptr, 0}, {"MUS_E3M3", 0, nullptr, 0}, {"MUS_E1M6", 0, nullptr, 0}, {"MUS_E1M3", 0, nullptr, 0},
	{"MUS_E1M2", 0, nullptr, 0}, {"MUS_E1M5", 0, nullptr, 0}, {"MUS_E1M9", 0, nullptr, 0}, {"MUS_E2M6", 0, nullptr, 0},

	{"MUS_E1M6", 0, nullptr, 0}, /* 4-1 */
	{"MUS_E1M2", 0, nullptr, 0}, {"MUS_E1M3", 0, nullptr, 0}, {"MUS_E1M4", 0, nullptr, 0}, {"MUS_E1M5", 0, nullptr, 0},
	{"MUS_E1M1", 0, nullptr, 0}, {"MUS_E1M7", 0, nullptr, 0}, {"MUS_E1M8", 0, nullptr, 0}, {"MUS_E1M9", 0, nullptr, 0},

	{"MUS_E2M1", 0, nullptr, 0}, /* 5-1 */
	{"MUS_E2M2", 0, nullptr, 0}, {"MUS_E2M3", 0, nullptr, 0}, {"MUS_E2M4", 0, nullptr, 0}, {"MUS_E1M4", 0, nullptr, 0},
	{"MUS_E2M6", 0, nullptr, 0}, {"MUS_E2M7", 0, nullptr, 0}, {"MUS_E2M8", 0, nullptr, 0}, {"MUS_E2M9", 0, nullptr, 0},

	{"MUS_E3M2", 0, nullptr, 0}, /* 6-1 */
	{"MUS_E3M3", 0, nullptr, 0}, /* 6-2 */
	{"MUS_E1M6", 0, nullptr, 0}, /* 6-3 */

	{"MUS_TITL", 0, nullptr, 0}, {"MUS_INTR", 0, nullptr, 0}, {"MUS_CPTD", 0, nullptr, 0}};

/* Sound info */

sfxinfo_t S_sfx[] = {{"none", NULL, 0, -1, NULL, 0, 0, 0, 0}, {"gldhit", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"gntful", NULL, 32, -1, NULL, 0, -1, 0, 0}, {"gnthit", NULL, 32, -1, NULL, 0, -1, 0, 0},
	{"gntpow", NULL, 32, -1, NULL, 0, -1, 0, 0}, {"gntact", NULL, 32, -1, NULL, 0, -1, 0, 0},
	{"gntuse", NULL, 32, -1, NULL, 0, -1, 0, 0}, {"phosht", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"phohit", NULL, 32, -1, NULL, 0, -1, 0, 0}, {"-phopow", &S_sfx[sfx_hedat1], 32, -1, NULL, 0, 1, 0, 0},
	{"lobsht", NULL, 20, -1, NULL, 0, 2, 0, 0}, {"lobhit", NULL, 20, -1, NULL, 0, 2, 0, 0},
	{"lobpow", NULL, 20, -1, NULL, 0, 2, 0, 0}, {"hrnsht", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"hrnhit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"hrnpow", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"ramphit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"ramrain", NULL, 10, -1, NULL, 0, 2, 0, 0},
	{"bowsht", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"stfhit", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"stfpow", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"stfcrk", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"impsit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"impat1", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"impat2", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"impdth", NULL, 80, -1, NULL, 0, 2, 0, 0},
	{"-impact", &S_sfx[sfx_impsit], 20, -1, NULL, 0, 2, 0, 0}, {"imppai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"mumsit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"mumat1", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"mumat2", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"mumdth", NULL, 80, -1, NULL, 0, 2, 0, 0},
	{"-mumact", &S_sfx[sfx_mumsit], 20, -1, NULL, 0, 2, 0, 0}, {"mumpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"mumhed", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"bstsit", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"bstatk", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"bstdth", NULL, 80, -1, NULL, 0, 2, 0, 0},
	{"bstact", NULL, 20, -1, NULL, 0, 2, 0, 0}, {"bstpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"clksit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"clkatk", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"clkdth", NULL, 80, -1, NULL, 0, 2, 0, 0}, {"clkact", NULL, 20, -1, NULL, 0, 2, 0, 0},
	{"clkpai", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"snksit", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"snkatk", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"snkdth", NULL, 80, -1, NULL, 0, 2, 0, 0},
	{"snkact", NULL, 20, -1, NULL, 0, 2, 0, 0}, {"snkpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"kgtsit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"kgtatk", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"kgtat2", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"kgtdth", NULL, 80, -1, NULL, 0, 2, 0, 0},
	{"-kgtact", &S_sfx[sfx_kgtsit], 20, -1, NULL, 0, 2, 0, 0}, {"kgtpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"wizsit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"wizatk", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"wizdth", NULL, 80, -1, NULL, 0, 2, 0, 0}, {"wizact", NULL, 20, -1, NULL, 0, 2, 0, 0},
	{"wizpai", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"minsit", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"minat1", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"minat2", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"minat3", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"mindth", NULL, 80, -1, NULL, 0, 2, 0, 0},
	{"minact", NULL, 20, -1, NULL, 0, 2, 0, 0}, {"minpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"hedsit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"hedat1", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"hedat2", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"hedat3", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"heddth", NULL, 80, -1, NULL, 0, 2, 0, 0}, {"hedact", NULL, 20, -1, NULL, 0, 2, 0, 0},
	{"hedpai", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"sorzap", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"sorrise", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"sorsit", NULL, 200, -1, NULL, 0, 2, 0, 0},
	{"soratk", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"soract", NULL, 200, -1, NULL, 0, 2, 0, 0},
	{"sorpai", NULL, 200, -1, NULL, 0, 2, 0, 0}, {"sordsph", NULL, 200, -1, NULL, 0, 2, 0, 0},
	{"sordexp", NULL, 200, -1, NULL, 0, 2, 0, 0}, {"sordbon", NULL, 200, -1, NULL, 0, 2, 0, 0},
	{"-sbtsit", &S_sfx[sfx_bstsit], 32, -1, NULL, 0, 2, 0, 0},
	{"-sbtatk", &S_sfx[sfx_bstatk], 32, -1, NULL, 0, 2, 0, 0}, {"sbtdth", NULL, 80, -1, NULL, 0, 2, 0, 0},
	{"sbtact", NULL, 20, -1, NULL, 0, 2, 0, 0}, {"sbtpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"plroof", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"plrpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"plrdth", NULL, 80, -1, NULL, 0, 2, 0, 0}, {"gibdth", NULL, 100, -1, NULL, 0, 2, 0, 0},
	{"plrwdth", NULL, 80, -1, NULL, 0, 2, 0, 0}, {"plrcdth", NULL, 100, -1, NULL, 0, 2, 0, 0},
	{"itemup", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"wpnup", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"telept", NULL, 50, -1, NULL, 0, 2, 0, 0}, {"doropn", NULL, 40, -1, NULL, 0, 2, 0, 0},
	{"dorcls", NULL, 40, -1, NULL, 0, 2, 0, 0}, {"dormov", NULL, 40, -1, NULL, 0, 2, 0, 0},
	{"artiup", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"switch", NULL, 40, -1, NULL, 0, 2, 0, 0},
	{"pstart", NULL, 40, -1, NULL, 0, 2, 0, 0}, {"pstop", NULL, 40, -1, NULL, 0, 2, 0, 0},
	{"stnmov", NULL, 40, -1, NULL, 0, 2, 0, 0}, {"chicpai", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"chicatk", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"chicdth", NULL, 40, -1, NULL, 0, 2, 0, 0},
	{"chicact", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"chicpk1", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"chicpk2", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"chicpk3", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"keyup", NULL, 50, -1, NULL, 0, 2, 0, 0}, {"ripslop", NULL, 16, -1, NULL, 0, 2, 0, 0},
	{"newpod", NULL, 16, -1, NULL, 0, -1, 0, 0}, {"podexp", NULL, 40, -1, NULL, 0, -1, 0, 0},
	{"bounce", NULL, 16, -1, NULL, 0, 2, 0, 0}, {"-volsht", &S_sfx[sfx_bstatk], 16, -1, NULL, 0, 2, 0, 0},
	{"-volhit", &S_sfx[sfx_lobhit], 16, -1, NULL, 0, 2, 0, 0}, {"burn", NULL, 10, -1, NULL, 0, 2, 0, 0},
	{"splash", NULL, 10, -1, NULL, 0, 1, 0, 0}, {"gloop", NULL, 10, -1, NULL, 0, 2, 0, 0},
	{"respawn", NULL, 10, -1, NULL, 0, 1, 0, 0}, {"blssht", NULL, 32, -1, NULL, 0, 2, 0, 0},
	{"blshit", NULL, 32, -1, NULL, 0, 2, 0, 0}, {"chat", NULL, 100, -1, NULL, 0, 1, 0, 0},
	{"artiuse", NULL, 32, -1, NULL, 0, 1, 0, 0}, {"gfrag", NULL, 100, -1, NULL, 0, 1, 0, 0},
	{"waterfl", NULL, 16, -1, NULL, 0, 2, 0, 0},

	/* Monophonic sounds */

	{"wind", NULL, 16, -1, NULL, 0, 1, 0, 0}, {"amb1", NULL, 1, -1, NULL, 0, 1, 0, 0},
	{"amb2", NULL, 1, -1, NULL, 0, 1, 0, 0}, {"amb3", NULL, 1, -1, NULL, 0, 1, 0, 0},
	{"amb4", NULL, 1, -1, NULL, 0, 1, 0, 0}, {"amb5", NULL, 1, -1, NULL, 0, 1, 0, 0},
	{"amb6", NULL, 1, -1, NULL, 0, 1, 0, 0}, {"amb7", NULL, 1, -1, NULL, 0, 1, 0, 0},
	{"amb8", NULL, 1, -1, NULL, 0, 1, 0, 0}, {"amb9", NULL, 1, -1, NULL, 0, 1, 0, 0},
	{"amb10", NULL, 1, -1, NULL, 0, 1, 0, 0}, {"amb11", NULL, 1, -1, NULL, 0, 0, 0, 0}};
