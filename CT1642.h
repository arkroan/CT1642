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

#ifndef CT1642_H
#define CT1642_H

#include "Arduino.h"

/***************************************************************************************************
* Mapping of CT1642 Pins to bits for the 7Seg Led Display
* Alter this structure to resemble your layout.
* byte: [ABCDEFGp]
****************************************************************************************************/
#define BIT_A (1<<7)    /*          A           Q2 is connected to segment A, represented by bit 7 */
#define BIT_B (1<<6)    /*       -------        Q3 is connected to segment B, represented by bit 6 */
#define BIT_C (1<<5)    /*      |       |       Q4 is connected to segment C, represented by bit 5 */
#define BIT_D (1<<4)    /*    F |       |  B    Q5 is connected to segment D, represented by bit 4 */
#define BIT_E (1<<3)    /*       ---G---        Q6 is connected to segment E, represented by bit 3 */
#define BIT_F (1<<2)    /*      |       |  C    Q7 is connected to segment F, represented by bit 2 */ 
#define BIT_G (1<<1)    /*    E |       |       Q8 is connected to segment G, represented by bit 1 */
#define BIT_P (1<<0)    /*       ---D---   P    Q9 is connected to segment dP,represented by bit 0 */

// For more information on how this works see 
//	https://www.arduino.cc/en/Reference/Bitshift

/****************************************************************************************************
* 7 Segment LED display codes. Layout is for common cathode Led Displays.
* Alter this structure to include more characters or to resemble your layout.
*****************************************************************************************************/
#define DATA_0  BIT_A|BIT_B|BIT_C|BIT_D|BIT_E|BIT_F
#define DATA_1  BIT_B|BIT_C
#define DATA_2  BIT_A|BIT_B|BIT_D|BIT_E|BIT_G
#define DATA_3  BIT_A|BIT_B|BIT_C|BIT_D|BIT_G
#define DATA_4  BIT_B|BIT_C|BIT_F|BIT_G
#define DATA_5  BIT_A|BIT_C|BIT_D|BIT_F|BIT_G
#define DATA_6  BIT_A|BIT_C|BIT_D|BIT_E|BIT_F|BIT_G
#define DATA_7  BIT_A|BIT_B|BIT_C
#define DATA_8  BIT_A|BIT_B|BIT_C|BIT_D|BIT_E|BIT_F|BIT_G
#define DATA_9  BIT_A|BIT_B|BIT_C|BIT_D|BIT_F|BIT_G
#define DATA_A  BIT_A|BIT_B|BIT_C|BIT_E|BIT_F|BIT_G
#define DATA_b  BIT_C|BIT_D|BIT_E|BIT_F|BIT_G
#define DATA_C  BIT_A|BIT_D|BIT_E|BIT_F
#define DATA_c  BIT_D|BIT_E|BIT_G
#define DATA_d  BIT_B|BIT_C|BIT_D|BIT_E|BIT_G
#define DATA_E  BIT_A|BIT_D|BIT_E|BIT_F|BIT_G
#define DATA_e  BIT_A|BIT_B|BIT_D|BIT_E|BIT_F|BIT_G
#define DATA_F  BIT_A|BIT_E|BIT_F|BIT_G
#define DATA_g  BIT_A|BIT_B|BIT_C|BIT_D|BIT_F|BIT_G
#define DATA_H BIT_B|BIT_C|BIT_E|BIT_F|BIT_G
#define DATA_I  BIT_E|BIT_F
#define DATA_i  BIT_E
#define DATA_J  BIT_B|BIT_C|BIT_D|BIT_E
#define DATA_L	BIT_D|BIT_E|BIT_F
#define DATA_n  BIT_C|BIT_E|BIT_G
#define DATA_o  BIT_C|BIT_D|BIT_E|BIT_G
#define DATA_P  BIT_A|BIT_B|BIT_E|BIT_F|BIT_G
#define DATA_r  BIT_E|BIT_G
#define DATA_S  BIT_A|BIT_F|BIT_G|BIT_C|BIT_D
#define DATA_t  BIT_D|BIT_E|BIT_F|BIT_G
#define DATA_U  BIT_B|BIT_C|BIT_D|BIT_E|BIT_F
#define DATA_y  BIT_B|BIT_C|BIT_D|BIT_F|BIT_G
#define DATA_DARK	0x00
#define DATA_DOT	BIT_P
#define DATA_COLON	BIT_P
#define UPRSCR  BIT_A
#define HYPN    BIT_G
#define UNDRSCR BIT_D

// For more information on how this works see 
// https://www.arduino.cc/en/Reference/BitwiseAnd

/****************************************************************************************************
* Header file class CT1642 definition
* For information on the variables, functions etc. see the CT1642.cpp file
*****************************************************************************************************/
class CT1642 {
    public:
		CT1642(int CLK_Pin, int DATA_Pin);
        CT1642(int CLK_Pin, int DATA_Pin, int KEY_Pin);
		void setPovDelay(int delayN);
		void showNumber(int number);
		void showSingle(int number, int digit);
		void showChars(char char1, char char2, char char3, char char4);
		void showTime(int hours, int minutes);
		int getKeyCode(void);

    private:
        int _DATA_Pin;
		int _CLOCK_Pin;
		int _KEY_Pin;
		int povDelay;
		// Define an array to hold the number bitmaps
		byte bitmap_table[17] = {
		  DATA_0, DATA_1, DATA_2, DATA_3,
		  DATA_4, DATA_5, DATA_6, DATA_7,
		  DATA_8, DATA_9, DATA_DARK, DATA_P,
		  DATA_DOT, DATA_H, UPRSCR, HYPN,
		  UNDRSCR
		};
		// Define an array to hold the button numbers
		int keymap_table[10] = {
			1, /*Key on pin Q9*/
			2, /*Key on pin Q8*/
			3, /*Key on pin Q7*/
			4, /*Key on pin Q6*/
			5, /*Key on pin Q5*/
			6, /*Key on pin Q4*/
			7, /*Key on pin Q3*/
			8, /*Key on pin Q2*/
			9 /*Does not exist*/
		};
		void write(byte bitChar, int digitNo);
		byte getDigitAddress(int digitNo);
		void setUpDigit(byte digitNo);
		void setPreamble(void);
		void setChar(byte ledChar);
		void latchDigit(void);
		void clear(void);
		byte getCharByte(char character);

};

#endif