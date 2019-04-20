#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <memory>
#include <Block.h>

enum TimingFunction
{
	TMFUNC_LINEAR,
	TMFUNC_EASE,
	TMFUNC_EASE_IN,
	TMFUNC_EASE_OUT,
	TMFUNC_EASE_IN_OUT
};

class ValueTransition
{
private:
    struct PercentValuePair
    {
        int percent;
        double value;
    };
    int ID;
    std::vector<PercentValuePair> mPairs;
public:
    ValueTransition(int ID) : ID(ID) {}
    double calculate(int elapsed, int duration, TimingFunction timingFunc);
    int propertyID() { return ID; }
    double initialValue() { return mPairs.front().value; }
    void add(int percent, double value);

};

class Animation
{
    friend class AnimationExecutor;
    public:
        Animation(int duration, TimingFunction timeFunc, int delay = 0): mDuration(duration),
                                                                         mTimingFunc(timeFunc),
                                                                         mDelay(delay) {}
        virtual ~Animation();

        ValueTransition* createTransition(int ID);

    private:
        int mDelay;
        int mDuration;
        TimingFunction mTimingFunc;
        std::vector<ValueTransition *> mTransitions;
};

class Block;
class AnimationExecutor
{
public:
    AnimationExecutor(std::shared_ptr<Animation> animation, Block* blockTarget) : mAnimation(animation),
                                                                                  mAlive(true),
                                                                                  mElapsed(-animation->mDelay),
                                                                                  mDuration(animation->mDuration),
                                                                                  mTimingFunction(animation->mTimingFunc),
                                                                                  mTransitions(animation->mTransitions),
                                                                                  mBlockTarget(blockTarget) {}
    void init();
    void progress(int delta_ms);
    void end();

    bool alive() { return mAlive; }
    ~AnimationExecutor() { end(); }

private:
    std::shared_ptr<Animation> mAnimation;
    Block *mBlockTarget;
    bool mAlive;
    int mElapsed;
    int mDuration;
    TimingFunction mTimingFunction;
    std::vector<ValueTransition *> &mTransitions;

};

#endif // ANIMATION_H
