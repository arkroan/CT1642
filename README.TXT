Arduino Library for CT/SM1642 ICs
==========================================

Usage
-----

This library supports the following devices:
    CT1642
    SM1642
    ET6227 (not tested yet)

The library examples should work with any Set Top Box Front panel with the aforementioned ICs
but please bear in mind that this library was created with the HITOP PA.222.03C
2013.3.25 Front Panel and an Arduino Leonardo.
So be extremely carefull in case you are trying it on a different front panel and/or arduino. 
This is a software based on the electronics of the HITOP Front Panel. Your device may vary.
I will not be held responsible for any damage you may cause on any of your devices or yourself by using this software.
You may do so at your own risk.

Info
----
The HITOP Front Panel uses the following layout for the CT1642 LED Display and Key connections:
CT1642\other_info\pics\ct1642_schematic.jpg

To connect the Front Panel to your arduino see the following picture:
CT1642\other_info\pics\CT_1642_StripPinout.png
	note: The yellow mark named 'From Resistor R3R2' indicates the connection to be made for the KEY PIN.

The examples use the following pins on the arduino Leonardo:
CLOCK_PIN 	is output no 6
DATA_PIN 	is output no 7
KEY_PIN		is input no 3   // Make sure this is an Interrupt PIN - it may be different on other versions of the arduino 

Credits
-------

The CT1642 library has been developed by George Efstathiou.

The Library started as a library development exercise based on the code from the 
arduino.cc 'Writing a Library for Arduino' tutorial:
https://www.arduino.cc/en/Hacking/LibraryTutorial

The ScanKey example uses code from the arduino.cc 'attachInterrupt()' Reference:
https://www.arduino.cc/en/Reference/AttachInterrupt


Website
-------

You can find the latest version of the library at
https://github.com/arkroan/CT1642

License
-------

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
