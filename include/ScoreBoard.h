#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class ScoreBoard
{
    public:
        ScoreBoard();

        int getPoint();
        void addPoint(int point);
        void resetPoint();

        void render();

    private:
        int mPoint;
        int mX;
        int mY;
};

#endif // SCOREBOARD_H
