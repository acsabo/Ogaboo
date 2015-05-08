/*
 * Ogaboo (Open Game Bootstrap) 1.0
 * https://sourceforge.net/projects/ogaboo/
 *
 * Copyright (c) 2014 Adriano de Castro Sabo
 * acsabo@hotmail.com
 *
 * Licensed under http://opensource.org/licenses/MIT
 */

#include "VideoClipManager.h"
#include "OgreTheoraDataStream.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

using namespace Ogre;
using namespace Acsabo;

VideoClipManager::VideoClipManager(OgreOggSound::OgreOggSoundManager* mSoundManager)
{
	iface_factory = new OpenAL_AudioInterfaceFactory(mSoundManager->getOpenalDevice());
	setAudioInterfaceFactory(iface_factory);
}

VideoClipManager::~VideoClipManager()
{
    delete iface_factory;
}

int nextPow2(int x)
{
    int y;
    for (y=1;y<x;y*=2);
    return y;
}

TheoraVideoClip* VideoClipManager::load(std::string mInputFileName, std::string material_name)	{
    std::string name=mInputFileName;
    std::string group_name=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

    int mTechniqueLevel=0;
    int mPassLevel=0;
    int mStateLevel=0;

    TheoraVideoClip* clip=createVideoClip(new OgreTheoraDataStream(mInputFileName,group_name),TH_BGRX,0,0);
    int w=clip->getWidth(),h=clip->getHeight();

    TexturePtr t = TextureManager::getSingleton().createManual(name,group_name,TEX_TYPE_2D,w,h,1,0,PF_X8R8G8B8,TU_DYNAMIC_WRITE_ONLY);

    if (t->getFormat() != PF_X8R8G8B8) cout << "ERROR: Pixel format is not X8R8G8B8 which is what was requested!";
    // clear it to black

    unsigned char* texData=(unsigned char*) t->getBuffer()->lock(HardwareBuffer::HBL_DISCARD);
    memset(texData,0,w*h*4);
    t->getBuffer()->unlock();
    mTextures[name]=t;

    // attach it to a material
    MaterialPtr material = MaterialManager::getSingleton().getByName(material_name);
    TextureUnitState* ts = material->getTechnique(mTechniqueLevel)->getPass(mPassLevel)->getTextureUnitState(mStateLevel);

    //Now, attach the texture to the material texture unit (single layer) and setup properties
    ts->setTextureName(name,TEX_TYPE_2D);
    ts->setTextureFiltering(FO_LINEAR, FO_LINEAR, FO_NONE);
    ts->setTextureAddressingMode(TextureUnitState::TAM_WRAP);

    return clip;
}

bool VideoClipManager::draw(const Ogre::FrameEvent& evt)
{
    if (evt.timeSinceLastFrame > 0.3f)
     update(0.3f);
    else
      update(evt.timeSinceLastFrame);

    // update playing videos
    std::vector<TheoraVideoClip*>::iterator it;
    TheoraVideoFrame* f;
    for (it=mClips.begin();it!=mClips.end();it++)
    {
     f=(*it)->getNextFrame();
     if (f)
     {
        int w=f->getWidth(),h=f->getHeight();
        TexturePtr t=mTextures[(*it)->getName()];

        unsigned char *texData=(unsigned char*) t->getBuffer()->lock(HardwareBuffer::HBL_DISCARD);
        unsigned char *videoData=f->getBuffer();

        memcpy(texData,videoData,w*h*4);

        t->getBuffer()->unlock();
        (*it)->popFrame();
     }
    return true;
    }
}
