all:
	g++ -std=c++17 -O3 main.cpp funcs.cpp controls.cpp dir.cpp -o HinaP -lSDL2 -lSDL2_mixer -lpthread 
