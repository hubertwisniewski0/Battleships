class Timer
{
    private:
        pthread_t timer;
        pthread_barrier_t barrier;
        bool timerOk = true;
        bool threadOk = true;
        bool barrierOk = true;

        static void* timerCallback(void* barrier)
        {
            pthread_barrier_t* barrier_c = (pthread_barrier_t*)barrier;
            while(true)
            {
                pthread_barrier_wait(barrier_c);
                SDL_Delay(100);
            }
        }

    public:
        Timer()
        {
            int e;
            e = pthread_barrier_init(&barrier, NULL, 2);
            if(e != 0)
            {
                errorMessage(std::string("pthread_barrier_init: ") + std::string(strerror(e)));
                timerOk = false;
                barrierOk = false;
                return;
            }
            e = pthread_create(&timer, NULL, timerCallback, &barrier);
            if(e != 0)
            {
                errorMessage(std::string("pthread_create: ") + std::string(strerror(e)));
                timerOk = false;
                threadOk = false;
                return;
            }
        }

        ~Timer()
        {
            if(threadOk)
                pthread_cancel(timer);
            if(barrierOk)
                pthread_barrier_destroy(&barrier);
        }

        bool ok()
        {
            return timerOk;
        }

        void synchronize()
        {
            pthread_barrier_wait(&barrier);
        }
};
