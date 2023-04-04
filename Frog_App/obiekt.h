#ifndef OBIEKT_H
#define OBIEKT_H

#include <QObject>
#include<QGraphicsPixmapItem>

class Obiekt : public QObject
{
    Q_OBJECT

private:
    double wspolrzedna_x;
    double wspolrzedna_y;
    QPixmap mPixmap;


public:
    Obiekt(QObject *parent = nullptr);
    virtual ~ Obiekt();

    double getWspolrzedna_x() const;
    void setWspolrzedna_x(double value);

    double getWspolrzedna_y() const;
    void setWspolrzedna_y(double value);

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &pixmap);



signals:

};

#endif // OBIEKT_H
