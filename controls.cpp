#include "funcs.hpp"

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

void printMenu(bool dir) {
  std::cout << "\nControls:\n";
  std::cout << "Arrow Up   -> Increase Volume\n";
  std::cout << "Arrow Down -> Decrease Volume\n";
  if (dir) {
    std::cout << "d          -> Show audio files and choose\n";
  }
  std::cout << "p          -> Pause Music\n";
  std::cout << "r          -> Resume Music\n";
  std::cout << "s          -> Stop Music\n";
  std::cout << "q          -> Quit\n";
}

