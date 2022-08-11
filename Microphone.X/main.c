/*
 * File:   main.c
 * Author: Mary Alejandra Valencia
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 3 de agosto de 2022, 11:32
 */


#include <xc.h>
#include <pic16f887.h>  //Header file PIC16f887 definitions
#include "config.h" //import the configurations from Header Files

int main(void) {
    OSCCON = 0x71;//Inicializa el oscilador.
    TRISC2 = 1; //Configura pin C2 como entrada.
    TRISC6 = 0; //Configura pin E0 como salida.
    PORTCbits.RC2 = 0; //Inicializa C2 en 0.
    PORTCbits.RC6 = 0; //Inicializa C2 en 0.

    while (1) {

        if(PORTCbits.RC2 == 1 ){

           if(PORTCbits.RC6 == 0){
            PORTCbits.RC6 = 1;  //Enciende el led
           }
           else if (PORTCbits.RC6){
            PORTCbits.RC6 = 0;  //Apaga el le
           }
        }
    }   
}
