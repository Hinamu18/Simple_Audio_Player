#include "funcs.hpp"
#include <cstdlib>
#include <iostream>
#include <ostream>

std::vector<std::string> Files_in_dir;
std::vector<std::string> Files_Names;
fs::path dir_path;
int i = 0, j = 0;

bool FileOrDir(std::string path) {
  if (fs::is_regular_file(path)) {
    music = Mix_LoadMUS(path.c_str());
    return true;

  } else if (fs::is_directory(path)) {
    dir_path = path;
    for (const auto& entry : fs::directory_iterator(dir_path)) {
      if (entry.is_regular_file()) {
        Files_in_dir.push_back(entry.path());
        Files_Names.push_back(entry.path().filename());
        i++;
        std::cout << i <<std::endl;
      }
    }
    Files_Names.push_back(" ");
    return false;
  } else {
    std::cout << "THERE IS NO SUCH A FILE OR A DIRECTORY" << std::endl;
    exit(1);
  }
}

void Dir_Show() {
  for (int j = 0; j < i; j++) {
    std::cout << j + 1 << ": " << Files_Names.at(j) << std::endl;
  }
}

bool choseAudio() {
  if (Files_in_dir.empty()) {
    std::cerr << "No audio files in directory." << std::endl;
    return false;
  }
  std::cout << "<- " << Files_Names.at(j) << " ->" << std::endl;
  music = Mix_LoadMUS(Files_in_dir.at(j).c_str());
  return true;
}

void nextFile(int n) {
  if (Files_in_dir.empty()) return;

  j += n;

  if (j < 0)
    j = i - 1;  
  else if (j >= i)
    j = 0;   

  stopMusic();
  music = Mix_LoadMUS(Files_in_dir.at(j).c_str());
  playMusic();

  std::cout << "Now playing: " << Files_Names.at(j) << std::endl;
}

void show_theFile() {
    if (Files_Names.empty()) return;
    std::cout << "<- " << Files_Names.at(j) << " ->" << std::endl;
}
