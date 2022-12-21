#ifndef TA_TOUCHSCREEN_H
#define TA_TOUCHSCREEN_H

#include "SDL.h"
#include "geometry.h"

namespace TA_TouchBackend {
    void processTouchEvent(SDL_TouchFingerEvent event);
    void update();
}

struct TA_Button : TA_Polygon {
private:
    bool pressed = false, hold = false, mode = false;

public:
    void update();
    void setMode() {mode = true;}
    bool isPressed() {return pressed;}
    bool isJustPressed() {return pressed && !hold;}
};

#endif // TA_TOUCHSCREEN_H