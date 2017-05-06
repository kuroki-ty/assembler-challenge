#include "HelloWorldScene.h"
#include "Example1.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _label = Label::createWithTTF("Answer", "fonts/Marker Felt.ttf", 64);
    _label->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/2));
    this->addChild(_label, 1);

    return true;
}

void HelloWorld::onEnter()
{
    auto example = new Example1();
    int answer = example->calcAnswer();
    _label->setString(std::to_string(answer));
}
