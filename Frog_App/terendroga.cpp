#include "terendroga.h"

#include<QRandomGenerator>

TerenDroga::TerenDroga(bool czyLosowyKierunek, int kierunek)
{
    Teren::setPixmap(QPixmap("://images/droga 800x100.png"));
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
    int pred = QRandomGenerator::global()->bounded(2000,6000);                //predkosc samochodu
    uruchomienieTimera(pred , 0);

}

TerenDroga::TerenDroga(QList<int> pozycjeSamochodow, int kierunek)
{
    kier = kierunek;
    Teren::setPixmap(QPixmap("://images/droga 800x100.png"));
    int pred = QRandomGenerator::global()->bounded(2000,6000); 
    for(int i = 0; i < pozycjeSamochodow.count()/2; i++)
    {
        Samochod *samochod = new Samochod(kierunek,pred,pozycjeSamochodow[2*i]);
        listaSamochodow.append(samochod);
        Teren::dodajObiektNaKoniec(samochod);
        samochod->Obiekt::setWspolrzedna_x(pozycjeSamochodow[2*i]);
        samochod->Obiekt::setWspolrzedna_y(pozycjeSamochodow[2*i + 1]);
    }
    uruchomienieTimera(pred , 1);
}

int TerenDroga::czyCosPoMnieSiePoruszaIwKtorymKierunku()
{
    return kier;
}

bool TerenDroga::czyMoznaStawacNaTeren()
{
    return true;
}

void TerenDroga::zatrzymajWszystkieObiekty()
{
    ileZostaloCzasuTimera = samochodTimer->remainingTime();
    samochodTimer->stop();
    foreach(Samochod *samochod,listaSamochodow)
    {
        samochod->zatrzymaj();
    }

}

void TerenDroga::wznowWszystkieObiekty()
{
    samochodTimer->start(ileZostaloCzasuTimera);
    foreach(Samochod *samochod,listaSamochodow)
    {
        samochod->wznow();
    }
}

void TerenDroga::usunPierwszyOBiektWTerenie()
{
    listaSamochodow.removeFirst();
}


void TerenDroga::uruchomienieTimera(int pred , bool bezPierwszego)
{
    int time;
    if(!bezPierwszego)
    {
        time = QRandomGenerator::global()->bounded(200,1200);             // czas pojawienia sie pierwszego samochodu
    }
    else
    {
        time =QRandomGenerator::global()->bounded(800,4000);
    }

    samochodTimer = new QTimer(this);
    connect(samochodTimer,&QTimer::timeout,[=]()
    {
        int time = QRandomGenerator::global()->bounded(800,4000);                                // czas pojawienia sie nastepnych
        Samochod *samochod = new Samochod(kier,pred);
        listaSamochodow.append(samochod);
        Teren::dodajObiektNaKoniec(samochod);
        samochodTimer->setInterval(time);
    });

    samochodTimer->start(time);
}



