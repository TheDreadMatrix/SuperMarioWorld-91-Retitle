# build.ps1

Write-Host "Compiling project..." -ForegroundColor Cyan

$timer = [System.Diagnostics.Stopwatch]::StartNew()

g++ `
src/main.cpp `
src/moderngl/program_mesh.cpp `
src/moderngl/texture.cpp `
src/glad.c `
assets/icon.res `
src_audio/core/soloud.cpp `
src_audio/core/soloud_audiosource.cpp `
src_audio/core/soloud_bus.cpp `
src_audio/core/soloud_core_3d.cpp `
src_audio/core/soloud_core_basicops.cpp `
src_audio/core/soloud_core_faderops.cpp `
src_audio/core/soloud_core_filterops.cpp `
src_audio/core/soloud_core_getters.cpp `
src_audio/core/soloud_core_setters.cpp `
src_audio/core/soloud_core_voicegroup.cpp `
src_audio/core/soloud_core_voiceops.cpp `
src_audio/core/soloud_fader.cpp `
src_audio/core/soloud_fft.cpp `
src_audio/core/soloud_fft_lut.cpp `
src_audio/core/soloud_file.cpp `
src_audio/core/soloud_filter.cpp `
src_audio/core/soloud_misc.cpp `
src_audio/core/soloud_queue.cpp `
src_audio/core/soloud_thread.cpp `
src_audio/backend/miniaudio/soloud_miniaudio.cpp `
src_audio/audiosource/wav/soloud_wav.cpp `
src_audio/audiosource/wav/soloud_wavstream.cpp `
src_audio/audiosource/wav/dr_impl.cpp `
src_audio/audiosource/wav/stb_vorbis.c `
src_audio/filter/soloud_biquadresonantfilter.cpp `
-Iinclude/ `
-Iinclude_audio/ `
-ISDL3/x86/include/ `
-LSDL3/x86/lib/ `
-lSDL3 `
-lopengl32 `
-std=c++17 `
-DWITH_MINIAUDIO `
-o super91.exe

$timer.Stop()

$seconds = [math]::Round($timer.Elapsed.TotalSeconds, 2)

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful! ($seconds sec)" -ForegroundColor Green
    Write-Host "Launching game..." -ForegroundColor Green

    .\super91.exe

} else {
    Write-Host "Build failed! ($seconds sec)" -ForegroundColor Red
}