LOCAL_PATH := $(call my-dir) 

#--------------- INCLUDES AREA

# Lua
include $(CLEAR_VARS)
LOCAL_MODULE := luacore
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libluacore.a
include $(PREBUILT_STATIC_LIBRARY)

# boost_system
include $(CLEAR_VARS)
LOCAL_MODULE := boost_system
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libboost_system-gcc-mt-s-1_53.a
include $(PREBUILT_STATIC_LIBRARY)

# boost_filesystem
include $(CLEAR_VARS)
LOCAL_MODULE := boost_filesystem
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libboost_filesystem-gcc-mt-s-1_53.a
include $(PREBUILT_STATIC_LIBRARY)

# boost_thread
include $(CLEAR_VARS)
LOCAL_MODULE := boost_thread
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libboost_thread-gcc-mt-s-1_53.a
include $(PREBUILT_STATIC_LIBRARY)

# OgreBulletCollisions
include $(CLEAR_VARS)
LOCAL_MODULE := OgreBulletCollisions
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreBulletCollisions.a
include $(PREBUILT_STATIC_LIBRARY)

# OgreBulletDynamics
include $(CLEAR_VARS)
LOCAL_MODULE := OgreBulletDynamics
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreBulletDynamics.a
include $(PREBUILT_STATIC_LIBRARY)

# Bullet
include $(CLEAR_VARS)
LOCAL_MODULE := Bullet
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libBullet.a
include $(PREBUILT_STATIC_LIBRARY)

# OgreMainStatic
include $(CLEAR_VARS)
LOCAL_MODULE := OgreMainStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreMainStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# OgreTerrainStatic
include $(CLEAR_VARS)
LOCAL_MODULE := OgreTerrainStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreTerrainStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# OgreOverlayStatic
include $(CLEAR_VARS)
LOCAL_MODULE := OgreOverlayStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreOverlayStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# RenderSystem_GLES2Static
include $(CLEAR_VARS)
LOCAL_MODULE := RenderSystem_GLES2Static
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/OGRE/libRenderSystem_GLES2Static.a
include $(PREBUILT_STATIC_LIBRARY)

# Plugin_ParticleFXStatic
include $(CLEAR_VARS)
LOCAL_MODULE := Plugin_ParticleFXStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/OGRE/libPlugin_ParticleFXStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# OgrePropertyStatic
include $(CLEAR_VARS)
LOCAL_MODULE := OgrePropertyStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgrePropertyStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# OgreVolumeStatic
include $(CLEAR_VARS)
LOCAL_MODULE := OgreVolumeStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreVolumeStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# OgreRTShaderSystemStatic
include $(CLEAR_VARS)
LOCAL_MODULE := OgreRTShaderSystemStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreRTShaderSystemStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# OgrePagingStatic
include $(CLEAR_VARS)
LOCAL_MODULE := OgrePagingStatic
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgrePagingStatic.a
include $(PREBUILT_STATIC_LIBRARY)

# LuaCppInterface
include $(CLEAR_VARS)
LOCAL_MODULE := LuaCppInterface
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libLuaCppInterface.a
include $(PREBUILT_STATIC_LIBRARY)

# CEGUI_Base
include $(CLEAR_VARS)
LOCAL_MODULE := CEGUI_Base
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libCEGUIBase-9999_Static.a
include $(PREBUILT_STATIC_LIBRARY)

# CEGUI_Ogre_Renderer
include $(CLEAR_VARS)
LOCAL_MODULE := CEGUI_Ogre_Renderer
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libCEGUIOgreRenderer-9999_Static.a
include $(PREBUILT_STATIC_LIBRARY)

# CEGUIFreeImageImageCodec_Static
include $(CLEAR_VARS)
LOCAL_MODULE := CEGUIFreeImageImageCodec_Static
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libCEGUIFreeImageImageCodec_Static.a
include $(PREBUILT_STATIC_LIBRARY)

# CEGUICoreWindowRendererSet_Static
include $(CLEAR_VARS)
LOCAL_MODULE := CEGUICoreWindowRendererSet_Static
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libCEGUICoreWindowRendererSet_Static.a
include $(PREBUILT_STATIC_LIBRARY)

# CEGUICommonDialogs_Static
include $(CLEAR_VARS)
LOCAL_MODULE := CEGUICommonDialogs_Static
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libCEGUICommonDialogs-9999_Static.a
include $(PREBUILT_STATIC_LIBRARY)

# CEGUITinyXMLParser_Static
include $(CLEAR_VARS)
LOCAL_MODULE := CEGUITinyXMLParser_Static
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libCEGUITinyXMLParser_Static.a
include $(PREBUILT_STATIC_LIBRARY)

# libCEGUIOpenGLRenderer
include $(CLEAR_VARS)
LOCAL_MODULE := libCEGUIOpenGLRenderer
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libCEGUIOgreRenderer-9999_Static.a
include $(PREBUILT_STATIC_LIBRARY)

# OIS
include $(CLEAR_VARS)
LOCAL_MODULE := OIS
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOIS.a
include $(PREBUILT_STATIC_LIBRARY)

# FreeImage
include $(CLEAR_VARS)
LOCAL_MODULE := FreeImage
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libFreeImage.a
include $(PREBUILT_STATIC_LIBRARY)

# FreeType
include $(CLEAR_VARS)
LOCAL_MODULE := FreeType
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

# mesa
include $(CLEAR_VARS)
LOCAL_MODULE := mesa
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libmesa.a
include $(PREBUILT_STATIC_LIBRARY)

# pcre
include $(CLEAR_VARS)
LOCAL_MODULE := pcre
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libpcre.a
include $(PREBUILT_STATIC_LIBRARY)

# Ogaboo
include $(CLEAR_VARS)
LOCAL_MODULE := Ogaboo
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgaboo.a
include $(PREBUILT_STATIC_LIBRARY)

# openal
include $(CLEAR_VARS)
LOCAL_MODULE := openal
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libopenal.a
include $(PREBUILT_STATIC_LIBRARY)

# SHADER
include $(CLEAR_VARS)
LOCAL_MODULE := SHADER
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libRenderSystem_GLES2Static.a
include $(PREBUILT_STATIC_LIBRARY)

# Plugin_OgreVideo
#include $(CLEAR_VARS)
#LOCAL_MODULE := Plugin_OgreVideo
#LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libPlugin_OgreVideo.so
#include $(PREBUILT_SHARED_LIBRARY)

# OgreOggSound
#include $(CLEAR_VARS)
#LOCAL_MODULE := OgreOggSound
#LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreOggSound.so
#include $(PREBUILT_SHARED_LIBRARY)

# OgreOggSound_Static
include $(CLEAR_VARS)
LOCAL_MODULE := OgreOggSound_Static
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreOggSound.a
include $(PREBUILT_STATIC_LIBRARY)

# Plugin_OgreVideo Static
include $(CLEAR_VARS)
LOCAL_MODULE := Plugin_OgreVideo_static
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libPlugin_OgreVideo.a
include $(PREBUILT_STATIC_LIBRARY)

# theora_player
include $(CLEAR_VARS)
LOCAL_MODULE := theora_player
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libtheoraplayer.a
include $(PREBUILT_STATIC_LIBRARY)

# theora
include $(CLEAR_VARS)
LOCAL_MODULE := theora
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libtheora.a
include $(PREBUILT_STATIC_LIBRARY)

# vorbis
include $(CLEAR_VARS)
LOCAL_MODULE := vorbis
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libvorbis.a
include $(PREBUILT_STATIC_LIBRARY)

# vorbis_file
include $(CLEAR_VARS)
LOCAL_MODULE := vorbis_file
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libvorbisfile.a
include $(PREBUILT_STATIC_LIBRARY)

# ogg
include $(CLEAR_VARS)
LOCAL_MODULE := ogg
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libogg.a
include $(PREBUILT_STATIC_LIBRARY)

# TinyXml
include $(CLEAR_VARS)
LOCAL_MODULE := TinyXml
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libtinyxml.a
include $(PREBUILT_STATIC_LIBRARY)

# LibZzip
include $(CLEAR_VARS)
LOCAL_MODULE := LibZzip
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libzzip.a
include $(PREBUILT_STATIC_LIBRARY)

# LibZlib
include $(CLEAR_VARS)
LOCAL_MODULE := LibZlib
LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libzlib.a
include $(PREBUILT_STATIC_LIBRARY)

## OgreOggSound
#include $(CLEAR_VARS)
#LOCAL_MODULE := OgreOggSound
#LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libOgreOggSound.a
#include $(PREBUILT_STATIC_LIBRARY)

# iconv
#include $(CLEAR_VARS)
#LOCAL_MODULE := iconv
#LOCAL_SRC_FILES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib/libiconv.so
#include $(PREBUILT_SHARED_LIBRARY)

#---------------

include $(CLEAR_VARS) 

LOCAL_MODULE    := native-activity 

LOCAL_C_INCLUDES := $(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OIS \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OGRE \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/Ogaboo \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OGRE/RenderSystems \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/OGRE/RenderSystems/GLES2 \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/bullet \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/ogrebullet/Collisions \
					$(NDK_ROOT)/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/include/ogrebullet/Dynamics \
					/C/Users/Adriano/git/Ogaboo/headers

LOCAL_SRC_FILES := \
        $(subst $(LOCAL_PATH)/,, \
        $(wildcard $(LOCAL_PATH)/*.cpp))

LOCAL_STATIC_LIBRARIES := android_native_app_glue Ogaboo OgreRTShaderSystemStatic Plugin_ParticleFXStatic RenderSystem_GLES2Static OgreOggSound_Static vorbis_file vorbis ogg \
						mesa OgreBulletCollisions OgreBulletDynamics Bullet theora theora_player OgreTerrainStatic boost_filesystem \
						LuaCppInterface luacore CEGUI_Base CEGUICommonDialogs_Static CEGUI_Ogre_Renderer OgreMainStatic \
						libCEGUIOpenGLRenderer CEGUIFreeImageImageCodec_Static CEGUICoreWindowRendererSet_Static \
						CEGUITinyXMLParser_Static boost_system boost_thread LibZzip LibZlib FreeImage FreeType OIS TinyXml pcre openal cpufeatures Plugin_OgreVideo_static 
												 
#LOCAL_SHARED_LIBRARIES := OgreOggSound Plugin_OgreVideo
						
LOCAL_CPPFLAGS := -DOGRE_MAC_FRAMEWORK
LOCAL_WHOLE_STATIC_LIBRARIES := android_support
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2 
				
include $(BUILD_SHARED_LIBRARY) 

$(call import-module,android/native_app_glue) 
$(call import-module,android/cpufeatures)
$(call import-module,android/support)

