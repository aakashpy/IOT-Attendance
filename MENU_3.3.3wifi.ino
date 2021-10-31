// *********************************************************************
// special settings
// *********************************************************************
// enable this line when you are not usigng a standard arduino
// for example when your chip is an ESP or a STM or SAM or something else
//#define _LCDML_cfg_use_ram 
// *********************************************************************
// includes
// *********************************************************************
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <LCDMenuLib2.h>
  #include <Adafruit_Fingerprint.h>
  #include <ESP8266WiFi.h>

// *********************************************************************
// LCDML display settings
// *********************************************************************
  const char* ssid     = "Nokia 2.3";
  const char* password = "123456789";
  const char* resource = "https://maker.ifttt.com/trigger/Temp/with/key/ogbLfsS8CTholqUEShJ7FSyVtCbWv6wUpJ1NYKUzimI";
  const char* server = "maker.ifttt.com";
  // settings for LCD
  #define _LCDML_DISP_cols  16
  #define _LCDML_DISP_rows  2
  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar
  int buzz =  D0;
  int f=1;
  int flag=-1;
  int lect_cnt=1;
  int Lect = 1;
  int Auth = -1;
  int roll;
  // LCD object
  // for i2c there are many different steps for initialization, some are listed here
  // when the rows and cols are not set here, they have to be set in the setup
  //LiquidCrystal_I2C lcd(0x27);  // Set the LCD I2C address
  //LiquidCrystal_I2C lcd(0x27, BACKLIGHT_PIN, POSITIVE);  // Set the LCD I2C address
  LiquidCrystal_I2C lcd(0x27,_LCDML_DISP_cols,_LCDML_DISP_rows);
  //LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
   SoftwareSerial mySerial(13, 15);
   Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  };

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();
  void mFunc_screensaver(uint8_t param);
  void mFunc_Student_Enroll(uint8_t param);
  void Read(uint8_t param);
  void Reset(uint8_t param);
  void Faculty_Enroll(uint8_t param);
  void Student_Enroll(uint8_t param);
  void mFunc_back(uint8_t param);

// *********************************************************************
// Global variables
// *********************************************************************
  uint8_t id = 0;

// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0
  // LCDML_0_X      => layer 1
  // LCDML_0_X_X    => layer 2
  // LCDML_0_X_X_X  => layer 3
  // LCDML_0_...      => layer ...

  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)

  LCDML_add         (0  , LCDML_0         , 1  , "  Main Menu"      , NULL);       // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (1  , LCDML_0         , 2  , "Attendance"        , Read);        // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (2  , LCDML_0         , 3  , "Settings"          , NULL);                    // NULL = no menu function
  LCDML_add         (3  , LCDML_0_3       , 1  , "  Settings"        , NULL);                    // NULL = no menu function
  LCDML_add         (4  , LCDML_0_3       , 2  , "Faculty-Enroll"    , Faculty_Enroll);                    // NULL = no menu function
  LCDML_add         (5  , LCDML_0_3       , 3  , "Student-Enroll"    , Student_Enroll);                    // NULL = no menu function
  LCDML_add         (6  , LCDML_0_3       , 4  , "Wifi-Status"     , wifi_stat);                    // NULL = no menu function
  LCDML_add         (7  , LCDML_0_3       , 5  , "Reset"            , NULL);                    // NULL = no menu function
  LCDML_add         (8  , LCDML_0_3_5     , 1  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (9  , LCDML_0_3_5     , 2  , "Back"             , mFunc_back);              // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (10 , LCDML_0_3_5     , 3  , "Back"             , mFunc_back);                // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (11 , LCDML_0_3_5     , 4  , "Reset"            , Reset);              // this menu function can be found on "LCDML_display_menuFunction" tab
  LCDML_add         (12 , LCDML_0_3_5     , 5  , "Back"             , mFunc_back);                    // NULL = no menu function

  // ***TIP*** Try to update _LCDML_DISP_cnt when you add a menu element.

  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    12

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // serial init; only be needed if serial control is used
    Serial.begin(9600); 
     finger.begin(57600);
     initWifi();// start serial
    Serial.println(F(_LCDML_VERSION)); // only for examples
    pinMode(buzz,OUTPUT);
    // LCD Begin
    lcd.begin();
    lcd.backlight();
    //lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);  // some display types needs here the initialization
    lcd.print(" ASD Smart Soln. ");
    lcd.setCursor(0,1);
    lcd.print(" IoT Attend Box ");
    delay(3000);
    digitalWrite(buzz,HIGH);
    delay(50);
    digitalWrite(buzz,LOW);
    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);
    finger.getTemplateCount();
     if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
     }
   else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
     }
    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
   // LCDML.SCREEN_disable();

    // Some needful methods

    // You can jump to a menu function from anywhere with
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name
  }
// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    LCDML.loop();
  }
