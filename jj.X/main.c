/*
 * File:   main.c
 * Author: UsuarioPC
 *
 * Created on 10 de agosto de 2022, 12:16
 */


#include <xc.h>
#include "config.h"
#include <stdbool.h>
#include <math.h>
#include <pic16f887.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BETA 4090
#define resistance 10

int main(void) {
    /* Replace with your application code */
    
    OSCCON = 0x71;   
    TRISC0=1; //Entrada
    TRISC1=1;
    TRISC2=1;
    TRISC3=0; //Salida
    TRISC4=0;
    TRISC5=0;
    TRISC6=0;
        
    PORTCbits.RC0=0;
    PORTCbits.RC1=0;
    PORTCbits.RC2=0;
    PORTCbits.RC3=0;
    PORTCbits.RC4=0;
    PORTCbits.RC5=0;
    PORTCbits.RC6=0;
    int i =0;
    while (1) {
        
    if( PORTCbits.RC0 == 1)
    {
    PORTCbits.RC3=1;
    PORTCbits.RC4=1;
    
    }
    else {
        PORTCbits.RC3=0;
        PORTCbits.RC4=0;   
    }
     if(PORTCbits.RC2 == 1 ){
            
     PORTCbits.RC6 = 1;  //Enciende el led
           
    }
    else {
        PORTCbits.RC6 = 0;  //Apaga el led
    }
     
     
    if( PORTCbits.RC1 == 1)
    {
        PORTCbits.RC5=1;
        PORTCbits.RC4=1;    
    }
    else {
        PORTCbits.RC5=0;
         PORTCbits.RC4=0;

    }
    }
}
