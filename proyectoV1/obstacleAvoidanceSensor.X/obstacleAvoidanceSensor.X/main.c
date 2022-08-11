/*
 *File:   main.c
 *Date: 2022
 *Author: Miguel Quevedo <mquevedo@unicauca.edu.co>
 *brief: obstacle avoidance sensor test
 */


#include    <xc.h>
#include    <pic16f887.h>
#include    "config.h"
#include <string.h>
#include "LCD.h"



double temp = 0.0;
void main(void) {
    
    OSCCON = 0x71;//INICIALIZA EL OSCILADOR
    
    LCD_Init();
    
    TRISC1 = 1; //CONFIGURA RC COMO ENTRADA
    TRISC4 = 0;
    TRISC5 = 0;
    PORTCbits.RC1 = 0;  
    PORTCbits.RC4 = 0;
    PORTCbits.RC5 = 0;
    __delay_ms(300);//ESPERA 300MS ANTES DE CONTINUAR
    
    while(1){
        /*
        if(PORTCbits.RC1 == 0){
                
            LCD_String_xy(0,0,"Alarma");
            PORTCbits.RC4 = 1; //Enciende el buzzer
            
            PORTCbits.RC5 = 1; //Enciende el led
            __delay_ms(300);
            
        }
        else if (PORTCbits.RC1 == 1){
        PORTCbits.RC5=0;
        PORTCbits.RC4 = 0; //Apaga el buzzer
        LCD_Clear();
        __delay_ms(1000);
        }
     */  
    if( PORTCbits.RC1 == 1)
    {
        PORTCbits.RC5=1;
        __delay_ms(300);
        PORTCbits.RC4=1;
        __delay_ms(1000);
         PORTCbits.RC4=0;
    }
    else if (PORTCbits.RC1 == 0){
        PORTCbits.RC5=0;
        __delay_ms(300);
    }
    }
        
    
}
