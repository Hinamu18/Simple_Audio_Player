#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include "func.h"

int main (int argc, char *argv[]){
  if (!initSDL()) {
    return -1;
  }
  if (argc < 2) {
    std::cout << "JUST ADD THE AUDIO PATH" << std::endl;
    return 1;
  }
  std::string audioFilePath = argv[1];
  music = Mix_LoadMUS(audioFilePath.c_str()); 

  playMusic();
  printMenu();

  bool quit = false;

  // set terminal to raw (no Enter needed)
  setRawMode();

  while (!quit) {
    unsigned char ch = getchar();  // gat a single char without waiting for Enter

    switch (ch) {
      case 27:  // (^)
        if (getchar() == '[') {
          int arrowKey = getchar();
          switch (arrowKey) {
            case 'A':  // up
              setVolume(volume + 10);
              std::cout << "Volume increased to " << volume << std::endl;
              break;
            case 'B':  // down
              setVolume(volume - 10);
              std::cout << "Volume decreased to " << volume << std::endl;
              break;
          }
        }
        break;

      case 'p':  
        if (isPlaying && !isPaused) {
          pauseMusic();
          std::cout << "Music paused!" << std::endl;
        }
        break;
      case 'r':  
        if (isPaused) {
          resumeMusic();
          std::cout << "Music resumed!" << std::endl;
        }
        break;
      case 's':  
        if (isPlaying) {
          stopMusic();
          std::cout << "Music stopped!" << std::endl;
        }
        break;
      case 'q':  
        quit = true;
        break;
      case 'd': //change audio from DIR 
      // TODO
      default:
        break;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }


  clean();
  return 0;
}

