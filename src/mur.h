#ifndef MUR_H
#define MUR_H

#include <util/delay.h>
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "led.h"

enum EtatMur
{
    debutLigne, 
    suivreMur,
    virageDroit,
    finLigne, 
    virageGauche
};

class Mur : public SuiveurLigne
{
public:
    Mur(uint8_t vitesse, LCM* lcd);
    ~Mur();

    void run();
    void doAction();
    void changeState();

    void enableSonar();
    void fetchSonar();

    void moveToWall();
    void moveAgainstWall();
    void goStraight();
    void followWall();
    void goToLine();

private:
    EtatMur _etat;
    Led _led;
    LCM* _lcd;
    bool _isDone;

    const uint8_t DEMARAGE = 254;
    const uint8_t HAUTE_INTENSITE = 90;
    const uint8_t BASSE_INTENSITE = 38;
    const uint8_t AVANT = 0;
    const uint8_t ARRIERE = 1;
};

#endif // MUR_H