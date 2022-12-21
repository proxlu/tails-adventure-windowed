LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/../SDL2_image/include \
                    $(LOCAL_PATH)/../SDL2_mixer/include \
                    $(LOCAL_PATH)/../tinyxml2

LOCAL_DISABLE_FORMAT_STRING_CHECKS := true

LOCAL_SRC_FILES := main.cpp \
                   engine/game.cpp \
                   engine/sprite.cpp \
                   engine/screen_state_machine.cpp \
                   engine/tools.cpp \
                   engine/sound.cpp \
                   engine/touchscreen.cpp \
                   engine/geometry.cpp \
                   engine/tilemap.cpp \
                   engine/camera.cpp \
                   engine/pawn.cpp \
                   engine/object_set.cpp \
                   game/character_controller.cpp \
                   game/character.cpp \
                   game/hud.cpp \
                   objects/explosion.cpp \
                   objects/bomb.cpp \
                   screens/intro_screen.cpp \
                   screens/title_screen.cpp \
                   screens/game_screen.cpp \
                   $(LOCAL_PATH)/../tinyxml2/tinyxml2.cpp

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid

include $(BUILD_SHARED_LIBRARY)
