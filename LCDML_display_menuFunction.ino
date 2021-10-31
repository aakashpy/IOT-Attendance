void Student_Enroll(uint8_t param)
{
  
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    LCDML_UNUSED(param);
    finger.begin(57600);
    if (finger.verifyPassword())
    {
      Serial.println("Found fingerprint sensor!");
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("Fp Sensor error :( ");
      delay(1000);
      LCDML.FUNC_goBackToMenu();
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Faculty Key");
    lcd.setCursor(0, 1);
    lcd.print("Required");
    Auth = getFingerprintID();
   // Serial.println(getFingerprintID());
    if(Auth==1)
    {

       f=1;
    }
    else
    {
     lcd.setCursor(0, 1);
     delay(1000);
     LCDML.FUNC_goBackToMenu();
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Student Enroll");
    lcd.setCursor(0, 1);
    lcd.print("Enter Id:");
    roll = 1;
    lcd.print(roll);
    LCDML.FUNC_disableScreensaver();
  }

  if (LCDML.FUNC_loop())
  {
    LCDML.FUNC_disableScreensaver();
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      if (LCDML.BT_checkUp()) // check if button left is pressed
      {

        LCDML.BT_resetUp(); // reset the left button
        roll++;
        if(roll==126)
        {
          roll=1;
        }
        lcd.setCursor(9, 1); lcd.print("   "); // set cursor
        lcd.setCursor(9, 1);
        lcd.print(roll); // print change content
      }
      if (LCDML.BT_checkDown()) // check if button left is pressed
      {
        LCDML.BT_resetDown(); // reset the left button
        roll--;
        if(roll==0)
        {
          roll=126;
        }
        lcd.setCursor(9, 1); lcd.print("   "); // set cursor
        lcd.setCursor(9, 1);
        lcd.print(roll); // print change content
      }
      if (LCDML.BT_checkEnter())
      {
        LCDML.BT_resetEnter();
        id=roll+1;
        getFingerprintEnroll();
        LCDML.FUNC_goBackToMenu();
      }
    }
  }

  if (LCDML.FUNC_close())     // ****** STABLE END *********
  {
    Auth=-1;
  }
}

//*********************************************************************
void Faculty_Enroll(uint8_t param)
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    finger.begin(57600);
    if (finger.verifyPassword())
    {
      Serial.println("Found fingerprint sensor!");
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("Fp Sensor error :( ");
      delay(1000);
      LCDML.FUNC_goBackToMenu();
    }
    LCDML_UNUSED(param);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Faculty Enroll");
    lcd.setCursor(0, 1);
    lcd.print("Faculty Id:");
    id = 1;
    lcd.print(id-1);
    LCDML.FUNC_disableScreensaver();
  }
  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {
    LCDML.FUNC_disableScreensaver();
    if (LCDML.BT_checkEnter())
    {
      LCDML.BT_resetEnter();
      getFingerprintEnroll();
      LCDML.FUNC_goBackToMenu();

    }
  }
  if (LCDML.FUNC_close())     // ****** STABLE END *********
  {

  }
} 

// *********************************************************************
void Reset(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);
    finger.begin(57600);
    if (finger.verifyPassword())
    {
      Serial.println("Found fingerprint sensor!");
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("Fp Sensor error :( ");
      delay(1000);
      LCDML.FUNC_goBackToMenu();
    }
    lcd.clear();
    lcd.print("Faculty Key");
    int p = getFingerprintID();
    if(p==1)
    {
     lcd.clear();
     lcd.print("  Box Reseted   ");
     finger.emptyDatabase();
    }
  }
  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

  }
  if (LCDML.FUNC_close())     // ****** STABLE END *********
  {
    LCDML.FUNC_goBackToMenu();
  }
}
//*****************************************************
void Read(uint8_t param)
{

  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    finger.begin(57600);
    LCDML_UNUSED(param);
    if (finger.verifyPassword())
    {
      Serial.println("Found fingerprint sensor!");
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("Fp Sensor error :( ");
      delay(1000);
      LCDML.FUNC_goBackToMenu();
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Faculty Key");
    lcd.setCursor(0, 1);
    lcd.print("Required");
    delay(100);
    Auth = getFingerprintID();
   // Serial.println(getFingerprintID());
    if(Auth==1)
    {
     //makeIFTTTRequest(1,0, 0);
     lcd.clear();
     lcd.print("Configuring...");
     delay(4000);
     lcd.clear();
     lcd.print("Enter Lect No");
     lcd.setCursor(0,1);
     lcd.print("No :");lcd.print(lect_cnt);
     Lect=lect_cnt;
    }
    else
    {
     lcd.setCursor(0, 1);
     lcd.print("Invalid");
     delay(1000);
     LCDML.FUNC_goBackToMenu();
    }
    
  }
  if (LCDML.FUNC_loop())
  {
    LCDML.FUNC_disableScreensaver();
    if(flag==-1)
    {
       if (LCDML.BT_checkUp()) // check if button left is pressed
      {
        LCDML.BT_resetUp(); // reset the left button
        lect_cnt=lect_cnt+1;
        lcd.setCursor(4, 1); lcd.print("                   "); // set cursor
        lcd.setCursor(4, 1);
        lcd.print(lect_cnt);
        Serial.println(lect_cnt);// print change content
      }
      else if (LCDML.BT_checkDown()) // check if button left is pressed
      {
        LCDML.BT_resetDown(); // reset the left button
         lect_cnt=lect_cnt-1;
        lcd.setCursor(4, 1); lcd.print("                  "); // set cursor
        lcd.setCursor(4, 1);
        lcd.print(lect_cnt);
        Serial.println(lect_cnt);// print change content
      }
       if (LCDML.BT_checkEnter())
      {
        LCDML.BT_resetEnter();
        flag=1;
        Lect= lect_cnt;  
      }
    }  
   if(flag==1)
   {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Student Entry");
    getFingerprintID();
     if(f==3)
    {
      LCDML.FUNC_goBackToMenu();
    }
   }
    LCDML.FUNC_disableScreensaver();
   }
  if (LCDML.FUNC_close())     // ****** STABLE END *********
  {
    flag=-1;
    f=1;
  }
}
// *********************************************************************
void wifi_stat(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
   lcd.clear();
   lcd.print("Stat: ");
   if (WiFi.status() != WL_CONNECTED)
    {
      lcd.print("Offline");
      lcd.setCursor(0,1);
      lcd.print("Waiting For Wifi");
      delay(10000);
      LCDML.FUNC_goBackToMenu();
    }
   else
    {
      lcd.print("Online");
      lcd.setCursor(0,1);
      lcd.print("Wifi:");lcd.print(ssid);
      delay(4000);
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(WiFi.localIP());
      delay(4000);
      LCDML.FUNC_goBackToMenu();
    }
  }
  if (LCDML.FUNC_loop())          // ****** LOOP *********
  {

  }
  if (LCDML.FUNC_close())     // ****** STABLE END *********
  {
    LCDML.FUNC_goBackToMenu();
  }
}
//*****************************************************
// *********************************************************************
void mFunc_screensaver(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // update LCD content
    lcd.noBacklight();
    lcd.setCursor(0, 0); // set cursor
    lcd.print(F("screensaver")); // print change content
    lcd.setCursor(0, 1); // set cursor
    lcd.print(F("press any key"));
    lcd.setCursor(0, 2); // set cursor
    lcd.print(F("to leave it"));
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if (LCDML.FUNC_loop())
  {
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      lcd.backlight();
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if (LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}

// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}
// *********************************************************************
/*void mFunc_jumpTo_timer_info(uint8_t param)
// *********************************************************************
{
  if (LCDML.FUNC_setup())         // ****** SETUP *********
  {
    // remmove compiler warnings when the param variable is not used:
    LCDML_UNUSED(param);

    // Jump to main screen
    LCDML.OTHER_jumpToFunc(mFunc_timer_info);
  }
}*/
