#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

Mix_Chunk *explosion_sound = NULL;
Mix_Chunk *bloop_sound = NULL;

// Function to initialize SDL and the explosion sound
int init_audio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio failed: %s\n", Mix_GetError());
        SDL_Quit();
        return -1;
    }

    explosion_sound = Mix_LoadWAV("sounds/explosion.wav");
    if (!explosion_sound) {
        fprintf(stderr, "Mix_LoadWAV failed: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    bloop_sound = Mix_LoadWAV("sounds/bloop.wav");
    if (!bloop_sound) {
        fprintf(stderr, "Mix_LoadWAV failed: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    return 0; // Success
}

// Function to play the explosion sound
void play_explosion_sound() {
    if (explosion_sound) {
        Mix_PlayChannel(-1, explosion_sound, 0);
    } else {
        fprintf(stderr, "Explosion sound not loaded\n");
    }
}

void play_bloop_sound() {
    if (bloop_sound) {
        Mix_PlayChannel(-1, bloop_sound, 0);
    } else {
        fprintf(stderr, "Bloop sound not loaded\n");
    }
}

// Clean up resources
void cleanup_audio() {
    if(explosion_sound) {
        Mix_FreeChunk(explosion_sound);
        explosion_sound = NULL;
    }
    if(bloop_sound) {
        Mix_FreeChunk(bloop_sound);
        bloop_sound = NULL;
    }
    Mix_CloseAudio();
    SDL_Quit();
}
