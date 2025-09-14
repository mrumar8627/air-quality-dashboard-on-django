// --- AIR QUALITY API for NodeMCU (ESP8266) ---
// Edit SSID and PASSWORD below, then upload.

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// I2C LCD address (0x27 common). If your LCD blank, run I2C scanner.
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi creds
const char* ssid = "dm22";
const char* password = "123456789";

ESP8266WebServer server(80);

// Voltage divider used between MQ_out and NodeMCU A0.
// R1 = top resistor (between MQ_out and A0), R2 = bottom resistor (A0 to GND)
const float R1 = 5600.0;  // ohms
const float R2 = 10000.0; // ohms

const float VCC = 5.0;         // MQ sensor supply voltage
const float LOAD_RESISTOR = 10000.0; // RL (typical on MQ breakout)

// helper: read a stable average analog
float readAvgAnalog(int samples=20, int delayMs=5) {
  long sum = 0;
  for (int i=0;i<samples;i++) {
    sum += analogRead(A0);
    delay(delayMs);
  }
  return (float)sum / samples;
}

void handleData() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    // DHT read failed
    t = -1000.0;
    h = -1000.0;
  }

  float analogVal = readAvgAnalog(30, 5); // 0..1023
  float vout = (analogVal / 1023.0) * 3.3; // voltage at A0 (NodeMCU dev board)
  float sensorVoltage = vout * ((R1 + R2) / R2); // approximate MQ output voltage before divider
  // Sensor resistance Rsensor (approx): Rsensor = (Vc - Vout) / Vout * RL
  float Rsensor = ((VCC - sensorVoltage) / sensorVoltage) * LOAD_RESISTOR;

  String json = "{";
  json += "\"temperature\":" + String(t,2) + ",";
  json += "\"humidity\":" + String(h,2) + ",";
  json += "\"analog\":" + String((int)analogVal) + ",";
  json += "\"vout\":" + String(vout,3) + ",";
  json += "\"sensor_voltage\":" + String(sensorVoltage,3) + ",";
  json += "\"Rsensor\":" + String(Rsensor,2);
  json += "}";
  server.send(200, "application/json", json);

  // update LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:" + String(t,1) + "C H:" + String(h,0) + "%");
  lcd.setCursor(0,1);
  lcd.print("G:" + String((int)analogVal));
}

void setup() {
  Serial.begin(115200);
  delay(10);
  dht.begin();
  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/data", handleData);
  server.on("/", [](){
    server.send(200, "text/plain", "ESP8266 Air Quality Sensor. Use /data for JSON.");
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
