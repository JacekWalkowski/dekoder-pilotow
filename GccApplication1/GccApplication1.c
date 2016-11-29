/*
 * GccApplication1.c
 *
 * Created: 2012-11-03 18:33:50
 *  Author: Jacek Walkowski
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include "podczerwien.h"
#include <avr/interrupt.h>

#define POWER_LED PB1;

void wykonaj();

volatile int wlaczony; //zmienna globalna jest automatycznie inicjalizowana wartoscia 0!

int main(void)
{
	//dioda POWER_LED
	DDRB |= 0x02;
	PORTB = 0x00;
	
	//PD2 jako wejœcie dla podczerwieni z podciagnieciem do Vcc
	DDRD = 0x00;
	PORTD |= 1<<PD2;
		
	//PORTC jako wyjscie dla LED czerwonych
	DDRC = 0x3F;
	PORTC = 0x00;
		
	//wlaczenie timer1
	TCCR1B |= (1<<CS11); //preskaler 8
	
	//wlaczenie zewnetrznego przerwania INT0 (aktywacja stanem niskim)
	GICR |= 1<<INT0;
	sei();
	
	while(1)
	{
		wykonaj();
	}
}

void wykonaj()
{
	//uruchamianie
	if((wlaczony==0) && (polecenie==POWER))
	{
		wlaczony=1;
		PORTB |= 1<<POWER_LED; //zapalenie diody zielonej
		polecenie = 0x00;
	}
	//wylaczanie
	if((wlaczony==1) && (polecenie==POWER))
	{
		wlaczony=0;
		PORTB &= ~1<<POWER_LED; //zgaszenie diody zielonej
		PORTC = 0x00; //zgaszenie zapalonych diod czerwonych
		polecenie = 0x00;
	}		
	
	//program:
	while(wlaczony==1 && polecenie==PLAY)
	{
		while(1)
		{
			if(PORTC == 0x00)	PORTC = 0x01; //jesli zadna lampka nie zapalona, zapal pierwsza
			while(PORTC<0x20)
			{
				if (polecenie==STOP) break;
				_delay_ms(100);
				PORTC <<= 1;
			}
			while(PORTC>0x01)
			{
				if (polecenie==STOP) break;
				_delay_ms(100);
				PORTC >>= 1;
			}
			if(polecenie==STOP) break;			
		}

	}
	if((wlaczony==1) && (polecenie==FF))
	{
		if(PORTC>0x01) PORTC >>= 1;
		polecenie = 0x00;
	}
	if((wlaczony==1) && (polecenie==REW))
	{
		if(PORTC<0x20) PORTC <<= 1;
		polecenie = 0x00;
	}
}

ISR(INT0_vect)
{
	skanuj();
}

void czysc()
{
	PORTC = 0x00;
}