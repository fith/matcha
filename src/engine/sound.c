#include "sound.h"

static void loadSounds(void);
void loadMusic(char *filename);
void playMusic(int loop);
void playSound(int id, int channel);
void stopMusic();

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

void initSounds(void)
{
    memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

    music = NULL;

    loadSounds();
}

static void loadSounds(void)
{
    sounds[SND_DOT_LIFT] = Mix_LoadWAV("resources/snd/lift.wav");
    sounds[SND_DOT_SWAP] = Mix_LoadWAV("resources/snd/swap.wav");
    sounds[SND_DOT_DROP] = Mix_LoadWAV("resources/snd/drop.wav");
    sounds[SND_DOT_POP1] = Mix_LoadWAV("resources/snd/pop1.wav");
    sounds[SND_DOT_POP2] = Mix_LoadWAV("resources/snd/pop2.wav");
    sounds[SND_DOT_POP3] = Mix_LoadWAV("resources/snd/pop3.wav");
}

void loadMusic(char *filename)
{
    if (music != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }

    music = Mix_LoadMUS(filename);
    if(!music) {
        printf("Mix_LoadMUS(\"%s\"): %s\n", filename, Mix_GetError());
    }   
}

void stopMusic() {
    Mix_HaltMusic();
}

void playMusic(int loop) {
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel) {
    Mix_PlayChannel(channel, sounds[id], 0);
}