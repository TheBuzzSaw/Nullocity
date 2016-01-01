#clang -O2 -c ../SDL2TK/source/glew.c
clang++ -std=c++11 -O2 -framework OpenGL -framework OpenAL -I../SDL2TK/include -I/usr/local/include/SDL2 ../SDL2TK/source/*.cpp ../source/*.cpp glew.o -lSDL2 -llua -o game.bin
