#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <audiofile.mp3>\n";
    return 1;
  }

  std::string filename = argv[1];

  SDL_Init(SDL_INIT_AUDIO);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

  Mix_Music* music = Mix_LoadMUS(filename.c_str());
  Mix_PlayMusic(music, 1);

  std::cout << "Playing " << filename << "\nPress Enter to quit\n";
  std::cin.get();

  Mix_HaltMusic();
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  SDL_Quit();

  return 0;
}
