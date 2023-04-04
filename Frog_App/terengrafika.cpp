#include "terengrafika.h"

TerenGrafika::TerenGrafika(QPixmap mPixmap)
{
    setPixmap(mPixmap);
}

TerenGrafika::~TerenGrafika()
{
    foreach(QGraphicsPixmapItem *qgraphicsPixmapItem,listaObiektow)
    {
        delete qgraphicsPixmapItem;
    }
}

QList<QGraphicsPixmapItem *> TerenGrafika::getListaObiektow() const
{
    return listaObiektow;
}

void TerenGrafika::setListaObiektow(const QList<QGraphicsPixmapItem *> &value)
{
    listaObiektow = value;
}

void TerenGrafika::dodajObiektDoListy(QGraphicsPixmapItem *mgraphicsPixmapItem)
{
    listaObiektow.append(mgraphicsPixmapItem);
}

QGraphicsPixmapItem &TerenGrafika::adres(int ktory)
{
    return *listaObiektow[ktory];
}

void TerenGrafika::usunPierwszyObiekt()
{
    delete listaObiektow.first();
    listaObiektow.removeFirst();
}




