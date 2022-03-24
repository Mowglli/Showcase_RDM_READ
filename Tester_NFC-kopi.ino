#include "x_nucleo_nfc04.h"
#include "RDMmaster.h"
#include <String.h>
#define DMXADRESS 512
#define DMXMODE 10

RDMmasterClass RDM;
int fixturemode;
int DMXAdress;
int test;
String divider = ";";
String data;
String reads[2]; 

int readText(String *t){
  uint16_t ret;
  NDEF_Text_info_t text_info;
  sRecordInfo_t recordInfo;
  // increase buffer size for bigger messages
  ret = NDEF_ReadNDEF(NDEF_Buffer);
    if (ret) {
      return ret;
    }

  ret = NDEF_IdentifyBuffer(&recordInfo, NDEF_Buffer);
    if (ret) {
       return ret;
    }

  ret = NDEF_ReadText(&recordInfo, &text_info);
    if (ret) {
      return ret;
    }

  if(text_info.encoding == NDEF_TEXT_UTF8) {
    //Serial.println("UTF-8 Encoding");
  } else if (text_info.encoding == NDEF_TEXT_UTF16){
    //Serial.println("UTF-16 Encoding");
  } else {
    //Serial.println("Unknown Encoding");
  }

  //Serial.print("Metadata: ");
  //Serial.println(text_info.language_code);
  //Serial.print("Plain text: ");
  //Serial.println(text_info.text);
  char * pch; 
  pch = strtok(text_info.text,";");
    while(pch != NULL){
      int i;
      //Serial.println(pch);
      reads[i]= pch;
      pch = strtok(NULL, ";");
      i++;
    }

   //Serial.println(reads[0].toInt());
   //Serial.println("opdeling er sket");
   //Serial.println(reads[1]);

  RDM.setDMXaddress(reads[0].toInt());
  delay(500);
  RDM.setFixtureMode(reads[1].toInt());
  delay(500);
  }
  

void setup() {
  //char read[] = (DMXAdress ";" fixturemode);
 
  RDM.initPins();
  RDM.initRDMdata();
  
  //Initialiser X_Nucleo_Nfc04
  if (X_Nucleo_Nfc04.begin()) {
    while (1) {
      X_Nucleo_Nfc04.ledOn(GREEN_LED);
      delay(100);
      X_Nucleo_Nfc04.ledOff(GREEN_LED);
      delay(100);
    }
  }

  while(1){
    X_Nucleo_Nfc04.ledOn(GREEN_LED);
      
  fixturemode = RDM.getFixtureMode();
  delay(25); 
  DMXAdress = RDM.getDMXAdress();


  String f;
  String d;
  f = String(fixturemode);
  d = String(DMXAdress);
  String val = d + divider + f;
  Serial.println("RDM: "+ val);
  const char *readVals = val.c_str();
  Serial.println(readVals);
  NDEF_WriteText(readVals);
    
      delay(500);
      //test = readText(&data);
      }

}

void loop() {
  //empty loop
}


