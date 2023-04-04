#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include"scene.h"
#include"rozgrywka.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

private:
    bool czyPierwszaGra;
    Ui::Widget *ui;
    Scene *scene;
    Rozgrywka *rozgrywka;


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // WIDGET_H
