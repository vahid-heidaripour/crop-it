#include "MainMenu.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#include "GameClassic.h"
#include "GameOptions.h"
#include "UserData.h"
#include "HelperFunctions.h"

USING_NS_CC;

bool MainMenu::init()
{
    if ( !LayerColor::initWithColor(Color4B::RED))
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gameNmaeLabel = Label::createWithSystemFont("CropIt!", GameOptions::getInstance()->getMainFont(), 36);
    gameNmaeLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - gameNmaeLabel->getContentSize().height));
    addChild(gameNmaeLabel);

    auto bestScoreLabel = Label::createWithSystemFont("Best Score",
            GameOptions::getInstance()->getMainFont(), 30);
    bestScoreLabel->setPosition(visibleSize / 2 + Size(0.0f, visibleSize.height / 3));
    addChild(bestScoreLabel);

    auto scoreLabel = Label::createWithSystemFont(ToString(UserData::getInstance()->getHighScore()),
            GameOptions::getInstance()->getMainFont(), 34);
    scoreLabel->setPosition(visibleSize / 2 + Size(0.0f, visibleSize.height / 4));
    addChild(scoreLabel);

    auto playButton = ui::Button::create("PlayButton.png");
    playButton->setPosition(origin+visibleSize/2);
    playButton->addClickEventListener([&](Ref* sender){
        auto classic = GameClassic::create();
        auto scene = Scene::create();
        scene->addChild(classic);
        Director::getInstance()->replaceScene(scene);
    });
    addChild(playButton);
    playButton->setScale(2.0f);

    return true;
}
