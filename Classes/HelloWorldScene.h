#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onEnter();
    
    CREATE_FUNC(HelloWorld);

private:
    cocos2d::Label* _label;
};

#endif // __HELLOWORLD_SCENE_H__
