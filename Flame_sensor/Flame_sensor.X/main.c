/*
 * File:   main.c
 * Author: Mary Alejandra Valencia
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 3 de agosto de 2022, 0:22
 */

#include    <xc.h>
#include    <pic16f887.h>
#include    "config.h"
#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>

int main(void) {
    OSCCON = 0x71;   
    TRISC0=1; //Configura el pin C0 como entrada.
    TRISC3=0; //Configura el pin C3 como salida.
    TRISC4=0; //Configura el pin C4 como salida.
    PORTCbits.RC0=0; //Inicializa C0 en 0.
    PORTCbits.RC3=0; //Inicializa C3 en 0.
    PORTCbits.RC4=0; //Inicializa C4 en 0.

    while(1) { 
        if( PORTCbits.RC0 == 1)
        {
            PORTCbits.RC3=1; //Activa Led1
            PORTCbits.RC4=1; //Activa buzzer
        }
        else if (PORTCbits.RC0 == 0){
            PORTCbits.RC3=0; //Desactiva Led2
            PORTCbits.RC4=0; //Desactiva buzzer
        }
     }
}
