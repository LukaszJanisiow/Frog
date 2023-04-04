#include "zaba.h"


Zaba::Zaba()
{
    Obiekt::setPixmap(QPixmap(":/images/zabaGIMP.png"));
    setWspolrzedna_x(0);
    setWspolrzedna_y(300);
}
void Zaba::przesun(bool l, bool p)
{
    if(l==1)
    {
        setWspolrzedna_x(getWspolrzedna_x() - 100);

    }
    else if(p==1)
    {
        setWspolrzedna_x(getWspolrzedna_x() + 100);
    }
}



