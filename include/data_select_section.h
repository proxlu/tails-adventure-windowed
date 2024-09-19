#ifndef DATA_SELECT_SECTION_H
#define DATA_SELECT_SECTION_H

#include "main_menu_section.h"
#include "sound.h"
#include "font.h"

class TA_DataSelectSection : public TA_MainMenuSection {
public:
    using TA_MainMenuSection::TA_MainMenuSection;
    void load() override;
    TA_MainMenuState update() override;
    void setAlpha(int alpha) override {this->alpha = alpha;}
    void draw() override;

private:
    const double menuStart = 16;
    const double menuOffset = 64;
    const double scrollSpeed = 12;
    const double selectorBlinkTime = 15;
    const double loadTime = 60;

    void updateSelection();
    int getSavePercent(int save);
    std::string getSaveTime(int save);

    TA_Sprite entrySprite, selectorRedSprite, selectorWhiteSprite, previewSprite;
    TA_Sound switchSound, loadSaveSound;
    TA_Font font;
    double timer = 0, selectorTimer = 0;

    double position = 0;
    int selection = 0, alpha = 255;
    bool locked = false;
};

#endif // DATA_SELECT_SECTION_H
