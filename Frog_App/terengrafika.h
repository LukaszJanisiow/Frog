#ifndef TERENGRAFIKA_H
#define TERENGRAFIKA_H


#include<QGraphicsPixmapItem>

class TerenGrafika : public QGraphicsPixmapItem
{

private:
    QList <QGraphicsPixmapItem*> listaObiektow;

public:
    TerenGrafika(QPixmap mPixmap);
    virtual ~TerenGrafika();

    QList<QGraphicsPixmapItem *> getListaObiektow() const;
    void setListaObiektow(const QList<QGraphicsPixmapItem *> &value);

    void dodajObiektDoListy(QGraphicsPixmapItem *mgraphicsPixmapItem);
    QGraphicsPixmapItem &adres(int ktory);
    void usunPierwszyObiekt();


};

#endif // TERENGRAFIKA_H
