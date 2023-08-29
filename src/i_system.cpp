
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

#include <QGuiApplication>

#ifdef sailfishapp
	#include <sailfishapp.h>
#elif auroraapp
	#include <auroraapp.h>
#endif

#include "doomdef.h"
#include "i_sound.h"

#ifdef __cplusplus
extern "C" {
#endif

char* homedir;
char* basedefault;

long mb_used = 8;
int DisplayTicker = 0;

// NOTE added new function
void Z_ChangeTag(byte* p, unsigned char t) {
	// TODO: make error output
	//	if (((memblock_t*) ((byte*) (p) - sizeof(memblock_t)))->id != 0x1d4a11)
	//		I_Error(
	//			"Z_CT at "__FILE__
	//			":%i",
	//			__LINE__);
	Z_ChangeTag2(p, t);
}

void I_Tactile([[maybe_unused]] int on, [[maybe_unused]] int off, [[maybe_unused]] int total) {
	/* UNUSED. */
	on = off = total = 0;
}

ticcmd_t emptycmd;

ticcmd_t* I_BaseTiccmd(void) {
	return &emptycmd;
}

int I_GetHeapSize(void) {
	return mb_used * 1024 * 1024;
}

byte* I_ZoneBase(size_t* size) {
	byte* dummy;

	*size = mb_used * 1024 * 1024;
	dummy = (byte*) malloc(*size);
	assert(dummy);
	return dummy;
}

/*
 * I_GetTime
 * returns time in 1/70th second tics
 */
int I_GetTime(void) {
	struct timeval tp;
	struct timezone tzp;
	int newtics;
	static int basetime = 0;

	gettimeofday(&tp, &tzp);
	if (!basetime)
		basetime = tp.tv_sec;
	newtics = (tp.tv_sec - basetime) * TICRATE + tp.tv_usec * TICRATE / 1000000;
	/* printf("Newtics: %d\n",newtics); */
	return newtics;
}

/* sets and/or gets your private Heretic-homedirectory */

void I_GetHomeDirectory(void) {
	auto fullPath = Aurora::Application::cacheDir().absolutePath().toStdString() + "/";
	homedir = (char*) malloc(fullPath.length() + 1);
	assert(homedir);
	sprintf(homedir, "%s", fullPath.c_str());

	basedefault = (char*) malloc(strlen(homedir) + strlen("heretic.cfg") + 1);
	assert(basedefault);
	sprintf(basedefault, "%sheretic.cfg", homedir);
}

/*
 * I_Init
 */
void I_Init(void) {
	if (!M_CheckParm("-nosound")) {
#ifdef __DOSOUND__
		I_InitSound();
#endif

#ifdef _DEBUGSOUND
		fprintf(stderr, "FIXME, Calling I_InitSound...\n");
#endif
	}

	else
		fprintf(stderr, "I_Init: sound disabled (-nosound)\n");
	if (!M_CheckParm("-nomusic")) {
#ifdef __DOMUSIC__
		I_InitMusic();
#endif

#ifdef _DEBUGSOUND
		fprintf(stderr, "FIXME, Calling I_InitMusic...\n");
#endif
	} else
		fprintf(stderr, "I_Init: backgound music disabled (-nomusic)\n");
}

/*
 * I_Quit
 */
void I_Quit(void) {
	D_QuitNetGame();
#ifdef __DOSOUND__
	I_ShutdownSound();
#endif

#ifdef _DEBUGSOUND
	fprintf(stderr, "(working?): Calling I_ShutdownSound...\n");
#endif

#ifdef __DOMUSIC__
	I_ShutdownMusic();
#endif

#ifdef _DEBUGSOUND
	fprintf(stderr, "FIXME, Calling I_ShutdownMusic...\n");
#endif

	M_SaveDefaults();
	I_ShutdownGraphics();

	free(homedir);
	free(basedefault);
	QGuiApplication::quit();
}

void I_WaitVBL(int count) {
	usleep(count * (1000000 / 70));
}

void I_BeginRead(void) {
}

void I_EndRead(void) {
}

#ifndef UNIX
byte* I_AllocLow(int length) {
	byte* mem;

	mem = (byte*) malloc(length);
	assert(mem);
	if (mem)
		memset(mem, 0, length);
	return mem;
}
#endif

/*
 * I_Error
 */
extern boolean demorecording;

#define _ERROR_HDR "Error: "

void I_Error(const char* error, ...) {
	va_list argptr;
	char err_buff[1024];

	/* put message first into buffer */
	va_start(argptr, error);
	strcpy(err_buff, _ERROR_HDR);
	vsprintf(err_buff + strlen(_ERROR_HDR), error, argptr);
	strncat(err_buff, "\n", sizeof(err_buff) / sizeof(char));
	va_end(argptr);

	/* Shutdown. Here might be other errors. */
	if (demorecording)
		G_CheckDemoStatus();

	D_QuitNetGame();

#ifdef __DOSOUND__
	I_ShutdownSound();
#endif

#ifdef _DEBUGSOUND
	fprintf(stderr, "FIXME, Calling I_ShutdownSound...\n");
#endif

#ifdef __DOMUSIC__
	I_ShutdownMusic();
#endif

#ifdef _DEBUGSOUND
	fprintf(stderr, "FIXME, Calling I_ShutdownMusic...\n");
#endif

	I_ShutdownGraphics();

	free(homedir);
	free(basedefault);

	/* now print the error to stderr */
	fprintf(stderr, "%s", err_buff);
	fprintf(stderr, "\nYou can send this bug message to: heretic@awerthmann.de\n\n");
	fflush(stderr);

	exit(-1);
}

#ifdef __cplusplus
}
#endif
