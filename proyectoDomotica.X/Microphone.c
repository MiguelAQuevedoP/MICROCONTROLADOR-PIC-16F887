/*
 * File:   Microphone.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 17:12
 */

#include <xc.h>
#include "config.h"
#include "pines.h"
int a = 0;

void microphone_init (void){
    TRISC2 = 1;
    TRISC6 = 0;
    Led3 = 0;
    Microfono = 0;
}
int LeerMicrofono ()
{
        if(Microfono == 1 ){
            a=1;
        }
        else {
            a=0;
        }
        return a;
}
