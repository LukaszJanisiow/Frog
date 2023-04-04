#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include<QKeyEvent>
#include<QGraphicsTextItem>

#include"terengrafika.h"
#include"przyciskstartugry.h"

using namespace std;
/**
 * \brief Klasa Scene odpowiada za grafikę aplikacji i tworzenie sceny
 */

class Scene : public QGraphicsScene
{
    Q_OBJECT
private:
    QSize rozmiarOkna;
    QGraphicsTextItem *wynikWyswietlanie;
    QList<TerenGrafika*> listaTerenowGrafika;
    QGraphicsItem *zabaGrafika;
    PrzyciskStartuGry *przyciskStartuGry;
    PrzyciskStartuGry *przyciskZapisu;


public:
    explicit Scene(QObject *parent = nullptr);
    void wyswietlanieAktualnegoWyniku(int aktualnyWynik);
    void setRozmiarOkna(const QSize &value);
    void wyswietlTeren(QPixmap mPixmap, double x, double y);
    void aktualizacja(int ktory,double x,double y);
    void dodajUsunTeren(QPixmap mPixmap, double x, double y);
    void dodajObiekt(QPixmap mPixmap, int numerRodzica, double x, double y);
    void dodajZabe(QPixmap mPixmap, int numerRodzica, double x, double y);
    void aktualizacjaObiektu(int numerRodzica, int numerObiektu, double x,double y);
    void usunObiekt(int numerRodzica);
    void nowaGra();
    void wyswietlPrzycisk(string napis,int ile);

signals:
    void przyciskStartWcisniety();
    void przyciskZapisuWcisniety();
    void przyciskWczytaniaWcisniety();

};

#endif // SCENE_H
