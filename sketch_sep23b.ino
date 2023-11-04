#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <dht11.h>


#include <iarduino_RTC.h>                                   // Подключаем библиотеку iarduino_RTC для работы с модулями реального времени.
iarduino_RTC time(RTC_DS1302, 3, 1, 2);  

dht11 DHT;
#define DHT11_PIN 4


LiquidCrystal_I2C lcd(0x27, 16, 2);
#define BACKLIGHT_PIN 13

int water; 



byte sunny1 [] = {
  B11111,
  B11111,
  B01111,
  B00111,
  B01011,
  B10010,
  B00010,
  B00010
};

byte sunny2 [] = {
  B00010,
  B00010,
  B10010,
  B01011,
  B00111,
  B01111,
  B11111,
  B11111
};
byte sunny3 [] = {
  B00010,
  B00001,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000
};
byte sunny4 [] = {
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00001,
  B00010
};
byte gradus [] = {
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
  B00000
};
byte download1 [] = {
  B01010,
  B01010,
  B01010,
  B01010,
  B11011,
  B01010,
  B00100,
  B00000
};
byte download2 [] = {
  B00000,
  B01010,
  B01010,
  B01010,
  B01010,
  B11011,
  B01110,
  B00100
};
void setup()
{
  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);
	// initialize the LCD
	lcd.begin();

  pinMode(A0, INPUT);  // к входу A0 подключим датчик (англ. «intput»)
  
  
  delay(300);                                             // Ждем готовности модуля отвечать на запросы
  time.begin();  
  time.settime(0, 53, 12);


  lcd.createChar(0, sunny1);
  lcd.createChar(1, sunny2);
  lcd.createChar(2, sunny3);
  lcd.createChar(3, sunny4);
  lcd.createChar(4, gradus);
  lcd.createChar(5, download1);
  lcd.createChar(6, download2);

  lcd.home ();
  lcd.print("Please");
  lcd.setCursor (0, 1);
  lcd.print("Wait!");
  delay(4000);
  lcd.clear();
  delay(1000);
  lcd.setCursor (7, 0);
  lcd.write(5);
  lcd.setCursor (0, 1);
  lcd.print(">>>>");
  delay(1000);
  lcd.clear();
  lcd.setCursor (7, 0);
  lcd.write(6);
  lcd.setCursor (0, 1);
  lcd.print(">>>>>>>>>>");
  delay(1000);
  lcd.clear();
  lcd.setCursor (7, 0);
  lcd.write(5);
  lcd.setCursor (0, 1);
  lcd.print(">>>>>>>>>>>>>>>>");
  delay(1000);
  lcd.clear();
  delay(3000);
  lcd.setCursor (0, 0);
  lcd.print("Hello!");
  lcd.setCursor (0, 1);
  lcd.print("Today is:");
  delay(5000);
  
  
}

void loop()
{
	
  //

  water = analogRead(A0);

//boolean waterdetect;

//if (water > 500) waterdetect = true;

if (water > 500){
    lcd.clear();
    lcd.setCursor (0, 0);
    lcd.print("WATER");
    lcd.setCursor (0, 1);
    lcd.print("DETECTED!");
    delay(3000);
  }
  
  time.gettime();

  //temperature
  int chk;
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }

  //Display
  
  lcd.home ();
  lcd.clear();
  lcd.setCursor (4, 0);
  lcd.print(time.gettime("H"));
  lcd.setCursor (6, 0);
  lcd.print(":");
  lcd.setCursor (7, 0);
  lcd.print(time.gettime("i"));
  lcd.setCursor (9, 0);
  lcd.print(":");
  lcd.setCursor (10, 0);
  lcd.print(time.gettime("s"));
  //lcd.setCursor (4, 1);
  //lcd.print(time.gettime("Y"));
  //lcd.setCursor (9, 1);
  //lcd.print(time.gettime("D"));
  lcd.setCursor (13, 1);
  lcd.print(DHT.humidity,1);
  lcd.setCursor (15, 1);
  lcd.print("%");
  lcd.setCursor (0, 1);
  lcd.print(DHT.temperature,1);
  lcd.setCursor (5, 1);
  lcd.print(water);
  lcd.setCursor (2, 1);
  lcd.write(4);
 
  delay(1000);
  //lcd.clear();
  //lcd.setCursor (0, 0);
  //lcd.print("Great");
  //lcd.setCursor (0, 1);
  //lcd.print("Weather!");
  //delay(0);
  
}