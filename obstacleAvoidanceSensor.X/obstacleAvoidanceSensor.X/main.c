/*
 *File:   main.c
 *Date: 2022
 *Author: Miguel Quevedo <mquevedo@unicauca.edu.co>
 *brief: obstacle avoidance sensor test
 */


#include    <xc.h>
#include    <pic16f887.h>
#include    "config.h"
#include    <string.h>
#include    "LCD.h"

void main(void) {
    
    OSCCON = 0x71;//Inicializa el oscilador.
    
    TRISC1 = 1; //Configura el pin C1 como entrada.
    TRISC4 = 0; //Configura el pin C4 como salida.
    TRISC5 = 0; //Configura el pin C5 como salida.
    PORTCbits.RC1 = 0; //Inicializa C1 en 0.
    PORTCbits.RC4 = 0; //Inicializa C4 en 0.
    PORTCbits.RC5 = 0; //Inicializa C5 en 0.
    
    while(1){
   
        if( PORTCbits.RC1 == 1)
        {
            PORTCbits.RC5=1; //Enciende el led
            PORTCbits.RC4=1; //Enciende el buzzer
        }
        else if (PORTCbits.RC1 == 0){
            PORTCbits.RC5=0; //Enciende el led
            PORTCbits.RC4=1; //Enciende el buzzer
        }
    }
}
