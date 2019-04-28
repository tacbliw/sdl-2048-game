#include "Animation.h"
#include "Block.h"

Animation::~Animation()
{
    //dtor
}

double ValueTransition::calculate(int elapsed, int duration)
{
    auto iter = mPairs.cbegin();

//    for (int i = 0; i < mPairs.size(); i++)
//    {
//        printf("%f ", iter->value);
//    }
//    printf("\n");

    while (elapsed * 100 / duration >= (iter + 1)->percent)
    {
        iter++;
        if (iter->percent == 100)
            return iter->value;
    }
    return iter->value + (elapsed * 100 / duration)/100.0 * ((iter + 1)->value - iter->value);
}

void ValueTransition::add(int percent, double value)
{
    PercentValuePair p;
    p.percent = percent;
    p.value = value;
    mPairs.push_back(p);
}

void AnimationExecutor::progress(int delta_ms)
{
    if (!mAlive)
        return;

    mElapsed += delta_ms;
    if (mElapsed < 0)
        return;
    if (mElapsed > mDuration)
        mAlive = false;
    for (auto iter = mTransitions.cbegin(); iter != mTransitions.cend(); iter++)
    {
        //printf("set ID = %d, value = %f\n", (*iter)->propertyID(), (*iter)->calculate(mElapsed, mDuration, mTimingFunction));
        mBlockTarget->setProperty((*iter)->propertyID(), (*iter)->calculate(mElapsed, mDuration));
    }
}

void AnimationExecutor::init()
{
    for (auto iter = mTransitions.cbegin(); iter != mTransitions.cend(); iter++)
    {
        mBlockTarget->setProperty((*iter)->propertyID(), (*iter)->initialValue());
    }
}

void AnimationExecutor::end()
{
    mElapsed = 0;
    progress(mDuration);
}

/////
ValueTransition* Animation::createTransition(int ID)
{
    ValueTransition *vt = new ValueTransition(ID);
    mTransitions.push_back(vt);
    return vt;
}
/////
