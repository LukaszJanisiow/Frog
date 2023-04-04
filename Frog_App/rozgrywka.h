#ifndef ROZGRYWKA_H
#define ROZGRYWKA_H

#include<scene.h>
#include<fstream>
#include<QMessageBox>

#include"zarzadzanieterenami.h"
#include"zaba.h"


class Rozgrywka: public QObject
{
    Q_OBJECT

private:
    Zaba *zaba;
    ZarzadzanieTerenami *zarzadzanieTerenami;
    int numerRodzicaZaby;
    bool graRozpoczeta;
    QList<Teren*> listaTerenow;
    int aktualnyWynik;
    Scene *scene;
    int ileZostaloCzasuTimera;
    QTimer *wyswietlanieTimer;
    bool zabaNaKlodzie;
    Obiekt *rodzicZabyKloda;
    double poprzedniaWspolrzednaKlody;
    int odliczaniePrzesuniecia;
    bool przerwa;
    bool czyPierwszaGra;

public:
    Rozgrywka(Scene *scene);
    bool CzyRuchMozliwy(int g_s_d,int l_s_p);
    void start();
    void nowaGra();
    void przycisk(QKeyEvent *event);

private:
    void dodajtereny();
    void przesuntereny();
    void skokZKlodyNaLad(bool w_s_d);
    void dolaczanieOdbieraniaSygnalowDoterenow(Teren *teren);
    bool skokZKlodyNaLadCzymozliwy(int x, bool w_s_d);
    void skokNaKlode(int doPrzoduTylu);
    void przerwaWGrze();
    void wznowienieGry();
    void zapisDoPliku();
    void wczytanieZPliku();

signals:
    void koniecGry();
    void zmianaWyniku();


};

#endif // ROZGRYWKA_H
