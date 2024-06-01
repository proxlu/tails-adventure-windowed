#ifndef TA_TOUCHSCREEN_H
#define TA_TOUCHSCREEN_H

#include "SDL2/SDL.h"
#include "geometry.h"
#include "tools.h"

namespace TA { namespace touchscreen {
    void handleEvent(SDL_TouchFingerEvent event);
    void update();
} }

class TA_Button : public TA_Polygon {
private:
    bool pressed = false, hold = false;
    TA_Point touchPosition;

public:
    void update();
    bool isPressed() {return pressed;}
    bool isJustPressed() {return pressed && !hold;}
    TA_Point getTouchPosition() {return touchPosition;}
};

#endif // TA_TOUCHSCREEN_H
