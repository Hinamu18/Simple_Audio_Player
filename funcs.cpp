#include "funcs.hpp"

Mix_Music* music;
bool isPlaying = true;
bool isPaused = false;
int volume = 50;

void setRawMode() {
  struct termios newt;
  tcgetattr(STDIN_FILENO, &newt);
  newt.c_lflag &= ~(ICANON | ECHO);
  newt.c_cc[VMIN] = 1;
  newt.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

bool initSDL() {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
    std::cerr << "SDL init error: " << SDL_GetError() << std::endl;
    return false;
  }

  if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
    std::cerr << "SDL_mixer init error: " << Mix_GetError() << std::endl;
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

void options() {
  std::cout << "Usage: hinap [options] [/DIR_PATH or ./file]" << std::endl;
}

