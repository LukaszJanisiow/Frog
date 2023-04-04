#include "zarzadzanieterenami.h"


ZarzadzanieTerenami::ZarzadzanieTerenami()
{
    tworzenieNowejListyTerenow();
}

void ZarzadzanieTerenami::usuniDodajTeren()
{
    delete listaTerenow.first();
    listaTerenow.removeFirst();
    int xRandomizer = QRandomGenerator::global()->bounded(3);   //tutaj
    if(xRandomizer == 0)
    {
        dodawanieTerenuMobilnego(xRandomizer);
    }
    else if (xRandomizer == 1)
    {
        TerenZielony *zielony = new TerenZielony(false);
        listaTerenow.append(zielony);
    }
    else if (xRandomizer == 2)
    {
          dodawanieTerenuMobilnego(xRandomizer);
    }
}

ZarzadzanieTerenami::~ZarzadzanieTerenami()
{
    foreach(Teren *teren,listaTerenow)
    {
        delete teren;
    }
}

void ZarzadzanieTerenami::nowaRozgrywka()
{
    while(!listaTerenow.isEmpty())
    {
        delete listaTerenow.first();
        listaTerenow.removeFirst();
    }


    tworzenieNowejListyTerenow();

}

QList<Teren *> ZarzadzanieTerenami::getListaTerenow() const
{
    return listaTerenow;
}


void ZarzadzanieTerenami::tworzenieNowejListyTerenow()
{
    TerenZielony *zielony = new TerenZielony(true);
    listaTerenow.append(zielony);
    zielony = new TerenZielony(true);
    listaTerenow.append(zielony);
    for(int i = 0 ; i < 9 ; i++)
    {
        int xRandomizer = QRandomGenerator::global()->bounded(3);
        if(xRandomizer == 0)
        {
           dodawanieTerenuMobilnego(xRandomizer);
        }
         if (xRandomizer == 1)
        {
            TerenZielony *zielony = new TerenZielony(false);
            listaTerenow.append(zielony);
        }
        else if (xRandomizer == 2)
        {
            dodawanieTerenuMobilnego(xRandomizer);
        }
    }
}

void ZarzadzanieTerenami::dolaczanieSygnaluOdWody(TerenWoda *woda)
{
    QObject::connect(woda,&TerenWoda::zabaNaKlodzie,[=]()
    {
        klodrodzicZaby = woda->getKlodaRodzicZaby();
    });
}

void ZarzadzanieTerenami::dodawanieTerenuMobilnego(int numerWylosowanegoTerenu)
{
    if(listaTerenow.last()->czyCosPoMnieSiePoruszaIwKtorymKierunku() ==0)
    {
        if(numerWylosowanegoTerenu == 0)
        {
            TerenDroga *droga = new TerenDroga(1,0);
            listaTerenow.append(droga);
        }
        else if(numerWylosowanegoTerenu == 2)
        {
            TerenWoda *woda = new TerenWoda(1,0);
            listaTerenow.append(woda);
            dolaczanieSygnaluOdWody(woda);
        }
    }
    else
    {
        if(numerWylosowanegoTerenu == 0)
        {
            TerenDroga *droga = new TerenDroga(0,- listaTerenow.last()->czyCosPoMnieSiePoruszaIwKtorymKierunku());
            listaTerenow.append(droga);
        }
        else if(numerWylosowanegoTerenu == 2)
        {
            TerenWoda *woda = new TerenWoda(0,- listaTerenow.last()->czyCosPoMnieSiePoruszaIwKtorymKierunku());
            listaTerenow.append(woda);
            dolaczanieSygnaluOdWody(woda);
        }
    }
}

Kloda *ZarzadzanieTerenami::getKlodrodzicZaby() const
{
    return klodrodzicZaby;
}

void ZarzadzanieTerenami::wczytywanieZPliu(QList<int> listaZapisu)
{
    while(!listaTerenow.isEmpty())
    {
        delete listaTerenow.first();
        listaTerenow.removeFirst();
    }
    int k = 0;
    for(int i = 0; i < 11; i++)
    {
        if(listaZapisu[k] == 0)
        {
            int ileObiektow = listaZapisu[2 + k];
            QList < int> wspolrzedneObiektow;
            for(int j = 0; j< ileObiektow; j++ )
            {
                wspolrzedneObiektow.append(listaZapisu[k + 3 + 2*j]);
                wspolrzedneObiektow.append(listaZapisu[k + 3 + 2*j + 1]);
            }
            TerenZielony *zielony = new TerenZielony(wspolrzedneObiektow);
            listaTerenow.append(zielony);
            k = k + 3 + ileObiektow * 2;
        }
        else if(listaZapisu[k] != 0 && listaZapisu[k + 1] == 1)
        {
            int ileObiektow = listaZapisu[2 + k];
            QList < int> wspolrzedneObiektow;
            for(int j = 0; j< ileObiektow; j++ )
            {

                wspolrzedneObiektow.append(listaZapisu[k + 3 + 2*j]);
                wspolrzedneObiektow.append(listaZapisu[k + 3 + 2*j + 1]);
            }
            TerenDroga *droga = new TerenDroga(wspolrzedneObiektow,listaZapisu[k]);
            listaTerenow.append(droga);
            k = k + 3 + ileObiektow * 2;
        }
        else if(listaZapisu[k] != 0 && listaZapisu[k + 1] == 0)
        {
            int ileObiektow = listaZapisu[2 + k];
            QList < int> wspolrzedneObiektow;
            for(int j = 0; j< ileObiektow; j++ )
            {

                wspolrzedneObiektow.append(listaZapisu[k + 3 + 2*j]);
                wspolrzedneObiektow.append(listaZapisu[k + 3 + 2*j + 1]);
            }
            TerenWoda *woda = new TerenWoda(wspolrzedneObiektow,listaZapisu[k]);
            listaTerenow.append(woda);
            k = k + 3 + ileObiektow * 2;
        }
    }
}


