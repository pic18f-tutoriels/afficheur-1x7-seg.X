#include <htc.h>

/**
 * Bits de configuration:
 */
#pragma config FOSC = INTIO67  // Osc. interne, A6 et A7 comme IO.
#pragma config IESO = OFF      // Pas d'osc. au démarrage.
#pragma config FCMEN = OFF     // Pas de monitorage de l'oscillateur.

// Nécessaires pour ICSP / ICD:
#pragma config MCLRE = EXTMCLR // RE3 est actif comme master reset.
#pragma config WDTEN = OFF     // Watchdog inactif.
#pragma config LVP = OFF       // Single Supply Enable bits off.

/**
 * Point d'entrée.
 * Configure le port A comme entrée, et le B comme sortie.
 * Puis copie la valeur lue du port A dans le port B.
 */
void main()
{
    unsigned char port;

    ANSELA = 0x00;      // Désactive les convertisseurs A/D.
    ANSELB = 0x00;      // Désactive les convertisseurs A/D.
    ANSELC = 0x00;      // Désactive les convertisseurs A/D.

    TRISB = 0xff;       // Tous les bits du port A comme entrées.
    TRISA = 0x00;       // Tous les bits du port C comme sorties.
    WPUB = 0xff;        // Active toutes les résistances de tirage du port B.
    INTCON2bits.RBPU=0; // Active le module de résistances de tirage.

    while(1)
    {
        // Récupère la valeur du port B...
        port = PORTB;

        // ...et la copie sur le port A.
        LATA = port;
    }
}
