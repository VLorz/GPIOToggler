#include "GPIOToggler.h"
#include <arduino.h>


GPIOToggler::GPIOToggler( int Output )
	: GPIOToggler( Output, 1000 )
{}


GPIOToggler::GPIOToggler( int Output, int CycleLen )
  : m_Output( Output ), m_Mode( TOGGLEMODE_MANUAL ), m_State( LOW ), m_ToggleTime( 0 ), m_CycleLen( CycleLen )
{
  if (m_Output >= 0)
  {
    pinMode( m_Output, OUTPUT );
    digitalWrite( m_Output, m_State );
  }
}


void GPIOToggler::setCycleLen( int len )
{
	m_CycleLen = len;
}


void GPIOToggler::setDutyCycle( double duty )
{
	int OnTime, OffTime;
	
	OnTime = (int)(m_CycleLen * duty);
	OffTime = (int)(m_CycleLen * (1-duty));
	
	if (OnTime <= 0)
		off();
	else if (OffTime <= 0)
		on();
	else
		blink( OnTime, OffTime );
}


void GPIOToggler::on()
{
  if (m_Output >= 0)
  {
    m_Mode = TOGGLEMODE_MANUAL;
    digitalWrite( m_Output, m_State = HIGH );
    m_ToggleTime = millis();
  }
}

void GPIOToggler::off()
{
  if (m_Output >= 0)
  {
    m_Mode = TOGGLEMODE_MANUAL;
    digitalWrite( m_Output, m_State = LOW );
    m_ToggleTime = millis();
  }
}

void GPIOToggler::blink( int delay )
{
  blink( delay, delay );
}

void GPIOToggler::blink( int OnTime, int OffTime )
{
  if (m_Output >= 0)
  {
    m_OnTime = OnTime;
    m_OffTime = OffTime;
    
    m_Mode = TOGGLEMODE_BLINKING;
    digitalWrite( m_Output, m_State = HIGH );
    m_ToggleTime = millis();
  }
}


void GPIOToggler::update()
{
  unsigned long Elapsed = millis() - m_ToggleTime;
  
  if (m_Output < 0)
    return;
    
  if (m_Mode == TOGGLEMODE_BLINKING)
  {
    if (m_State == LOW)
    {
      if (Elapsed >= m_OffTime)
      {
        digitalWrite( m_Output, m_State = HIGH );
        m_ToggleTime = m_ToggleTime + m_OffTime;
      }
    }
    else
    {
      if (Elapsed >= m_OnTime)
      {
        digitalWrite( m_Output, m_State = LOW );
        m_ToggleTime = m_ToggleTime + m_OnTime;
      }
    }
  }
}

