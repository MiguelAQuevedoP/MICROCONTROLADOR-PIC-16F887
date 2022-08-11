/*
 * File:   flame_sensor.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 16:07
 */


#include <xc.h>
#include "config.h"
#include "pines.h"
int f=0;
void sensorFlame_init (void){
TRISC0=1; //Entrada
TRISC3=0; //Salida led1
TRISC4=0; //Salida (buzzer)
FlameSensor=0; // Pin C0 inicia en 0
Led1=0; // Pin C3 inicia en 0
buzzer=0; // Pin C4 inicia en 0
}

int LeerSensorFlame (){

    if( FlameSensor == 1)
    {
        f=1;
    }
    else if (FlameSensor == 0){
        f=0;
    }
    
    return f;
}

