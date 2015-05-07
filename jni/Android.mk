LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Ogaboo

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../headers \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/boost \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/boost/lambda \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OIS \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OGRE \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OGRE/RenderSystems \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OGRE/RenderSystems/GLES2 \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/bullet \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/ogrebullet/Collisions \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/ogrebullet/Dynamics
					
LOCAL_SRC_FILES := \
        $(subst $(LOCAL_PATH)/,, \
        $(wildcard $(LOCAL_PATH)/../*.cpp))
        
LOCAL_STATIC_LIBRARIES := android_native_app_glue cpufeatures        

#LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 

include $(BUILD_STATIC_LIBRARY)

$(call import-module,android/native_app_glue) 
$(call import-module,android/cpufeatures)
