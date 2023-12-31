
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include <sys/time.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "i_sound.h"
#include "soundst.h"

#include "doomdef.h"

#ifdef __cplusplus
extern "C" {
#endif

char* doomwaddir;
char* ptr;

extern char* doomwaddir;

/*
 * The number of internal mixing channels,
 *  the samples calculated for each mixing step,
 *  the size of the 16bit, 2 hardware channel (stereo)
 *  mixing buffer, and the samplerate of the raw data.
 */

/* Needed for calling the actual sound output. */
#define SAMPLECOUNT 512
#define NUM_CHANNELS 8
/* It is 2 for 16bit, and 2 for two channels. */
#define BUFMUL 4
#define MIXBUFFERSIZE (SAMPLECOUNT * BUFMUL)

#define SAMPLERATE 11025 /* Hz */
#define SAMPLESIZE 2 /* 16bit */

/* The actual lengths of all sound effects. */
int lengths[NUMSFX];

/* The actual output device. */
int audio_fd;

/*
 * The global mixing buffer.
 * Basically, samples from all active internal channels
 * are modifed and added, and stored in the buffer
 *  that is submitted to the audio device.
 */
signed short mixbuffer[MIXBUFFERSIZE];

/* The channel step amount... */
unsigned int channelstep[NUM_CHANNELS];
/* ... and a 0.16 bit remainder of last step. */
unsigned int channelstepremainder[NUM_CHANNELS];

/* The channel data pointers, start and end. */
unsigned char* channels[NUM_CHANNELS];
unsigned char* channelsend[NUM_CHANNELS];

/*
 * Time/gametic that the channel started playing,
 *  used to determine oldest, which automatically
 *  has lowest priority.
 * In case number of active sounds exceeds
 *  available channels.
 */
int channelstart[NUM_CHANNELS];

/*
 * The sound in channel handles,
 *  determined on registration,
 *  might be used to unregister/stop/modify,
 *  currently unused.
 */
int channelhandles[NUM_CHANNELS];

/*
 * SFX id of the playing sound effect.
 * Used to catch duplicates (like chainsaw).
 */
int channelids[NUM_CHANNELS];

/* Pitch to stepping lookup, unused. */
int steptable[256];

/* Volume lookups. */
int vol_lookup[128 * 256];

/* Hardware left and right channel volume lookup. */
int* channelleftvol_lookup[NUM_CHANNELS];
int* channelrightvol_lookup[NUM_CHANNELS];

/*
 * This function loads the sound data from the WAD lump,
 *  for single sound.
 */
void* getsfx([[maybe_unused]] int sfx_id, [[maybe_unused]] char* sfxname, [[maybe_unused]] int* len) {
	//	int size;
	//	char name[20];
	//	unsigned char* paddedsfx;
	//	unsigned char* sfx;
	//	int paddedsize;
	//	int sfxlump;
	//	int i;

	//	/*
	//     * Get the sound data from the WAD, allocate lump
	//     *  in zone memory.
	//     */
	//	sprintf(name, "%s", sfxname);

	//	if (W_CheckNumForName(name) == -1)
	//		sfxlump = /* W_GetNumForName("dspistol"); */ W_GetNumForName("gldhit");
	//	else
	//		sfxlump = W_GetNumForName(name);

	//	size = W_LumpLength(sfxlump);

	//	/* Andre: this should be fixed ! */

	//	gsi_load_raw_sample(sfx_id, wadfiles[0], lumpinfo[sfxlump].position + 8, size - 8, 11025, 1, GSI_8BIT);
	//	gsi_flush();

	//	/* Return allocated padded data. */
	//	return (void*) (paddedsfx + 8);
}

/*
 * This function adds a sound to the
 *  list of currently active sounds,
 *  which is maintained as a given number
 *  (eight, usually) of internal channels.
 * Returns a handle.
 */
int addsfx([[maybe_unused]] int sfxid, [[maybe_unused]] int volume, [[maybe_unused]] int step,
	[[maybe_unused]] int seperation) {
	//	static unsigned short handlenums = 0;

	//	int i;
	//	int rc = -1;

	//	int oldest = gametic;
	//	int oldestnum = 0;
	//	int slot;

	//	int rightvol;
	//	int leftvol;

	//	{
	//		/* Loop all channels, check. */
	//		for (i = 0; i < NUM_CHANNELS; i++) {
	//			/* Active, and using the same SFX? */
	//			if ((channels[i]) && (channelids[i] == sfxid)) {
	//				/* Reset. */
	//				channels[i] = 0;
	//				/*
	//		 * We are sure that iff,
	//		 *  there will only be one.
	//		 */
	//				gsi_kill_sound(i);
	//				break;
	//			}
	//		}
	//	}

	//	/* Loop all channels to find oldest SFX. */
	//	for (i = 0; (i < NUM_CHANNELS) && (channels[i]); i++) {
	//		if (channelstart[i] < oldest) {
	//			oldestnum = i;
	//			oldest = channelstart[i];
	//		}
	//	}

	//	/*
	//     * Tales from the cryptic.
	//     * If we found a channel, fine.
	//     * If not, we simply overwrite the first one, 0.
	//     * Probably only happens at startup.
	//     */
	//	if (i == NUM_CHANNELS)
	//		slot = oldestnum;
	//	else
	//		slot = i;

	//	/*
	//     * Okay, in the less recent channel,
	//     *  we will handle the new SFX.
	//     * Set pointer to raw data.
	//     */
	//	channels[slot] = (unsigned char*) S_sfx[sfxid].data;

	//	/* Set pointer to end of raw data. */
	//	channelsend[slot] = channels[slot] + lengths[sfxid];

	//	/* Reset current handle number, limited to 0..100. */
	//	if (!handlenums)
	//		handlenums = 100;

	//	/*
	//     * Assign current handle number.
	//     * Preserved so sounds could be stopped (unused).
	//     */
	//	channelhandles[slot] = rc = handlenums++;

	//	/*
	//     * Set stepping???
	//     * Kinda getting the impression this is never used.
	//     */
	//	channelstep[slot] = step;

	//	channelstepremainder[slot] = 0;

	//	/* Should be gametic, I presume. */
	//	channelstart[slot] = gametic;

	//	/*
	//     * Separation, that is, orientation/stereo.
	//     *  range is: 1 - 256
	//     */
	//	seperation += 1;

	//	/*
	//     * Per left/right channel.
	//     *  x^2 seperation,
	//     *  adjust volume properly.
	//     */
	//	leftvol = volume - ((volume * seperation * seperation) >> 16); /* /(256*256); */
	//	seperation = seperation - 257;
	//	rightvol = volume - ((volume * seperation * seperation) >> 16);

	//	fprintf(stderr, "rightvol: %d\n", rightvol);
	//	fprintf(stderr, "leftvol: %d\n", leftvol);

	//	/* Sanity check, clamp volume. */
	//	if (rightvol < 0 || rightvol > 127)
	//		I_Error("rightvol out of bounds");

	//	if (leftvol < 0 || leftvol > 127)
	//		I_Error("leftvol out of bounds");

	//	/*
	//     * Get the proper lookup table piece
	//     *  for this volume level???
	//     */
	//	channelleftvol_lookup[slot] = &vol_lookup[leftvol * 256];
	//	channelrightvol_lookup[slot] = &vol_lookup[rightvol * 256];

	//	/*
	//     * Preserve sound SFX id,
	//     *  e.g. for avoiding duplicates of chainsaw.
	//     */
	//	channelids[slot] = sfxid;

	//	gsi_play_sound(slot, sfxid, GSI_CMD_OVERWRITE);
	//	seperation += 257; /* undo above, or just ((seperation *2)-257 -> (seperation *2)+257 .. */

	//	gsi_send_commands(10, GSI_CMD_SET_VOLUME | GSI_CMD_CURRENT, volume * 2, GSI_CMD_SET_PAN | GSI_CMD_CURRENT,
	//		(((seperation * 2) - 257) >> 8) & 255, ((seperation * 2) - 257) & 255,
	//		GSI_CMD_SET_SAMPLE_FACTOR | GSI_CMD_CURRENT, step >> 24, step >> 16, step >> 8, step);

	//	gsi_flush();

	//	/* You tell me. */
	//	return rc;
	return 0;
}

/*
 * SFX API
 * Note: this was called by S_Init.
 * However, whatever they did in the
 * old DPMS based DOS version, this
 * were simply dummies in the Linux
 * version.
 * See soundserver initdata().
 */
void I_SetChannels() {
	//	/*
	//     * Init internal lookups (raw data, mixing buffer, channels).
	//     * This function sets up internal lookups used during
	//     *  the mixing process.
	//     */
	//	int i;
	//	int j;

	//	int* steptablemid = steptable + 128;

	//	/*
	//     * This table provides step widths for pitch parameters.
	//     * I fail to see that this is currently used.
	//     */
	//	for (i = -128; i < 128; i++)
	//		steptablemid[i] = (int) (pow(2.0, (i / 64.0)) * 65536.0);

	//	/*
	//     * Generates volume lookup tables
	//     *  which also turn the unsigned samples
	//     *  into signed samples.
	//     */
	//	for (i = 0; i < 128; i++)
	//		for (j = 0; j < 256; j++)
	//			vol_lookup[i * 256 + j] = (i * (j - 128) * 256) / 127;
}

void I_SetSfxVolume([[maybe_unused]] int volume) {
	//	/*
	//     * Identical to DOS.
	//     * Basically, this should propagate
	//     *  the menu/config file setting
	//     *  to the state variable used in
	//     *  the mixing.
	//     */
	//	snd_SfxVolume = volume;

	//	/* doom volume = 0-127 */
	//	gsi_set_volume(GSI_PCM, volume * 2);
	//	gsi_flush();
}

/*
 * MUSIC API
 */
void I_SetMusicVolume([[maybe_unused]] int volume) {
	//	/* Internal state variable. */
	//	snd_MusicVolume = volume;
	//	/*
	//     * Now set volume on output device.
	//     * Whatever( snd_MusciVolume );
	//     */

	//	/* doom volume = 0-127 */
	//	gsi_set_volume(GSI_SYNTH, volume * 2);
	//	gsi_flush();
}

/*
 * Retrieve the raw data lump index
 *  for a given SFX name.
 */
int I_GetSfxLumpNum(sfxinfo_t* sfx) {
	char namebuf[9];
	int dummy;
	sprintf(namebuf, "%s", sfx->name);
	dummy = W_GetNumForName(namebuf);

	fprintf(stderr, "[I_GetSfxLumpNum] sfx->name: %s ; W_GetNumForName: %d\n", sfx->name, dummy);

	return dummy;
}

/*
 * Starting a sound means adding it
 *  to the current list of active sounds
 *  in the internal channels.
 * As the SFX info struct contains
 *  e.g. a pointer to the raw data,
 *  it is ignored.
 * As our sound handling does not handle
 *  priority, it is ignored.
 * Pitching (that is, increased speed of playback)
 *  is set, but currently not used by mixing.
 */
int I_StartSound(int id, int vol, int sep, int pitch, [[maybe_unused]] int priority) {
	/* UNUSED */
	priority = 0;

	/* Returns a handle (not used). */
	id = addsfx(id, vol, steptable[pitch], sep);

	fprintf(stderr, "handle is %d\n", id);
	return id;
}

void I_StopSound([[maybe_unused]] int handle) {
	/*
     * You need the handle returned by StartSound.
     * Would be looping all channels,
     *  tracking down the handle,
     *  an setting the channel to zero.
     */
}

int I_SoundIsPlaying(int handle) {
	/* Ouch. */
	return gametic < handle;
}

/*
 * This function loops all active (internal) sound
 *  channels, retrieves a given number of samples
 *  from the raw sound data, modifies it according
 *  to the current (internal) channel parameters,
 *  mixes the per channel samples into the global
 *  mixbuffer, clamping it to the allowed range,
 *  and sets up everything for transferring the
 *  contents of the mixbuffer to the (two)
 *  hardware channels (left and right, that is).
 *
 * This function currently supports only 16bit.
 */
void I_UpdateSound(void) {
	//	/*
	//     * Mix current sound data.
	//     * Data, from raw sound, for right and left.
	//     */
	//	register unsigned int sample;
	//	register int dl;
	//	register int dr;

	//	/* Pointers in global mixbuffer, left, right, end. */
	//	signed short* leftout;
	//	signed short* rightout;
	//	signed short* leftend;
	//	/* Step in mixbuffer, left and right, thus two. */
	//	int step;

	//	/* Mixing channel index. */
	//	int chan;

	//	/*
	//     * Left and right channel
	//     *  are in global mixbuffer, alternating.
	//     */
	//	leftout = mixbuffer;
	//	rightout = mixbuffer + 1;
	//	step = 2;

	//	/*
	//     * Determine end, for left channel only
	//     *  (right channel is implicit).
	//     */
	//	leftend = mixbuffer + SAMPLECOUNT * step;

	//	/*
	//     * Mix sounds into the mixing buffer.
	//     * Loop over step*SAMPLECOUNT,
	//     *  that is 512 values for two channels.
	//     */
	//	while (leftout != leftend) {
	//		/* Reset left/right value. */
	//		dl = 0;
	//		dr = 0;

	//		/*
	//	     * Love thy L2 chache - made this a loop.
	//	     * Now more channels could be set at compile time
	//	     *  as well. Thus loop those  channels.
	//	     */
	//		for (chan = 0; chan < NUM_CHANNELS; chan++) {
	//			/* Check channel, if active. */
	//			if (channels[chan]) {
	//				/* Get the raw data from the channel. */
	//				sample = *channels[chan];
	//				/* Add left and right part */

	//				/*
	//			     *  for this channel (sound)
	//			     *  to the current data.
	//			     * Adjust volume accordingly.
	//			     */
	//				dl += channelleftvol_lookup[chan][sample];
	//				dr += channelrightvol_lookup[chan][sample];

	//				/* Increment index ??? */
	//				channelstepremainder[chan] += channelstep[chan];

	//				/* MSB is next sample??? */
	//				channels[chan] += channelstepremainder[chan] >> 16;

	//				/* Limit to LSB??? */
	//				channelstepremainder[chan] &= 65536 - 1;

	//				/* Check whether we are done. */
	//				if (channels[chan] >= channelsend[chan])
	//					channels[chan] = 0;
	//			}
	//		}

	//		/*
	//	     * Clamp to range. Left hardware channel.
	//	     * Has been char instead of short.
	//	     * if (dl > 127) *leftout = 127;
	//	     * else if (dl < -128) *leftout = -128;
	//	     * else *leftout = dl;
	//	     */

	//		if (dl > 0x7fff)
	//			*leftout = 0x7fff;
	//		else if (dl < -0x8000)
	//			*leftout = -0x8000;
	//		else
	//			*leftout = dl;

	//		/* Same for right hardware channel. */
	//		if (dr > 0x7fff)
	//			*rightout = 0x7fff;
	//		else if (dr < -0x8000)
	//			*rightout = -0x8000;
	//		else
	//			*rightout = dr;

	//		/* Increment current pointers in mixbuffer. */
	//		leftout += step;
	//		rightout += step;
	//	}
}

/*
 * This would be used to write out the mixbuffer
 *  during each game loop update.
 * Updates sound buffer and audio device at runtime. 
 * It is called during Timer interrupt with SNDINTR.
 * Mixing now done synchronous, and
 *  only output be done asynchronous?
 */
void I_SubmitSound(void) {
	/* Write it to DSP device. */
	write(audio_fd, mixbuffer, SAMPLECOUNT * BUFMUL);
}

void I_UpdateSoundParams(int handle, [[maybe_unused]] int vol, [[maybe_unused]] int sep, [[maybe_unused]] int pitch) {
	/*
     * I fail too see that this is used.
     * Would be using the handle to identify
     *  on which channel the sound might be active,
     *  and resetting the channel parameters.
     */

	/* #warning add update here. */

	fprintf(stderr, "I_UpdateSoundParams for handle=%d\n", handle);
	/*
     * ===> is handle really the channel? check
     * gsi_send_commands(6,
     *	GSI_CMD_SET_VOLUME, handle, volume *2,
     *	GSI_CMD_SET_PAN | GSI_CMD_CURRENT, (((seperation *2)-257) >>8)&255, ((seperation *2)-257)&255
     *	);
     *gsi_flush();
     */
}

void I_ShutdownSound(void) {
	//	gsi_close();
	//	gsi_flush();

	//	/* Done. */
	//	return;
}

extern char* wadfiles[];

void I_InitSound() {
	//	int i;

	//	if (gsi_init(NULL)) {
	//		fprintf(stderr, "GSI: unable to connect to server\n");
	//		return;
	//	}

	//	doomwaddir = (char*) malloc(256);
	//	assert(doomwaddir);
	//	strncpy(doomwaddir, wadfiles[0], 255);
	//	doomwaddir[255] = 0;

	//	ptr = getcwd(doomwaddir, 256);
	//	if (ptr == NULL) {
	//		perror("getcwd");
	//		I_Error("bailing out...\n");
	//	}

	//	fprintf(stderr, "doomwaddir: %s\n", doomwaddir);

	//	gsi_chdir(doomwaddir);

	//	gsi_init_pcm(11025, 2, GSI_16BIT, 10);
	//	gsi_flush();

	//	/* Initialize external data (all sounds) at start, keep static. */
	//	fprintf(stderr, "I_InitSound: ");

	//	for (i = 1; i < NUMSFX; i++) {
	//		S_sfx[i].lumpnum = -1;
	//		/* Alias? Example is the chaingun sound linked to pistol. */
	//		if (!S_sfx[i].link) {
	//			/* Load data from WAD file. */
	//			S_sfx[i].data = getsfx(i, S_sfx[i].name, &lengths[i]);
	//		} else {
	//			/* Previously loaded already? */
	//			S_sfx[i].data = S_sfx[i].link->data;
	//			lengths[i] = lengths[(S_sfx[i].link - S_sfx) / sizeof(sfxinfo_t)];
	//		}
	//	}
	//	fprintf(stderr, " pre-cached all sound data\n");

	//	/* Now initialize mixbuffer with zero. */
	//	for (i = 0; i < MIXBUFFERSIZE; i++)
	//		mixbuffer[i] = 0;

	//	/* Finished initialization. */
	//	fprintf(stderr, "I_InitSound: sound module ready\n");
}

/*
 * MUSIC API.
 */
void I_InitMusic(void) {
	//	fprintf(stderr, "I_InitMusic:\n");
	//	gsi_grab_synth();
	//	gsi_flush();
}

void I_ShutdownMusic(void) {
	//	gsi_release_synth();
	//	gsi_flush();
}

static int looping = 0;
static int musicdies = -1;

void I_PlaySong([[maybe_unused]] int handle, [[maybe_unused]] int loop) {
	//	/*
	//     * WHS: in doom, loop = boolean, i.e. if loop=0 then play only once (see
	//     * s_sound.c for a call with loop=false)
	//     */
	//	gsi_play_song(1 - loop);
	//	gsi_flush();
	//	looping = loop;
	//	musicdies = gametic + TICRATE * 30;
}

void I_PauseSong([[maybe_unused]] int handle) {
	//	gsi_stop_song();
	//	gsi_flush();
	//	handle = 0;
}

void I_ResumeSong([[maybe_unused]] int handle) {
	//	gsi_continue_song();
	//	gsi_flush();
	//	handle = 0;
}

void I_StopSong([[maybe_unused]] int handle) {
	//	gsi_stop_song();
	//	gsi_flush();

	//	looping = 0;
	//	musicdies = 0;
}

void I_UnRegisterSong([[maybe_unused]] int handle) {
}

int I_RegisterSong(void* data) {
	data = NULL;
	return 1;
}

/* Is the song playing? */
int I_QrySongPlaying([[maybe_unused]] int handle) {
	handle = 0;
	return looping || musicdies > gametic;
}

#ifdef __cplusplus
}
#endif
