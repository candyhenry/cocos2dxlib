#include "cocos2d.h"
USING_NS_CC;

#include "CardFliper.h"

CardFliperNode::CardFliperNode()
    :_pSprIn(nullptr)
    ,_pSprOut(nullptr)
    //,_pTarget(NULL)
    //,_pSelector(NULL)
    ,_callBack(nullptr)
    ,_bCanFlip(true)
{

}

CardFliperNode::~CardFliperNode()
{
    CC_SAFE_RELEASE(_pSprIn);
    CC_SAFE_RELEASE(_pSprOut);
}

CardFliperNode* CardFliperNode::create( cocos2d::Node* pSprIn, cocos2d::Node* pSpOut, cocos2d::Ref* pTarget, cocos2d::SEL_CallFuncO pSelector )
{
    CardFliperNode* pDataRet = new CardFliperNode();
    if (pDataRet && pDataRet->initWithData(pSprIn, pSpOut, pTarget, pSelector))
    {
        pDataRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pDataRet);
    }
    return pDataRet;
}

bool CardFliperNode::initWithData( cocos2d::Node* pSprIn, cocos2d::Node* pSpOut, cocos2d::Ref* pTarget, cocos2d::SEL_CallFuncO pSelector )
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! pSprIn || ! pSpOut);

        Size contentSize = pSpOut->getContentSize();
        addChild(pSprIn);
        CC_SAFE_RETAIN(pSprIn);
        _pSprIn = pSprIn;
        _pSprIn->setVisible(false);
        _pSprIn->setPosition(Vec2(contentSize.width/2, contentSize.height/2));
        
        addChild(pSpOut);
        pSpOut->setPosition(pSprIn->getPosition());
        CC_SAFE_RETAIN(pSpOut);
        _pSprOut = pSpOut;
        _pSprOut->setPosition(Vec2(contentSize.width/2, contentSize.height/2));


        //_pTarget = pTarget;
        //_pSelector = pSelector;

        setContentSize(contentSize);
        setAnchorPoint(Vec2(0.5f, 0.5f));

        bRet = true;
    } while (0);
    return bRet;
}

CardFliperNode* CardFliperNode::create(
    cocos2d::Node* pSprIn,
    cocos2d::Node* pSprOut,
    flipFuncCB  callback
    ){
        CardFliperNode* pDataRet = new CardFliperNode();
        if (pDataRet && pDataRet->initWithData(pSprIn, pSprOut, callback)){
            pDataRet->autorelease();
        }else{
            CC_SAFE_DELETE(pDataRet);
        }
        return pDataRet;
}

bool CardFliperNode::initWithData(
    cocos2d::Node* pSprIn,
    cocos2d::Node* pSprOut,
    flipFuncCB  callback
    ){
        bool bRet = false;
        do 
        {
            CC_BREAK_IF(! pSprIn || ! pSprOut);

            Size contentSize = pSprOut->getContentSize();
            addChild(pSprIn);
            CC_SAFE_RETAIN(pSprIn);
            _pSprIn = pSprIn;
            _pSprIn->setVisible(false);
            _pSprIn->setPosition(Vec2(contentSize.width/2, contentSize.height/2));

            addChild(pSprOut);
            pSprOut->setPosition(pSprIn->getPosition());
            CC_SAFE_RETAIN(pSprOut);
            _pSprOut = pSprOut;
            _pSprOut->setPosition(Vec2(contentSize.width/2, contentSize.height/2));

            setContentSize(contentSize);
            setAnchorPoint(Vec2(0.5f, 0.5f));
            bRet = true;
        } while (0);
        return bRet;
}

void CardFliperNode::setSprIn( cocos2d::Node* pSprIn )
{
    Size contentSize = getContentSize();
    if (pSprIn != _pSprIn)
    {
        if (pSprIn)
        {
            addChild(pSprIn);
            CC_SAFE_RETAIN(pSprIn);
            pSprIn->setVisible(false);
            pSprIn->setPosition(contentSize* 0.5);
        }
        if (_pSprIn)
        {
            removeChild(_pSprIn, true);
            CC_SAFE_RELEASE(_pSprIn);
        }
        _pSprIn = pSprIn;
    }
}

void CardFliperNode::setSprOut( cocos2d::Node* pSprOut )
{
    Size contentSize = getContentSize();
    if (pSprOut != _pSprOut)
    {
        if (pSprOut)
        {
            addChild(pSprOut);
            CC_SAFE_RETAIN(pSprOut);
            pSprOut->setPosition(contentSize * 0.5f );
        }
        if (_pSprOut)
        {
            removeChild(_pSprOut, true);
            CC_SAFE_RELEASE(_pSprOut);
        }
        _pSprOut = pSprOut;
    }
}

//void CardFliperNode::setListener( cocos2d::Ref* pTarget, cocos2d::SEL_CallFuncO pSelector )
//{
//    _pTarget = pTarget;
//    _pSelector = pSelector;
//}

void CardFliperNode::flipCard()
{
    if (_bCanFlip)
    {
        _bCanFlip = false;
        auto pOrbitCamera = OrbitCamera::create(0.5f, 1, 0, 0.0f, 90.0f, 0, 0);
        auto pHide = Hide::create();
        //auto pFunc = CallFunc::create(this, callfunc_selector(CardFliperNode::flipCallBack));
        auto pFunc = CallFunc::create(CC_CALLBACK_0(CardFliperNode::flipCallBack, this));
        auto pAction = Sequence::create(pOrbitCamera, pHide, pFunc, NULL);
        _pSprOut->runAction(pAction);
    }
}

bool CardFliperNode::isFliping()
{
    bool bRet = false;
    do 
    {
        bRet = (_pSprIn->getNumberOfRunningActions()+ _pSprOut->getNumberOfRunningActions()) > 0 ? true : false;
    } while (0);
    return bRet;
}


void CardFliperNode::setCanFlip( bool bCanFlip )
{
    _bCanFlip = bCanFlip;
}

cocos2d::Rect CardFliperNode::rect()
{
    return Rect( _position.x - _contentSize.width * _anchorPoint.x,
        _position.y - _contentSize.height * _anchorPoint.y,
        _contentSize.width, _contentSize.height);
}

void CardFliperNode::flipCallBack()
{
    auto show = Show::create();
    auto camera = OrbitCamera::create(0.5f, 1, 0, 270.0f, 90.0f, 0, 0);
    //auto pFunc = CCCallFunc::create(this, callfunc_selector(CardFliperNode::showCallBack));
    auto pFunc = CallFunc::create(CC_CALLBACK_0(CardFliperNode::showCallBack, this));

    auto pAction = Sequence::create(show,camera,pFunc, NULL);
    _pSprIn->runAction(pAction);

}

void CardFliperNode::showCallBack()
{
    CC_SWAP(_pSprIn, _pSprOut, Node*);
    //if (_pTarget && _pSelector)
    //{
    //    (_pTarget->*_pSelector)(this);
    //}
    if (_callBack){
        _callBack(this);
    }
}
