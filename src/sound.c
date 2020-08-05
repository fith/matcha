#include "sound.h"

static void loadSounds(void);
void loadMusic(char *filename);
void playMusic(int loop);
void playSound(int id, int channel);

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
    // sounds[SND_PLAYER_FIRE] = Mix_LoadWAV("snd/laser.wav");
    // sounds[SND_ENEMY_FIRE] = Mix_LoadWAV("snd/enemy_laser.wav");
    // sounds[SND_PLAYER_DIE] = Mix_LoadWAV("snd/player_die.wav");
    // sounds[SND_ENEMY_DIE] = Mix_LoadWAV("snd/enemy_die.wav");
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

void playMusic(int loop)
{
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel)
{
    Mix_PlayChannel(channel, sounds[id], 0);
}