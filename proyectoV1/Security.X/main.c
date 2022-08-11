/*
 * File:   main.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 12:50

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2022. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/
#include <xc.h>
#include <pic16f887.h>  /*Header file PIC16f887 definitions*/
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "LCD.h"
#include "KEYPAD.h"

const char password[5] ={'2','0','2','1',0};
char pass_user[5];
unsigned char idx = 0;
int counter_try = 0;

void main() {

    char key = '0';
    //Configura Fosc = 8Mhz interno, Fuente de Fosc del sistema = interno
    OSCCON = 0x71; //Configura oscilador interno (FOSC = 8Mhz)
    ANSELH = 0x00;
    TRISC = 0x00;
    TRISA = 0x00;
    LCD_Init(); //Inicializa el LCD
  
    keypad_init(); //Inicializa el keypad

    while (1) {
        LCD_String_xy(0,0,"Press a Key");
        LCD_Command(0xC0); 
        do{
            key = keypad_getkey();
            if(key != 0){
                //LCD_Char('*');/* display pressed key on LCD16x2 */
                LCD_Char(key);/* display pressed key on LCD16x2 */
                pass_user[idx++] = key;
            }
            __delay_ms(100);
        }while(idx < 5);
        
        if(strncmp(pass_user,password,4)==0){
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Correcta");
            PORTA = 0x01;
            for(int i = 0; i < 8; i++){
                
                if(i % 2 == 0){
                    PORTC = 0xAA;
                }
                else if(i % 2 != 0){
                    PORTC = 0x55;
                }
            }

        }
        else{
            counter_try = counter_try++;
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Incorrecta");            
        }
        if (counter_try == 3){
            LCD_Clear();
            LCD_String_xy(0,0,"Ingreso No Permitido");
            PORTA = 0x02;
            __delay_ms(12000);
        }
        __delay_ms(2000);
        LCD_Clear();
        idx = 0;
    }
    
    
}

