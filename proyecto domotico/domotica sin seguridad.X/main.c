/*
 * File:   main.c
 * Author: Miguel Antonio Quevedo Pantoja
 * Correo: mquevedo@unicauca.edu.co
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

//ADC
int value_adc = 0;//16 bits
unsigned char counter_digito = 0;
double temp = 0.0;
unsigned char lm35 = 0;

//Maquina
int stateHome = 0;

//bandera casa ocupada
int flag = 0;

void main(void) {
    
    OSCCON = 0x71;
    ANSELH = 0x00;
    TRISC = 0x00;
    TRISA = 0x00;
//ADC_init
    ANSEL = 0x01;
    PORTA = 0;
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
    
//flame_sensor
    TRISC0 = 1; //Entrada
    TRISC3 = 0; //Salida led1
    TRISC4 = 0; //Salida buzzer
    FlameSensor = 0; // Pin C0 inicia en 0 (sensor de flama)
    Led1 = 0; // Pin C3 inicia en 0 (led1))
    buzzer = 0; // Pin C4 inicia en 0
    
//microfono
    TRISC2 = 1;//Entrada
    TRISC6 = 0;//Salida led3
    Led3 = 0; //puerto C6 inicia en 0
    Microfono = 0; //puerto C2 inicia en 0
    
//sensor_proximidad
    TRISC1 = 1;//se configura como entrada en el pin C1
    TRISC5 = 0;//salida en C5 led2
    PORTCbits.RC1 = 0;  //salida C1 inicia en cero (sensor de ostaculos))
    Led2 = 0; //salida RC5 inicia en 0
    
    LCD_Init();
    
    while (1){
        
        //Sensor de flama
        if( FlameSensor == 1){
            buzzer = 1; //Activar buzzer
            Led1 = 1;
        }
        //microfono
        else if( Microfono == 1){
            Led3 = 1;
        }
        //sensor de obstaculos
        else if ( SensorObstaculos == 1){
            buzzer = 1; //Activar buzzer
            Led2 = 1; //Activa segundo LED
        }
        else{
            buzzer = 0; //desactiva buzzer
            Led1 = 0; //desactiva primer LED
            Led2 = 0; //desactiva segundo LED
        }
        
        //captura la temperatura
        ADCON0bits.GO_DONE = 1; //  Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        
        //conversion temperatura
        long a = (long)(1023 - temp);
        float tempC = (float)(BETA /(log((1025.0 * 10/ a - 10) / 10) + BETA / 298.0) - 273.0);
        
        //imprime la temperatura
        char Temperature [10];
        sprintf(Temperature, "%d%cC", (int)tempC,0xdf );
        //LCD_Clear();
        LCD_String_xy(1,0,"Temperatura:");
        LCD_String(Temperature);
        LCD_String("  ");
        
        if (  tempC > 25){
            LCD_String_xy(2,0,"Disminuir Temp");
            //__delay_ms(2000);
        }
        else  if ( tempC < 18 ){
            LCD_String_xy(2,0,"Aumentar Temp"); 
            //__delay_ms(2000);
        }
        else {
            LCD_String_xy(2,0,"Temp Adecuada");
            //__delay_ms(2000);
        }
        __delay_ms(1000);  
    }
}