#include "obiektmobilny.h"
#include "scene.h"
#include"rozgrywka.h"

ObiektMobilny::ObiektMobilny(int kier, int pred):
    zatrzymany(false)
{
    kierunek = kier;
    predkosc = pred;
}

bool ObiektMobilny::getKierunek() const
{
    return kierunek;
}



