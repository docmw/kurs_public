void sendSMSanswer(char * senderNumber, uint8_t SMSindex) {
  char smstosend [30];
  strcpy_P(smstosend, PGM_GETSTR(SMSansw, SMSindex));
  SIM800.sendSMS(senderNumber, smstosend);
}
void SMSdecode(uint8_t numberIndex, char * newSMS) {


  uint8_t tableSize;
  int chkSMSindex = 0;
  char * senderNumber;


  if (numberIndex == 1) senderNumber = MNumber;
  else if (numberIndex == 2) senderNumber = INumber;
  else return;
  tableSize = (sizeof(SMScommands) / sizeof(SMScommands[0])) - 1;
  Serial.println(tableSize);
  for (uint8_t i = 1; i <= tableSize; i++) {
    char checkingCommand[30];
    strcpy_P(checkingCommand, PGM_GETSTR(SMScommands, i));


    if (strstr(newSMS, checkingCommand) != NULL) {

      chkSMSindex = i;
      Serial.println(chkSMSindex);
      break;
    }
  }

switch (chkSMSindex) {
    case 1:         //send sms from memory
      break;
    case 2:         //set alarm to detection mode
      changeAlarmMode(detectionmode);
      sendSMSanswer(senderNumber, chkSMSindex);
      break;
    case 3:         //set alarm to standby mode
      changeAlarmMode(standbymode);
      digitalWrite(outsounderPin, HIGH);
      digitalWrite(insounderPin, LOW);
      if (heatmode == 1) {
        heatmodechange(3);
      }
      sendSMSanswer(senderNumber, chkSMSindex);
      break;

    case 6:         //send sms with temperatures
      char smsToSendT[54];
      char t[6];
      strcpy_P(smsToSendT, PGM_GETSTR(SMSansw, chkSMSindex));
      dtostrf(tempsalon, 3, 1, t);
      for (int i = 0; i < 4; i++) {
        if (t[i] == '\0') break;
        smsToSendT[6 + i] = t[i];
      }

      dtostrf(TempBedroom, 3, 1, t);
      for (int i = 0; i < 4; i++) {
        if (t[i] == '\0') break;
        smsToSendT[22 + i] = t[i];
      }
      dtostrf(tempoutside, 4, 1, t);
      for (int i = 0; i < 5; i++) {
        if (t[i] == '\0') break;
        smsToSendT[33 + i] = t[i];
      }
      dtostrf(TempRTC, 3, 1, t);
      for (int i = 0; i < 4; i++) {
        if (t[i] == '\0') {
          smsToSendT[33 + i] = '\n';
          break;
        }
        smsToSendT[48 + i] = t[i];
      }

      Serial.println(smsToSendT);
      SIM800.sendSMS(senderNumber, smsToSendT);
      break;
    case 7:         //light on
      digitalWrite(salonlightPin, HIGH);
      sendSMSanswer(senderNumber, chkSMSindex);
      autolight = 0;
      break;
    case 8:         //light off
      digitalWrite(salonlightPin, LOW);
      autolight = 0;
      sendSMSanswer(senderNumber, chkSMSindex);
      break;
    case 9:         //light auto
      autolight = 2;
      sendSMSanswer(senderNumber, chkSMSindex);
      break;

    case 12:        //send command to external controller
      digitalWrite(LeonardoPowerPin, LOW);
      delay(2000);
      Leonardo.print(F("R"));
      sendSMSanswer(senderNumber, chkSMSindex);
      break;

    case 15:
      unsigned long current;
      current = millis();
      unsigned long lastMoveDelta;
      lastMoveDelta = current - lastTimeMove;
      int d = lastMoveDelta / 86400000;
      int h = (lastMoveDelta/3600000) - (d * 24);
      int m = (lastMoveDelta/60000) - (d * 24 * 60) - (h * 60);
      char smsToSend3[50];
      char z[2];
      strcpy_P(smsToSend3, PGM_GETSTR(SMSansw, chkSMSindex));
      sprintf(z, "%i", d);
      smsToSend3[0] = z[0];
      if (z[1] != '\0')smsToSend3[1] = z[1];
      sprintf(z, "%i", h);
      smsToSend3[6] = z[0];
      if (z[1] != '\0')smsToSend3[7] = z[1];
      sprintf(z, "%i", m);
      smsToSend3[14] = z[0];
      if (z[1] != '\0')smsToSend3[15] = z[1];
      SIM800.sendSMS(senderNumber, smsToSend3);
      break;



    case 22:
      SIM800.delAllSMS();
      delay(1000);
      break;
    case 23:
      char smsToSend2[20];
      char am[2];
      strcpy_P(smsToSend2, PGM_GETSTR(SMSansw, chkSMSindex));
      sprintf(am, "%i", alarmmode);
      strcat(smsToSend2, am);
      SIM800.sendSMS(senderNumber, smsToSend2);
      break;


    default:
      SIM800.sendSMS(senderNumber, smsToSendT);
      break;


  }

}
