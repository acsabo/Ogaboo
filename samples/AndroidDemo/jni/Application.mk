# The ARMv7 is significanly faster due to the use of the hardware FPU
APP_ABI := armeabi 
APP_PLATFORM := android-19

APP_STL := gnustl_static

# use this to select gcc instead of clang
NDK_TOOLCHAIN_VERSION := 4.8

# then enable c++11 extentions in source code
APP_CPPFLAGS := -std=gnu++11 -fexceptions -frtti -Wno-deprecated 
APP_CPPFLAGS += -D___ANDROID___ -DANDROID -DBOOST_BIND_NO_PLACEHOLDERS -DZZIP_OMIT_CONFIG_H 

APP_CPPFLAGS += -fpermissive
APP_CPPFLAGS += -g3
