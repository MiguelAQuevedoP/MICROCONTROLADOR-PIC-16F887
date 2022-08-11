/*
 * File:   main.c
 * Author: Mary Alejandra Valencia
 *
 * Created on 3 de agosto de 2022, 11:32
 */


#include <xc.h>
#include <pic16f887.h>  //Header file PIC16f887 definitions
#include "config.h" //import the configurations from Header Files

int main(void) {
    OSCCON = 0x71;//INICIALIZA EL OSCILADOR
    TRISC2 = 1; //Configura pin C2 como entrada
    TRISC6 = 0; //Configura pin E0 como salida
    PORTCbits.RC2=0;
    PORTCbits.RC6=0;
    int i = 0;
    while (1) {

        if(PORTCbits.RC2 == 1 ){
            i++;
            __delay_ms(2000);
           if(PORTCbits.RC6 == 0 && i == 2){
            PORTCbits.RC6 = 1;  //Enciende el led
            i=0; 
           }
           else if (PORTCbits.RC6 == 1 && i==2){
            PORTCbits.RC6 = 0;  //Apaga el led
            i=0;
           }
        }
    }   
}
