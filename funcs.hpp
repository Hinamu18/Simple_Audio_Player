#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

#define AUDIO_RATE      44100
#define AUDIO_FORMAT    MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS  2
#define AUDIO_CHUNKSIZE 1024

// Global Variables
extern Mix_Music* music;
extern bool isPlaying;
extern bool isPaused;
extern int volume;
// Audio
bool FileOrDir(std::string path);
void playMusic(); 
void pauseMusic();
void resumeMusic();
void stopMusic();
void setVolume(int vol);

// SDL / Init
bool initSDL();
void clean();

// Terminal I/O
void setRawMode();
void repeate();

// UI
void printMenu(bool dir);
void options();

// Directory Handling
void Dir_Show();
bool choseAudio();
void nextFile(int n);
void show_theFile();

#endif // FUNCS_HPP
