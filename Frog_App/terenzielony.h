#ifndef TERENZIELONY_H
#define TERENZIELONY_H

#include "teren.h"
#include "drzewo.h"

class TerenZielony : public Teren
{

private:
    QList<Obiekt*> listaObiektow;

public:
    TerenZielony(bool czyPierwszylubDrugi);
    TerenZielony(QList <int> pozycjeDrzew);

    virtual ~TerenZielony();
    virtual int czyCosPoMnieSiePoruszaIwKtorymKierunku();
    virtual bool czyMoznaStawacNaTeren();
    virtual void zatrzymajWszystkieObiekty();
    virtual void wznowWszystkieObiekty();
    virtual void usunPierwszyOBiektWTerenie();


};

#endif // TERENZIELONY_H
