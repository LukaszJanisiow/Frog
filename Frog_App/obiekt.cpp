#include "obiekt.h"

Obiekt::Obiekt(QObject *parent) : QObject(parent),
    wspolrzedna_x(0),
    wspolrzedna_y(0)
{

}

Obiekt::~Obiekt()
{
}

double Obiekt::getWspolrzedna_x() const
{
    return wspolrzedna_x;
}

void Obiekt::setWspolrzedna_x(double value)
{
    wspolrzedna_x = value;
}

double Obiekt::getWspolrzedna_y() const
{
    return wspolrzedna_y;
}

void Obiekt::setWspolrzedna_y(double value)
{
    wspolrzedna_y = value;
}

QPixmap Obiekt::getPixmap() const
{
    return mPixmap;
}

void Obiekt::setPixmap(const QPixmap &pixmap)
{
    mPixmap = pixmap;
}
