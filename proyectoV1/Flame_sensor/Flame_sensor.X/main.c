/*
 * File:   main.c
 * Author: UsuarioPC
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
TRISC0=1; //Entrada
TRISC3=0; //Salida
TRISC4=0;
PORTCbits.RC0=0;
PORTCbits.RC3=0;
PORTCbits.RC4=0;

while(1) { 
    if( PORTCbits.RC0 == 1)
    {
    PORTCbits.RC3=1;
    __delay_ms(300);
    PORTCbits.RC4=1;
    __delay_ms(1000);
     PORTCbits.RC4=0;
    }
    else if (PORTCbits.RC0 == 0){
        PORTCbits.RC3=0;
        __delay_ms(300);
    }
    }
}
