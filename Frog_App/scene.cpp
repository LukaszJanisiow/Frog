#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene(parent)

{
    QPixmap image(":/images/sky4.png");
    QBrush mBrush;
    mBrush.setTexture(image);
    this->setForegroundBrush(mBrush);

    QFont mFont("consolas",30,QFont::Bold);
    wynikWyswietlanie = addText(QString::number(0),mFont);
    wynikWyswietlanie->setDefaultTextColor(QColorConstants::Yellow);
    wynikWyswietlanie->setZValue(5);
    wynikWyswietlanie->setPos(350 ,-375);

    przyciskStartuGry = new PrzyciskStartuGry("Start");
    addWidget(przyciskStartuGry);
    przyciskStartuGry->move(-50,0);
    przyciskZapisu = new PrzyciskStartuGry("Zapisz");
}

void Scene::wyswietlanieAktualnegoWyniku(int aktualnyWynik)
{
  wynikWyswietlanie->setPlainText(QString::number(aktualnyWynik));
  if(aktualnyWynik < 10)
  {
      wynikWyswietlanie->setPos(350 ,-rozmiarOkna.height()/2 + 25);
  }
  else if (aktualnyWynik >= 10 && aktualnyWynik <100)
  {
      wynikWyswietlanie->setPos(325 ,-rozmiarOkna.height()/2 + 25);
  }
  else if (aktualnyWynik >= 100)
  {
      wynikWyswietlanie->setPos(300 ,-rozmiarOkna.height()/2 + 25);
  }

}

void Scene::setRozmiarOkna(const QSize &value)
{
    rozmiarOkna = value;
}

void Scene::wyswietlTeren(QPixmap mPixmap, double x, double y)
{
    TerenGrafika *terenGrafika = new TerenGrafika(mPixmap);
    listaTerenowGrafika.append(terenGrafika);
    terenGrafika->setPos(x,y);
    addItem(terenGrafika);
}


void Scene::aktualizacja(int ktory, double x, double y)
{
    listaTerenowGrafika[ktory]->setPos(x,y);
}

void Scene::dodajUsunTeren(QPixmap mPixmap, double x, double y)
{
    removeItem(listaTerenowGrafika.first());
    delete listaTerenowGrafika.first();
    listaTerenowGrafika.removeFirst();
    wyswietlTeren(mPixmap,x,y);
}

void Scene::dodajObiekt(QPixmap mPixmap, int numerRodzica, double x, double y)
{
    QGraphicsPixmapItem *obiektGrafika = new QGraphicsPixmapItem(mPixmap);
    listaTerenowGrafika[numerRodzica]->dodajObiektDoListy(obiektGrafika);
    obiektGrafika->setPos(x,y);
    obiektGrafika->setParentItem(listaTerenowGrafika[numerRodzica]);
}



void Scene::dodajZabe(QPixmap mPixmap, int numerRodzica, double x, double y)
{
    zabaGrafika = (addPixmap(mPixmap));
    zabaGrafika -> setParentItem(listaTerenowGrafika[numerRodzica]);
    zabaGrafika->setPos(x,y);
}

void Scene::aktualizacjaObiektu(int numerRodzica, int numerObiektu,double x, double y)
{
    if(numerObiektu == -1)
    {
        zabaGrafika->setParentItem(listaTerenowGrafika[numerRodzica]);
        zabaGrafika->setPos(x,y);
    }
    else
    {
        if(listaTerenowGrafika[numerRodzica])
        {
            listaTerenowGrafika[numerRodzica]->adres(numerObiektu).setPos(x,y);
        }
    }
}

void Scene::usunObiekt(int numerRodzica)
{
    listaTerenowGrafika[numerRodzica]->usunPierwszyObiekt();
}

void Scene::nowaGra()
{
    zabaGrafika->setParentItem(0);
    foreach(TerenGrafika *terenGrafika,listaTerenowGrafika)
    {
        removeItem(terenGrafika);
        delete terenGrafika;
        listaTerenowGrafika.removeFirst();
    }
}

void Scene::wyswietlPrzycisk(string napis,int ile)
{
    delete przyciskStartuGry;
    przyciskStartuGry = new PrzyciskStartuGry(napis);
    addWidget(przyciskStartuGry);
    przyciskStartuGry->move(0,0);
    connect(przyciskStartuGry,&PrzyciskStartuGry::start,[=]()
    {

        emit przyciskStartWcisniety();
        przyciskZapisu->setVisible(0);

    });
    if(ile == 2)
    {
        delete przyciskZapisu;
        przyciskZapisu = new PrzyciskStartuGry("Zapisz");
        addWidget(przyciskZapisu);
        przyciskZapisu->move(0, 50);
        connect(przyciskZapisu,&PrzyciskStartuGry::start,[=]()
        {

            emit przyciskZapisuWcisniety();

        });
    }
    if(ile == 1)
    {
        delete przyciskZapisu;
        przyciskZapisu = new PrzyciskStartuGry("Wczytaj");
        addWidget(przyciskZapisu);
        przyciskZapisu->move(0, 50);
        connect(przyciskZapisu,&PrzyciskStartuGry::start,[=]()
        {

            emit przyciskWczytaniaWcisniety();

        });
    }
}
