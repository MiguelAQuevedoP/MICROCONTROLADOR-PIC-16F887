/*!
\file   config.h
\date   2022
\author Miguel Quevedo <mquevedo@unicauca.edu.co>
\brief  configurations
*/

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

// config
#pragma config FOSC = INTRC_CLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

// CONFIG2
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#define _XTAL_FREQ 8000000//frecuency


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */