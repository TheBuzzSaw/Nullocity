CFLAGS = -c -I/usr/local/include -I/usr/local/include/SDL2 -I../SDL2TK/include
LIBS = -l

CXX = clang++ -std=c++11 $(CFLAGS)
CC = clang $(CFLAGS)

all: nullocity.bin

# SDL2TK

Address32.o:
	$(CXX) ../SDL2TK/source/Address32.cpp

AudioBuffer.o:
	$(CXX) ../SDL2TK/source/AudioBuffer.cpp

AudioContext.o:
	$(CXX) ../SDL2TK/source/AudioContext.cpp

AudioDevice.o:
	$(CXX) ../SDL2TK/source/AudioDevice.cpp

AudioSource.o:
	$(CXX) ../SDL2TK/source/AudioSource.cpp

Module.o:
	$(CXX) ../SDL2TK/source/Module.cpp

Port.o:
	$(CXX) ../SDL2TK/source/Port.cpp

Program.o:
	$(CXX) ../SDL2TK/source/Program.cpp

ProgramBuilder.o:
	$(CXX) ../SDL2TK/source/ProgramBuilder.cpp

Shader.o:
	$(CXX) ../SDL2TK/source/Shader.cpp

Surface.o:
	$(CXX) ../SDL2TK/source/Surface.cpp

TimeSpan.o:
	$(CXX) ../SDL2TK/source/TimeSpan.cpp

Tools.o:
	$(CXX) ../SDL2TK/source/Tools.cpp

Window.o:
	$(CXX) ../SDL2TK/source/Window.cpp

WindowSettings.o:
	$(CXX) ../SDL2TK/source/WindowSettings.cpp

glew.o:
	$(CC) ../SDL2TK/source/glew.c

# Nullocity

ActionMappings.o:
	$(CXX) ../source/ActionMappings.cpp

AudioManager.o:
	$(CXX) ../source/AudioManager.cpp

Builders.o:
	$(CXX) ../source/Builders.cpp

CollisionHandler.o:
	$(CXX) ../source/CollisionHandler.cpp

Entity.o:
	$(CXX) ../source/Entity.cpp

GameModule.o:
	$(CXX) ../source/GameModule.cpp

KeyNames.o:
	$(CXX) ../source/KeyNames.cpp

LuaReference.o:
	$(CXX) ../source/LuaReference.cpp

LuaState.o:
	$(CXX) ../source/LuaState.cpp

ModelLoader.o:
	$(CXX) ../source/ModelLoader.cpp

SimpleBufferObject.o:
	$(CXX) ../source/SimpleBufferObject.cpp

SimpleBuilder.o:
	$(CXX) ../source/SimpleBuilder.cpp

SimpleProgram.o:
	$(CXX) ../source/SimpleProgram.cpp

main.o: ../source/main.cpp
	$(CXX) ../source/main.cpp

nullocity.bin: Address32.o AudioBuffer.o AudioContext.o AudioDevice.o AudioSource.o glew.o Module.o Port.o Program.o ProgramBuilder.o Shader.o Surface.o TimeSpan.o Tools.o Window.o WindowSettings.o ActionMappings.o AudioManager.o Builders.o CollisionHandler.o Entity.o GameModule.o KeyNames.o LuaReference.o LuaState.o ModelLoader.o SimpleBufferObject.o SimpleBuilder.o SimpleProgram.o main.o
	clang++ *.o -o nullocity.bin -L/usr/local/lib -lSDL2 -lSDL2_image -llua -framework OpenGL -framework OpenAL

clean:
	rm -f *.o