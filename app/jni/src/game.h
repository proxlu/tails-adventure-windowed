#ifndef TA_GAME_H
#define TA_GAME_H

#include <chrono>
#include "SDL.h"
#include "screen_state_machine.h"

class TA_Game {
private:
    const int baseHeight = 144;
    const double pixelAspectRatio = 1;
    const double minWindowAspectRatio = 1.2, maxWindowAspectRatio = 2.4;
    const int soundFrequency = 44100, soundChunkSize = 256;

    void toggleFullscreen();
    void updateWindowSize();

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, currentTime;
    TA_ScreenStateMachine screenStateMachine;

    bool firstFrame = true;
    long long fpsTimer = 0;
    int fpsCount = 0, refreshRate = 60, defaultWindowWidth = 1024, defaultWindowHeight = 576;
    bool useVsync = true, fullscreen = true;

public:
    TA_Game();
    ~TA_Game();
    bool process();
    void update();
};

#endif //TA_GAME_H