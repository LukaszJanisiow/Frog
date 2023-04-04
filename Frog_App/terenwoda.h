#ifndef TERENWODA_H
#define TERENWODA_H

#include<QRandomGenerator>
#include<QTimer>

#include "teren.h"
#include "kloda.h"

class TerenWoda : public Teren
{
private:
    QTimer *klodaTimer;
    int kier;
    int ileZostaloCzasuTimera;
    Kloda *klodaRodzicZaby;
    QList<Kloda*> listaKlod;

public:
    TerenWoda(bool czyLosowyKierunek, int kierunek);
    TerenWoda(QList <int> pozycjeObiektow, int kierunek);

    virtual int czyCosPoMnieSiePoruszaIwKtorymKierunku();
    virtual bool czyMoznaStawacNaTeren();
    virtual void zatrzymajWszystkieObiekty();
    virtual void wznowWszystkieObiekty();
    Kloda *getKlodaRodzicZaby() const;
    virtual void usunPierwszyOBiektWTerenie();

private:
    void startTimerKlody(int pred, bool bezPierwszego);

};

#endif // TERENWODA_H
