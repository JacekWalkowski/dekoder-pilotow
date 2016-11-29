/*
 * podczerwien.h
 *
 * Created: 2012-12-23 14:03:27
 *  Author: Jacek Walkowski
 */ 


#ifndef PODCZERWIEN_H_
#define PODCZERWIEN_H_
#include <avr/io.h>

//kody przyciskow pilota DAEWOO
#define POWER 0xA8
#define PLAY 0x70
#define STOP 0xB0
#define FF 0xF0
#define REW 0x08
#define ENCORE 0x3C
#define STILL 0x88
#define SLOW 0xC8
#define TRACKplus 0x18
#define TRACKminus 0xE8

uint16_t czas[40];
char polecenie;

void skanuj();

#endif /* PODCZERWIEN_H_ */