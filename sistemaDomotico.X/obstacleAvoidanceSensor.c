/*
 * File:   obstacleAvoidanceSensor.c
 * Author: Mary Alejandra Valencia Urrea
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 3 de agosto de 2022, 17:16
 */


#include <xc.h>
#include <pic16f887.h> 
#include "config.h"
#include "pines.h"
#include "LCD.h"
#include <string.h>

int r = 0;

void sensorProximidad_init(void){
    TRISC1 = 1; //Configurar pin C1 como entrada.
}

int LeerSensorProximidad(){
    if( SensorObstaculos == 1)
    {
        r=1;
    }
    else if (SensorObstaculos == 0){
        r=0;
    }
    return r;
}
