#ifndef KLODA_H
#define KLODA_H

#include "obiektmobilny.h"

class Kloda : public ObiektMobilny
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

private:
    qreal m_x;
    QPropertyAnimation *xAnimation;
    int ileZostaloCzasuAnimacji;
    int wJakiejPozycjigdyWstrzymano;

public:
    Kloda(int kier, int pred);
    Kloda(int kier, int pred,int x);
    void zatrzymaj();
    void wznow();

private:
    qreal x() const;

public slots:
    void setX(qreal x);


};

#endif // KLODA_H
