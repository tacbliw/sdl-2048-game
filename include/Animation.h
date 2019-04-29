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

class Block;
class Animation
{
    public:
        struct TranstionInformation
        {
            int percent;
            double value;
        };
        Animation(int duration, Block* blockTarget): mDuration(duration), mBlockTarget(blockTarget), mElapsed(0), mAlive(true) {}

        void add(int percent, double value);//

        double calculate(int elapsed, int duration);
        void init();//
        void progress(int delta_ms);//
        void setMode(MODE mode) { this->mMode = mode; }//

    private:
        int mDuration;
        int mElapsed;
        Block *mBlockTarget;
        std::vector<TranstionInformation> infoTrans;
        bool mAlive;
        MODE mMode;
};



#endif // ANIMATION_H
