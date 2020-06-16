#include <LiquidCrystal.h> //Please replace the single quote characters ('') with the parenthesis character (<>)

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)

#include "DHT.h"
#define DHTPIN 9     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  dht.begin();
}

void loop() {
  delay(2000);
  Serial.print("Temperature: ");
  
  Serial.print(getTemp("c"));
  
  Serial.print(" *C ");
  Serial.print(getTemp("f"));
  Serial.println (" *F");
  Serial.println("******************");  
  Serial.print("Heat index: ");
  Serial.print(getTemp("hic"));
  Serial.print(" *C ");
  Serial.print(getTemp("hif"));
  Serial.println(" *F");
  Serial.print(getTemp("k"));
  Serial.println(" *K");
  Serial.println("*******************");    
  Serial.print("Humidity: ");
  Serial.print(getTemp("h"));
  Serial.println(" % ");
  Serial.println("//////////////////");
  lcd.setCursor(0,0);
  lcd.print("Temperature : ");
  lcd.print(getTemp("c"));
  lcd.print(" *C ");
  lcd.print(getTemp("f"));
  lcd.print(" *C ");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(getTemp("h"));
  lcd.print(" % ");
  
  
  
}

float getTemp(String req)
{

 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // Compute heat index in Kelvin 
  float k = t + 273.15;
  if(req =="c"){
    return t;//return Cilsus
  }else if(req =="f"){
    return f;// return Fahrenheit
  }else if(req =="h"){
    return h;// return humidity
  }else if(req =="hif"){
    return hif;// return heat index in Fahrenheit
  }else if(req =="hic"){
    return hic;// return heat index in Cilsus
  }else if(req =="k"){
    return k;// return temprature in Kelvin
  }else{
    return 0.000;// if no reqest found, retun 0.000
  }
 
}
