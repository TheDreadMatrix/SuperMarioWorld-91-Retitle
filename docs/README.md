#TEST FILES

cd C:\Users\User\.vscode\MyGameC++\apython
venv/Scripts/activate


RUN GAME
./main.exe
./super91.exe


#DEFINED HEADERS

g++ -std=c++17 -ISDL3/x86/include -Iinclude -Iinclude_audio -x c++-header include/myheaders/imports.hpp
g++ -std=c++17 -ISDL3/x86/include -Iinclude -x c++-header include/myheaders/opengl/all.hpp
g++ -std=c++17 -ISDL3/x86/include -Iinclude -Iinclude_audio -x c++-header include/myheaders/stdport/stdport.hpp


COMPILER COMMAND

1) g++ main.cpp src/glad.c -o main.exe

2) g++ main.cpp src/*.cpp src/glad.c -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o main.exe


3) g++ main.cpp src/glad.c -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o main.exe


#WITHOUT GUI MODE

4) g++ src/main.cpp src/glad.c assets/icon.res -lwinmm -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o super91.exe

#WITH GUI MODE

5) g++ src/main.cpp src/glad.c assets/icon.res -Iinclude/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -o super91.exe -mwindows





#AUDIO 

6) g++ src/main.cpp src/moderngl/program_mesh.cpp src/moderngl/texture.cpp src/glad.c assets/icon.res src_audio/core/soloud.cpp src_audio/core/soloud_audiosource.cpp src_audio/core/soloud_bus.cpp src_audio/core/soloud_core_3d.cpp src_audio/core/soloud_core_basicops.cpp src_audio/core/soloud_core_faderops.cpp src_audio/core/soloud_core_filterops.cpp src_audio/core/soloud_core_getters.cpp src_audio/core/soloud_core_setters.cpp src_audio/core/soloud_core_voicegroup.cpp src_audio/core/soloud_core_voiceops.cpp src_audio/core/soloud_fader.cpp src_audio/core/soloud_fft.cpp src_audio/core/soloud_fft_lut.cpp src_audio/core/soloud_file.cpp src_audio/core/soloud_filter.cpp src_audio/core/soloud_misc.cpp src_audio/core/soloud_queue.cpp src_audio/core/soloud_thread.cpp src_audio/backend/miniaudio/soloud_miniaudio.cpp src_audio/audiosource/wav/soloud_wav.cpp src_audio/audiosource/wav/soloud_wavstream.cpp src_audio/audiosource/wav/dr_impl.cpp src_audio/audiosource/wav/stb_vorbis.c src_audio/filter/soloud_biquadresonantfilter.cpp  -Iinclude/ -Iinclude_audio/ -ISDL3/x86/include/ -LSDL3/x86/lib/ -lSDL3 -lopengl32 -std=c++17 -DWITH_MINIAUDIO -o super91.exe
