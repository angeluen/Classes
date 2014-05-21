//
//  MainScene.cpp
//  TestCocos
//
//  Created by 김민준 on 2014. 4. 2..
//
//

#include "MainScene.h"
#include "PlayScene.h"
Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    layer->setScale(2.0f);
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto WinSize = Director::getInstance()->getWinSize();
    
    
    auto PlayItem = MenuItemImage::create("play-0.png",
                                           "play-1.png",
                                           CC_CALLBACK_1(MainScene::PlayCallBack, this));
    
    auto OptionItem = MenuItemImage::create("option-0.png",
                                            "option-1.png",
                                            CC_CALLBACK_1(MainScene::OptionCallBack, this));
    
    auto HelpItem = MenuItemImage::create("help-0.png", "help-1.png",
                                          CC_CALLBACK_1(MainScene::HelpCallBack, this));
    
    auto QuitItem = MenuItemImage::create("quit-0.png",
                                          "quit-1.png",
                                          CC_CALLBACK_1(MainScene::QuitCallBack, this));
    
	PlayItem->setPosition(Point(0,0));
    OptionItem->setPosition(Point(0,0));
    HelpItem->setPosition(Point(0,0));
    QuitItem->setPosition(Point(0,0));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(PlayItem, OptionItem, HelpItem, QuitItem, NULL);
    menu->alignItemsVertically();
    
    this->addChild(menu, 1);
    
    auto BgSprite = Sprite::create("BG_1.png");
    BgSprite->setPosition(WinSize.width/2, WinSize.height/2);
    this->addChild(BgSprite, -10);
    return true;
}

void MainScene::PlayCallBack(Ref *pSender)
{
    auto pScene = PlayScene::createScene();
    auto pFade = TransitionFade::create(2.0f, pScene, Color3B::WHITE);
    Director::getInstance()->replaceScene(pFade);
}

void MainScene::OptionCallBack(Ref *pSender)
{

}

void MainScene::HelpCallBack(Ref *pSender)
{
    
}

void MainScene::QuitCallBack(Ref *pSender)
{
    Director::getInstance()->end();
}
