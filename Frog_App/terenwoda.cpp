#include "terenwoda.h"



TerenWoda::TerenWoda(bool czyLosowyKierunek, int kierunek)
{
    Teren::setPixmap(QPixmap(":/images/woda_minecraft.jfif"));
    if(czyLosowyKierunek)
    {
        kier = QRandomGenerator::global()->bounded(2);
        if(kier == 0)
        {
            kier = -1;
        }
    }
    else
    {
        kier = kierunek;
    }
    int pred = QRandomGenerator::global()->bounded(3000,5000);
    startTimerKlody(pred,0);
}

TerenWoda::TerenWoda(QList<int> pozycjeObiektow, int kierunek)
{
    kier = kierunek;
    Teren::setPixmap(QPixmap(":/images/woda_minecraft.jfif"));
    int pred = QRandomGenerator::global()->bounded(2000,6000);
    for(int i = 0; i < pozycjeObiektow.count()/2; i++)
    {
        Kloda *kloda = new Kloda(kierunek,pred,pozycjeObiektow[2*i]);
        kloda->Obiekt::setWspolrzedna_x(pozycjeObiektow[2*i]);
        kloda->Obiekt::setWspolrzedna_y(pozycjeObiektow[2*i + 1]);
        listaKlod.append(kloda);
        Teren::dodajObiektNaKoniec(kloda);
    }
    startTimerKlody(pred , 1);
}

void TerenWoda::startTimerKlody(int pred, bool bezPierwszego)
{
    int time;
    if(!bezPierwszego)
    {
        time = QRandomGenerator::global()->bounded(0,1000);                 //losowanie pojawanienia sie czasu pierwszej klody
    }
    else
    {
        time = QRandomGenerator::global()->bounded(1000,2500);
    }

    klodaTimer = new QTimer(this);
    connect(klodaTimer,&QTimer::timeout,[=]()
    {
        int time = QRandomGenerator::global()->bounded(1000,2500);        //losowanie interwalu pojawanienia sie nastepnych klod   zmienione
        Kloda *kloda = new Kloda(kier,pred);
        listaKlod.append(kloda);
        Teren::dodajObiektNaKoniec(kloda);
        klodaTimer->setInterval(time);
    });

    klodaTimer->start(time);

}

Kloda *TerenWoda::getKlodaRodzicZaby() const
{
    return klodaRodzicZaby;
}

void TerenWoda::usunPierwszyOBiektWTerenie()
{
    listaKlod.removeFirst();
}


int TerenWoda::czyCosPoMnieSiePoruszaIwKtorymKierunku()
{
    return kier;
}

bool TerenWoda::czyMoznaStawacNaTeren()
{
    return false;
}

void TerenWoda::zatrzymajWszystkieObiekty()
{
    ileZostaloCzasuTimera = klodaTimer->remainingTime();
    klodaTimer->stop();
    foreach(Kloda *kloda,listaKlod)
    {
        kloda->zatrzymaj();
    }
}

void TerenWoda::wznowWszystkieObiekty()
{
    klodaTimer->start(ileZostaloCzasuTimera);
    foreach(Kloda *kloda,listaKlod)
    {
        kloda->wznow();
    }
}


