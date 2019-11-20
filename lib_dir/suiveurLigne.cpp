#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "suiveurLigne.h"
#include "uart.h"

SuiveurLigne::SuiveurLigne(uint8_t vitesse) :
    Navigator(vitesse)
{
};

void SuiveurLigne::redressementDroit(){
    ajustementPWM(0, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
};

void SuiveurLigne::redressementGauche()
{  
    ajustementPWM(_vitesse, DIRECTION::AVANT, 0, DIRECTION::AVANT);
};

void SuiveurLigne::tournerDroit(){
    ajustementPWM(_vitesse, DIRECTION::ARRIERE, _vitesse, DIRECTION::AVANT);
    while(!(PINC & (1 << EXTREME_DROITE)));
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
};

void SuiveurLigne::tournerGauche(){
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::ARRIERE);
    while(!(PINC & (1 << EXTREME_GAUCHE)));
    ajustementPWM(_vitesse,DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
};

bool SuiveurLigne::suivreLigne(){
    _delay_ms(75);
    if (!suiveurLigneAllume())
    {
        //transmissionUART(90);
        _delay_ms(15); //Delais de debounce
        if (!suiveurLigneAllume())
        {
            stopPWM();
            return false;
        }
    }
    else if (!(PINC & (1 << MILIEU)))
    {
        if(PINC & (1 << EXTREME_GAUCHE) || PINC & (1 << GAUCHE))
        {
            redressementDroit();
        }
        else if (PINC & (1 << EXTREME_DROITE) || PINC & (1 << DROITE)) 
        {
            redressementGauche();
        }
        return true;
    }
    else
    {
        ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
        return true;
    }
    return true;
};

bool SuiveurLigne::suiveurLigneAllume(){
    return (PINC & (1<< EXTREME_GAUCHE) ||
            PINC & (1<< GAUCHE) ||
            PINC & (1<< MILIEU) ||
            PINC & (1<< DROITE) ||
            PINC & (1<< EXTREME_DROITE));
};
