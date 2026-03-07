
RUN GAME
./main.exe
./super91.exe


#DEFINED HEADERS

g++ -std=c++17 -ISDL3/x86/include -Iinclude -x c++-header include/myheaders/imports.hpp
g++ -std=c++17 -ISDL3/x86/include -Iinclude -x c++-header include/myheaders/opengl/all.hpp


COMPILER COMMAND

1) g++ main.cpp src/glad.c -o main.exe

2) g++ main.cpp src/*.cpp src/glad.c -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o main.exe


3) g++ main.cpp src/glad.c -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o main.exe


#WITHOUT GUI MODE

4) g++ src/main.cpp src/glad.c assets/icon.res -lwinmm -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o super91.exe

#WITH GUI MODE

5) g++ src/main.cpp src/glad.c assets/icon.res -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o super91.exe -mwindows