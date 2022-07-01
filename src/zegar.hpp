class CZegar
{
    private:
        pthread_t zegar;
        pthread_barrier_t bariera;
        bool Zegar_OK = true;
        bool watek_ok = true;
        bool bariera_ok = true;
        static void* zegar_c(void* bariera_v)
        {
            pthread_barrier_t* bariera_c = (pthread_barrier_t*)bariera_v;
            while(true)
            {
                pthread_barrier_wait(bariera_c);
                SDL_Delay(100);
            }
        }
    public:
        CZegar()
        {
            int e;
            e = pthread_barrier_init(&bariera,NULL,2);
            if(e != 0)
            {
                wiadomosc_o_bledzie(std::string("pthread_barrier_init: ") + std::string(strerror(e)));
                Zegar_OK = false;
                bariera_ok = false;
                return;
            }
            e = pthread_create(&zegar,NULL,zegar_c,&bariera);
            if(e != 0)
            {
                wiadomosc_o_bledzie(std::string("pthread_create: ") + std::string(strerror(e)));
                Zegar_OK = false;
                watek_ok = false;
                return;
            }
        }
        ~CZegar()
        {
            if(watek_ok)
                pthread_cancel(zegar);
            if(bariera_ok)
                pthread_barrier_destroy(&bariera);
        }
        bool ok()
        {
            return Zegar_OK;
        }
        void synchronizuj()
        {
            pthread_barrier_wait(&bariera);
        }
};
