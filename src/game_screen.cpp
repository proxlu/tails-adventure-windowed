#include "game_screen.h"
#include "save.h"

void TA_GameScreen::init()
{
    isSeaFox = ((int)TA::levelPath.size() >= 7 && TA::levelPath.substr(0, 7) == "maps/lr");

    if(isSeaFox) {
        links.seaFox = &seaFox;
    }
    else {
        links.character = &character;
    }

    links.tilemap = &tilemap;
    links.camera = &camera;
    links.objectSet = &objectSet;
    links.hud = &hud;
    links.controller = &controller;

    controller.load();
    controller.setMode(TA_ONSCREEN_CONTROLLER_GAME);

    if(isSeaFox) {
        seaFox.load(links);
    }
    else {
        character.load(links);
    }
    
    objectSet.setLinks(links);
    tilemap.load(TA::levelPath + ".tmx");
    tilemap.setCamera(&camera);
    hud.load(links);
    objectSet.load(TA::levelPath + ".xml");

    if(isSeaFox) {

    }
    else {
        character.setSpawnPoint(objectSet.getCharacterSpawnPoint(), objectSet.getCharacterSpawnFlip());
    }
    
    TA::previousLevelPath = TA::levelPath;
}

TA_ScreenState TA_GameScreen::update()
{
    controller.update();
    hud.update();
    objectSet.updateMusic();

    if(!hud.isPaused()) {
        if(!isSeaFox) {
            character.handleInput();
        }
        objectSet.update();

        if(isSeaFox) {
            seaFox.update();
            camera.update(false, false);
        }
        else {
            character.update();
            camera.update(character.isOnGround(), character.isJumpingOnSpring() || character.isOnStrongWind() || character.isUsingSpeedBoots());
        }
    }

    if(isSeaFox) {

    }
    else {
        character.setPaused(hud.isPaused());
    }

    tilemap.setUpdateAnimation(!hud.isPaused());
    objectSet.setPaused(hud.isPaused());

    tilemap.draw(0);
    objectSet.draw(0);

    if(isSeaFox) {
        seaFox.draw();
    }
    else {
        character.draw();
    }
    
    objectSet.draw(1);
    tilemap.draw(1);
    objectSet.draw(2);
    hud.draw();
    controller.draw();

    if(hud.getTransition() != TA_SCREENSTATE_CURRENT) {
        return hud.getTransition();
    }
    if(!isSeaFox && character.gameOver()) {
        return TA_SCREENSTATE_GAMEOVER;
    }
    if(!isSeaFox && character.isTeleported()) {
        TA::save::saveToLatest();
        return TA_SCREENSTATE_HOUSE;
    }
    if(objectSet.getTransition() != TA_SCREENSTATE_CURRENT) {
        if(objectSet.getTransition() == TA_SCREENSTATE_MAP) {
            TA::save::saveToLatest();
        }
        return objectSet.getTransition();
    }
    return TA_SCREENSTATE_CURRENT;
}

void TA_GameScreen::quit()
{

}
