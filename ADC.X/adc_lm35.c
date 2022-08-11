/*
 * File:   adc_lm35.c
 * Author: Mary Alejandra Valencia
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 3 de agosto de 2022, 0:22
 */

#include    <xc.h>
#include    <pic16f887.h>
#include    "config.h"
#include    <string.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <math.h>
#include    "LCD.h"
#define     BETA 4090
#define     resistance 10

unsigned int value_adc = 0;//16 bits
unsigned char counter_digito = 0;
double temp = 0.0;
unsigned char lm35 = 0;

void main(void) {
    
    OSCCON = 0x71; //Inicializa el oscilador.
    ANSEL = 0x01; //  Configura el Puerto como Entrada Analógica.
    PORTA=0;
    TRISA0 = 1; //Configura el pin A0 como entrada.
    TRISA1 = 0; //Configura el pin A1 como salida.
    TRISA2 = 0; //Configura el pin A2 como salida.
    TRISA3 = 0; //Configura el pin A3 como salida.
    
    
//ADC CONFIGURACION
    ADCON1bits.ADFM = 1; //  Justificación Derecha (modo-8bits).
    ADCON1bits.VCFG0 = 0; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON1bits.VCFG1 = 0; 
    
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Analógico AN0.
    ADCON0bits.ADCS = 0b01; //  Tiempo de Conversión Fosc/8.
    ADCON0bits.ADON = 1;//  Habilita el Módulo AD.
    
    __delay_us(30);
    LCD_Init();
    
    while (1) {
         //camptura temperatura
        ADCON0bits.GO_DONE = 1; //  Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        
        //Convertir temperatura
        long a = (long)(1023 - temp);
        float tempC = (float)(BETA /(log((1025.0 * 10/ a - 10) / 10) + BETA / 298.0) - 273.0); //Calcualo de temperatura
        //Imprime la temperatura
        char Temperature [10];
        sprintf(Temperature, "%d%cC", (int)tempC,0xdf ); //Convierte temperatura en cadena
        LCD_String_xy(1,0,"TEMP:");
        LCD_String(Temperature); //Imprime temperatura en LCD
        LCD_String("  ");
        
        //Adecuar temperatura
        if (  tempC > 25){
            LCD_String_xy(2,0,"Disminuir Temp");
        }
        else  if ( tempC < 18 ){
            LCD_String_xy(2,0,"Aumentar Temp"); 
        }
        else {
            LCD_String_xy(2,0,"Adecuada");
        }
    
    LCD_String("  ");
        
    }
   
}