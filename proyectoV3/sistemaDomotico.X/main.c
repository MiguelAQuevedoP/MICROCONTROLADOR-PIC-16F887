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
#include    <pic16f887.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BETA 4090
#define resistance 10

void main(void) {
    keypad_init();
    LCD_Init();
    sensorFlame_init();
    microphone_init();
    sensorProximidad_init();
    ADC_init();
    bool flag = true;
    while (1)
    {
         __delay_ms(300);
        LeerSensorFlame();
        long a = (long)(1023 - capturaTemp());
        float tempC = (float)(BETA /(log((1025.0 * 10/ a - 10) / 10) + BETA / 298.0) - 273.0);
        //imprime la temperatura
        char Temperature [10];
        sprintf(Temperature, "%d%cC", (int)tempC,0xdf );
        LCD_String_xy(1,0,"TEMP:");
        LCD_String(Temperature);
        LCD_String("  ");
        if (  tempC > 25){
             LCD_Clear();
            LCD_String_xy(2,0,"Disminuir Temp");
            __delay_ms(3000);
        }
        else  if ( tempC < 18 ){
             LCD_Clear();
            LCD_String_xy(2,0,"Aumentar Temp"); 
             __delay_ms(3000);
        }
        else {
             LCD_Clear();
            LCD_String_xy(2,0,"Temp Adecuada");
             __delay_ms(3000);
             LCD_Clear();
        }
    __delay_ms(300);
    LeerSensorProximidad();
    __delay_ms(300);
    if (verificarSeguridad() == 1){
    __delay_ms(300);
    LeerMicrofono();
    }
    }
}
