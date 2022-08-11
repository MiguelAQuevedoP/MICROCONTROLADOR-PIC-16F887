/*
 * File:   Microphone.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 17:12
 */

#include <xc.h>
#include "config.h"
#include "pines.h"
int i=0;

void microphone_init (void){
    Microfono = 1; 
    TRISC6 = 0;
    Led3=0;
}
void LeerMicrofono ()
{
        if(Microfono == 1 ){
            i++;
            __delay_ms(2000);
           if(Led3 == 0 && i == 2){
            Led3 = 1;  //Enciende el led
            i=0; 
           }
           else if (Led3 == 1 && i==2){
            Led3 = 0;  //Apaga el led
            i=0;
           }
        }
}