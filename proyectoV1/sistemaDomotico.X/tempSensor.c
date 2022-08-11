/*
 * File:   tempSensor.c
 * Author: UsuarioPC
 *
 * Created on 3 de agosto de 2022, 17:24
 */
unsigned int value_adc = 0;//16 bits
unsigned char counter_digito = 0;
double temp = 0.0;
unsigned char lm35 = 0;

void Temp_init(void){
    
}

double capturaTemp (){
    ADCON0bits.GO_DONE = 1; //  Inicia la COnversió AD.
    while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
    value_adc = ADRESH; //  Lectura de valor AD.
    value_adc = (value_adc << 8) + ADRESL;
    temp = value_adc;
        
    return temp;
}
    void configuracionPines (){
        ADCON1bits.ADFM = 1; //  Justificación Derecha (modo-8bits).
        ADCON1bits.VCFG0 = 0; //  Selecciona Voltajes de Referencia (5v-0v).
        ADCON1bits.VCFG1 = 0; 

        ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Analógico AN0.
        ADCON0bits.ADCS = 0b01; //  Tiempo de Conversión Fosc/8.

        ADCON0bits.ADON = 1;//  Habilita el Módulo AD.
    }
    
    
    
