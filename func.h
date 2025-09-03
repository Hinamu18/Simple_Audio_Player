#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>

#define AUDIO_RATE  44100
#define AUDIO_FORMAT  MIX_DEFAULT_FORMAT
#define AUDIO_CHANNELS  2
#define AUDIO_CHUNKSIZE  1024

Mix_Music* music = nullptr;
bool isPlaying = false;
bool isPaused = false;
int volume = 50;


void setRawMode() {
  struct termios newt;
  tcgetattr(STDIN_FILENO, &newt); // Get current terminal settings
  newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echoing
  newt.c_cc[VMIN] = 1; // Minimum input is 1 character
  newt.c_cc[VTIME] = 0; // No timeout
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply changes
}


bool initSDL() {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
    std::cerr << "SDL init error: " << SDL_GetError() << std::endl;
    return false;
  }

  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
    std::cerr << "SDL_mixer int error: " << Mix_GetError() << std::endl;
    return false;
  }

  if (Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNKSIZE) == -1) {
    std::cerr << "open audio error: " << Mix_GetError() << std::endl;
    return false;
  }

  return true;
}

void clean() {
  Mix_CloseAudio();
  Mix_Quit();
  SDL_Quit();
}


void playMusic() {
  if (Mix_PlayMusic(music, -1) == -1) {
    std::cerr << "play music error: " << Mix_GetError() << std::endl;
    return;
  }
  isPlaying = true;
  isPaused = false;
}

void pauseMusic() {
  Mix_PauseMusic();
  isPlaying = false;
  isPaused = true;
}

void resumeMusic() {
  Mix_ResumeMusic();
  isPlaying = true;
  isPaused = false;
}

void stopMusic() {
  Mix_HaltMusic();
  isPlaying = false;
  isPaused = false;
}

void setVolume(int vol) {
  if (vol < 0) vol = 0;
  if (vol > 100) vol = 100;
  Mix_VolumeMusic(vol);
  volume = vol;
}

void printMenu() {
  std::cout << "\nControls:\n";
  std::cout << "Arrow Up   -> Increase Volume\n";
  std::cout << "Arrow Down -> Decrease Volume\n";
  std::cout << "p          -> Pause Music\n";
  std::cout << "r          -> Resume Music\n";
  std::cout << "s          -> Stop Music\n";
  std::cout << "q          -> Quit\n";
}
