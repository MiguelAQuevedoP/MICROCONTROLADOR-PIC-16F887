/*
 * File:   alarma.c
 * Author: Mary Alejandra Valencia
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 8 de agosto de 2022, 10:29
 */
#include <xc.h>
#include <pic16f887.h> 
#include "config.h"
#include "pines.h"

void alarma_init (void){
    buzzer = 0; //Configura el buzzer como salida.
    Led1=0; //Configura el Led1 como salida.
    Led2=0; //Configura el Led2 como salida.
    Led3=0; //Configura el Led3 como salida.
    TRISC3=0; //Inicializa puerto C3 en 0.
    TRISC5=0; //Inicializa puerto C5 en 0.
    TRISC6=0; //Inicializa puerto C6 en 0.
    TRISC4=0; //Inicializa puerto C4 en 0.
}

void alarmaSeguridad (){
    buzzer=1;
    Led1=1;
}

void alarmaFlama (){
    buzzer=1;
    Led2=1;    
}

void apagarAlarma1(){
    buzzer=0;
    Led1=0;
}

void apagarAlarma2(){
    buzzer=0;
    Led2=0;
}


