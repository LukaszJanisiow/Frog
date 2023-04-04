#ifndef PRZYCISKSTARTUGRY_H
#define PRZYCISKSTARTUGRY_H

#include<QPushButton>

using namespace std;

/**
 * \brief Klasa PrzyciskStartuGry odpowiada za tworzenie przycisków
 */
class PrzyciskStartuGry :  public QPushButton
{
    Q_OBJECT
public:
    /**
     * \brief Tworzy przycisk o podanej nazwie
     *  @param napis nazwa wyswietlana na przycisku
     */
    PrzyciskStartuGry(string napis);

signals:
    /**
     * \brief Sygnal, że przycisk został naciśnięty
     */
    void start();


protected:
    /**
     * \brief Funkcja odpowiadająca za reakcję na kliknięcie przycisku
     */
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // PRZYCISKSTARTUGRY_H
