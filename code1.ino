
#define BLYNK_TEMPLATE_ID "TMPL2aHHDgoKk"
#define BLYNK_TEMPLATE_NAME "Soil Moisture and Temperature Monitor"
#define BLYNK_AUTH_TOKEN "sQTgbmEAL7vCWJAkgJN_S6K0ZGMKZ-dn"
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
// Replace with your network credentials
const char *ssid = "182";
const char *password = "159992ra";

// Replace with your Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

#define DHTPIN 26 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(26, DHT11);


void sendSensor()
{
   /*int soilmoisturevalue = analogRead(A0);
   soilmoisturevalue = map(soilmoisturevalue, 0, 1023, 0, 100);*/
  
   int value = analogRead(A0);
  value = map(value,400,1023,100,0);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, value);
    Blynk.virtualWrite(V1, t);
    Blynk.virtualWrite(V2, h);
    Serial.print("Soil Moisture : ");
    Serial.print(value);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
}
void setup()
{   
  
  Serial.begin(115200);
  

  Blynk.begin(auth, ssid,password);
  dht.begin();
  timer.setInterval(100L, sendSensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }
