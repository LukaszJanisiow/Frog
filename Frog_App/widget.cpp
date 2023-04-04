#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QWidget>
#include<QPushButton>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , czyPierwszaGra(true)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new Scene(this);
    scene->setSceneRect(-250,-300,500,600);
    scene->setRozmiarOkna(ui->graphicsView->frameSize());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMinimumSize(800,800);
    rozgrywka = new Rozgrywka(scene);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    scene->setRozmiarOkna(ui->graphicsView->frameSize());
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    rozgrywka->przycisk(event);
}





