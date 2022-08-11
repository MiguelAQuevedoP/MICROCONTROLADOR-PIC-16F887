/*
 * File:   ADC.c
 * Author: UsuarioPC
 *
 * Created on 5 de agosto de 2022, 13:06
 */


#include    <xc.h>
#include    <pic16f887.h>
#include    "config.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "LCD.h"
#define BETA 4090


int value_adc = 0;//16 bits
unsigned char counter_digito = 0;
int temp = 0;
unsigned char lm35 = 0;

void ADC_init(void) {
    
    ANSEL = 0x01;
    PORTA=0;
    TRISA0 = 1; //Configura el pin A0 como entrada.
    TRISA1 = 0; //Configura el pin A1 como salida.
    TRISA2 = 0; //Configura el pin A2 como salida.
    TRISA3 = 0; //Configura el pin A3 como salida.
     
//ADC CONFIGURACION
    ADCON1bits.ADFM = 1; //  Justificaci�n Derecha (modo-8bits).
    ADCON1bits.VCFG0 = 0; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON1bits.VCFG1 = 0; 
    
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Anal�gico AN0.
    ADCON0bits.ADCS = 0b01; //  Tiempo de Conversi�n Fosc/8.
    ADCON0bits.ADON = 1;//  Habilita el M�dulo AD.
}

int capturaTemp (){
        ADCON0bits.GO_DONE = 1; //  Inicia la COnversi� AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversi�n AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        
        return temp;
}
char valorTemperatura(){
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
        __delay_ms(3000);
    return Temperature;
}

