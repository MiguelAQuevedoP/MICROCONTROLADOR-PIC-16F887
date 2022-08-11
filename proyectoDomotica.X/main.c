/*
 * File:   main.c
 * Author: Miguel Antonio Quevedo Pantoja
 * Correo: mquevedo@unicauca.edu.co
 *
 * Created on agosto de 2022
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
#define BETA 4090 //VALOR NECESARIO PARA LA CONVERSION DE TEMPERATURA
#define resistance 10 //NECESARIO PARA LA CONVERSION DE TEMPERATURA
const char inputPassword[5] = {'2','0','2','1',0}; //CONTRASEÑA DE ENTRADA DE SISTEMA
const char exitPassword[2] = {'*',0}; //CONTRASEÑA DE SALIDA DE SISTEMA
char pass_user[5];
char pass_user2 [2];
unsigned char idx = 0;//ACUMULA NUMERO DE CARACTERES PARA LA CONTRASEÑA DE ENTRADA DE SISTEMA
unsigned char idx2 = 0;//ACUMULA NUMERO DE CARACTERES PARA LA CONTRASEÑA DE SALIDA DE SISTEMA
int counter_try = 0;//CUENTA LOS INTENTOS ERRONEOS DE CONTRAÑESA DE ENTRADA
char key = '0';//LA CONTRASEÑA DE ENTRADA SE GUARDA COMO LLAVE PARA ENTRAR
char key2 = '0';//LA CONTRASEÑA DE ENTRADA SE GUARDA COMO LLAVE PARA SALIR

//ADC
int value_adc = 0;//16 bits
unsigned char counter_digito = 0;
double temp = 0.0;
unsigned char lm35 = 0;

//BANDERA INDICA SI LA HABITACIÓN ESTÁ OCUPADA O NO
int flag = 0;

void main(void) {
    
    OSCCON = 0x71;
    ANSELH = 0x00;
    TRISC = 0x00;
    TRISA = 0x00;
    
//ADC_init
    ANSEL = 0x01;//CONFIGURA EL PIN COMO ENTRADA ANALOGICA
    PORTA = 0;//INICIALIZA EL PUERTO A COMO CERO
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
    TRISC0 = 1; //CONFIGURA EL PIN C0 COMO ENTRADA PARA SENSOR DE FLAMA
    TRISC3 = 0; //CONFIGURA EL PIN C3 COMO SALIDA PARA LED 1
    TRISC4 = 0; //CONFIGURA EL PIN C4 COMO SALIDA PARA BUZZER
    PORTCbits.RC0 = 0; // Pin C0 inicia en 0 (sensor de flama)
    Led1 = 0; // Pin C3 inicia en 0 (led1)
    buzzer = 0; // Pin C4 inicia en 0
    
//microfono
    TRISC2 = 1;//CONFIGURA EL PIN C2 COMO ENTRADA PARA MICROFONO
    TRISC6 = 0;//CONFIGURA EL PIN C6 COMO ENTRADA PARA LED 3
    Led3 = 0; //PIN C6 inicia en 0
    Microfono = 0; //PIN C2 inicia en 0
    
//sensor_proximidad
    TRISC1 = 1;//CONFIGURA EL PIN C1 COMO ENTRADA PARA SENSOR DE PROXIMIDAD
    TRISC5 = 0;//CONFIGURA EL PIN C5 COMO SALIDA PARA LED 2
    PORTCbits.RC1 = 0;  //salida C1 inicia en cero (sensor de ostaculos)
    Led2 = 0; //salida RC5 inicia en 0
    
    keypad_init();//INICIALIZA EL TECLADO
    LCD_Init();//INICIALIZA EL LCD
    
    while (1){
        
        //Sensor de flama
        if( PORTCbits.RC0 == 1){
            buzzer = 1; //Activar buzzer
            Led1 = 1; //ACTIVA EL PIN C3 (LED 1)
        }
        else{
            buzzer = 0; //desactiva buzzer
            Led1 = 0; //DESACTIVA EL PIN C3 (LED 1)
            Led2 = 0; //DESACTIVA EL PIN C5 (LED 2)
        }
        //SI LA CASA ESTÁ VACIA FLAG = 0 POR LO TANTO EL SENSOR DE PROXIMIDAD
        //ESTARÁ ACTIVO
        //Sensor de proximidad
        if (flag == 0){
            if ( PORTCbits.RC1 == 1){
                buzzer = 1; //Activar buzzer
                Led2 = 1; //Activa segundo LED
            }
        }
        //microfono
        else if(Microfono == 1){
            Led3 = 1;
        }
        
        //captura la temperatura
        ADCON0bits.GO_DONE = 1; //  Inicia la Conversión AD.
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
        __delay_ms(1000);
        
        //Seguridad
        if (flag == 0){//SI LA HABITACION ESTÁ VACIA
            if(idx == 0){//SI NO SE HA INGRESADO NINGUN CARACTER
                LCD_String_xy(2,0,"Press a Key IN");//MENSAJE EN PANTALLA
                LCD_Command(0xC0);
            }
            do{
                key = keypad_getkey();//REGISTRA COMO LLAVE LA CONTRASEÑA INGRERSADA
                if(key != 0){
                    LCD_Clear();
                    LCD_Char(key);/* display pressed key on LCD16x2 */
                    pass_user[idx++] = key;
                }
            }while(idx<5);
        }
        //SI LA HABITACION ESTÁ OCUPADA FLAG = 1
        else{
            if (idx2 == 0){//SI LA OCNTRASEÑA DE SALIDA NO TIENE NINGUN CARACTER
                LCD_Clear();
                LCD_String_xy(2,0,"Press a Key OUT");
                LCD_Command(0xC0); 
            }
            key2 = keypad_getkey2();//REGISTRA LA CONTRASEÑA DE SALIDA
            if(key2 != 0){
                LCD_Char(key2);/* display pressed key on LCD16x2 */
                pass_user2[idx2++] = key2;
            }
        }
        
        if (idx > 4 ){//SI LOS CARACTERES DE CONTRASEÑA DE ENTRADA SON SUFICIENTES COMPRUEBA SI ES CORRECTA
            if(strncmp(pass_user,inputPassword,4)==0){
                LCD_Clear();
                //Ingreso
                buzzer = 0;
                LCD_String_xy(0,0,"Clave Correcta" );
                __delay_ms(2000);
                flag = 1;
            }
            else if (counter_try == 3){//SI LA CONTRASEÑA DE ENTRADA SUPERA LOS INTENTOS FALLIDOS
                LCD_Clear();
                LCD_String_xy(0,0,"Ingreso No Permitido");
                __delay_ms(5000);
                idx = 0;
            }
            else {//SI LA CONTRASEÑA DE ENTRADA NO ES CORRECTA
                LCD_Clear();
                counter_try = counter_try++;//SUMA UN INTENTO DE CONTRASEÑA INCORRECTA
                LCD_String_xy(0,0,"Clave incorrecta" );
                __delay_ms(200);
                idx = 0;
            }
        }
        
        else if(idx2 > 1){//SI LA CONTRAÑESA SE SALIDA SUPERA LOS CARACTERES COMPRUEBA SI ES CORRECTA
            if(strncmp(pass_user2,exitPassword,1)==0){
                LCD_Clear();
                LCD_String_xy(0,0,"Clave Correcta" );
                LCD_String_xy(2,0,"Fuera del sistema");
            }
            else{
                LCD_Clear();
                LCD_String_xy(0,0,"Clave incorrecta");
                LCD_String_xy(2,0,"Ingrese caracter");
            }
            idx2 = 0;
        }
        __delay_ms(1000);
        
    }
}

