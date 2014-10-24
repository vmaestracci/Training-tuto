#include "AnimationHandler.h"

void AnimationHandler::update(const float dt)
{
    if(mCurrentAnim >= mAnimations.size() || mCurrentAnim < 0)
        return;

    float duration = mAnimations[mCurrentAnim].mDuration;

    if(static_cast<int>( (mTime+dt)/duration ) > static_cast<int>( mTime/duration ))
    {
        int frameNumber = static_cast<int>( (mTime+dt)/duration );

        frameNumber %= mAnimations[mCurrentAnim].getLength();

        sf::IntRect rect = mFrameSize;
        rect.left = rect.width*frameNumber;
        rect.top = rect.height*mCurrentAnim;

        mBounds = rect;
    }

    mTime += dt;

    if(mTime > duration*mAnimations[mCurrentAnim].getLength())
        mTime = 0.0f;
}

void AnimationHandler::addAnim(Animation& anim)
{
    mAnimations.push_back(anim);
}

void AnimationHandler::changeAnim(unsigned int animID)
{
    if(mCurrentAnim == animID || animID >= mAnimations.size() || animID < 0)
        return;

    mCurrentAnim = animID;

    sf::IntRect rect = mFrameSize;
    rect.top = rect.height*animID;
    mBounds = rect;

    mTime = 0.0f;
}

