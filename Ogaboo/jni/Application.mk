APP_ABI := armeabi 
APP_PLATFORM := android-19

APP_STL :=gnustl_static

# use this to select gcc instead of clang
NDK_TOOLCHAIN_VERSION := 4.8

# then enable c++11 extentions in source code
APP_CPPFLAGS := -std=gnu++11 -frtti -fexceptions -fpermissive
APP_CPPFLAGS += -g3
APP_CPPFLAGS += -DANDROID
