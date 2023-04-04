#include "samochod.h"


Samochod::Samochod(int kier, int pred) :
    ObiektMobilny(kier,pred)
{
    int kolor = QRandomGenerator::global()->bounded(2);
    xAnimation = new QPropertyAnimation(this,"x",this);
    if(ObiektMobilny::kierunek == -1)
    {
        if( kolor == 0)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwLewoGIMP.png"));
        }
        else if( kolor == 1)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwLewo2GIMP.png"));
        }
        xAnimation->setStartValue(1000);
        xAnimation ->setEndValue(-300);

    }
    else if(ObiektMobilny::kierunek == 1)
    {
        if( kolor == 0)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwPrawoGIMP.png"));
        }
        else if( kolor == 1)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwPrawo2GIMP.png"));
        }

        xAnimation->setStartValue(-200);
        xAnimation ->setEndValue(1100);

    }

    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(ObiektMobilny::predkosc);

    xAnimation->start();


}

Samochod::Samochod(int kier, int pred, int x):
    ObiektMobilny(kier,pred)
{
    int kolor = QRandomGenerator::global()->bounded(2);
    xAnimation = new QPropertyAnimation(this,"x",this);
    setWspolrzedna_x(x);
    if(ObiektMobilny::kierunek == -1)
    {
        if( kolor == 0)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwLewo.png"));
        }
        else if( kolor == 1)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwLewo2.png"));
        }
        xAnimation->setStartValue(x);
        xAnimation ->setEndValue(-300);
        xAnimation->setDuration(ObiektMobilny::predkosc - (1000 - x)/1300.0 * ObiektMobilny::predkosc);
    }
    else if(ObiektMobilny::kierunek == 1)
    {
        if( kolor == 0)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwPrawo.png"));
        }
        else if( kolor == 1)
        {
            Obiekt::setPixmap(QPixmap(":/images/samochodwPrawo2.png"));
        }
        xAnimation->setStartValue(x);
        xAnimation ->setEndValue(1100);
        xAnimation->setDuration(ObiektMobilny::predkosc - (x + 200)/1300.0 * ObiektMobilny::predkosc);
    }
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->start();
}

qreal Samochod::x() const
{
    return m_x;
}


void Samochod::zatrzymaj()
{
    ileZostaloCzasuAnimacji = predkosc - xAnimation->currentTime();
    wJakiejPozycjigdyWstrzymano =  this->x();
    xAnimation->stop();
}

void Samochod::wznow()
{
    xAnimation->setStartValue(wJakiejPozycjigdyWstrzymano);
    xAnimation->setDuration(ileZostaloCzasuAnimacji);
    xAnimation->start();
}



void Samochod::setX(qreal x)
{
    m_x = x;
    if(ObiektMobilny::zatrzymany)
    {
        zatrzymaj();
    }
    Obiekt::setWspolrzedna_x(m_x);
}

