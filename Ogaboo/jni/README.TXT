FROM Msys console type:
$ cd <profile>/git/ogaboo-code/Ogaboo/jni/
i.e -> $ cd /c/Users/a.sabo/git/ogaboo-code/Ogaboo/jni/
$ ndk-build
[armeabi] Cygwin         : Generating dependency file converter script
[armeabi] Compile++ thumb: Ogaboo <= DotSceneLoader.cpp
[armeabi] Compile++ thumb: Ogaboo <= GAbstractHandler.cpp
[armeabi] Compile++ thumb: Ogaboo <= GBaseClass.cpp
[armeabi] Compile++ thumb: Ogaboo <= OgreTheoraDataStream.cpp
[armeabi] Compile++ thumb: Ogaboo <= OpenAL_AudioInterface.cpp
c:/Users/Adriano/git/ogaboo-code/Ogaboo/jni/../OpenAL_AudioInterface.cpp: In des
tructor 'virtual OpenAL_AudioInterface::~OpenAL_AudioInterface()':
c:/Users/Adriano/git/ogaboo-code/Ogaboo/jni/../OpenAL_AudioInterface.cpp:43:37:
warning: passing NULL to non-pointer argument 3 of 'void alSourcei(ALuint, ALenu
m, ALint)' [-Wconversion-null]
   alSourcei(mSource, AL_BUFFER, NULL);
                                     ^
[armeabi] Compile++ thumb: Ogaboo <= VideoClipManager.cpp
[armeabi] StaticLibrary  : libOgaboo.a

$ export NDK_ROOT=/c/android/android-ndk-r10c

$ cp ../obj/local/armeabi/libOgaboo.a $NDK_ROOT/toolchains/arm-linux-androideabi-4.8/prebuilt/windows/user/lib