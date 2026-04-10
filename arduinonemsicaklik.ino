#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2     
#define DHTTYPE DHT22   // Burayı DHT22 yaptık!

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2); 

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DHT22 Hazirlaniyor");
  delay(2000);
}

void loop() {
  // DHT22 yaklaşık 2 saniyede bir veri üretir
  float nem = dht.readHumidity();
  float isi = dht.readTemperature();

  // Veri okunamazsa hata ver
  if (isnan(nem) || isnan(isi)) {
    lcd.clear();
    lcd.print("Sensor Hatasi!");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sicaklik: ");
  lcd.print(isi, 1); // Virgülden sonra 1 basamak (DHT22 hassasiyeti için)
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Nem: %");
  lcd.print(nem, 1);

  delay(2000); 
}