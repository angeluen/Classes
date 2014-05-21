//
//  Object.h
//  TestCocos
//
//  Created by 김민준 on 2014. 4. 23..
//
//

#ifndef __TestCocos__Pillar__
#define __TestCocos__Pillar__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Pillar : public Node
{
private:
    Sprite *p_Pillar_down;
    Sprite *p_Pillar_up;
    
public:
    virtual bool init();
    
    void Update();
    
    static Pillar* create();
    
    bool getBoundingBoxUp(Sprite *target);

    Sprite *getUpSprite() {return p_Pillar_up; }
    Sprite *getDownSprite() {return p_Pillar_down; }
    
};

#endif /* defined(__TestCocos__Object__) */
