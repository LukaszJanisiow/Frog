#include "rozgrywka.h"

Rozgrywka::Rozgrywka(Scene *scene):
  zarzadzanieTerenami(new ZarzadzanieTerenami),
  numerRodzicaZaby(1),
  graRozpoczeta(false),
  aktualnyWynik(0),
  scene(scene),
  zabaNaKlodzie(false),
  odliczaniePrzesuniecia(300 - 30*numerRodzicaZaby),
  przerwa(false),
  czyPierwszaGra(true)
{
  zaba = new Zaba();
  listaTerenow = zarzadzanieTerenami->getListaTerenow();
  dodajtereny();
  zaba->setWspolrzedna_x(310);
  zaba->setWspolrzedna_y(10);
  scene->dodajZabe(zaba->getPixmap(),numerRodzicaZaby,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
  scene->wyswietlPrzycisk("Start",1);
  connect(scene,&Scene::przyciskStartWcisniety,[=]()
  {
      if(czyPierwszaGra == true)
      {
          start();
          czyPierwszaGra = false;
      }
      else
      {
          if(przerwa)
          {
              wznowienieGry();
              graRozpoczeta = true;
          }
          else
          {
              nowaGra();
          }
      }
  });

  connect(scene,&Scene::przyciskZapisuWcisniety,[=](){
      zapisDoPliku();
  });
  connect(scene,&Scene::przyciskWczytaniaWcisniety,[=](){
      wczytanieZPliku();
  });

  //nowa czas

  connect(this,&Rozgrywka::koniecGry,[=]()
  {
      graRozpoczeta = false;
      wyswietlanieTimer->stop();
      scene->wyswietlPrzycisk("Start",0);
      foreach(Teren *teren,listaTerenow)
      {
          teren->stop();
      }
  });
  wyswietlanieTimer = new QTimer(this);
  wyswietlanieTimer->setInterval(10);
  connect(wyswietlanieTimer,&QTimer::timeout,[=]()
  {
      if(przerwa)
      {
          wyswietlanieTimer->setInterval(10);
          przerwa = false;
      }
      scene->aktualizacjaObiektu(numerRodzicaZaby,-1,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
      odliczaniePrzesuniecia = odliczaniePrzesuniecia - 1;
      if(odliczaniePrzesuniecia == 0)
      {
          if(numerRodzicaZaby == 0 )
          {
              emit koniecGry();
          }
          else
          {
              numerRodzicaZaby--;
              odliczaniePrzesuniecia = 300 - 30 * numerRodzicaZaby;
              zarzadzanieTerenami->usuniDodajTeren();
              listaTerenow = zarzadzanieTerenami->getListaTerenow();
              przesuntereny();
              dolaczanieOdbieraniaSygnalowDoterenow(listaTerenow.last());
          }
      }
     int i = 0;
     foreach(Teren *teren,listaTerenow)
     {
         scene->aktualizacja(i,teren->getWspolrzena_x(),teren->getWspolrzedna_y());
         int k = 0;
         if(teren->czyCosPoMnieSiePoruszaIwKtorymKierunku()!= 0)
         {
             foreach(Obiekt *obiekt,listaTerenow[i]->getListaObiektow())
             {
                 scene->aktualizacjaObiektu(i,k,obiekt->getWspolrzedna_x(),obiekt->getWspolrzedna_y());
                 k++;
                 if(obiekt->getWspolrzedna_x() < -250 || obiekt->getWspolrzedna_x() > 1050)
                 {
                     scene->usunObiekt(i);
                     listaTerenow[i]->usunObiektPierwszy();
                     k--;
                 }
                 if(i == numerRodzicaZaby && teren->czyMoznaStawacNaTeren() && (obiekt->getWspolrzedna_x() - 70 < zaba->getWspolrzedna_x() && obiekt->getWspolrzedna_x() + 80 > zaba->getWspolrzedna_x())) //zmienione z 80 i 100
                 {
                     emit koniecGry();
                 }
             }
         }
         i++;
     }
     if(zabaNaKlodzie)
     {
         zaba->setWspolrzedna_x(zaba->getWspolrzedna_x() + rodzicZabyKloda->getWspolrzedna_x() - poprzedniaWspolrzednaKlody);
         poprzedniaWspolrzednaKlody = rodzicZabyKloda->getWspolrzedna_x();
         scene->aktualizacjaObiektu(numerRodzicaZaby,-1,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
         if(zaba->getWspolrzedna_x() > 800 || zaba->getWspolrzedna_x() < -80)
         {
             emit koniecGry();
         }
     }
 });
}


bool Rozgrywka::CzyRuchMozliwy(int g_s_d,int l_s_p)
{
    int i = numerRodzicaZaby + g_s_d;
    if(i < 0 || i > 9)
    {
        return false;
    }
    if(zaba->Obiekt::getWspolrzedna_x() - 100*l_s_p < 0 || zaba->Obiekt::getWspolrzedna_x() - 100*l_s_p > 800)
    {
        return false;
    }
    foreach(Obiekt *obiekt, listaTerenow[i]->getListaObiektow())
    {
        if(obiekt->getWspolrzedna_x() == zaba->Obiekt::getWspolrzedna_x() - 10 - 100 * l_s_p)
        {
            return false;
        }
    }
    return true;
}

void Rozgrywka::start()
{
  int i =0;
  odliczaniePrzesuniecia = 300 - 30 * numerRodzicaZaby;
  foreach(Teren *teren,listaTerenow)
  {
      teren->Teren::Animacja(i,numerRodzicaZaby);
      i++;
  }
  graRozpoczeta = true;
  wyswietlanieTimer->start();

}


void Rozgrywka::nowaGra()
{
  scene->nowaGra();
  numerRodzicaZaby = 1;
  zarzadzanieTerenami->nowaRozgrywka();
  listaTerenow = zarzadzanieTerenami->getListaTerenow();
  dodajtereny();
  zaba->setWspolrzedna_x(310);
  zaba->setWspolrzedna_y(10);
  scene->aktualizacjaObiektu(numerRodzicaZaby,-1,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
  aktualnyWynik = 0;
  scene->wyswietlanieAktualnegoWyniku(aktualnyWynik);
  start();
}

void Rozgrywka::dodajtereny()
{
  int i =0;
  foreach(Teren *teren,listaTerenow)
  {
      teren->setWspolrzena_x(-400);
      teren->setWspolrzedna_y(400 - 100*i);
      scene->wyswietlTeren(teren->getPixmap(),teren->getWspolrzena_x(),teren->getWspolrzedna_y());
      foreach(Obiekt *obiekt, teren->getListaObiektow())
      {
          scene->dodajObiekt(obiekt->getPixmap(),i,obiekt->getWspolrzedna_x(),obiekt->getWspolrzedna_y());
      }
      if(graRozpoczeta)
      {
          teren->Teren::Animacja(i, numerRodzicaZaby);
      }
      i++;
      dolaczanieOdbieraniaSygnalowDoterenow(teren);
  }

}


void Rozgrywka::przesuntereny()
{
  int i =0;
  scene->dodajUsunTeren(listaTerenow.last()->getPixmap(),listaTerenow.last()->getWspolrzena_x(),listaTerenow.last()->getWspolrzedna_y());
  foreach(Obiekt *obiekt, listaTerenow.last()->getListaObiektow())
  {
      scene->dodajObiekt(obiekt->getPixmap(),10,obiekt->getWspolrzedna_x(),obiekt->getWspolrzedna_y());
  }
  foreach(Teren *teren,listaTerenow)
  {
      teren->setWspolrzedna_y(-400);
      teren->setWspolrzedna_y(300 - 100*i);
      teren->Teren::Animacja(i, numerRodzicaZaby);
      i++;
  }
}


void Rozgrywka::skokZKlodyNaLad(bool g_s_d)
{
  int celaZaby = zaba->getWspolrzedna_x()/100;
  float celaZabyFloat = (zaba->getWspolrzedna_x())/100;
  if (celaZabyFloat - celaZaby < 0.6 && listaTerenow[numerRodzicaZaby]->czyCosPoMnieSiePoruszaIwKtorymKierunku() == -1)
  {
      if(skokZKlodyNaLadCzymozliwy((celaZaby) * 100 , g_s_d))
      {
          zaba->setWspolrzedna_x(celaZaby * 100 + 10);
          if(g_s_d)
          {
              numerRodzicaZaby++;
              aktualnyWynik++;
          }
          else
          {
              numerRodzicaZaby--;
              aktualnyWynik--;
          }
          zabaNaKlodzie = 0;
      }
  }
  else if (celaZabyFloat - celaZaby < 0.4 && listaTerenow[numerRodzicaZaby]->czyCosPoMnieSiePoruszaIwKtorymKierunku() == 1 )
  {
      if(skokZKlodyNaLadCzymozliwy((celaZaby) * 100,g_s_d))
      {
          zaba->setWspolrzedna_x(celaZaby * 100 + 10);
         if(g_s_d)
          {
            numerRodzicaZaby++;
              aktualnyWynik++;
         }
          else
         {
            numerRodzicaZaby--;
            aktualnyWynik--;
          }
         zabaNaKlodzie = 0;
      }
  }
  else
  {
      if(skokZKlodyNaLadCzymozliwy((celaZaby + 1) * 100,g_s_d))
      {
          zaba->setWspolrzedna_x((celaZaby + 1) * 100 + 10);
          if(g_s_d)
          {
              numerRodzicaZaby++;
              aktualnyWynik++;
          }
          else
          {
              numerRodzicaZaby--;
              aktualnyWynik--;
          }
          zabaNaKlodzie = false;
      }
  }
  scene->wyswietlanieAktualnegoWyniku(aktualnyWynik);
}

void Rozgrywka::dolaczanieOdbieraniaSygnalowDoterenow(Teren *teren)
{
  connect(teren,&Teren::koniecGry,[=]()
  {
      emit koniecGry();
  });
  connect(teren,&Teren::dodajeObiektNaKoniec,[=](){
      scene->dodajObiekt(teren->getListaObiektow().last()->getPixmap(),listaTerenow.indexOf(teren),teren->getListaObiektow().last()->getWspolrzedna_x(),teren->getListaObiektow().last()->getWspolrzedna_y());
  });
}

bool Rozgrywka::skokZKlodyNaLadCzymozliwy(int x, bool g_s_d)
{
  QList<Obiekt*> dzieciTerenu;
  if(g_s_d)
  {
      dzieciTerenu = listaTerenow[numerRodzicaZaby + 1]->getListaObiektow();
      if(listaTerenow[numerRodzicaZaby + 1]->czyCosPoMnieSiePoruszaIwKtorymKierunku() != 0)
      {
          return true;
      }
  }
  else
  {
      dzieciTerenu = listaTerenow[numerRodzicaZaby - 1]->getListaObiektow();
      if(listaTerenow[numerRodzicaZaby - 1]->czyCosPoMnieSiePoruszaIwKtorymKierunku() != 0)
      {
          return true;
      }
  }
  foreach(Obiekt *obiekt,dzieciTerenu)
  {
      if(obiekt->getWspolrzedna_x() == x)
      {
          return false;
      }
  }
      return true;
}

void Rozgrywka::skokNaKlode(int doPrzoduTylu)
{
    zabaNaKlodzie = false;
    foreach(Obiekt *obiekt,listaTerenow[numerRodzicaZaby +doPrzoduTylu]->getListaObiektow())
    {
        if(obiekt->getWspolrzedna_x() < zaba->getWspolrzedna_x() + 60 && obiekt->getWspolrzedna_x() + 150 > zaba->getWspolrzedna_x())  //zmienione 80 i 160
        {
            zabaNaKlodzie = true;
            rodzicZabyKloda = obiekt;
            poprzedniaWspolrzednaKlody = obiekt->getWspolrzedna_x();
            numerRodzicaZaby= numerRodzicaZaby + doPrzoduTylu;
            aktualnyWynik = aktualnyWynik + doPrzoduTylu;
            scene->wyswietlanieAktualnegoWyniku(aktualnyWynik);
        }
    }
    if(!zabaNaKlodzie)
    {
        numerRodzicaZaby= numerRodzicaZaby + doPrzoduTylu;
        aktualnyWynik = aktualnyWynik + doPrzoduTylu;
        scene->wyswietlanieAktualnegoWyniku(aktualnyWynik);
        scene->aktualizacjaObiektu(numerRodzicaZaby,-1,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
        emit koniecGry();
    }
}

void Rozgrywka::przerwaWGrze()
{
    ileZostaloCzasuTimera = wyswietlanieTimer->remainingTime();
    wyswietlanieTimer->stop();
    foreach(Teren *teren,listaTerenow)
    {
        teren->stop();
    }
    przerwa = true;
    scene-> wyswietlPrzycisk("Wznow",2);
}

void Rozgrywka::wznowienieGry()
{
  wyswietlanieTimer->start(ileZostaloCzasuTimera);
  foreach(Teren *teren,listaTerenow)
  {
      teren->wznowienieGry();
  }
}

void Rozgrywka::zapisDoPliku()
{
    qDebug() << "Zapisuje";
    ofstream plikZapisu("zapisZaba");
    if(plikZapisu.good())
    {
        qDebug() << "Jest git";
        plikZapisu << "1" <<endl;
        plikZapisu << aktualnyWynik << endl;
        plikZapisu << numerRodzicaZaby << endl;
        plikZapisu << zabaNaKlodzie << endl;
        for(int i =0 ; i < 11 ; i++)
        {
            plikZapisu << listaTerenow[i]->czyCosPoMnieSiePoruszaIwKtorymKierunku()<<endl;
            plikZapisu << listaTerenow[i]->czyMoznaStawacNaTeren()<<endl;
            plikZapisu << listaTerenow[i]->getListaObiektow().count() << endl;
            foreach(Obiekt *obiekt,listaTerenow[i]->getListaObiektow())
            {
                plikZapisu << obiekt->getWspolrzedna_x() << endl;
                plikZapisu << obiekt->getWspolrzedna_y() << endl;
            }
            plikZapisu << "42" << endl;
        }
        plikZapisu << zaba->getWspolrzedna_x() << endl;
        plikZapisu << zaba->getWspolrzedna_y() << endl;
    }
    else
    {
        QMessageBox informacja;
        informacja.setIcon(QMessageBox::Warning);
        informacja.setText("Brak mozliwosci zapisu");
        informacja.exec();
    }
    plikZapisu.close();

}

void Rozgrywka::wczytanieZPliku()
{
    ifstream plikZapisu("zapisZaba");
    if(plikZapisu.good())
    {
        string wartoscZPliku;
        getline(plikZapisu,wartoscZPliku);
        if(wartoscZPliku == "1")
        {
            getline(plikZapisu,wartoscZPliku);
            aktualnyWynik = stoi(wartoscZPliku);
            getline(plikZapisu,wartoscZPliku);
            numerRodzicaZaby = stoi(wartoscZPliku);
            getline(plikZapisu,wartoscZPliku);
            zabaNaKlodzie = stoi(wartoscZPliku);

            QList <int> listaZapisu;
            for(int i = 0; i < 11; i++)
            {
                for(int k =0; k< 3; k++)
                {
                    getline(plikZapisu,wartoscZPliku);
                    listaZapisu.append(stoi(wartoscZPliku));
                }
                int ileObiektow = stoi(wartoscZPliku);
                for(int k = 0; k < ileObiektow; k++ )
                {
                    getline(plikZapisu,wartoscZPliku);
                    listaZapisu.append(stoi(wartoscZPliku));
                    getline(plikZapisu,wartoscZPliku);
                    listaZapisu.append(stoi(wartoscZPliku));
                }
                getline(plikZapisu,wartoscZPliku);
                if(wartoscZPliku!="42")
                {
                    QMessageBox informacja;
                    informacja.setIcon(QMessageBox::Warning);
                    informacja.setText("Plik uszkodzony. Brak mozliwosci odczytania z pliku");
                    informacja.exec();
                    return;
                }
            }
            getline(plikZapisu,wartoscZPliku);
            zaba->setWspolrzedna_x(stoi(wartoscZPliku));
            getline(plikZapisu,wartoscZPliku);
            zaba->setWspolrzedna_y(stoi(wartoscZPliku));
            zarzadzanieTerenami->wczytywanieZPliu(listaZapisu);
            listaTerenow = zarzadzanieTerenami->getListaTerenow();
            if(zabaNaKlodzie)
            {
                foreach(Obiekt *obiekt,listaTerenow[numerRodzicaZaby]->getListaObiektow())
                {
                    if(obiekt->getWspolrzedna_x() < zaba->getWspolrzedna_x() + 80 && obiekt->getWspolrzedna_x() + 160 > zaba->getWspolrzedna_x())
                    {
                        rodzicZabyKloda = obiekt;
                        poprzedniaWspolrzednaKlody = obiekt->getWspolrzedna_x();
                    }
                }
            }

            czyPierwszaGra = false;
            scene->nowaGra();

            dodajtereny();
            scene->aktualizacjaObiektu(numerRodzicaZaby,-1,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
            scene->wyswietlanieAktualnegoWyniku(aktualnyWynik);
            start();
        }
    }
    else
    {
        QMessageBox informacja;
        informacja.setIcon(QMessageBox::Warning);
        informacja.setText("Brak mozliwosci zapisu");
        informacja.exec();
    }
}

void Rozgrywka::przycisk(QKeyEvent *event)
{
    if(graRozpoczeta == true)
    {
        if (!listaTerenow[numerRodzicaZaby]->czyMoznaStawacNaTeren())
        {
            if (event->key() == Qt::Key_W)
            {
                if(listaTerenow[numerRodzicaZaby + 1]->czyMoznaStawacNaTeren())
                {
                    if(CzyRuchMozliwy(1,0))
                    {
                        skokZKlodyNaLad(1);
                    }
                }
                else
                {
                    skokNaKlode(1);
                }
            }
            else if(event->key() == Qt::Key_S)
            {

                if(CzyRuchMozliwy(-1,0))
                {
                    if(listaTerenow[numerRodzicaZaby - 1]->czyMoznaStawacNaTeren())
                    {
                        skokZKlodyNaLad(0);
                    }
                    else
                    {
                        skokNaKlode(-1);
                    }
                }
            }
        }
        else
        {
            if(event->key() == Qt::Key_W)
            {
                if(CzyRuchMozliwy(1,0))
                {
                    if(!listaTerenow[numerRodzicaZaby +1]->czyMoznaStawacNaTeren())
                    {
                        skokNaKlode(1);

                    }
                    else
                    {
                        zabaNaKlodzie = false;
                        numerRodzicaZaby++;
                        aktualnyWynik++;
                        scene->wyswietlanieAktualnegoWyniku(aktualnyWynik);
                    }
                }
            }
            else if(event->key() == Qt::Key_S)
            {
                if(CzyRuchMozliwy(-1,0))
                {
                    if(!listaTerenow[numerRodzicaZaby -1]->czyMoznaStawacNaTeren())
                    {
                        skokNaKlode(-1);

                    }
                    else
                    {
                        zabaNaKlodzie = false;
                        numerRodzicaZaby--;
                        aktualnyWynik--;
                        scene->wyswietlanieAktualnegoWyniku(aktualnyWynik);
                    }
                }
            }

        }
        if(event->key() == Qt::Key_A)
        {
            if(CzyRuchMozliwy(0,1))
            {
                zaba->przesun(1,0);
                if(!listaTerenow[numerRodzicaZaby]->czyMoznaStawacNaTeren())
                {
                    if(zaba->getWspolrzedna_x() - rodzicZabyKloda->getWspolrzedna_x() < -80 || zaba->getWspolrzedna_x() - rodzicZabyKloda->getWspolrzedna_x() > 160)
                    {
                        zabaNaKlodzie = false;
                        scene->aktualizacjaObiektu(numerRodzicaZaby,-1,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
                        emit koniecGry();
                    }
                }

            }
        }
        if(event->key() == Qt::Key_D)
        {
            if(CzyRuchMozliwy(0,-1))
            {
                zaba->przesun(0,1);
                if(!listaTerenow[numerRodzicaZaby]->czyMoznaStawacNaTeren())
                {
                    if(zaba->getWspolrzedna_x() - rodzicZabyKloda->getWspolrzedna_x() < -80 || zaba->getWspolrzedna_x() - rodzicZabyKloda->getWspolrzedna_x() > 160)
                    {
                        zabaNaKlodzie = false;
                        scene->aktualizacjaObiektu(numerRodzicaZaby,-1,zaba->getWspolrzedna_x(),zaba->getWspolrzedna_y());
                        emit koniecGry();
                    }
                }
            }
        }
        if(event->key() == Qt::Key_Escape)
        {
            przerwaWGrze();
            graRozpoczeta = false;

        }

    }
    else
    {
        if(event->key() == Qt::Key_P)
        {
            wznowienieGry();
            graRozpoczeta = true;
        }
    }

}


