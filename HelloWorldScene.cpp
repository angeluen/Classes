#include "HelloWorldScene.h"
#include "MainScene.h"
#include "PlayScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("BG_1.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(0,0));
    sprite->setAnchorPoint(Point(0,0));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    auto GameLogo = Sprite::create("Game_Logo.png");
    GameLogo->setAnchorPoint(Point(0, 0));
    GameLogo->setPosition(Point(155, 710));
    this->addChild(GameLogo);
    
    auto StartLogo = Sprite::create("Start_logo.png");
    StartLogo->setAnchorPoint(Point(0, 0));
    StartLogo->setPosition(Point(205, 545));
    this->addChild(StartLogo);
    
    
    //Touch Event
    _touchListener = EventListenerTouchAllAtOnce::create();
    
    
    _touchListener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    
    dispatcher->addEventListenerWithSceneGraphPriority( _touchListener, this);
    
    return true;
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches , Event* event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    Touch* touch;
    Point *location = new Point[touches.size()];
    
    for(int i=0; i<touches.size(); i++)
    {
        touch = (Touch*)(*it);
        location[i] = touch->getLocation();
        it++;
        
        CCLOG("location[%d] x=%f, y=%f", i, location[i].x, location[i].y);
    }
    Scene *pScene = PlayScene::createScene();
    TransitionFade *pFade = TransitionFade::create(1.f, pScene, Color3B::WHITE);
    Director::getInstance()->replaceScene(pFade);
    delete location;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
