/* W_wad.c */

#ifdef NeXT
	#include <ctype.h>
	#include <libc.h>

	/* next doesn't need a binary flag in open call */
	#define O_BINARY 0

#else

	#ifdef UNIX
		#include <assert.h>
		#include <ctype.h>
		#include <fcntl.h>
		#include <malloc.h>
		#include <stdlib.h>
		#include <string.h>
		#include <sys/stat.h>
		#include <sys/types.h>
		#include <unistd.h>

		#ifdef HAVE_ALLOCA_H
			#include <alloca.h>
		#endif /* HAVE_ALLOCA_H */

		#define O_BINARY 0
	#endif /* UNIX */

	#include <unistd.h>
	#include <assert.h>
	#include <ctype.h>
	#include <malloc.h>
	#include <cstring>

	#ifdef __GLIBC__
		// NOTE: use uio.h istean io.h
		//		#include <sys/io.h>
		#include <sys/uio.h>
	#else
		#include <sys/uio.h>
	#endif /* __GLIBC__ */

	#include <fcntl.h>
	#include <stdio.h>
	#include <string.h>
	#include <sys/stat.h>
#endif /* NeXT */

#include "doomdef.h"

#ifndef HOMEDIR
	#define HOMEDIR "/.heretic"
#endif /* HOMEDIR */

/* ===============
 *    TYPES
 * =============== 
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char identification[4]; /* should be IWAD */
	int numlumps __PACKED__;
	int infotableofs __PACKED__;
} __PACKED__ wadinfo_t;

typedef struct {
	int filepos;
	int size;
	char name[8];
} __PACKED__ filelump_t;

/* =============
 *  GLOBALS
 * ============= 
 */

lumpinfo_t* lumpinfo; /* location of each lump on disk */
int numlumps;

void** lumpcache;

/* =================== */

#ifdef UNIX

	#define strcmpi strcasecmp

void strupr(char* s) {
	while (*s)
		*s++ = toupper(*s);
}

/*
================
=
= filelength
=
================
*/

int filelength(int handle) {
	struct stat fileinfo;

	if (fstat(handle, &fileinfo) == -1)
		I_Error("Error fstating");

	return fileinfo.st_size;
}

#endif /* UNIX */

#define O_BINARY 00

void ExtractFileBase(const char* path, char* dest) {
	const char* src;
	int length;

	src = path + strlen(path) - 1;

	/* back up until a \ or the start */
	while (src != path && *(src - 1) != '\\' && *(src - 1) != '/')
		src--;

	/* copy up to eight characters */

	memset(dest, 0, 8);
	length = 0;

	while (*src && *src != '.') {
		if (++length == 9)
			I_Error("Filename base of %s >8 chars", path);
		*dest++ = toupper((int) *src++);
	}
}

/* Helper function */

int wadopen(const char* fileName) {
	int fd = -1;
	char* fn;
	char* envhome;

	fn = (char*) malloc(strlen("./") + strlen(fileName) + 1);
	assert(fn);
	sprintf(fn, "./%s", fileName);
	if (!access(fn, R_OK)) {
		fd = open(fn, O_RDONLY | O_BINARY);
		free(fn);
		return fd;
	}

	if ((envhome = getenv("HERETICHOME")) != NULL) {
		fn = (char*) malloc(strlen(envhome) + strlen("/") + strlen(fileName) + 1);
		assert(fn);
		sprintf(fn, "%s/%s", envhome, fileName);
		fd = open(fn, O_RDONLY | O_BINARY);
		free(fn);
	}

	if ((fd < 0) && ((envhome = getenv("HOME")) != NULL)) {
		fn = (char*) malloc(strlen(envhome) + strlen(HOMEDIR "/") + strlen(fileName) + 1);
		assert(fn);
		sprintf(fn, "%s" HOMEDIR "/%s", envhome, fileName);
		fd = open(fn, O_RDONLY | O_BINARY);
		free(fn);
	}

	if ((fd < 0) && (envhome = getenv("PATH"))) {
		char *path = strdup(envhome), *curentry;
		assert(path);
		while (strlen(path) && (fd < 0)) {
			if (!(curentry = strrchr(path, ':')))
				curentry = path;
			else
				*curentry++ = 0;
			fn = (char*) malloc(strlen(curentry) + 19 + strlen(fileName)); /* Add space for /, ../share/heretic/ */
			assert(fn);
			sprintf(fn, "%s/%s", curentry, fileName);
			fd = open(fn, O_RDONLY | O_BINARY);
			/* check ../share/heretic */
			if (fd < 0) {
				sprintf(fn, "%s/../share/heretic/%s", curentry, fileName);
				fd = open(fn, O_RDONLY | O_BINARY);
			}
			free(fn);
			*curentry = 0;
		}
		free(path);
	}

	if (fd < 0)
		fd = open(fileName, O_RDONLY | O_BINARY);

	return fd;
}

/*
  ============================================================================
  
  LUMP BASED ROUTINES
  
  ============================================================================
*/

/*
  ====================
  =
  = W_AddFile
  =
  = All files are optional, but at least one file must be found
  = Files with a .wad extension are wadlink files with multiple lumps
  = Other files are single lumps with the base filename for the lump name
  =
  ====================
*/

void W_AddFile(const char* filename) {
	wadinfo_t header;
	lumpinfo_t* lump_p;
	int handle;
	size_t length;
	int startlump;
	filelump_t *fileinfo, singleinfo;

	/*
   * open the file and add to directory
   */

	if ((handle = wadopen(filename)) == -1) {
		printf(" couldn't open %s\n", filename);
		return;
	}

	printf(" adding %s\n", filename);
	startlump = numlumps;

	if (strcasecmp(filename + strlen(filename) - 3, "wad")) {
		/* single lump file */
		fileinfo = &singleinfo;
		singleinfo.filepos = 0;
		// NOTE: Check correct file size
		//		singleinfo.size = LONG(filelength(handle));
		singleinfo.size = lseek(handle, 0, SEEK_END) + 1;
		ExtractFileBase(filename, singleinfo.name);
		numlumps++;
	} else {
		/* WAD file */
		read(handle, &header, sizeof(header));
		if (strncmp(header.identification, "IWAD", 4)) {
			if (strncmp(header.identification, "PWAD", 4))
				I_Error("Wad file %s doesn't have IWAD or PWAD id\n", filename);
		}
		header.numlumps = LONG(header.numlumps);
		header.infotableofs = LONG(header.infotableofs);
		length = header.numlumps * sizeof(filelump_t);
		fileinfo = static_cast<filelump_t*>(alloca(length));
		lseek(handle, header.infotableofs, SEEK_SET);
		read(handle, fileinfo, length);
		numlumps += header.numlumps;
	}

	/* Fill in lumpinfo */
	lumpinfo = static_cast<lumpinfo_t*>(realloc(lumpinfo, numlumps * sizeof(lumpinfo_t)));
	if (!lumpinfo)
		I_Error("Couldn't realloc lumpinfo");
	lump_p = &lumpinfo[startlump];

	for (int i = startlump; i < numlumps; i++, lump_p++, fileinfo++) {
		lump_p->handle = handle;
		lump_p->position = LONG(fileinfo->filepos);
		lump_p->size = LONG(fileinfo->size);
		strncpy(lump_p->name, fileinfo->name, 8);
	}
}

/*
  ====================
  =
  = W_InitMultipleFiles
  =
  = Pass a null terminated list of files to use.
  =
  = All files are optional, but at least one file must be found
  =
  = Files with a .wad extension are idlink files with multiple lumps
  =
  = Other files are single lumps with the base filename for the lump name
  =
  = Lump names can appear multiple times. The name searcher looks backwards,
  = so a later file can override an earlier one.
  =
  ====================
*/

void W_InitMultipleFiles(const char** filenames) {
	int size;

	/* open all the files, load headers, and count lumps */
	numlumps = 0;
	lumpinfo = static_cast<lumpinfo_t*>(malloc(1)); /* will be realloced as lumps are added */

	for (; *filenames; filenames++)
		W_AddFile(*filenames);

	if (!numlumps)
		I_Error("W_InitFiles: no files found");

	/* set up caching */
	size = numlumps * sizeof(*lumpcache);
	lumpcache = static_cast<void**>(malloc(size));
	assert(lumpcache);
	if (!lumpcache)
		I_Error("Couldn't allocate lumpcache");
	memset(lumpcache, 0, size);
}

/*
  ====================
  =
  = W_InitFile
  =
  = Just initialize from a single file
  =
  ====================
*/

void W_InitFile(const char* filename) {
	const char* names[2];

	names[0] = filename;
	names[1] = NULL;
	W_InitMultipleFiles(names);
}

/*
  ====================
  =
  = W_NumLumps
  =
  ====================
*/

int W_NumLumps(void) {
	return numlumps;
}

/*
  ====================
  =
  = W_CheckNumForName
  =
  = Returns -1 if name not found
  =
  ====================
*/

int W_CheckNumForName(const char* name) {
	char name8[9];
	int v1, v2;
	lumpinfo_t* lump_p;

	/* make the name into two integers for easy compares */

	strncpy(name8, name, 8);
	name8[8] = 0; /* in case the name was a fill 8 chars */
	// NOTE: lower name
	//strlwr(name8); /* case insensitive */
	for (auto& it : name8) {
		it = toupper(it);
	}

	v1 = *(int*) name8;
	v2 = *(int*) &name8[4];

	/* scan backwards so patch lump files take precedence */

	lump_p = lumpinfo + numlumps;

	while (lump_p-- != lumpinfo)
		if (*(int*) lump_p->name == v1 && *(int*) &lump_p->name[4] == v2)
			return lump_p - lumpinfo;

	return -1;
}

/*
  ====================
  =
  = W_GetNumForName
  =
  = Calls W_CheckNumForName, but bombs out if not found
  =
  ====================
*/

int W_GetNumForName(const char* name) {
	int i;

	i = W_CheckNumForName(name);
	if (i != -1)
		return i;

	I_Error("W_GetNumForName: %s not found!", name);
	return -1;
}

/*
  ====================
  =
  = W_LumpLength
  =
  = Returns the buffer size needed to load the given lump
  =
  ====================
*/

int W_LumpLength(int lump) {
	if (lump >= numlumps)
		I_Error("W_LumpLength: %i >= numlumps", lump);
	return lumpinfo[lump].size;
}

/*
  ====================
  =
  = W_ReadLump
  =
  = Loads the lump into the given buffer, which must be >= W_LumpLength()
  =
  ====================
*/

void W_ReadLump(int lump, void* dest) {
	int c;
	lumpinfo_t* l;

	if (lump >= numlumps)
		I_Error("W_ReadLump: %i >= numlumps", lump);
	l = lumpinfo + lump;

	/* I_BeginRead (); - for use with DiskIconFlashing... */

	lseek(l->handle, l->position, SEEK_SET);
	c = read(l->handle, dest, l->size);

	if (c < l->size)
		I_Error("W_ReadLump: only read %i of %i on lump %i", c, l->size, lump);
	/* I_EndRead (); - for use with DiskIconFlashing... */
}

/*
  ====================
  =
  = W_CacheLumpNum
  =
  ====================
*/

void* W_CacheLumpNum(int lump, int tag) {
	[[maybe_unused]] byte* ptr;

	if (lump >= numlumps)
		I_Error("W_CacheLumpNum: %i >= numlumps", lump);

	if (!lumpcache[lump]) { /* read the lump in */
		/* printf ("cache miss on lump %i\n",lump); */
		ptr = static_cast<byte*>(Z_Malloc(W_LumpLength(lump), tag, &lumpcache[lump]));
		W_ReadLump(lump, lumpcache[lump]);
	} else {
		/* printf ("cache hit on lump %i\n",lump); */
		Z_ChangeTag(static_cast<byte*>(lumpcache[lump]), tag);
	}

	return lumpcache[lump];
}

/*
  ====================
  =
  = W_CacheLumpName
  =
  ====================
*/

void* W_CacheLumpName(const char* name, int tag) {
	return W_CacheLumpNum(W_GetNumForName(name), tag);
}

/*
  ====================
  =
  = W_Profile
  =
  ====================
*/

// Ripped out for Heretic
/*
int	info[2500][10];
int	profilecount;

void W_Profile (void)
{
	int		i;
	memblock_t	*block;
	void	*ptr;
	char	ch;
	FILE	*f;
	int		j;
	char	name[9];
	
	
	for (i=0 ; i<numlumps ; i++)
	{	
		ptr = lumpcache[i];
		if (!ptr)
		{
			ch = ' ';
			continue;
		}
		else
		{
			block = (memblock_t *) ( (byte *)ptr - sizeof(memblock_t));
			if (block->tag < PU_PURGELEVEL)
				ch = 'S';
			else
				ch = 'P';
		}
		info[i][profilecount] = ch;
	}
	profilecount++;
	
	f = fopen ("waddump.txt","w");
	name[8] = 0;
	for (i=0 ; i<numlumps ; i++)
	{
		memcpy (name,lumpinfo[i].name,8);
		for (j=0 ; j<8 ; j++)
			if (!name[j])
				break;
		for ( ; j<8 ; j++)
			name[j] = ' ';
		fprintf (f,"%s ",name);
		for (j=0 ; j<profilecount ; j++)
			fprintf (f,"    %c",info[i][j]);
		fprintf (f,"\n");
	}
	fclose (f);
}
*/

#ifdef __cplusplus
}
#endif
