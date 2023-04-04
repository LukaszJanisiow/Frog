#include "terenzielony.h"
#include<QRandomGenerator>

TerenZielony::TerenZielony(bool czyPierwszylubDrugi)
{
    Teren::setPixmap(QPixmap(":/images/trawa.png"));
    int iloscDrzew = QRandomGenerator::global()->bounded(3);
    if(!czyPierwszylubDrugi)
    {
        for(int i = 0; i < iloscDrzew; i++)
        {
            Drzewo *drzewo = new Drzewo;
            listaObiektow.append(drzewo);
            int xRandomizer = QRandomGenerator::global()->bounded(8);
            drzewo->Obiekt::setWspolrzedna_x(xRandomizer*100);
            drzewo->Obiekt::setWspolrzedna_y(0);
        }   
    }
    Teren::setListaObiektow(listaObiektow);
}

TerenZielony::TerenZielony(QList<int> pozycjeDrzew)
{
    Teren::setPixmap(QPixmap(":/images/trawa.png"));
    for(int i = 0; i < pozycjeDrzew.count()/2; i++)
    {
        Drzewo *drzewo = new Drzewo;
        listaObiektow.append(drzewo);
        drzewo->Obiekt::setWspolrzedna_x(pozycjeDrzew[2*i]);
        drzewo->Obiekt::setWspolrzedna_y(pozycjeDrzew[2*i + 1]);
    }
    Teren::setListaObiektow(listaObiektow);
}

TerenZielony::~TerenZielony()
{
    foreach(Obiekt *obiekt,listaObiektow)
    {
        delete obiekt;
    }
}

int TerenZielony::czyCosPoMnieSiePoruszaIwKtorymKierunku()
{
    return 0;
}

bool TerenZielony::czyMoznaStawacNaTeren()
{
    return true;
}

void TerenZielony::zatrzymajWszystkieObiekty()
{

}

void TerenZielony::wznowWszystkieObiekty()
{

}

void TerenZielony::usunPierwszyOBiektWTerenie()
{

}
