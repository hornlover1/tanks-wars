#ifndef MASTERTIMER_H
#define MASTERTIMER_H

#include <QTimer>

//used for the countdown

class MasterTimer {
    MasterTimer();
    static int time = 999;
    static MasterTimer instance;
public:
    //singleton class
    static MasterTimer getInstance();

    void setTime(int newTime) { time = newTime;}

private:
    void CountDown();
};

#endif //MasterTime_h
