#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей

const int latchPin = 10;
const int clockPin = 11;
const int dataPin = 12;

byte brght[] = {0b00000000, 0b00000001, 0b00000011, 0b00000111, 0b00001111, 0b00011111, 0b00111111, 0b01111111, 0b11111111};
byte customCharBlock[8] = {
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111, 
    0b11111
};

bool choice1 = 0;
int PIN = 0;
int bR = 0;
int bB = 0;


void setup(){
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT); 
  

  pinMode(8, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея
  lcd.createChar(1, customCharBlock);
  
  digitalWrite(latchPin, LOW);
}
int opa(int PIN, int brightness){
  for(int i = 0; i < brightness; i++){
      lcd.setCursor(i,1);
      lcd.print(char(1));
    }
    for(int j = brightness;j<16;j++){
      lcd.setCursor(j,1);
      lcd.print("-");
    };
    int lenght = map(brightness, 0, 16, 0, 8);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, brght[lenght]);
    digitalWrite(latchPin, HIGH);
  int butY = map(analogRead(A0), 0, 1023, 0, 255);
  if(analogRead(A0) < 500){
    
    if(brightness == 16) return 16;
    lcd.setCursor(0,1);
    lcd.print("                ");
    brightness++;
    for(int i = 0; i < brightness; i++){
      lcd.setCursor(i,1);
      lcd.print(char(1));
    }
    for(int j = brightness;j<16;j++){
      lcd.setCursor(j,1);
      lcd.print("-");
    };
    int lenght = map(brightness, 0, 16, 0, 8);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, brght[lenght]);
    digitalWrite(latchPin, HIGH);
        
    int brght_for_svet1 = map(brightness, 0,16,0,255);
    analogWrite(PIN, brght_for_svet1);
        
  }
      
  if(analogRead(A0) > 600){
    if(brightness == 0) return 0;
    lcd.setCursor(0,1);
    lcd.print("                ");
    brightness--;
    int brght_for_svet2 = map(brightness,0,16,0,255);
    analogWrite(PIN,brght_for_svet2);
    
    for(int i = 0; i < brightness; i++){
      lcd.setCursor(i,1);
      lcd.print(char(1));
      
    }
    for(int j = brightness;j<16;j++){
      lcd.setCursor(j,1);
      lcd.print("-");
    };
    
        
    int lenght = map(brightness, 0, 16, 0, 8);
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, brght[lenght]);
    digitalWrite(latchPin, HIGH);
  }
  return brightness;
}


void loop(){
  int butX = map(analogRead(A1), 0, 1023, 0, 255);
  bool button = !digitalRead(8);
  
  while(true){
    choice1 = 0;
    lcd.setCursor(0, 0);
    lcd.print("PIN |SELECT| COL");
    lcd.setCursor(4, 1);
    lcd.print("|B|");
    lcd.setCursor(9, 1);
    lcd.print("|R|");
    lcd.setCursor(5, 1);
    while(!button){
      button = !digitalRead(8);
      delay(200);
      butX = map(analogRead(A1), 0, 1023, 0, 255);
      if(butX < 100){
        lcd.setCursor(5, 1);
        choice1 = 0;
      }
      if(butX > 200){
        lcd.setCursor(10, 1);
        choice1 = 1;
      }
      lcd.blink();
      delay(1);
      if(button){
        lcd.clear();
      }
    }
    lcd.noBlink();
    lcd.setCursor(15,0);
    if(choice1 == 0){
      lcd.print("B");
    }
    if(choice1 == 1){
      lcd.print("R");
    }
    
    //понижение, повышение
    if(choice1 == 1){
      lcd.setCursor(2, 0);
      lcd.print("|BRIGHTNESS|");
      PIN = 6;
    }
    if(choice1 == 0){
      lcd.setCursor(2, 0);
      lcd.print("|BRIGHTNESS|");
      PIN = 9;
    }
    
    int brightness = 0;
    while(button){
      lcd.setCursor(0, 0);
      lcd.print(PIN);
      button = digitalRead(8);
      delay(200);
      if(PIN == 6){
        brightness = bR;
        bR = opa(PIN, brightness);
      }
      if (PIN == 9){
        brightness = bB;
        bB = opa(PIN, brightness);
      } 
    }
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, 0b00000000);
    digitalWrite(latchPin, HIGH);
    lcd.clear();
  }
}


