/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

/*
Code from wiring-digital.c from the arduino core. See undefined.cpp file for more info
*/

#ifndef UDEFDDUEPIN_H
#define UDEFDDUEPIN_H

#include "Arduino.h"

// struct used to hold the descriptions for the "non arduino" pins.
// from the Arduino.h files
extern const PinDescription unDefPinDescription[] ;

extern void pinModeUndefined( uint32_t ulPin, uint32_t ulMode );
extern void digitalWriteUndefined( uint32_t ulPin, uint32_t ulVal );

#endif /* UDEFDDUEPIN_H_ */

