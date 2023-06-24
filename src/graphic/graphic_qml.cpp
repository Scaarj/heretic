#include <unistd.h>

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <errno.h>
#include <netinet/in.h>
#include <signal.h>

#include "doomdef.h"

#include "painter.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHOW_FPS

#ifdef SHOW_FPS
static struct timeval starttime;
static long totalframes;
static int showfps = 0;

static void reset_framecounter(void) {
}
#endif

static int X_screen;
static int X_width;
static int X_height;
static int true_color = FALSE;
static unsigned long* xpixel;
static boolean doShm;
static int X_shmeventtype;
static int XShm_is_attached = FALSE;
static boolean grabMouse;
static int multiply = 1;
static int init_truec_pals(void);
static int free_truec_pals(void);
static int get_pal_usage(void);

static int oldgamma;

int xlatekey(void) {
}

void I_ShutdownGraphics(void) {
}

void I_StartFrame(void) {
}

static int lastmousex = 0;
static int lastmousey = 0;
static boolean mousemoved = false;
static boolean shmFinished;

extern ScenePainter* painter;

void I_GetEvent(void) {
}

void I_StartTic(void) {
}

void I_FinishUpdate(void) {
}

static int get_pal_usage(void) {
}

static int init_truec_pals(void) {
}

static int free_truec_pals(void) {
}

void I_SetPalette(byte* palette) {
	if (painter) {
		painter->setPallete(palette);
	}
}

void grabsharedmemory(size_t size) {
}

void InitGraphLib(void) {
}

void I_InitGraphics(void) {
}

unsigned int exptable[256];

void InitExpand(void) {
}

double exptable2[256 * 256];

void InitExpand2(void) {
}

int inited;

void Expand4(unsigned* lineptr, double* xline) {
}

void I_CheckRes() {
}

#ifdef __cplusplus
}
#endif
