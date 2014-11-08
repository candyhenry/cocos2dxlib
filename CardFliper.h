#ifndef _CardFliper_H__
#define _CardFliper_H__
#include "2d/CCNode.h"

class CardFliperNode
    :public cocos2d::Node
{
    CardFliperNode();
public:
    ~CardFliperNode();
    typedef std::function<void(cocos2d::Ref*)> flipFuncCB;
    CREATE_FUNC(CardFliperNode);

    virtual bool init(){ return true; }

    static CardFliperNode* create(
        cocos2d::Node* pSprIn, 
        cocos2d::Node* pSpOut, 
        cocos2d::Ref* pTarget, 
        cocos2d::SEL_CallFuncO pSelector);

    bool initWithData(
        cocos2d::Node* pSprIn, 
        cocos2d::Node* pSpOut, 
        cocos2d::Ref* pTarget, 
        cocos2d::SEL_CallFuncO pSelector);

    static CardFliperNode* create(
        cocos2d::Node* pSprIn,
        cocos2d::Node* pSprOut,
        flipFuncCB  callback
        );

    bool initWithData(
        cocos2d::Node* pSprIn,
        cocos2d::Node* pSprOut,
        flipFuncCB  callback
        );

    //设置卡牌正面
    void setSprIn(cocos2d::Node* pSprIn);
    //设置卡牌背面
    void setSprOut(cocos2d::Node* pSprOut);
    //设置回调
    //void setListener(cocos2d::Ref* pTarget, cocos2d::SEL_CallFuncO pSelector);
    void setCallback(const flipFuncCB& callback) { _callBack = callback; }
    //翻转卡牌
    void flipCard();
    //是否正在翻转中
    bool isFliping();
    //设置能再次翻转
    void setCanFlip( bool bCanFlip );
    //能否翻转
    bool IsCardCanFlip() { return _bCanFlip; }
    //矩形
    cocos2d::Rect rect();
protected:
    void flipCallBack();
    void showCallBack();
private:
    //卡牌正面
    cocos2d::Node*                                  _pSprIn;
    //卡牌背面
    cocos2d::Node*                                  _pSprOut;
    //回调设置
    //cocos2d::Ref*                                   _pTarget;
    //回调函数
    //cocos2d::SEL_CallFuncO                            _pSelector;
    //翻转函数回调
    flipFuncCB                                      _callBack;
    //能否再次翻转
    bool                                              _bCanFlip;
};

#endif