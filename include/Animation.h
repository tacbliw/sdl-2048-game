#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <memory>
#include <Block.h>

enum MODE
{
    X_TRAN,
    Y_TRAN
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
    double calculate(int elapsed, int duration);
    int propertyID() { return ID; }
    double initialValue() { return mPairs.front().value; }
    void add(int percent, double value);

};

class Animation
{
    friend class AnimationExecutor;
    public:
        Animation(int duration): mDuration(duration) {}
        virtual ~Animation();

        ValueTransition* createTransition(int ID);

    private:
        int mDelay;
        int mDuration;
        std::vector<ValueTransition *> mTransitions;
};

class Block;
class AnimationExecutor
{
public:
    AnimationExecutor(std::shared_ptr<Animation> animation, Block* blockTarget) : mAnimation(animation),
                                                                                  mAlive(true),
                                                                                  mElapsed(0),
                                                                                  mDuration(animation->mDuration),
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
    std::vector<ValueTransition *> &mTransitions;

};

#endif // ANIMATION_H
