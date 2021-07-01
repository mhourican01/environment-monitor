#include "DHT.h"
#include <LiquidCrystal.h>
#define Type DHT11
#define VIN 5
#define R 10000

// DHT variables
int dhtPin=2;
float temp;
float rh;
int setTime=500;
int dt=10000;

// LCD variables
int rs=7;
int en=8;
int d4=9;
int d5=10;
int d6=11;
int d7=12;

// Photoresistor variables
int lightPin=A0;
int lightVal;
int lux;

DHT HT(dhtPin,Type);
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HT.begin();
  lcd.begin(16,2);
  pinMode(lightPin,INPUT);
  delay(setTime);
}

void loop() {
  lcd.setCursor(0,0);
  displayDhtData();

  lcd.setCursor(0,1);
  displayLux();
  
  delay(dt);
  lcd.clear();
}

// Gets temperature and humidity reading from DHT11 sensor
void getDhtData() {
  temp=HT.readTemperature();
  rh=HT.readHumidity();
}

// Prints temperature and humidity reading to LCD
void displayDhtData() {
  getDhtData();
  
  lcd.print("Temp:");
  lcd.print(int(temp));
  lcd.print("C RH:");
  lcd.print(int(rh));
  lcd.print("%");
}

// Converts resistance of photoresistor to lux reading
void convertToLux() {
  lightVal=analogRead(lightPin);

  float vOut = float(lightVal) * (VIN / float(1023));
  float rLDR = (R * (VIN - vOut))/vOut;
  lux =500/(rLDR/1000);
}

// Prints lux reading to LCD
void displayLux() {
  convertToLux();
  
  lcd.print("Lux: ");
  lcd.print(lux);
  lcd.print(" lx");
}
