#ifndef ZARZADZANIETERENAMI_H
#define ZARZADZANIETERENAMI_H

#include <QRandomGenerator>

#include "teren.h"
#include "terendroga.h"
#include "terenzielony.h"
#include "terenwoda.h"


class ZarzadzanieTerenami
{

private:
    Kloda *klodrodzicZaby;
    QList<Teren*> listaTerenow;
public:
    ZarzadzanieTerenami();
    ~ZarzadzanieTerenami();
    void usuniDodajTeren(); 
    void nowaRozgrywka();
    QList<Teren *> getListaTerenow() const;
    Kloda *getKlodrodzicZaby() const;
    void wczytywanieZPliu(QList <int> listaZapisu);

private:
    void tworzenieNowejListyTerenow();
    void dolaczanieSygnaluOdWody(TerenWoda *woda);
    void dodawanieTerenuMobilnego(int numerWylosowanegoTerenu);


};

#endif // ZARZADZANIETERENAMI_H
