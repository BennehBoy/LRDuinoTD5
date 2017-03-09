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

#ifndef buttons_h
#define buttons_h
#include <Arduino.h>
//#include <WProgram.h>

#define buttons_up 0 // no-transitional
#define buttons_pressed 1 // transitional, no longer in use
#define buttons_down 2 // no-transitional
#define buttons_held 3
#define buttons_released 4
#define buttons_debounce 5 // One needs to wait till debounce is over to become pressed.
#define buttons_hold_time 1000
#define buttons_debounce_time 50
#define buttons_dash_threshold 10
#define buttons_repeat_time 250
#define buttons_dash_time 50
#define buttons_disabled 99
#define btn_auto 254 //Auto buttons are attached to pin 254
#define btn_null 255 //Null buttons are attached to pin 255
#define auto_ratio 5 // Auto button is pressed every auto_ratio*repeat_time, so 1.25s.

class Button
{
  public:
  Button(byte p, byte pd);
  Button(byte p, byte pd, unsigned int ana);

  boolean read_pin();
  byte sense();
  
  void do_up();
  void do_debounce();
  void do_down();
  void do_released();
  void do_held();

  boolean ana_button;
  unsigned int ana_value;

  byte stat;
  byte pin;
  byte pressed; // Polarity of buttons. For those with push-up resistors enabled, button pressed corresponds to low so this is LOW. 
  byte counts;
  boolean holding;
  unsigned long t_down;
  static unsigned long t_last_action; // This stores the last time any real button was active. You may use this to implement sleeping mode.
};


#endif
// pressed=HIGH means pressing buttons gives HIGH. A pull-down resistor is needed. pressed=LOW means pressing buttons gives LOW. One can use the internal pull-up resistor.
