/*
 * File:   Microphone.c
 * Author: Mary Alejandra Valencia Urrea
 * Correo: maryvalencia@unicauca.edu.co
 *
 * Created on 3 de agosto de 2022, 17:12
 */

#include <xc.h>
#include <pic16f887.h> 
#include "config.h"
#include "pines.h"

void microphone_init (void){
    TRISC2 = 1; //Configura el pin C2 como entrada
}
int LeerMicrofono ()
{
    int a ;
        if(Microfono == 1 ){
            a = 1;
        }
        else {
            a = 0;
        }
        return a ;
 
}