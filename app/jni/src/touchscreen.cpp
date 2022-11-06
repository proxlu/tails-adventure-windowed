#include <map>
#include <set>
#include "touchscreen.h"
#include "globals.h"
#include "error.h"

namespace TA_TouchBackend {
    std::map<int, TA_Point> currentFingers;
    std::set<int> justPressedFingers;
}

void TA_TouchBackend::update()
{
    justPressedFingers.clear();
}

void TA_TouchBackend::processTouchEvent(SDL_TouchFingerEvent event)
{
    if(event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION) {
        if(event.type == SDL_FINGERDOWN) {
            justPressedFingers.insert(event.fingerId);
        }
        currentFingers[event.fingerId] = {event.x * gScreenWidth, event.y * gScreenHeight};
    }
    else {
        currentFingers.erase(event.fingerId);
    }
}

void TA_Button::update()
{
    if(mode) {
        bool flag = false;
        for(auto finger : TA_TouchBackend::currentFingers) {
            TA_Point point = finger.second;
            if(inside(point)) {
                if(TA_TouchBackend::justPressedFingers.count(finger.first)) {
                    pressed = true;
                }
                else if(pressed) {
                    hold = true;
                }
                flag = true;
            }
        }
        if(!flag) {
            pressed = hold = false;
        }
    }
    else {
        pressed = hold = false;
        for(auto finger : TA_TouchBackend::currentFingers) {
            TA_Point point = finger.second;
            if(inside(point)) {
                if(!TA_TouchBackend::justPressedFingers.count(finger.first)) {
                    hold = true;
                }
                pressed = true;
            }
        }
    }
}
