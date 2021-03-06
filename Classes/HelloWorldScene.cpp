#include "HelloWorldScene.h"
#include "Example1.h"
#include "Example2.h"
#include "Example3.h"

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
    std::string answer = "";

/*** Example1
    auto example1 = new Example1();
    answer = std::to_string(example1->calcAnswer());
 ***/
/*** Example2
    auto example2 = new Example2();
    answer = example2->calcAnswer();
 ***/

    auto example3 = new Example3();
    answer = example3->calcAnswer();

    _label->setString(answer);
}
