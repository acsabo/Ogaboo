#ifndef VIDEOCLIPMANAGER_H
#define VIDEOCLIPMANAGER_H
#include <string>
#include <map>

#include <theoraplayer/TheoraVideoManager.h>
#include <theoraplayer/TheoraVideoClip.h>
#include <theoraplayer/TheoraVideoFrame.h>
#include <theoraplayer/TheoraDataSource.h>

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreTextureManager.h>
#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreMaterial.h>
#include <OGRE/OgreTechnique.h>

#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreHardwarePixelBuffer.h>

#include "OpenAL_AudioInterface.h"
#include "OgreOggSoundManager.h"

//copia do OPENGL gl.h <mudar isso>
#define GL_RGB 0x1907

namespace Acsabo {

    class VideoClipManager : public TheoraVideoManager
    {
        std::map<std::string,Ogre::TexturePtr> mTextures;
        private:
            TheoraOutputMode outputMode = TH_RGB;
            unsigned int textureFormat = GL_RGB;
        public:
            OpenAL_AudioInterfaceFactory* iface_factory;
            VideoClipManager(OgreOggSound::OgreOggSoundManager* mSoundManager);
            virtual ~VideoClipManager();
            TheoraVideoClip* load(std::string file, std::string material_name);
            bool draw(const Ogre::FrameEvent& evt);
        protected:

    };
}
#endif // VIDEOCLIPMANAGER_H
