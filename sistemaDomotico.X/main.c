/*
 * File:   main.c
 * Author: Mary Alejandra Valencia Urrea
 * Correo: maryvalencia@unicauca.edu.co
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
unsigned char idx2 = 0;
int counter_try = 0;
char key = '0';
char key1 = '0';
bool casaOcupada = false;

void main(void) {
    OSCCON = 0x71;
    ANSELH = 0x00;
    TRISC0 = 0;
    TRISC1 = 0;
    TRISC2 = 0;
    TRISC6 = 0;
    
    //Inicia los sensores
    keypad_init();
    LCD_Init();
    sensorFlame_init();
    microphone_init();
    sensorProximidad_init();
    ADC_init();
    alarma_init();

    while (1)
    {
       //Sensor de flama 
        if (LeerSensorFlame() == 1)
        {
            alarmaFlama();
        }
        else
        {
            apagarAlarma1(); 
        }
        
        //Sensor de temperatura
        
        long a = (long)(1023 - capturaTemp());
        float tempC = (float)(BETA /(log((1025.0 * 10/ a - 10) / 10) + BETA / 298.0) - 273.0); //Calcular temperatura
        
        //Imprime la temperatura
        char Temperature [10];
        sprintf(Temperature, "%d%cC", (int)tempC,0xdf ); //Convierte temperatura en cadena
        LCD_Clear();
        LCD_String_xy(2,0,"TEMP:");
        LCD_String(Temperature); //Imprime temperatura
        LCD_String("  ");
        
        //Adecuar temperatura
        if (  tempC > 25){
            LCD_String_xy(2,0,"Disminuir Temp");
        }
        else  if ( tempC < 18 ){
            LCD_String_xy(2,0,"Aumentar Temp"); 
        }
        else {
            LCD_String_xy(2,0,"Temp Adecuada");
        }
       
        //Seguridad
        
        LCD_String_xy(0,0,"Press a Key:"); 
      
        switch (casaOcupada){
        
       
            case false: 
                
                //Lee el sensor de proximidad
                if (LeerSensorProximidad() == 1){
                    alarmaSeguridad();
                }
                else{
                    apagarAlarma2();
                }
                
                key = keypad_getkey();
                
                //Imprimir contraseña de entrada en LCD
                if(key != '0'){
                    LCD_Clear();
                    LCD_Char(key);
                    LCD_String("  ");
                    __delay_ms(1000);
                    pass_user[idx++] = key; 
                }
                
                //Decide si la contraseña es correcta o incorrecta
                if (idx == 5){
                    if (strncmp(pass_user,inputPassword,5)== 0) { //Compara contraseña introducida con contraseña definida
                        LCD_Clear();
                        LCD_String_xy(2,0,"Clave Correcta" );
                        __delay_ms(1000);
                        casaOcupada = true; //Ingresa a la habitación
                        counter_try = 0;
                    }
                    else{
                        counter_try = counter_try++;
                        LCD_Clear();
                        LCD_String_xy(2,0,"Clave Incorrecta");  
                        __delay_ms(500);
                    }
                    if (counter_try == 3){
                        LCD_Clear();
                        LCD_String_xy(2,0,"Ingreso No Permitido");
                        __delay_ms(12000);
                        counter_try = 0;
                    }
                }
            break;
                
            case true:
                 
                //Encender o apagar Luz
                if( LeerMicrofono() == 1 ){

                    if(Led3 == 0){
                    Led3 = 1;  //Enciende el led
                    }
                    else if (Led3 == 1){
                    Led3 = 0;  //Apaga el led
                    }
                }
                
                key1 = keypad_getkey();
                
                //Imprimir contraseña de salida en LCD
                if (key1 != '0'){
                    LCD_Clear();
                    LCD_Char(key1);//display pressed key on LCD16x2 
                    LCD_String("  ");
                    pass_user2[idx2++] = key1;
                 }
                //Decide si la contrasea es correcta o incorrecta
                if (idx2 == 2){
                    if (strncmp(pass_user2,exitPassword,2)==0) { //Compara contraseña introducida con contrasea definida
                        LCD_Clear();
                        LCD_String_xy(2,0,".Clave Correcta" );
                        casaOcupada = false; //Sale de la habitación
                        counter_try = 0;
                    }
                    else{
                        counter_try = counter_try++;
                        LCD_Clear();
                        LCD_String_xy(2,0,".Clave Incorrecta");            
                    }
                    if (counter_try == 3){
                        LCD_Clear();
                        LCD_String_xy(2,0,".Ingreso No Permitido");
                        __delay_ms(12000);
                        counter_try = 0;
                    }
                }
            break;
        } 
        
    }
}
