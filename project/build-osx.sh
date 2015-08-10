clang -O2 -c ../SDL2TK/source/glew.c
clang++ -std=c++11 -O2 -o Nullocity.bin -I/usr/local/include -I/usr/local/include/SDL2 -I../SDL2TK/include ../source/*.cpp ../SDL2TK/source/*.cpp ./glew.o -L/usr/local/lib -lSDL2 -lSDL2_image -llua -framework OpenGL -framework OpenAL
