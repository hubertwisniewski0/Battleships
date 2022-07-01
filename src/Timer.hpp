//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_TIMER_HPP
#define BATTLESHIPS_TIMER_HPP

#include <pthread.h>

class Timer {
private:
    pthread_t timer;
    pthread_barrier_t barrier;
    bool timerOk = true;
    bool threadOk = true;
    bool barrierOk = true;

    static void *timerCallback(void *barrier);

public:
    Timer();

    ~Timer();

    bool ok();

    void synchronize();
};

#endif //BATTLESHIPS_TIMER_HPP
