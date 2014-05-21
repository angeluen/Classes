//
//  PlayScene.h
//  TestCocos
//
//  Created by 김민준 on 2014. 4. 3..
//
//

#ifndef __TestCocos__PlayScene__
#define __TestCocos__PlayScene__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "extensions/cocos-ext.h"
#include "VisibleRect.h"
#include "Pillar.h"
#include <list>
#include <random>

#define PTM_RATIO 32.0

USING_NS_CC_EXT;
USING_NS_CC;
using namespace std;

class PlayScene : public Layer, b2ContactListener
{
private:
    float Random_Seed(int max, int min);
    
    Sprite *Player;
    Sprite *ReadyLogo;
    b2Body *p_body;
    
    Sprite *BGSprite[2];
    
    list<Pillar*> *p_Pillar;


    float Regen_Time;
    
    Size winSize;
    
    b2World *_world;

    bool IsDebug;
    bool IsStart;
    bool IsDelete;
public:
    static Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
    
    
    void update(float dt);
    
    void SetPhysics();
    
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    
    virtual void BeginContact(b2Contact *contact);
    
};
#endif /* defined(__TestCocos__PlayScene__) */
