//
// Created by hubert25632 on 01.07.22.
//

#include "Timer.hpp"
#include "Messages.hpp"
#include <cstring>
#include <SDL.h>

Timer::Timer() {
    int e;
    e = pthread_barrier_init(&barrier, nullptr, 2);
    if (e != 0) {
        errorMessage(std::string("pthread_barrier_init: ") + std::string(strerror(e)));
        timerOk = false;
        barrierOk = false;
        return;
    }
    e = pthread_create(&timer, nullptr, timerCallback, &barrier);
    if (e != 0) {
        errorMessage(std::string("pthread_create: ") + std::string(strerror(e)));
        timerOk = false;
        threadOk = false;
        return;
    }
}

Timer::~Timer() {
    if (threadOk)
        pthread_cancel(timer);
    if (barrierOk)
        pthread_barrier_destroy(&barrier);
}

bool Timer::ok() {
    return timerOk;
}

void Timer::synchronize() {
    pthread_barrier_wait(&barrier);
}

void *Timer::timerCallback(void *barrier) {
    pthread_barrier_t *barrier_c = (pthread_barrier_t *) barrier;
    while (true) {
        pthread_barrier_wait(barrier_c);
        SDL_Delay(100);
    }
}
