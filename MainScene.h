//
//  MainScene.h
//  TestCocos
//
//  Created by 김민준 on 2014. 4. 2..
//
//

#ifndef __TestCocos__MainScene__
#define __TestCocos__MainScene__

#include <iostream>
#include <cocos2d.h>

USING_NS_CC;

class MainScene : public cocos2d::Layer
{
private:
    
    
public:
    
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    
    void PlayCallBack(cocos2d::Ref* pSender);
    void OptionCallBack(cocos2d::Ref* pSender);
    void QuitCallBack(cocos2d::Ref* pSender);
    void HelpCallBack(cocos2d::Ref* pSender);
};
#endif /* defined(__TestCocos__MainScene__) */
