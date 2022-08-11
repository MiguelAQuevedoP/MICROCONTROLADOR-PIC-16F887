/*
 * File:   main.c
 * Author: Mary Alejandra Valencia
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 3 de agosto de 2022, 12:50
*/

#include <xc.h>
#include <pic16f887.h>  
#include <stdio.h>
#include <string.h>
#include "CONFIG.h"
#include "LCD.h"
#include "KEYPAD.h"

const char password[5] ={'2','0','2','1',0};
char pass_user[5];
unsigned char idx = 0;
int counter_try = 0;
char key = '0';

void main() {

    OSCCON = 0x71; //Configura oscilador interno (FOSC = 8Mhz)
    ANSELH = 0x00;
    TRISC = 0x00; 
    TRISA = 0x00;
    LCD_Init(); //Inicializa el LCD
    keypad_init(); //Inicializa el keypad

    while (1) {
        
        //Digitar contraseña
        LCD_String_xy(0,0,"Press a Key");
        LCD_Command(0xC0); 
        do{
            key = keypad_getkey();
            if(key != 0){
                LCD_Char(key); //Visualiza caracteres digitados en LCD
                pass_user[idx++] = key; //Guarda cada caracter en pass_user
            }
            __delay_ms(100);
        }while(idx < 5);
        
       
        if(strncmp(pass_user,password,4)==0){ // Compara la contraseña digitada con la contraseña declarada
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Correcta");
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
            __delay_ms(12000); //Retardo de 12 segundos cuando la contraseña es incorrecta tres veces
        }
        __delay_ms(2000);
        LCD_Clear();
        idx = 0;
    }
    
    
}

