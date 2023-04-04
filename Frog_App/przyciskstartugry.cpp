#include "przyciskstartugry.h"

PrzyciskStartuGry::PrzyciskStartuGry(string napis)
{
    setText(QString::fromStdString(napis));
}

void PrzyciskStartuGry::mousePressEvent(QMouseEvent *event)
{
    emit start();
    this->setVisible(false);
}
