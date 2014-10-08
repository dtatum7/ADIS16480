////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Analog Devices, Inc.
//  October 2014
//  By: Daniel H. Tatum
////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ADIS16480.cpp
////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//  This file is part of Interfacing ADIS16480 with Arduino example.
//
//  Interfacing ADIS16480 with Arduino example is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  Interfacing ADIS16480 with Arduino example is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser Public License for more details.
//
//  You should have received a copy of the GNU Lesser Public License
//  along with Interfacing ADIS16480 with Arduino example.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ADIS16480.h"

////////////////////////////////////////////////////////////////////////////
// ADIS16480(int CS)
////////////////////////////////////////////////////////////////////////////
// Constructor with configurable CS pin and creates _CS private variable
////////////////////////////////////////////////////////////////////////////
// CS - Chip select pin
////////////////////////////////////////////////////////////////////////////
ADIS16480::ADIS16480(int CS) {
  _CS = CS;
  SPI.begin(); // initialize SPI bus
  SPI.setBitOrder(MSBFIRST); // for ADIS16480
  SPI.setClockDivider(SPI_CLOCK_DIV4); // for 4MHz
  SPI.setDataMode(SPI_MODE3); // Clock base at zero, sampled on rising, propagated on falling
  pinMode(_CS, OUTPUT); // Set CS pin to be an Output
  digitalWrite(_CS, HIGH); // Initialize CS pin to be high
}

////////////////////////////////////////////////////////////////////////////
//                           Destructor
////////////////////////////////////////////////////////////////////////////
ADIS16480::~ADIS16480(){
  // Put device to sleep
  sleep();
  // Close SPI bus
  SPI.end();
}
