#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
    public:
         Animation(unsigned int startFrame, unsigned int endFrame, float duration) :
             mStartFrame(startFrame),
             mEndFrame(endFrame),
             mDuration(mDuration)
         {}

    public:
        unsigned int getLength() { return mEndFrame - mStartFrame + 1; }

    public:
        unsigned int mStartFrame;
        unsigned int mEndFrame;
        float mDuration;
};

class AnimationHandler
{
    public:

        AnimationHandler() :
            mTime(0),
            mCurrentAnim(-1)
        {
        }

        AnimationHandler(const sf::IntRect& frameSize) :
            mTime(0),
            mCurrentAnim(-1),
            mFrameSize(frameSize)
        {
        }

    public:

        void update(const float dt);
        void addAnim(Animation& anim);
        void changeAnim(unsigned int animID);

    public:

        sf::IntRect mBounds;
        sf::IntRect mFrameSize;

    private:
        std::vector<Animation> mAnimations;
        float mTime; // Time since animation started
        int mCurrentAnim;
};

#endif // ANIMATIONHANDLER_H
