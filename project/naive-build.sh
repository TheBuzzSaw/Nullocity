clang -O3 -c ../../SDL2TK/source/glew.c
clang++ -std=c++11 -O3 -framework OpenGL -framework OpenAL -framework SDL2 -I/Library/Frameworks/SDL2.framework/Headers -I../../SDL2TK/include ../../SDL2TK/source/*.cpp ../source/*.cpp glew.o -llua -o game.bin
