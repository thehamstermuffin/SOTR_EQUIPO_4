/*
 * SOTR.c
 * ATEMEGA16
 * Created: 10/12/2017 07:17:06 p. m.
 * Author : SOTR
 */ 
#define led 1<<1;//Pin 1 SALIDA
#define B_Serial 1<<2;//Pin 2 SALIDA
#define B_analog 1<<0;//Pin 0 SALIDA
#define BAUD  9600  //Definimos los baudios
#define F_CPU 8000000UL//Velocidad de trabajo
#include <avr/io.h>//Entrada y salida
#include <util/delay.h>//Para los retardos
#include <util/setbaud.h>//Para fijar los baudios
#include <avr/sleep.h>//Para liberar CPU
#include <avr/interrupt.h>//Para interrupciones
int valor=0;//Variable para la lectura del ADC ya multiplicada por la resolucion
char str[16];//Cadena para enviar datos
unsigned int valorAdc;//Lectura del ADC
int main(void)
{
	TCNT0 = 232;//Offset del 
	TCCR0 = _BV(CS00) | _BV(CS02); // Timer0 modo normal, sin usar el pin OC0, prescaler de 1024
	TIMSK = _BV(TOIE0);// habilta interrupción por desbordamiento de timer0	
	sei();// habilita interrupciones globales
	UsartInit(); //Configuramoas la comunicacion serial
	ADCInit();  //Configuramos el ADC
	UsartPutString("Hola"); //Enviamos mensaje de prueba
    DDRC = 255;//Se Define el  puerto D como salida (1 salida, 0 entrada)
	DDRA = 0; //Se define el puerto A como entrada
    while (1) 
    {		
    }	
}

void UsartInit() {
	
	UBRRL = UBRRL_VALUE;
	UBRRH = UBRRH_VALUE;
	
	UCSRC = _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1);
	
	UCSRB = _BV(RXEN) | _BV(TXEN);
}

void UsartPutChar(char c) {
	while (!(UCSRA & _BV(UDRE)));
	UDR = c;
}

void UsartPutString(char* s) {
	while (*s)
	UsartPutChar(*s++);
}

void ADCInit() {
	
	// Referencia AVCC
	ADMUX = _BV(REFS0);
	// ADC habilitado con preescaler de 128
	// F_ADC = 4000000/128 = 31.25 KHz
	// F_MUESTREO = 62500/13 = 2.4Khz
	// T_MUESTREO = 1/4800 = 416us
	// La conversión tarda 416us.
	ADCSRA = _BV(ADEN) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
}

int ADCRead(int canal) {
	
	// seleccionamos el nuevo canal a leer solo modificando solo
	// los bits MUX0 MUX1 y MUX2.
	ADMUX = (ADMUX & 0xF8) | (canal & 0x07);
	
	// se inicia la conversión.
	ADCSRA |= _BV(ADSC);
	
	// espera a que termina la conversión.
	while(ADCSRA & _BV(ADSC));
	
	// regresamos el valor de la conversión.
	return ADC;
}

// función para atender la interrupción
ISR(TIMER0_OVF_vect){
	PORTC ^= _BV(PC3);// se conmuta el estado del led para inidicar la frecuencia de reloj
	TCNT0 = 232;//Se aplica un offset para que desborde cada 3ms
	valor++;
	switch (valor)
	{
		case 1: ///TAREA 1 LECTURA ANALOGICA
		PORTC|=B_analog;
		valorAdc = ADCRead("0");
		PORTC&=~B_analog;
		break;
		case 2: //TAREA 2 ADECUACION DE LA LECTURA PARA ENVIO
		PORTC|=led;
		int real=valorAdc*4880;//La lectura en microvolts (sin punto decimal)
		itoa(real, str, 10);
		PORTC&=~led;
		break;
		case 3: //TAREA 3 ENVIO DE LA LECTURA POR PUERTO SERIAL
		PORTC|=B_Serial;
		UsartPutString("ADC:");
		PORTC&=~B_Serial;
		valor=0;
		break;	
	}
}

