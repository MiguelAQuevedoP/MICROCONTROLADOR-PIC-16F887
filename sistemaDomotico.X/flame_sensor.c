/*
 * File:   flame_sensor.c
 * Author: Mary Alejandra Valencia
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 3 de agosto de 2022, 16:07
 */

#include <xc.h>
#include <pic16f887.h> 
#include "config.h"
#include "pines.h"
int f=0;

void sensorFlame_init (void){
    TRISC0 = 1; //Configura el pin C0 como entrada
}

int LeerSensorFlame (){

    if( FlameSensor == 1){
        f=1;
    }
    else if (FlameSensor == 0){
        f=0;
    }
    return f;
}
