//
// Created by hubert25632 on 01.07.22.
//

#include "Timer.hpp"
#include <cstring>
#include <SDL.h>

Timer::Timer(MessageService *messageService) {
    int e;
    e = pthread_barrier_init(&barrier, nullptr, 2);
    if (e != 0)
        messageService->showMessage(MessageService::MessageType::Error,
                                    "pthread_barrier_init: " + std::string(strerror(e)));
    e = pthread_create(&timer, nullptr, timerCallback, &barrier);
    if (e != 0)
        messageService->showMessage(MessageService::MessageType::Error, "pthread_create: " + std::string(strerror(e)));
}

Timer::~Timer() {
    pthread_cancel(timer);
    pthread_barrier_destroy(&barrier);
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
