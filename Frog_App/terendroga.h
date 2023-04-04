#ifndef TERENDROGA_H
#define TERENDROGA_H

#include <QTimer>

#include "teren.h"
#include "samochod.h"


class TerenDroga : public Teren
{
    Q_OBJECT

private:
    QTimer *samochodTimer;
    int kier;
    int ileZostaloCzasuTimera;
    QList<Samochod*> listaSamochodow;

public:
    TerenDroga(bool czyLosowyKierunek, int kierunek);
    TerenDroga(QList <int> pozycjeSamochodow, int kierunek);
    virtual int czyCosPoMnieSiePoruszaIwKtorymKierunku();
    virtual bool czyMoznaStawacNaTeren();
    virtual void zatrzymajWszystkieObiekty();
    virtual void wznowWszystkieObiekty();
    virtual void usunPierwszyOBiektWTerenie();

private:
    void uruchomienieTimera(int pred, bool bezPierwszego);

};

#endif // TERENDROGA_H
