//
//  PlayScene.cpp
//  TestCocos
//
//  Created by 김민준 on 2014. 4. 3..
//
//

#include "PlayScene.h"


Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool PlayScene::init()
{
    if(!Layer::create())
        return false;
    
    winSize = Director::getInstance()->getWinSize();
    
   
    p_Pillar = new list<Pillar*>();
    
    
  
    Regen_Time = 0.f;
    IsStart = false;
    IsDelete = false;
    
    for(int i=0; i<2; i++)
    {
        BGSprite[i] = Sprite::create("BG_1.png");
        BGSprite[i]->setPosition(Point(i * winSize.width,0));
        BGSprite[i]->setAnchorPoint(Point(0,0));
        this->addChild(BGSprite[i], 0);
    
    }
    
    ReadyLogo = Sprite::create("Start_logo.png");
    ReadyLogo->setPosition(Point(205, 400));
    ReadyLogo->setAnchorPoint(Point(0, 0));
    this->addChild(ReadyLogo, 20);
    
    this->SetPhysics();
   
    ///////////////// SetPlayer Body ////////////////////
    Player = Sprite::create("Bird_1.png");
    Player->setPosition(winSize.width / 2, winSize.height / 2);
    
    auto p_animation = Animation::create();
    p_animation->setDelayPerUnit(0.1f);
    
    for(int i=1; i<=3; i++)
    {
        char str[100];
        sprintf(str, "Bird_%d.png", i);
        p_animation->addSpriteFrameWithFile(str);
    }
    auto p_Animate = Animate::create(p_animation);
    auto Repeat_Animation = RepeatForever::create(p_Animate);
    Player->runAction(Repeat_Animation);
    
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(Player->getPositionX()/PTM_RATIO, Player->getPositionY()/PTM_RATIO);
    
    p_body = _world->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);
    
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 2.f;
    fixtureDef.friction = 0.001f;
    p_body->CreateFixture(&fixtureDef);
    /////////////////////////////////////////////////////
    
    
    this->addChild(Player, 10);
    

    
    //Touch Event
    
    auto _touchListener = EventListenerTouchAllAtOnce::create();
    
    
    _touchListener->onTouchesBegan = CC_CALLBACK_2(PlayScene::onTouchesBegan, this);
    
    EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
    
    dispatcher->addEventListenerWithSceneGraphPriority( _touchListener, this);
    
    
    return true;
    
}

void PlayScene::update(float dt)
{
    
    Regen_Time += dt;
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
   
    _world->Step(dt, velocityIterations, positionIterations);

    Player->setPosition(
               p_body->GetPosition().x * PTM_RATIO,
               p_body->GetPosition().y * PTM_RATIO);
    
    
    for(int i=0; i<2; i++)
    {
        if(BGSprite[i]->getPositionX() <= -winSize.width)
        {
            BGSprite[i]->setPosition(winSize.width, BGSprite[i]->getPositionY());
        }
        
        BGSprite[i]->setPosition(BGSprite[i]->getPositionX() - 5, BGSprite[i]->getPositionY());
    }
    
    
    
    if(Regen_Time >= 2.f)
    {
        Pillar *pi = Pillar::create();
        
        pi->setPosition(800,this->Random_Seed(0, -600));
        this->addChild(pi, 10);
        p_Pillar->push_back(pi);
        
        Regen_Time = 0.f;
        
        
    }

    list<Pillar*>::iterator p_it;
    for(p_it = p_Pillar->begin(); p_it != p_Pillar->end(); p_it++)
    {
        Point DownPosition = (*p_it)->getDownSprite()->getPosition() + (*p_it)->getPosition();
        
        Rect DownBounding = Rect(DownPosition.x, DownPosition.y,
                DownPosition.x + 81,
                DownPosition.y + 721);
        // 81 721
        
        Point UpPosition = (*p_it)->getUpSprite()->getPosition() + (*p_it)->getPosition();
        
        Rect UpBounding = Rect(UpPosition.x, UpPosition.y,
                    UpPosition.x + 86,
                    UpPosition.y + 732);
        
        // 86 732
        
        if((*p_it)->getPositionX() < - 100)
        {
            p_Pillar->erase(p_it);
            
            
        }
        if(Player->getBoundingBox().intersectsRect(DownBounding) || Player->getBoundingBox().intersectsRect(UpBounding))
        {
            CCLOG("Bound");
            this->unscheduleUpdate();
        }
        
        (*p_it)->setPosition((*p_it)->getPositionX() - 5, (*p_it)->getPositionY());
        
    }
    

 
    
    
}

void PlayScene::SetPhysics()
{
    b2Vec2 gravity;
    
	gravity.Set(0.0f, -40.f);
    
	_world = new b2World(gravity);
    
	_world->SetAllowSleeping(true);
	
	_world->SetContinuousPhysics(true);
    
	_world->SetContactListener( this );
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    //_debugDraw->SetFlags(flags);
    
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    
    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    
}

void PlayScene::BeginContact(b2Contact *contact)
{
    if(contact->GetFixtureA() == p_body->GetFixtureList() || contact->GetFixtureB() == p_body->GetFixtureList())
    {
        //this->unscheduleUpdate();
    }
}

void PlayScene::onTouchesBegan(const std::vector<Touch*>& touches , Event* event)
{
    std::vector<Touch*>::const_iterator it = touches.begin();
    Touch* touch;
    Point *location = new Point[touches.size()];

    
    if(IsStart == false)
    {
        ReadyLogo->setVisible(false);
        IsStart = true;
        this->scheduleUpdate();
    }
    
    p_body->SetLinearVelocity(b2Vec2(0, 0));
    p_body->ApplyForce(b2Vec2(0, 1000), b2Vec2(0, 0), true);

    for(int i=0; i<touches.size(); i++)
    {
        touch = (Touch*)(*it);
        location[i] = touch->getLocation();
        it++;
        
        //CCLOG("location[%d] x=%f, y=%f", i, location[i].x, location[i].y);
    }
    
    

}

float PlayScene::Random_Seed(int max, int min)
{
    std::random_device rd;
    std::mt19937 rEngine(rd());
    std::uniform_real_distribution<>dist(min, max);

    auto result = dist(rEngine);
    
    return result;
    
    
}