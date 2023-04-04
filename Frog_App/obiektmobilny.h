#ifndef OBIEKTMOBILNY_H
#define OBIEKTMOBILNY_H

#include<QPropertyAnimation>

#include "obiekt.h"

class ObiektMobilny : public Obiekt
{

public:
    ObiektMobilny(int kier, int pred);
    bool getKierunek() const;


protected:
    int kierunek;
    int predkosc;
    bool zatrzymany;


};

#endif // OBIEKTMOBILNY_H
