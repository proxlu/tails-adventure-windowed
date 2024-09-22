#ifndef TA_OPTIONS_MENU_H
#define TA_OPTIONS_MENU_H

#include <memory>
#include "main_menu_section.h"
#include "controller.h"
#include "font.h"
#include "sound.h"

enum TA_MoveSoundId {
    TA_MOVE_SOUND_SWITCH,
    TA_MOVE_SOUND_SELECT,
    TA_MOVE_SOUND_ERROR,
    TA_MOVE_SOUND_EMPTY
};

class TA_Option {
public:
    virtual std::string getName() {return "name";}
    virtual std::string getValue() {return "value";}
    virtual TA_MoveSoundId move(int delta) {return TA_MOVE_SOUND_ERROR;}

    virtual bool isLocked() {return false;}
    virtual TA_MoveSoundId updateLocked() {return TA_MOVE_SOUND_EMPTY;}
};

class TA_OptionsSection : public TA_MainMenuSection {
private:
    const double listTransitionTime = 5;

    void updateGroupSelector();
    void updateOptionSelector();
    void playMoveSound(TA_MoveSoundId id);

    void updateAlpha();
    int getLeftX() {return TA::screenWidth / 2 - 80;}

    void drawGroupList();
    void drawOptionList();
    void drawHighlight(double y);

    enum State {
        STATE_SELECTING_GROUP,
        STATE_SELECTING_OPTION,
        STATE_QUIT
    };

    TA_Font font;
    double listTransitionTimeLeft = -1;

    State state = STATE_SELECTING_GROUP;
    std::vector<std::string> groups{"video", "controls", "sound"};
    std::vector<std::vector<std::unique_ptr<TA_Option>>> options;
    TA_Sound switchSound, selectSound, backSound, errorSound;
    std::array<TA_OnscreenButton, 4> buttons;
    int group = 0, option = 0, alpha = 255, baseAlpha = 255;

public:
    using TA_MainMenuSection::TA_MainMenuSection;
    void load() override;
    TA_MainMenuState update() override;
    void draw() override;
    void setAlpha(int alpha) override {baseAlpha = alpha;}
};

#endif // TA_OPTIONS_MENU_H
