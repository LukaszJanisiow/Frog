#ifndef TEREN_H
#define TEREN_H

#include <QObject>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>


#include "obiekt.h"

class Teren : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y WRITE setY)

private:
    bool czyPierwszaAnimacja;
    qreal m_y;
    QPropertyAnimation *yAnimation;
    int ileZostaloCzasuAnimacji;
    int numerRodzicaZabygdyRozpoczelaSieAnimacja;
    int ktorygdyRozpoczelaSieAnimacja;
    int wJakiejPozycjigdyWstrzymano;
    QList<Obiekt*> listaObiektow;
    double wspolrzena_x;
    double wspolrzedna_y;
    QPixmap mPixmap;


public:
    Teren();
    virtual ~Teren();;
    void Animacja(int ktory , int numerRodzicaZaby);
    void stop();
    void wznowienieGry();
    void setListaObiektow(const QList<Obiekt *> &value);
    void dodajObiektNaKoniec(Obiekt *obiekt);
    void usunObiektPierwszy();
    virtual int czyCosPoMnieSiePoruszaIwKtorymKierunku() = 0;
    virtual bool czyMoznaStawacNaTeren() = 0;
    virtual void zatrzymajWszystkieObiekty() = 0;
    virtual void wznowWszystkieObiekty() = 0;
    virtual void usunPierwszyOBiektWTerenie() = 0;

    double getWspolrzena_x() const;
    void setWspolrzena_x(double value);

    double getWspolrzedna_y() const;
    void setWspolrzedna_y(double value);

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &pixmap);

    QList<Obiekt *> getListaObiektow() const;

private:
    qreal y() const;

public slots:
    void setY(qreal y);

signals:
    void koniecGry();
    void zabaNaKlodzie();
    void koniecGryWoda();
    void usuwamPierwszyObiekt();
    void dodajeObiektNaKoniec();





};

#endif // TEREN_H
