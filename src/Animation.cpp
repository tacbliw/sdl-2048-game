#include "Animation.h"
#include "Block.h"

Animation::~Animation()
{
    //dtor
}

double Animation::calculate(int elapsed, int duration)
{
    auto iter = infoTrans.cbegin();

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

void Animation::add(int percent, double value)
{
    TranstionInformation ti;
    ti.percent = percent;
    ti.value = value;
    infoTrans.push_back(ti);
}


void Animation::progress(int delta_ms)
{
    if (!mAlive)
        return;

    mElapsed += delta_ms;
    if (mElapsed < 0)
        return;
    if (mElapsed > mDuration)
        mAlive = false;
    // for (auto iter = mTransitions.cbegin(); iter != mTransitions.cend(); iter++)
    // {
        //printf("set ID = %d, value = %f\n", (*iter)->propertyID(), (*iter)->calculate(mElapsed, mDuration, mTimingFunction));
    if (mMode == X_TRAN)
        mBlockTarget->set_mX(calculate(mElapsed, mDuration));
    else
        mBlockTarget->set_mY(calculate(mElapsed, mDuration));
    // }
}

void Animation::init()
{
    if (mMode == X_TRAN)
        mBlockTarget->set_mX(infoTrans.front().value);
    else
        mBlockTarget->set_mY(infoTrans.front().value);
}

void Animation::end()
{
    mElapsed = 0;
    progress(mDuration);
}
