class CGra
{
    private:
        uint8_t plansze[2][10][10];
        void zeruj_plansze()
        {
            for(uint8_t i = 0; i < 2; i++)
                for(uint8_t j = 0; j < 10; j++)
                    for(uint8_t k = 0; k < 10; k++)
                        plansze[i][j][k] = 0;
        }
        void losuj_statki()
        {
            for(uint8_t i = 0; i < 2; i++)
            {
                for(uint8_t l = 4; l > 0;l--)
                {
                    for(uint8_t c = 0; c < 5-l;)
                    {
                        uint8_t start[2]; //Współrzędne początku statku
                        uint8_t kierunek;
                        kierunek = rand() % 2;
                        if(kierunek == 0) //Losuj kierunek: 0 - poziomy, 1 - pionowy
                        {
                            start[0] = rand() % (10 - (l-1));
                            start[1] = rand() % 10;
                        }
                        else
                        {
                            start[0] = rand() % 10;
                            start[1] = rand() % (10 - (l-1));
                        }
                        bool wolne = true;
                        for(int8_t ckx = start[0]-1; ckx < start[0]+(kierunek == 0 ? l+1 : 2) && wolne; ckx++) //Sprawź, czy jest wystarczająco dużo wolnego miejsca, aby postawić statek (ignoruj krawędzie planszy)
                        {
                            for(int8_t cky = start[1]-1; cky < start[1]+(kierunek == 0 ? 2 : l+1) && wolne; cky++)
                            {
                                if(ckx < 0 || ckx > 9 || cky < 0 || cky > 9)
                                    continue;
                                if(plansze[i][ckx][cky] != 0)
                                    wolne = false;
                            }
                        }
                        if(wolne)
                        {
                            if(kierunek == 0)
                                for(uint8_t pole = start[0]; pole < start[0]+l; pole++)
                                    plansze[i][pole][start[1]] = 1;
                            else
                                for(uint8_t pole = start[1]; pole < start[1]+l; pole++)
                                    plansze[i][start[0]][pole] = 1;
                            c++;
                        }
                    }
                }
            }
        }
        bool zatopiony(uint8_t i, uint8_t x, uint8_t y, uint8_t p_x, uint8_t p_y, bool zaznacz)
        {
            for(int8_t j = x-1; j < x+2; j++)
            {
                for(int8_t k = y-1; k < y+2; k++)
                {
                    if(j < 0 || j > 9 || k < 0 || k > 9 || ( j == x && k == y ) || ( j == p_x && k == p_y ) )
                        continue;
                    if(plansze[i][j][k] == 1)
                        return false;
                    else if(plansze[i][j][k] == 3)
                        if(!zatopiony(i,j,k,x,y,zaznacz))
                            return false;
                }
            }
            if(zaznacz)
                plansze[i][x][y] = 6;
            return true;
        }
    public:
        void nowa_gra()
        {
            zeruj_plansze();
            losuj_statki();
        }
        CGra()
        {
            nowa_gra();
        }
        uint8_t strzal(uint8_t i, uint8_t x, uint8_t y)
        {
            if(x > 9 || y > 9)
                return 2;
            uint8_t poprz = plansze[i][x][y];
            if(poprz == 0)
                plansze[i][x][y] = 2;
            else if(poprz == 1)
                plansze[i][x][y] = 3;
            bool wygrana = true;
            for(uint8_t j = 0; j < 10 && wygrana; j++)
                for(uint8_t k = 0; k < 10 && wygrana; k++)
                    if(plansze[i][j][k] == 1)
                        wygrana = false;
            if(poprz != 1)
                return poprz;
            else if(zatopiony(i,x,y,x,y,false) || wygrana)
            {
                zatopiony(i,x,y,x,y,true);
                if(wygrana)
                    return 4;
                else
                    return 5;
            }
            else
                return 1;
        }
        uint8_t pole(uint8_t i, uint8_t x, uint8_t y)
        {
            if(x > 9 || y > 9)
                return 2;
            uint8_t p = plansze[i][x][y];
            return p;
        }
};
class CWrog
{
    private:
        CGra* Gra;
        int8_t pierw_pole[2] = {0,0};
        int8_t poprz_pole[2] = {0,0};
        int8_t kierunek[2] = {0,0};
        int8_t poprz_kierunek[2] = {0,0};
        bool zainteresowany = false;
        void zapamietaj(int8_t* pole) //Zapamiętaj ostatnie pole, kierunek ostrzału i jego efekt (wywołać po trafieniu statku)
        {
            for(uint8_t i = 0; i < 2; i++)
            {
                poprz_pole[i] = pole[i];
                poprz_kierunek[i] = kierunek[i];
                if(!zainteresowany)
                    pierw_pole[i] = pole[i];
            }
            zainteresowany = true;
        }
        void zapomnij_kierunek()
        {
            for(uint8_t i = 0; i < 2; i++)
            {
                kierunek[i] = 0;
            }
        }
        void zapomnij() //Resetuj pamięć (wywołać po zatopieniu statku)
        {
            zapomnij_kierunek();
            for(uint8_t i = 0; i < 2; i++)
            {
                poprz_pole[i] = 0;
                pierw_pole[i] = 0;
                poprz_kierunek[i] = 0;
            }
            zainteresowany = false;
        }
        void odwroc() //Odwróć kierunek ostrzału oraz przywróć ostatnio ostrzeliwane pole do pierwszego (wywołać po jednoczesnym nietrafieniu i zainteresowaniu)
        {
            for(uint8_t i = 0; i < 2; i++)
            {
                kierunek[i] = -(poprz_kierunek[i]);
                poprz_pole[i] = pierw_pole[i];
            }
        }
        void ustaw_pole_rel(int8_t* pole, int8_t* kierunek_, int8_t* rel) //Ustaw pole na pozycję przesuniętą o kierunek względem pola rel
        {
            for(uint8_t i = 0; i < 2; i++)
                pole[i] = rel[i] + kierunek_[i];
        }
        bool sensowne_pole(int8_t* pole) //Sprawdza, czy strzał w dane pole ma sens (czy dookoła niego nie ma trafionych lub zatopionych statków)
        {
            uint8_t p;
/*            if(zainteresowany)
                return true;*/
            for(int8_t i = pole[0]-1; i < pole[0]+2; i++)
            {
                for(int8_t j = pole[1]-1; j < pole[1]+2; j++)
                {
                    if(zainteresowany && i == poprz_pole[0] && j == poprz_pole[1])
                        continue;
                    p = Gra->pole(0,i,j);
                    if(p == 3 || p == 6)
                    {
                        if(poprz_pole[0] == pierw_pole[0] && poprz_pole[1] == pierw_pole[1])
                            zapomnij_kierunek();
                        else
                            odwroc();
                        return false;
                    }
                }
            }
            return true;
        }
    public:
        CWrog(CGra* G)
        {
            Gra = G;
        }
        uint8_t graj(uint8_t *x, uint8_t *y)
        {
            int8_t pole[2],s;
            uint8_t proby = 0;
//            int tttt;
            while(true)
            {
                if(proby++ > 250)
                {
                    zapomnij();
                    return 7;
                }
//std::cout << "KR: " << (int)kierunek[0] << "\t" << (int)kierunek[1] << "\nPKR:" << (int)poprz_kierunek[0] << "\t" << (int)poprz_kierunek[1] << "\nPIP:" << (int)pierw_pole[0] << "\t" << (int)pierw_pole[1] << "\nPOP:" << (int)poprz_pole[0] << "\t" << (int)poprz_pole[1] << "\n";
                if(!zainteresowany) //Jeśli poprzednio był trafiony, to warto sprawdzić pola dookoła
                    for(uint8_t i = 0; i < 2; i++)
                        pole[i] = rand() % 10;
/*{
    std::cin >> tttt;
    pole[i] = tttt;
}*/
                else
                {
                    if(kierunek[0] == 0 && kierunek[1] == 0) //Jeśli nie ustalono kierunku ostrzału, wylosuj go
                    {
                        for(int8_t i = 0; i < 2; i++)
                        {
                            kierunek[i] = rand() % 3 - 1;
                            if(kierunek[0] != 0)
                            {
                                kierunek[1] = 0;
                                break;
                            }
                        }
                    }
                    ustaw_pole_rel(pole,kierunek,poprz_pole);
                }
//std::cout << "P:  " << (int)pole[0] << "\t" << (int)pole[1] << "\n";
                if(sensowne_pole(pole))
                    s = Gra->strzal(0,pole[0],pole[1]);
                else
                    continue;
                *x = pole[0];
                *y = pole[1];
//std::cout << "S:  " << (int)s << "\n";
                if(s == 0 || s == 2 || s == 3 || s == 6)
                {
                    if(zainteresowany)
                        odwroc();
                    if(s == 0)
                        break;
                }
                if(s == 1)
                {
                    zapamietaj(pole);
                    break;
                }
                if(s == 4)
                    break;
                if(s == 5)
                {
                    zapomnij();
                    break;
                }
            }
            return s;
        }
        void reset()
        {
            zapomnij();
        }
};
