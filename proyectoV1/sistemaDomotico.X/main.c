/*
 * File:   main.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 17:20
 */

#include "KEYPAD.h"
#include <xc.h>
#include "LCD.h"
#include "config.h"
#include "pines.h"
#include <stdbool.h>
#include <math.h>
#include <pic16f887.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BETA 4090
#define resistance 10
const char inputPassword[5] = {'2','0','2','1',0};
const char exitPassword[2] = {'*',0};
char pass_user[5];
char pass_user2 [2];
unsigned char idx = 0;
int counter_try = 0;
char key = '0';

void main(void) {
    keypad_init();
    LCD_Init();
    sensorFlame_init();
    microphone_init();
    sensorProximidad_init();
    ADC_init();
 
    while (1)
    {
        OSCCON = 0x71;
        ANSELH = 0x00;
        TRISC = 0x00;
        TRISA = 0x00;
       
        //Sensor de flama
        if (LeerSensorFlame() == 1)
        {
            buzzer = 1; //Activar buzzer
            Led1=1;
        }
        else
        {
             buzzer = 0; //Apagar buzzer
             Led1=0;
        }
        
        if (LeerSensorProximidad() == 1){
            buzzer = 1;
            Led2=1;
        }
        else{
            buzzer = 0;  
            Led2=0;
        }
        __delay_ms(2000);
        /*
        long a = (long)(1023 - capturaTemp());
        float tempC = (float)(BETA /(log((1025.0 * 10/ a - 10) / 10) + BETA / 298.0) - 273.0);
        //imprime la temperatura
        char Temperature [10];
        sprintf(Temperature, "%d%cC", (int)tempC,0xdf );
        LCD_Clear();
        LCD_String_xy(1,0,"TEMP:");
        LCD_String(Temperature);
        LCD_String("  ");
        if (  tempC > 25){
            
            LCD_String_xy(2,0,"Disminuir Temp");
            //LCD_Clear();
        }
        else  if ( tempC < 18 ){
            
            LCD_String_xy(2,0,"Aumentar Temp"); 
            //LCD_Clear();
        }
        else {
            
            LCD_String_xy(2,0,"Temp Adecuada");
            //LCD_Clear();
        }
        __delay_ms(3000);*/
   

        //Seguridad
        LCD_Clear();
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

        
        if(strncmp(pass_user,inputPassword,4)==0){
            LCD_Clear();
            //Ingreso

            LCD_String_xy(0,0,"Clave Correcta" );
            __delay_ms(200);
            
            do{
                
            if (LeerMicrofono() == 1){
                Led3=1;
            }
            else if (Led3 == 1){
                Led3=0;
            }
            idx=0;  
            LCD_Clear();
            LCD_String_xy(0,0,"Press a Key.");
            LCD_Command(0xC0); 
        
            
                key = keypad_getkey();
                if(key != 0){
                    //LCD_Char('*');/* display pressed key on LCD16x2 */
                    LCD_Char(key);/* display pressed key on LCD16x2 */
                    pass_user[idx++] = key;
                }
                __delay_ms(100);
            }while(idx < 2);
        
            if(strncmp(pass_user2,exitPassword,4)==0){
                LCD_Clear();
                LCD_String_xy(0,0,"Clave Correcta" );
            }
            else{
                LCD_Clear();
                counter_try = counter_try++;
                LCD_String_xy(0,0,"Clave incorrecta" );
            }
        }
        else{
                LCD_Clear();
                counter_try = counter_try++;
                LCD_String_xy(0,0,"Clave incorrecta" );
                __delay_ms(200);
            }
        if (counter_try == 3){
            LCD_Clear();
            LCD_String_xy(0,0,"Ingreso No Permitido");
            __delay_ms(5000);
        }
        
        __delay_ms(2000);
        LCD_Clear();
        idx = 0;
    }
}
