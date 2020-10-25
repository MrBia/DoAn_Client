LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
		   $(LOCAL_PATH)/../../../Classes/HelloWorldScene.cpp \
		   $(LOCAL_PATH)/../../../Classes/ResourceManager.cpp \
		   $(LOCAL_PATH)/../../../Classes/Diamond.cpp \
		   $(LOCAL_PATH)/../../../Classes/FightHammer.cpp \
		   $(LOCAL_PATH)/../../../Classes/ControlMusic.cpp \
		   $(LOCAL_PATH)/../../../Classes/Fire.cpp \
		   $(LOCAL_PATH)/../../../Classes/GamePlay.cpp \
		   $(LOCAL_PATH)/../../../Classes/GamePlay2.cpp \
  		   $(LOCAL_PATH)/../../../Classes/Glass.cpp \
		   $(LOCAL_PATH)/../../../Classes/Glass2.cpp \
		   $(LOCAL_PATH)/../../../Classes/Item_game.cpp \
		   $(LOCAL_PATH)/../../../Classes/Keys.cpp \
		   $(LOCAL_PATH)/../../../Classes/LoadingLogo.cpp \
		   $(LOCAL_PATH)/../../../Classes/MainCharactor.cpp \
		   $(LOCAL_PATH)/../../../Classes/MainMenu.cpp \
		   $(LOCAL_PATH)/../../../Classes/MapGame.cpp \
		   $(LOCAL_PATH)/../../../Classes/MiniGameScene.cpp \
		   $(LOCAL_PATH)/../../../Classes/Objject.cpp \
		   $(LOCAL_PATH)/../../../Classes/Rock.cpp \
		   $(LOCAL_PATH)/../../../Classes/SneakyJoystick.cpp \
		   $(LOCAL_PATH)/../../../Classes/SneakyJoystickSkinnedBase.cpp \
		   $(LOCAL_PATH)/../../../Classes/Spider.cpp \
		   $(LOCAL_PATH)/../../../Classes/TestMapScene1.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
