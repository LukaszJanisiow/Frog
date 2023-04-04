#include "kloda.h"

Kloda::Kloda(int kier, int pred)  :
    ObiektMobilny(kier,pred)
{
    Obiekt::setWspolrzedna_y(10);
    Obiekt::setPixmap(QPixmap("://images/drewno.png"));
    xAnimation = new QPropertyAnimation(this,"x",this);
    if(ObiektMobilny::kierunek == -1)
    {
        xAnimation->setStartValue(1000);
        xAnimation ->setEndValue(-300);
    }
    else if(ObiektMobilny::kierunek == 1)
    {
        xAnimation->setStartValue(-200);
        xAnimation ->setEndValue(1100);
    }
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(ObiektMobilny::predkosc);
    xAnimation->start();

}

Kloda::Kloda(int kier, int pred, int x) :
    ObiektMobilny(kier,pred)
{
    Obiekt::setPixmap(QPixmap("://images/drewno.png"));
    xAnimation = new QPropertyAnimation(this,"x",this);
    setWspolrzedna_x(x);
    setWspolrzedna_y(10);
    if(ObiektMobilny::kierunek == -1)
    {
        xAnimation->setStartValue(x);
        xAnimation ->setEndValue(-300);
        xAnimation->setDuration(ObiektMobilny::predkosc - (1000 - x)/1300.0 * ObiektMobilny::predkosc);
    }
    else if(ObiektMobilny::kierunek == 1)
    {
        xAnimation->setStartValue(x);
        xAnimation ->setEndValue(1100);
        xAnimation->setDuration(ObiektMobilny::predkosc - (x + 200)/1300.0 * ObiektMobilny::predkosc);
    }
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->start();
}

void Kloda::zatrzymaj()
{
    ileZostaloCzasuAnimacji = predkosc - xAnimation->currentTime();
    wJakiejPozycjigdyWstrzymano =  this->x();
    xAnimation->stop();
}

void Kloda::wznow()
{
    xAnimation->setStartValue(wJakiejPozycjigdyWstrzymano);
    xAnimation->setDuration(ileZostaloCzasuAnimacji);
    xAnimation->start();
}


qreal Kloda::x() const
{
    return m_x;
}

void Kloda::setX(qreal x)
{
    m_x = x;
    setWspolrzedna_x(x);
}
