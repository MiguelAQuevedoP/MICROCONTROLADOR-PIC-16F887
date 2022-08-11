/*
 * File:   obstacleAvoidanceSensor.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 17:16
 */


#include <xc.h>
#include "config.h"
#include "pines.h"
#include "LCD.h"
#include <string.h>
int r=0;

void sensorProximidad_init(void){
    TRISC1 = 1; 
    TRISC4 = 0;
    TRISC5 = 0;
    SensorObstaculos = 0;  
    buzzer = 0;
    Led2 = 0;
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
