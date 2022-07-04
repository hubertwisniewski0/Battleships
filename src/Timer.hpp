//
// Created by hubert25632 on 01.07.22.
//

#ifndef BATTLESHIPS_TIMER_HPP
#define BATTLESHIPS_TIMER_HPP

#include <pthread.h>
#include "MessageService.hpp"

class Timer {
private:
    pthread_t timer;
    pthread_barrier_t barrier;

    static void *timerCallback(void *barrier);

public:
    Timer(MessageService *messageService);

    ~Timer();

    void synchronize();
};

#endif //BATTLESHIPS_TIMER_HPP
