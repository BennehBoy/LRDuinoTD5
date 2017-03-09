/*
Buttons.h -
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 Inspired by:
 Phi-1 shield and phi-menu for Arduino by Dr. John Liu
*/

#include "Buttons.h"
unsigned long Button::t_last_action=0;

Button::Button(byte p, byte pd)
// Digital button
// A 255 on p means the button is null. A null button always returns buttons_up. This way one can create all the null buttons in case only say 3 buttons are needed. None of the sensing programs need to be changed with the help of null buttons.
// Not implemented: A 254 on p means the button is auto. An auto button will periodically return buttons_held and buttons_released.
{
  pressed=pd;
  pin=p;
  stat=buttons_up;
  counts=0;
  holding=false;
  ana_button=false;
  ana_value=0;
  t_last_action=millis();
  switch(p)
  {
    case btn_null:
    break;
    
    case btn_auto:
    t_down=millis();
    break;

    default:
  pinMode(p, INPUT_PULLUP);  
    break;
  }
}


Button::Button(byte p, byte pd, unsigned int ana)
// Analog button
{
  pressed=pd;
  pin=p;
  stat=buttons_up;
  counts=0;
  holding=false;
  ana_button=true;
  ana_value=ana;
  t_last_action=millis();
  switch(p)
  {
    case btn_null:
    break;
    
    case btn_auto:
    t_down=millis();
    break;

    default:
    //digitalWrite(p, HIGH);
    break;
  }
}

byte Button::sense()
{
  if (millis()<t_last_action) t_last_action=0;
  // Treating special buttons: null and auto buttons
  switch(pin)
  {
    case btn_null:
    stat=buttons_up; // Null buttons are always in buttons_up status.
    return stat;
    break;
    
    case btn_auto:
    if (millis()<t_down) t_down=0;
    if (t_down<t_last_action) t_down=t_last_action; // Make sure if a real button is pressed, the auto button is reset and will wait for a full period. So if you hang on to a real button, the auto button is not going to start clicking until you let go the real button.
    if ((millis()-t_down)>auto_ratio*buttons_repeat_time)
    {
      t_down=millis();
      stat=buttons_released;
    }
    else
    {
      stat=buttons_down;
    }
    return stat;
    break;

    default:
    break;
  }
  
  switch(stat)
  {
    case buttons_up:
    do_up();
    break;
    
    case buttons_debounce:
    do_debounce();
    break;
    
    case buttons_down:
    do_down();
    break;
    
    case buttons_held:
    do_held();
    break;
    
    case buttons_released:
    do_released();
    break;
    
    default:
    break;
  }
  return stat;
}

boolean Button::read_pin()
{
  if(!ana_button)    
  {
    return digitalRead(pin);  
  }
  else
  {
    int val = analogRead(pin);   // read the input pin
    if((val >= (ana_value - 50)) && (val <= (ana_value + 50)))
      return true;
    else
      return false;      
  }
}

void Button::do_up()
{
  holding=false;
  counts=0;
  if (read_pin()==pressed)
  {
    stat=buttons_debounce;
    t_down=millis();
    t_last_action=t_down;
  }
}

void Button::do_debounce()
{
  if (read_pin()==pressed)
  {
    if ((millis()-t_down)>buttons_debounce_time) stat=buttons_down;
  }
  
  else stat=buttons_up;
}

void Button::do_down()
{
  int thre;
  if (read_pin()!=pressed)
  {
    stat=holding?buttons_up:buttons_released;
    t_last_action=millis();
  }
  else
  {
    if (holding)
    {
      if (counts>buttons_dash_threshold) thre=buttons_dash_time;
      else thre=buttons_repeat_time;
    }
    else thre=buttons_hold_time;
    
    
    if (millis()-t_down>thre)
    {
      stat=buttons_held;
      t_last_action=millis();
      if (counts<=buttons_dash_threshold) counts++;
    }
    else
    {
      stat=buttons_down;
      t_last_action=millis();
    }
  }
}

void Button::do_released()
{
  stat=buttons_up;
  t_last_action=millis();
  holding=false;
  counts=0;
}

void Button::do_held()
{
  holding=true;
  if (read_pin()==pressed)
  {
    stat=buttons_down;
    t_down=millis();
    t_last_action=t_down;
  }
  else
  {
    stat=buttons_released;
    t_last_action=millis();
  }
}

