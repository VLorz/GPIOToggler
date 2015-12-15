/*
 * GPIOToggler.h - Library for implementing software control over one GPIO output
 * on the Arduino. Created by Victor Lorenzo (EDesignsForge), December 8, 2015.
 * This library supersedes the GPIOLed library.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of GNU Lesser General Public License version 3.0,
 * as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
 * This library makes use of the following libraries which are copied here
 * for convenience:
 *  > PinChangeInt library for the Arduino
 *    https://github.com/GreyGnome/PinChangeInt
 *    Many thanks to Mike Schwager (GreySGnome).
 *
*/
#ifndef  _GPIOToggler_h_
#define  _GPIOToggler_h_


#include <inttypes.h>
#include <Arduino.h>



typedef enum {
  TOGGLEMODE_MANUAL,
  TOGGLEMODE_BLINKING,
} GPIOToggle_mode_t;


class GPIOToggler
{
  public:
	GPIOToggler( int Output );
    GPIOToggler( int Output, int CycleLen );
    
    void on();
    void off();
    void blink( int delay );
    void blink( int OnTime, int OffTime );
	void setCycleLen( int len );
	void setDutyCycle( double duty );
    bool blinking() { return (m_Mode == TOGGLEMODE_BLINKING); }
    
    void update();
    
    int state() { return m_State; };
  
  private:
    int m_Output;
    int m_State;
    unsigned long m_ToggleTime;
    int m_OnTime;
    int m_OffTime;
    GPIOToggle_mode_t m_Mode;
	int m_CycleLen;
};



#endif  /* _GPIOToggler_h_ */

