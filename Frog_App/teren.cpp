#include "teren.h"

Teren::Teren():
    czyPierwszaAnimacja (true),
    wspolrzena_x (-400)
{
    yAnimation = new QPropertyAnimation(this,"y",this);
}

Teren::~Teren()
{
    delete yAnimation;
}

qreal Teren::y() const
{
    return m_y;
}

QList<Obiekt *> Teren::getListaObiektow() const
{
    return listaObiektow;
}

QPixmap Teren::getPixmap() const
{
    return mPixmap;
}

void Teren::setPixmap(const QPixmap &pixmap)
{
    mPixmap = pixmap;
}

double Teren::getWspolrzena_x() const
{
    return wspolrzena_x;
}

void Teren::setWspolrzena_x(double value)
{
    wspolrzena_x = value;
}

double Teren::getWspolrzedna_y() const
{
    return wspolrzedna_y;
}

void Teren::setWspolrzedna_y(double value)
{
    wspolrzedna_y = value;
}

void Teren::setListaObiektow(const QList<Obiekt *> &value)
{
    listaObiektow = value;
}

void Teren::dodajObiektNaKoniec(Obiekt *obiekt)
{
    listaObiektow.append(obiekt);
    emit dodajeObiektNaKoniec();
}

void Teren::usunObiektPierwszy()
{
    delete listaObiektow.first();
    listaObiektow.removeFirst();
    usunPierwszyOBiektWTerenie();
}


void Teren::Animacja(int ktory , int numerRodzicaZaby)
{
//    if(!czyPierwszaAnimacja)
//    {
        delete yAnimation;
//    }
    yAnimation = new QPropertyAnimation(this,"y",this);
    yAnimation->setStartValue(400 - 100 * ktory);
    yAnimation ->setEndValue(500 - 100 * ktory);
    yAnimation->setEasingCurve(QEasingCurve::Linear);
    yAnimation->setDuration(3000 - 300 * numerRodzicaZaby);
    yAnimation->start();
    numerRodzicaZabygdyRozpoczelaSieAnimacja = numerRodzicaZaby;
    ktorygdyRozpoczelaSieAnimacja = ktory;
    czyPierwszaAnimacja = false;
}

void Teren::stop()
{
    ileZostaloCzasuAnimacji = 3000 - 300 * numerRodzicaZabygdyRozpoczelaSieAnimacja - yAnimation->currentTime();
    wJakiejPozycjigdyWstrzymano =  this->y();
    yAnimation->stop();
    zatrzymajWszystkieObiekty();
}

void Teren::wznowienieGry()
{
    wznowWszystkieObiekty();
    yAnimation->setStartValue(wJakiejPozycjigdyWstrzymano);
    yAnimation->setEndValue(500 - 100 * ktorygdyRozpoczelaSieAnimacja);
    yAnimation->setDuration(ileZostaloCzasuAnimacji);
    yAnimation->start();
}

void Teren::setY(qreal y)
{
    m_y = y;
    wspolrzedna_y = m_y;
}


