#include "GameClassic.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "Ball.h"
#include "HelperFunctions.h"


USING_NS_CC;
using namespace std;

bool GameClassic::init() {
    if (!LayerColor::initWithColor(Color4B::ORANGE)) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto label = Label::createWithTTF("Game: Classic", "fonts/Marker Felt.ttf", 24);
    label->setPosition(
            Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label);

    drawingNode = DrawNode::create();
    addChild(drawingNode);
    InitialGameArea();
    InitialBall();

    RenderSegment();




    return true;
}

void GameClassic::InitialGameArea() {
    const auto center = GetGameAreaCenter();
    const auto SEG_LEN = GetGameAreaSquareWidth();
    ///////////////// Transparent Square Background (Game Area Shadow)
    drawingNode->drawSolidRect(center + Vec2(-SEG_LEN, -SEG_LEN), center + Vec2(+SEG_LEN, +SEG_LEN),
                               Color4F(50, 50, 50, 0.4));
    /////////////////
    //CreateShape_InitialSquare();
    //CreateShape_InitialSquare();
    CreateShape_Custom1();
}

Vec2 GameClassic::GetGameAreaCenter() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = origin + visibleSize / 2 + Vec2(0, visibleSize.height / 8.0);
    return center;
}

int GameClassic::GetGameAreaSquareWidth() {
    return 270;
}

void GameClassic::RenderSegment() {
    for (pair<Vec2, Vec2> &seg: _segments)
        drawingNode->drawSegment(seg.first, seg.second, 3, Color4F::BLACK);
}

void GameClassic::CreateShape_InitialSquare() {

    const auto center = GetGameAreaCenter();
    const auto SEG_LEN = GetGameAreaSquareWidth();

    _segments.clear();
    _segments.push_back(make_pair(center + Vec2(-SEG_LEN, +SEG_LEN), center + Vec2(+SEG_LEN, +SEG_LEN)));
    _segments.push_back(make_pair(center + Vec2(+SEG_LEN, +SEG_LEN), center + Vec2(+SEG_LEN, -SEG_LEN)));
    _segments.push_back(make_pair(center + Vec2(+SEG_LEN, -SEG_LEN), center + Vec2(-SEG_LEN, -SEG_LEN)));
    _segments.push_back(make_pair(center + Vec2(-SEG_LEN, -SEG_LEN), center + Vec2(-SEG_LEN, +SEG_LEN)));
}

void GameClassic::CreateShape_Custom1() {
    const auto center = GetGameAreaCenter();
    const auto SEG_LEN = GetGameAreaSquareWidth();

    _segments.clear();
    _segments.push_back(make_pair(center + Vec2(-SEG_LEN, +SEG_LEN), center + Vec2(+SEG_LEN, +SEG_LEN)));
    _segments.push_back(make_pair(center + Vec2(+SEG_LEN, +SEG_LEN), center + Vec2(+SEG_LEN, -SEG_LEN)));
    _segments.push_back(make_pair(center + Vec2(+SEG_LEN, -SEG_LEN), center + Vec2(0, -SEG_LEN)));
    _segments.push_back(make_pair(center + Vec2(0, -SEG_LEN), center + Vec2(0, 0)));
    _segments.push_back(make_pair(center + Vec2(0, 0), center + Vec2(-SEG_LEN, 0)));
    _segments.push_back(make_pair(center + Vec2(-SEG_LEN, 0), center + Vec2(-SEG_LEN, +SEG_LEN)));
}

void GameClassic::InitialBall() {
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _ball = Ball::create("ball.png", &_segments);
    _ball->setPosition(GetGameAreaCenter() + Vec2(100, 100));
    _ball->SetVelocity(Vec2(500,110));
    addChild(_ball);

    schedule([&](float dt)
    {
        _ball->MoveBall(dt);
        }, 1.0/60, "ball_tick");

//    schedule([&](float dt)
//             {
//                 _ball->SetVelocity(Vec2((GetRand01()-0.5)*120, (GetRand01()-0.5)*120));
//             }, 1, "ball_tick_velo");

}