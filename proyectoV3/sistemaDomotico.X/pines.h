
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */


#define  FlameSensor PORTCbits.RC0  
#define SensorObstaculos PORTCbits.RC1  
#define Microfono PORTCbits.RC2
#define  Led1 PORTCbits.RC3
#define  Led2 PORTCbits.RC5
#define  Led3 PORTCbits.RC6
#define  buzzer PORTCbits.RC4

void sensorFlame_init(void);
void LeerSensorFlame();
void ADC_init(void);
int capturaTemp();
void microphone_init (void);
void LeerMicrofono ();
void sensorProximidad_init(void);
void LeerSensorProximidad();
void seguridad_init (void);
void verificarSeguridad();

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

