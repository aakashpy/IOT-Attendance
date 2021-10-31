uint8_t getFingerprintID()
{
  uint8_t p = -1;
  while (p != FINGERPRINT_OK)
  {
    lcd.setCursor(0, 1);
    lcd.print("               ");
    lcd.setCursor(0, 1);
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        lcd.print("Image Ok");
        break;
      case FINGERPRINT_NOFINGER:
        lcd.print("No finger");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        lcd.print("Com error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        lcd.print("Img error");
        break;
      default:
        lcd.print("Error");
        break;
    }
  }
  lcd.setCursor(0, 1);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      lcd.print("Image Ok");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.print("Img messy");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.print("Com error");
      break;
    case FINGERPRINT_FEATUREFAIL:
      lcd.print("No features");
      break;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.print("No features");
      break;
    default:
      lcd.print("Error");
      break;
  }
  lcd.setCursor(0, 1);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK)
  {
    Serial.println("Found a print match!");
    lcd.clear();
    lcd.print("Found ID #"); lcd.print(finger.fingerID-1);
    lcd.setCursor(0, 1);
    lcd.print("Confidence "); lcd.print(finger.confidence);
    if (finger.fingerID != 1)
    {
      makeIFTTTRequest(1, finger.fingerID-1, Lect);
    }
    else
    {
      if(f==2)
      {
        makeIFTTTRequest(2,0,0);  f = 3;
      }
      if(f==1)
      {
        f=2;
      }
     
    }
  }
  else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.print("Com error");
  }
  else if (p == FINGERPRINT_NOTFOUND) {
    lcd.print("No match");
  }
  else {
    lcd.print("Error");
  }
  return finger.fingerID;
}
