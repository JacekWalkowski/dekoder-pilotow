/*
 * podczerwien.c
 *
 * Created: 2012-12-23 14:03:47
 *  Author: Jacek Walkowski
 */

//sygnal podczerwieni odbierany przez pin PD2 portu PORTD (jest to sygnal mogacy wywolac zewnetrzne przerwanie INT0)

#include "podczerwien.h"
#include <avr/io.h>

void skanuj()
{
	int i=0;
	while(!(PIND&0x04))
	{
		TCNT1 = 0x00;
		while(!(PIND&0x04)); //czekaj gdy logiczne 1 na pinie PD2
		czas[i] = TCNT1*8;
		++i;
		TCNT1 = 0x00;
		while((PIND&0x04) && TCNT1<0x186A); //czekaj gdy logiczne 0 i czas nie dluzszy niz 10 000ms
		czas[i] = TCNT1*8;
		if(czas[i]>45000) break;
		++i;
	}
	polecenie = (czas[20]+czas[21])>1400 ? polecenie|0x80 : polecenie&~0x80;
	polecenie = (czas[22]+czas[23])>1400 ? polecenie|0x40 : polecenie&~0x40;
	polecenie = (czas[24]+czas[25])>1400 ? polecenie|0x20 : polecenie&~0x20;
	polecenie = (czas[26]+czas[27])>1400 ? polecenie|0x10 : polecenie&~0x10;
	polecenie = (czas[28]+czas[29])>1400 ? polecenie|0x08 : polecenie&~0x08;
	polecenie = (czas[30]+czas[31])>1400 ? polecenie|0x04 : polecenie&~0x04;
	polecenie = (czas[32]+czas[33])>1400 ? polecenie|0x02 : polecenie&~0x02;
	polecenie = (czas[34]+czas[35])>1400 ? polecenie|0x01 : polecenie&~0x01;
}