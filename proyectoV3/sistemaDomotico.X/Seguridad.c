/*
 * File:   Seguridad.c
 * Author: UsuarioPC
 *
 * Created on 5 de agosto de 2022, 13:22
 */


#include <xc.h>
#include <pic16f887.h>  /*Header file PIC16f887 definitions*/
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "LCD.h"
#include "KEYPAD.h"

const char password[5] ={'2','0','2','1',0};
char pass_user[5];
unsigned char idx = 0;
int counter_try = 0;
char key = '0';
int flag = 0;

void seguridad_init (void){
    ANSELH = 0x00;
    TRISC = 0x00;
    TRISA = 0x00;
}

void verificarSeguridad(){
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
            flag = 1;
            /*PORTA = 0x01;
            for(int i = 0; i < 8; i++){
        
                if(i % 2 == 0){
                    PORTC = 0xAA;
                }
                else if(i % 2 != 0){
                    PORTC = 0x55;
                }
            }*/

        }
        else{
            counter_try++;
            LCD_Clear();
            LCD_String_xy(0,0,"Clave Incorrecta"); 
            flag = 0;
        }
        if (counter_try == 3){
            LCD_Clear();
            LCD_String_xy(0,0,"Ingreso No Permitido");
            //PORTA = 0x02;
            __delay_ms(12000);
            flag = 0;
        }
        __delay_ms(2000);
        LCD_Clear();
        idx = 0;
        return flag;
}
