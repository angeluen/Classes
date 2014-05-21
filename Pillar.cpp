//
//  Object.cpp
//  TestCocos
//
//  Created by 김민준 on 2014. 4. 23..
//
//

#include "Pillar.h"


bool Pillar::init()
{
    p_Pillar_down = Sprite::create("Pillar_Down.png");
    p_Pillar_up = Sprite::create("Pillar_Up.png");
    
    p_Pillar_down->setAnchorPoint(Point(0, 0));
    p_Pillar_up->setAnchorPoint(Point(0, 0));
    
    p_Pillar_down->setPosition(0, 0);
    p_Pillar_up->setPosition(0, 1000);
    
    this->addChild(p_Pillar_down);
    this->addChild(p_Pillar_up);
    
    return true;
}

Pillar* Pillar::create()
{
    Pillar *node = new Pillar;
    node->init();
    node->autorelease();
    return node;
}


bool Pillar::getBoundingBoxUp(Sprite *target)
{
    if(target->getBoundingBox().intersectsRect(p_Pillar_up->getBoundingBox())
       || target->getBoundingBox().intersectsRect(p_Pillar_down->getBoundingBox()))
       {
           return true;
        
       }
    

    return false;
}
