################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DotSceneLoader.cpp \
../GAbstractHandler.cpp \
../GBaseClass.cpp \
../OgreTheoraDataStream.cpp \
../OpenAL_AudioInterface.cpp \
../VideoClipManager.cpp 

OBJS += \
./DotSceneLoader.o \
./GAbstractHandler.o \
./GBaseClass.o \
./OgreTheoraDataStream.o \
./OpenAL_AudioInterface.o \
./VideoClipManager.o 

CPP_DEPS += \
./DotSceneLoader.d \
./GAbstractHandler.d \
./GBaseClass.d \
./OgreTheoraDataStream.d \
./OpenAL_AudioInterface.d \
./VideoClipManager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D_WIN32_WINNT=0x0601 -I"C:\MinGW\include\OIS" -I"C:\MinGW\include\BULLET" -I"C:\MinGW\include\OGRE" -I"C:\MinGW\include\theoraplayer" -I"C:\MinGW\include\AL" -I"C:\MinGW\include\OgreBullet" -I"C:\MinGW\include\OgreBullet\Dynamics" -I"C:\MinGW\include\OgreBullet\Collisions" -I"C:\MinGW\include" -I"C:\Users\Adriano\git\Ogaboo\headers" -O3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


