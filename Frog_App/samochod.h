#ifndef SAMOCHOD_H
#define SAMOCHOD_H

#include <obiektmobilny.h>
#include <QRandomGenerator>

class Samochod : public ObiektMobilny
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
private:
    QPropertyAnimation *xAnimation;
    qreal m_x;
    int ileZostaloCzasuAnimacji;
    int wJakiejPozycjigdyWstrzymano;

public:
    Samochod(int kier, int pred);
    Samochod(int kier, int pred,int x);
    void zatrzymaj();
    void wznow();

public slots:
    void setX(qreal x);


private:
    qreal x() const;   
};

#endif // SAMOCHOD_H
