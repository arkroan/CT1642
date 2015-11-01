/*****************************************************************************
**																			**
**  Device:	CT1642/SM1642/ET6227											**
**																			**
**	Info:	Usage of an 18Bit shift register found in the front panels of 	**
**			various household electronic appliances ( such as				**
**			set-top boxes, DVD players or various other LED display			**
**			devices).														**
**																			**
**  Files:	CT_1642.h														**
**			CT_1642.cpp														**
**																			**
******************************************************************************
******************************************************************************
**																			**
**  Created by:		G.Efstathiou 31 Oct 2015								**
**  Download from:	https://github.com/arkroan/CT1642						**
**																			**
**  Copyright (C) 2015 George Efstathiou									**
**																			**
******************************************************************************
**																			**
**	Description:															**
**  This library simplifies the use of the CT/SM 1642 Led Driver IC.		**
**	It provides simple functions for LED segment write and KEY read.		**
**	Also applies to ET6227 IC.												**
**																			**
**	License:																**
**  This program is free software: you can redistribute it and/or modify	**
**  it under the terms of the GNU General Public License as published by	**
**  the Free Software Foundation, either version 3 of the License, or		**
**  (at your option) any later version.										**
**																			**
**  This program is distributed in the hope that it will be useful,			**
**  but WITHOUT ANY WARRANTY; without even the implied warranty of			**
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the			**
**  GNU General Public License for more details.							**
**																			**
**  You should have received a copy of the GNU General Public License		**
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.	**
**																			**
******************************************************************************/
#include "Arduino.h"
#include <CT1642.h>

// CT1642 Constructor
//************************************************************************/
CT1642::CT1642(int CLK_Pin, int DATA_Pin){	
	_DATA_Pin = DATA_Pin;
	_CLOCK_Pin = CLK_Pin;
	
	pinMode(_DATA_Pin, OUTPUT);
	digitalWrite(_DATA_Pin, LOW);
	pinMode(_CLOCK_Pin, OUTPUT);
	digitalWrite(_CLOCK_Pin, LOW);
	
	// Setup default delay between digit display (ms)
	povDelay = 2;
	
	clear(); 
}

// CT1642 Constructor with Key Scan
//************************************************************************/
CT1642::CT1642(int CLK_Pin, int DATA_Pin, int KEY_Pin){	
	
	_DATA_Pin = DATA_Pin;
	_CLOCK_Pin = CLK_Pin;
	_KEY_Pin = KEY_Pin;
	
	pinMode(_DATA_Pin, OUTPUT);
	digitalWrite(_DATA_Pin, LOW);
	pinMode(_CLOCK_Pin, OUTPUT);
	digitalWrite(_CLOCK_Pin, LOW);
	pinMode(_KEY_Pin, INPUT);
	
	// Setup default delay between digit display (ms)
	povDelay = 2;
	
	clear(); 
}

// Writes a byte value on the chosen segment
//************************************************************************/
void CT1642::write(byte bitChar, int digitNo) {
  byte DigitAddress = 0;
  
  // Get the address of the seven segment digit
  DigitAddress = getDigitAddress(digitNo);

  // Set the address of the seven segment digit
  setUpDigit(DigitAddress);

  // Set preamble
  setPreamble();

  // Write the desired data
  setChar(bitChar);

  // Activate the output register of the ct1642
  latchDigit();

}

// Get the 7Segment Digit Address
//************************************************************************/
byte CT1642::getDigitAddress(int digitNo){
	
	byte digit = 0;
	
	switch (digitNo)
	  {
		case 1: { 
			// X000
			// 0x7f = DEC-127, BIN-B01111111
			digit = 0x7f;
			break;
		  }
		case 2: { 
			// 0X00
			// 0xbf = DEC-191, BIN-10111111
			digit = 0xbf;
			break;
		  }
		case 3: { 
			// 00:X0
			// 0xdf = DEC-223, BIN-11011111
			digit = 0xdf;
			break;
		  }
		case 4: { 
			// 00:0X
			// 0xef = DEC-239, BIN-11101111
			digit = 0xef;
			break;
		  }
		case 5: { 
			/* Switch OFF the display for the keyboard scan */
			// 0xff = DEC-255, BIN-11111111
			digit = 0xff;
			break;
		  }
		default: { 
			/* Display is switched off by default */
			digit = 0xff;
			break;
		  }
	}
	return digit;
}

// Set the 7Segment Digit Address in the CT1642 register
//************************************************************************/
void CT1642::setUpDigit(byte digitNo){
  // Set the address of the seven segment digit
  // in the CT1642
  // Write the desired address - 4 bits
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(_CLOCK_Pin, LOW);
    if ( (digitNo << i) & 0x80)
    {
      digitalWrite(_DATA_Pin, HIGH);
    }
    else
    {
      digitalWrite(_DATA_Pin, LOW);
    }
    digitalWrite(_CLOCK_Pin, HIGH);
  }
  
}

// Set the message preamble (6bit empty data) in the CT1642 register
//************************************************************************/
void CT1642::setPreamble(void){
  // Set the address of the seven segment digit
  // in the CT1642
  // Send empty/unused bits - 6 bits
  for (int i = 0; i < 6; i++)
  {
    digitalWrite(_DATA_Pin, HIGH);
    digitalWrite(_CLOCK_Pin, LOW);
    digitalWrite(_CLOCK_Pin, HIGH);
  }
  
}

// Set the value to be displayed (8bit char data) in the CT1642 register
//************************************************************************/
void CT1642::setChar(byte ledChar){
  // Set the value to be displayed 
  // in the CT1642
  // Write the desired data - 8 bits
  for (int i = 0; i < 8; i++) {
    digitalWrite(_CLOCK_Pin, LOW);
    if ( (ledChar << i) & 0x80)
    {
      digitalWrite(_DATA_Pin, HIGH);
    }
    else
    {
      digitalWrite(_DATA_Pin, LOW);
    }
    digitalWrite(_CLOCK_Pin, HIGH);
  }
  
}

// Activate the output latch of the CT1642 register
//************************************************************************/
void CT1642::latchDigit(void){
  // Activate the output register of the ct1642
  digitalWrite(_DATA_Pin, LOW);
  digitalWrite(_DATA_Pin, HIGH);
  digitalWrite(_CLOCK_Pin, LOW);
  digitalWrite(_DATA_Pin, LOW);
  digitalWrite(_DATA_Pin, HIGH);
}

// Clears all segment displays
//************************************************************************/
void CT1642::clear(void){
	write(0x00, 1);
	write(0x00, 2);
	write(0x00, 3);
	write(0x00, 4);
}

// Displays an int number on 4 segment displays
//************************************************************************/
void CT1642::showNumber(int number){ // int
  // Temporary values for thousands, hundreds, tens and units
  int d1, d2, d3, d4;
  int digits = 0;

  // Do some boundary checks
  if (number > 9999)
    number = 9999;
  if (number < 0)
    number = 0;

  // Define the number of digits
  digits = 1;
  if (number >= 10) {
    digits = 2;
  }
  if (number >= 100) {
    digits = 3;
  }
  if (number >= 1000) {
    digits = 4;
  }
  
  switch (digits) {
    case 1: {
		// Get units
		d4 = (int) number;
		
		write(bitmap_table[d4], 4);
		delay(povDelay);
		//write(DATA_DARK, 4);
	  
		break;
	}
    case 2: {
		// Get tens
		d3 = (int) (number / 10);
		number = number - (d3 * 10);
		// Get units
		d4 = (int) number;
		
		write(bitmap_table[d3], 3);
		delay(povDelay);
		//write(DATA_DARK, 3);

		write(bitmap_table[d4], 4);
		delay(povDelay);
		//write(DATA_DARK, 4);
		
		break;
	}
	case 3: {
		// Get hundreds
		d2 = (int) (number / 100);
		number = number - (d2 * 100);
		// Get tens
		d3 = (int) (number / 10);
		number = number - (d3 * 10);
		// Get units
		d4 = (int) number;

		write(bitmap_table[d2], 2);
		delay(povDelay);
		//write(DATA_DARK, 2);
		
		write(bitmap_table[d3], 3);
		delay(povDelay);
		//write(DATA_DARK, 3);

		write(bitmap_table[d4], 4);
		delay(povDelay);
		//write(DATA_DARK, 4);
		break;
	}
	case 4: {
		// Get thousands
		d1 = (int) (number / 1000);
		number = number - (d1 * 1000);
		// Get hundreds
		d2 = (int) (number / 100);
		number = number - (d2 * 100);
		// Get tens
		d3 = (int) (number / 10);
		number = number - (d3 * 10);
		// Get units
		d4 = (int) number;
		
		write(bitmap_table[d1], 1);
		delay(povDelay);
		//write(DATA_DARK, 1);

		write(bitmap_table[d2], 2);
		delay(povDelay);
		//write(DATA_DARK, 2);

		write(bitmap_table[d3], 3);
		delay(povDelay);
		//write(DATA_DARK, 3);

		write(bitmap_table[d4], 4);
		delay(povDelay);
		//write(DATA_DARK, 4);

		break;
	}
  }
}

// Displays an int number on 4 segment displays
//************************************************************************/
void CT1642::showTime(int hours, int minutes){ // time
	int hd,md;
	int hd1, hd2, md1, md2;
	
	if (hours >= 10 && hours <= 23) {
		
		hd = 2;
		
		// Get tens
		hd1 = (int) (hours / 10);
		hours = hours - (hd1 * 10);
		// Get units
		hd2 = (int) hours;
		
	} else if (hours >= 0 && hours <= 9) {
		hd = 1;
	} else {
		hd = 1;
		hours = 0;
	}
	
	if (minutes >= 10 && minutes <= 59) {
		md = 2;
		
		// Get tens
		md1 = (int) (minutes / 10);
		minutes = minutes - (md1 * 10);
		// Get units
		md2 = (int) minutes;
	} else if (minutes >= 0 && minutes <= 9) {
		md = 1;
	} else {
		md = 1;
		minutes = 0;
	}
	
	if (hd == 2){
		write(bitmap_table[hd1], 1);
		delay(povDelay);
		//write(DATA_DARK, 1);
		write((byte) bitmap_table[hd2]|DATA_COLON, 2);
		delay(povDelay);
		//write(DATA_DARK, 2);
	} else {
		write(bitmap_table[0], 1);
		delay(povDelay);
		//write(DATA_DARK, 1);
		write(bitmap_table[hours]|DATA_COLON, 2);
		delay(povDelay);
		//write(DATA_DARK, 2);
	}
	
	if (md == 2){
		write(bitmap_table[md1], 3);
		delay(povDelay);
		//write(DATA_DARK, 3);
		write(bitmap_table[md2], 4);
		delay(povDelay);
		//write(DATA_DARK, 4);
	} else {
		write(bitmap_table[0], 3);
		delay(povDelay);
		//write(DATA_DARK, 3);
		write(bitmap_table[minutes], 4);
		delay(povDelay);
		//write(DATA_DARK, 4);
	}

}

// Displays an int number on 1 segment
//************************************************************************/
void CT1642::showSingle(int number, int digit){
	int toWrite = 0;
	
	if (number >= 0 && number <= 9) {
		toWrite = number;
	}
	
	write((byte) bitmap_table[toWrite], digit);
	delay(povDelay);
	clear();
}

// Displays up to 4 characters on 4 segments
//************************************************************************/
void CT1642::showChars(char char1, char char2, char char3, char char4){
	
	byte c1 = getCharByte(char1);
	byte c2 = getCharByte(char2);
	byte c3 = getCharByte(char3);
	byte c4 = getCharByte(char4);
	
	write(c1, 1);
	delay(povDelay);

	write(c2, 2);
	delay(povDelay);

	write(c3, 3);
	delay(povDelay);

	write(c4, 4);
	delay(povDelay);
	
}

// Maps a character to byte bitmap
//************************************************************************/
byte CT1642::getCharByte(char character){
	
  switch (character) {
    case '0':
      return bitmap_table[0];
      break;
    case '1':
      return bitmap_table[1];
      break;
    case '2':
      return bitmap_table[2];
      break;
    case '3':
      return bitmap_table[3];
      break;
    case '4':
      return bitmap_table[4];
      break;
    case '5':
      return bitmap_table[5];
      break;
    case '6':
      return bitmap_table[6];
      break;
    case '7':
      return bitmap_table[7];
      break;
    case '8':
      return bitmap_table[8];
      break;
    case '9':
      return bitmap_table[9];
      break;
    case '-':
      return (byte) HYPN ;
      break;
    case 'A':
      return (byte) DATA_A ;
      break;
    case 'b':
      return (byte) DATA_b ;
      break;
    case 'C':
      return (byte) DATA_C ;
      break;
    case 'd':
      return (byte) DATA_d ;
      break;
    case 'E':
      return (byte) DATA_E ;
      break;
    case 'F':
      return (byte) DATA_F ;
      break;
	case 'r':
      return (byte) DATA_r ;
      break;
	case ' ':
      return (byte) DATA_DARK ;
      break;
    default: 
      return (byte) HYPN ;
  }
}

// Sets the persistence of vision delay
//************************************************************************/
void CT1642::setPovDelay(int delayN){
	povDelay = delayN;
}

// Gets the button pressed
//************************************************************************/
int CT1642::getKeyCode(void){
	int i;
	int avail = 0;
	int bitKeyPressed = 0;
	int keyCodeSum = 0;

	// Get Key bitmap of key pressed
	for (i = 0; i < 8; i++) {
		write(1 << i, 5);
		delay(2);
		bitKeyPressed = digitalRead(_KEY_Pin);

		if (1 == bitKeyPressed) {
			avail++;
			keyCodeSum += keymap_table[i];
		}
	}

	if (avail > 0)
	{
		return keyCodeSum;
	}
	else /*when none*/
	{
		return keymap_table[9];
	}
}


