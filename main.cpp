#include "funcs.hpp"

bool dir = false;

int main (int argc, char *argv[]){
  if (!initSDL()) {
    return -1;
  }
  if (argc < 2) {
    options();
    return 1;
  }
  if(FileOrDir(argv[1])){
    playMusic();
    printMenu(dir);
  }else {
    choseAudio();
    dir = true;
    playMusic();
    printMenu(dir);
  }

  bool quit = false;
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
              repeate();
            case 'B':  // down
              setVolume(volume - 10);
              std::cout << "Volume decreased to " << volume << std::endl;
              break;
              repeate();
            case 'D': // Right
              nextFile(-1);
              repeate();
            case 'C': // Left
              nextFile(1);
              repeate();
          }
        }
        break;

      case 'p':  
        if (isPlaying && !isPaused) {
          pauseMusic();
          repeate();
          std::cout << "Music paused!" << std::endl;
        }
        break;
      case 'r':  
        if (isPaused) {
          resumeMusic();
          repeate();
          std::cout << "Music resumed!" << std::endl;
        }
        break;
      case 's':  
        if (isPlaying) {
          stopMusic();
          repeate();
          std::cout << "Music stopped!" << std::endl;
        }
        break;
      case 'q':  
        quit = true;
        break;
      case 'd': //change audio from DIR 
        Dir_Show();
        repeate();
      default:
        break;

        repeate();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }


  clean();
  return 0;
}

void repeate(){
  std::cout << "\033[2J\033[1;1H";
  show_theFile();
  printMenu(dir);
}
