/*------------------------------------------------------------------------------
*  DotScene.h
*
*  This file provides some methods for the parsing of a .scene file, with
*  support for userData.
*
*  http://code.google.com/p/project-pr/source/browse/#svn%2Ftrunk%2Fportal_adaptation%2Fsrc%2Fmodel%2Fdotscene
*------------------------------------------------------------------------------*/

#ifndef DOT_SCENE_H
#define DOT_SCENE_H

#include <tinyxml.h>
#include <OGRE/Ogre.h>

class nodeProperty
{
public:
    Ogre::String nodeName;
    Ogre::String propertyNm;
    Ogre::String valueName;
    Ogre::String typeName;

    nodeProperty(Ogre::String node,Ogre::String propertyName,Ogre::String value,Ogre::String type)
    {
        nodeName = node;
        propertyNm = propertyName;
        valueName = value;
        typeName = type;
    }
};

class CDotScene
{
public:
    CDotScene() : mSceneMgr(0) {}
    virtual ~CDotScene() {}

    void parseDotScene( const Ogre::String &SceneName, const Ogre::String& groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *pAttachNode = NULL, Ogre::String sPrependNode = "");
    Ogre::String getProperty(Ogre::String ndNm, Ogre::String prop);

    std::vector<nodeProperty> nodeProperties;
    Ogre::SceneManager *getScemeManager()
    {
    	return mSceneMgr;
    }
protected:
    void processNode(TiXmlElement *XMLNode, Ogre::SceneNode *pAttach);
    Ogre::SceneManager *mSceneMgr;
    Ogre::String m_sPrependNode;
};

#endif
