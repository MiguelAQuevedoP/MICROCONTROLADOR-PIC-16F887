/*
 * File:   flame_sensor.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 16:07
 */


#include <xc.h>
#include "config.h"
#include "pines.h"

void sensorFlame_init (void){
TRISC0=1; //Entrada
TRISC3=0; //Salida led1
TRISC4=0; //Salida led2
FlameSensor=0; // Pin C0 inicia en 0
Led1=0; // Pin C3 inicia en 0
buzzer=0; // Pin C4 inicia en 0
}

void LeerSensorFlame (){

    if( FlameSensor == 1)
    {
    Led1=1;
    buzzer=1;
    __delay_ms(1000);
     buzzer=0;
    }
    else if (FlameSensor == 0){
        PORTCbits.RC3=0;
    }
}
