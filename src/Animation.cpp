#include "Animation.h"
#include "UnitBezier.h"
#include "Block.h"

static UnitBezier bezier_ease(0.25, 0.1, 0.25, 1.0);
static UnitBezier bezier_easeIn(0.42, 0.0, 1.0, 1.0);
static UnitBezier bezier_easeOut(0.0, 0.0, 0.58, 1.0);
static UnitBezier bezier_easeInOut(0.42, 0.0, 0.58, 1.0);

inline double timing(TimingFunction timingFunc, int duration, double input)
{
	switch(timingFunc) {
	case TMFUNC_LINEAR:
		return input;
	case TMFUNC_EASE:
		return bezier_ease.solve(input, duration);
	case TMFUNC_EASE_IN:
		return bezier_easeIn.solve(input, duration);
	case TMFUNC_EASE_OUT:
		return bezier_easeOut.solve(input, duration);
	case TMFUNC_EASE_IN_OUT:
		return bezier_easeInOut.solve(input, duration);
	default:
		// avoid warning
		return 0.0;
	}
}

inline double interploate(double from, double to, double radio)
{
    return from + (to - from) * radio;
}

Animation::~Animation()
{
    //dtor
}

double ValueTransition::calculate(int elapsed, int duration, TimingFunction timingFunc)
{
    auto iter = mPairs.cbegin();

    while (elapsed * 100 / duration >= (iter + 1)->percent)
    {
        iter++;
        if (iter->percent == 100)
            return iter->value;
    }

    auto next = iter + 1;
    auto offset = elapsed - iter->percent / 100.0 * duration;
    auto percent_diff = next->percent - iter->percent;
    auto interval = percent_diff / 100.0 * duration;

    return interploate(iter->value, next->value, timing(timingFunc, duration, offset/interval));
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
        printf("set ID = %d, value = %f\n", (*iter)->propertyID(), (*iter)->calculate(mElapsed, mDuration, mTimingFunction));
        mBlockTarget->setProperty((*iter)->propertyID(), (*iter)->calculate(mElapsed, mDuration, mTimingFunction));
    }
    printf("End rui`\n");
}

void AnimationExecutor::init()
{
    for (auto iter = mTransitions.cbegin(); iter != mTransitions.cend(); iter++)
    {
        //printf("set property: ID = %d, value = %d\n", (*iter)->propertyID(), (*iter)->initialValue());
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
