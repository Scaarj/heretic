#ifndef __AMMAP_H__
#define __AMMAP_H__

#include "doomdef.h"

#include "r_local.h"

#ifdef __cplusplus
extern "C" {
#endif

/* For use if I do walls with outsides/insides */
#define REDS (256 - 5 * 16)
#define REDRANGE 16
#define BLUES (256 - 4 * 16 + 8)
#define BLUERANGE 8
#define GREENS (7 * 16)
#define GREENRANGE 16
#define GRAYS (6 * 16)
#define GRAYSRANGE 16
#define BROWNS (4 * 16)
#define BROWNRANGE 16
#define YELLOWS (256 - 32 + 7)
#define YELLOWRANGE 1
#define BLACK 0
#define WHITE (256 - 47)
#define PARCH 13 * 8 - 1
#define BLOODRED 150
#define BLUEKEY 197
#define YELLOWKEY 144
#define GREENKEY 220

/* Automap colors */
#define BACKGROUND PARCH
#define YOURCOLORS WHITE
#define YOURRANGE 0
#define WALLCOLORS REDS
#define WALLRANGE REDRANGE
#define TSWALLCOLORS GRAYS
#define TSWALLRANGE GRAYSRANGE
#define FDWALLCOLORS BROWNS
#define FDWALLRANGE BROWNRANGE
#define CDWALLCOLORS YELLOWS
#define CDWALLRANGE YELLOWRANGE
#define THINGCOLORS GREENS
#define THINGRANGE GREENRANGE
#define SECRETWALLCOLORS WALLCOLORS
#define SECRETWALLRANGE WALLRANGE
#define GRIDCOLORS (GRAYS + GRAYSRANGE / 2)
#define GRIDRANGE 0
#define XHAIRCOLORS GRAYS

/* drawing stuff */
#define FB 0

#define AM_PANDOWNKEY KEY_DOWNARROW
#define AM_PANUPKEY KEY_UPARROW
#define AM_PANRIGHTKEY KEY_RIGHTARROW
#define AM_PANLEFTKEY KEY_LEFTARROW
#define AM_ZOOMINKEY '='
#define AM_ZOOMOUTKEY '-'
#define AM_STARTKEY KEY_TAB
#define AM_ENDKEY KEY_TAB
#define AM_GOBIGKEY '0'
#define AM_FOLLOWKEY 'f'
#define AM_GRIDKEY 'g'

#define AM_NUMMARKPOINTS 10

#define AM_MSGHEADER (('a' << 24) + ('m' << 16))
#define AM_MSGENTERED (AM_MSGHEADER | ('e' << 8))
#define AM_MSGEXITED (AM_MSGHEADER | ('x' << 8))

#define INITSCALEMTOF (.2 * FRACUNIT) /* scale on entry */
/* how much the automap moves window per tic in frame-buffer coordinates */
#define F_PANINC 4 /* moves 140 pixels in 1 second */
/* how much zoom-in per tic */
#define M_ZOOMIN ((int) (1.02 * FRACUNIT)) /* goes to 2x in 1 second */
/* how much zoom-out per tic */
#define M_ZOOMOUT ((int) (FRACUNIT / 1.02)) /* pulls out to 0.5x in 1 second */

/* translates between frame-buffer and map distances */
#define FTOM(x) FixedMul(((x) << 16), scale_ftom)
#define MTOF(x) (FixedMul((x), scale_mtof) >> 16)
/* translates between frame-buffer and map coordinates */
#define CXMTOF(x) (f_x + MTOF((x) -m_x))
#define CYMTOF(y) (f_y + (f_h - MTOF((y) -m_y)))

/* the following is crap */
#define LINE_NEVERSEE ML_DONTDRAW

typedef struct {
	int x, y;
} fpoint_t;

typedef struct {
	fpoint_t a, b;
} fline_t;

typedef vertex_t mpoint_t;

typedef struct {
	mpoint_t a, b;
} mline_t;

typedef struct {
	fixed_t slp, islp;
} islope_t;

/* extern int f_x, f_y, f_w, f_h; */

#ifdef __cplusplus
}
#endif

#endif   /* __AMMAP_H__ */

