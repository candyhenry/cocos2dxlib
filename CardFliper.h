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

    //���ÿ�������
    void setSprIn(cocos2d::Node* pSprIn);
    //���ÿ��Ʊ���
    void setSprOut(cocos2d::Node* pSprOut);
    //���ûص�
    //void setListener(cocos2d::Ref* pTarget, cocos2d::SEL_CallFuncO pSelector);
    void setCallback(const flipFuncCB& callback) { _callBack = callback; }
    //��ת����
    void flipCard();
    //�Ƿ����ڷ�ת��
    bool isFliping();
    //�������ٴη�ת
    void setCanFlip( bool bCanFlip );
    //�ܷ�ת
    bool IsCardCanFlip() { return _bCanFlip; }
    //����
    cocos2d::Rect rect();
protected:
    void flipCallBack();
    void showCallBack();
private:
    //��������
    cocos2d::Node*                                  _pSprIn;
    //���Ʊ���
    cocos2d::Node*                                  _pSprOut;
    //�ص�����
    //cocos2d::Ref*                                   _pTarget;
    //�ص�����
    //cocos2d::SEL_CallFuncO                            _pSelector;
    //��ת�����ص�
    flipFuncCB                                      _callBack;
    //�ܷ��ٴη�ת
    bool                                              _bCanFlip;
};

#endif