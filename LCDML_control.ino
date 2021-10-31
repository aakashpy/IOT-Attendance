// =====================================================================
// CONTROL v2.2.0
// =====================================================================
// *********************************************************************
// Features 
// - max 6 Buttons with special names (enter, quit, up, down, left, right)
// new Features on v2.2.0
// - max 64 Events, this could be a button ore something (Counter 0 - 63) 
// - standard buttons and events can be used at the same time
// - Event 0 - 3 can be used with a menu callback function (when set this event, the function is called)
// - The range from 0 - 3 can be changed in LCDMenuLib2.h
// Attention!!
// - events have to be reset manual over LCDML.CE_reset(number) ore LCDML.CE_resetAll();
// - they will not be reseted from the menu library
// *********************************************************************
// content:
// (2) Control over 4 - 6 digital input pins (internal pullups enabled)
// *********************************************************************

#define _LCDML_CONTROL_cfg      2

// theory:
// "#if" is a preprocessor directive and no error, look here:
// (English) https://en.wikipedia.org/wiki/C_preprocessor
// (German)  https://de.wikipedia.org/wiki/C-Pr%C3%A4prozessor
// *********************************************************************
// *************** (2) CONTROL OVER DIGITAL PINS ***********************
// *********************************************************************
#if(_LCDML_CONTROL_cfg == 2)
// settings
  unsigned long g_LCDML_DISP_press_time = 0;

  #define _LCDML_CONTROL_digital_low_active      1   // 0 = high active (pulldown) button, 1 = low active (pullup)
                                                      // http://playground.arduino.cc/CommonTopics/PullUpDownResistor
  #define _LCDML_CONTROL_digital_enable_quit     1
  #define _LCDML_CONTROL_digital_enable_lr       1
  #define _LCDML_CONTROL_digital_enter           12
  #define _LCDML_CONTROL_digital_up              0
  #define _LCDML_CONTROL_digital_down            2
  #define _LCDML_CONTROL_digital_quit            14
// *********************************************************************
void lcdml_menu_control(void)
{
  // If something must init, put in in the setup condition
  if(LCDML.BT_setup()) {
    // runs only once
    // init buttons
    pinMode(_LCDML_CONTROL_digital_enter      , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_up         , INPUT_PULLUP);
    pinMode(_LCDML_CONTROL_digital_down       , INPUT_PULLUP);
    # if(_LCDML_CONTROL_digital_enable_quit == 1)
      pinMode(_LCDML_CONTROL_digital_quit     , INPUT_PULLUP);
    # endif
    # if(_LCDML_CONTROL_digital_enable_lr == 1)
    # endif
  }

  #if(_LCDML_CONTROL_digital_low_active == 1)
  #  define _LCDML_CONTROL_digital_a !
  #else
  #  define _LCDML_CONTROL_digital_a
  #endif

  uint8_t but_stat = 0x00;

  bitWrite(but_stat, 0, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_enter)));
  bitWrite(but_stat, 1, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_up)));
  bitWrite(but_stat, 2, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_down)));
  #if(_LCDML_CONTROL_digital_enable_quit == 1)
  bitWrite(but_stat, 3, _LCDML_CONTROL_digital_a(digitalRead(_LCDML_CONTROL_digital_quit)));
  #endif
  #if(_LCDML_CONTROL_digital_enable_lr == 1)
  #endif

  if (but_stat > 0) {
    if((millis() - g_LCDML_DISP_press_time) >= 200) {
      g_LCDML_DISP_press_time = millis(); // reset press time

      if (bitRead(but_stat, 0)) {digitalWrite(buzz,HIGH);delay(50);digitalWrite(buzz,LOW);LCDML.BT_enter();}
      if (bitRead(but_stat, 1)) {digitalWrite(buzz,HIGH);delay(50);digitalWrite(buzz,LOW); LCDML.BT_up();}
      if (bitRead(but_stat, 2)) {digitalWrite(buzz,HIGH);delay(50);digitalWrite(buzz,LOW); LCDML.BT_down();}
      if (bitRead(but_stat, 3)) {digitalWrite(buzz,HIGH);delay(50);digitalWrite(buzz,LOW); LCDML.BT_quit();}
    }
  }
}
#else
  #error _LCDML_CONTROL_cfg is not defined or not in range
#endif
