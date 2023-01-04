/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
BG_DIY_WxStn.ino 
Author: sirtuxalot@gmail.com
Last Update: 22 Dec 2021
Notes: Standardize format of sketch constants
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#define DEBUG 0

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

// Libraries

#include <Wire.h>                      // common library for all I2C stuf
#include <DHT.h>                       // library for DHT11
#include <SFE_BMP180.h>                // library for BMP180
#include <BH1750.h>                    // library for BH1750 (AKA GY-30)
#include <ESP8266WiFi.h>               // library for web server

// Defines

const int DHTPIN {14};                 // pin for DHT11
const char DHTTYPE {DHT11};            // name for DHT11
DHT dht(DHTPIN, DHTTYPE);              // initialize DHT11 sensor
const float ALTITUDE {171.0};          // Altitude of Lock Haven, PA in meters
SFE_BMP180 pressure;                   // name for BMP180 
BH1750 lightMeter;                     // name for BH1750 (AKA GY-30)
const char* ssid {"XXXXXXXXXX"};       // SSID of wireless network
const char* password {"XXXXXXXXXX"};   // Password for wireless network
WiFiServer espServer(80);              // HTTP port
IPAddress ip(###, ###, ###, ###);      // IP address of device
IPAddress gateway(###, ###, ###, ###); // Gateway IP address
IPAddress subnet(###, ###, ###, ###);  // Network Subnet Mask

// Variables

float temp = 0;
float humid = 0;
float pres = 0;
int light = 0;
unsigned long LastEntry;
int Delay = 5000;

void setup() {

  // for DHT11
  dht.begin();

  // for BMP180
  pressure.begin();

  // for BH1750 (AKA GY-30)
  lightMeter.begin();

  // connect to wireless network
  Serial.begin(115200);                // Begin Serial Communication with 115200 Baud Rate
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);                 // Configure ESP8266 in STA Mode
  WiFi.config(ip, gateway, subnet);    // Setup IP Addressing of device
  WiFi.begin(ssid, password);          // Connect to Wi-Fi based on above SSID and Password
  while(WiFi.status() != WL_CONNECTED) // Loop validating connection to wireless network
  {
    Serial.print("*");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to Wi-Fi: ");
  Serial.println(ssid);
  Serial.println();
  Serial.println("Starting ESP8266 Web Server...");
  espServer.begin();                   // Start the HTTP web Server
  Serial.println("ESP8266 Web Server Started");
  Serial.println();
  Serial.print("The URL of ESP8266 Web Server is: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("Use the above URL in your Browser to access ESP8266 Web Server\n");

}

void loop() {
  // Wait a few seconds between measurements.
  LastEntry = millis();
  while (millis() < LastEntry + Delay) {
    // read DHT11 sensor
    float humid = dht.readHumidity();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float temp = dht.readTemperature(true);
    // Check if any reads failed and exit early (to try again).
    if (isnan(humid) || isnan(temp)) {
  	  Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(temp, humid);
    debug("heat index: ");
    debug(hif);
    debugln();

    // read BMP180 sensor (we could optinally use this for temperature)
    char status;
    double T, P, pres, a;
    //pressure.startTemperature();
    //pressure.getTemperature(T);
    //pressure.startPressure(3);
    //pressure.getPressure(P, T);
    //pres = P;

    // If you want sea-level-compensated pressure, as used in weather reports,
    // you will need to know the altitude at which your measurements are taken.
    // We're using a constant called ALTITUDE in this sketch:
  
    debugln();
    debug("provided altitude: ");
    debug(ALTITUDE);
    debug(" meters, ");
    debug(ALTITUDE*3.28084);
    debugln(" feet");
  
    // If you want to measure altitude, and not pressure, you will instead need
    // to provide a known baseline pressure. This is shown at the end of the sketch.

    // You must first get a temperature measurement to perform a pressure reading.

    // Start a temperature measurement:
    // If request is successful, the number of ms to wait is returned.
    // If request is unsuccessful, 0 is returned.

    status = pressure.startTemperature();
    if (status != 0) {
      // Wait for the measurement to complete:
      delay(status);

      // Retrieve the completed temperature measurement:
      // Note that the measurement is stored in the variable T.
      // Function returns 1 if successful, 0 if failure.

      status = pressure.getTemperature(T);
      if (status != 0) {
        // Print out the measurement:
        debug("temperature: ");
        debug(T);
        debug(" deg C, ");
        debug((9.0/5.0)*T+32.0);
        debugln(" deg F");
      
        // Start a pressure measurement:
        // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
        // If request is successful, the number of ms to wait is returned.
        // If request is unsuccessful, 0 is returned.

        status = pressure.startPressure(3);
        if (status != 0) {
          // Wait for the measurement to complete:
          delay(status);

          // Retrieve the completed pressure measurement:
          // Note that the measurement is stored in the variable P.
          // Note also that the function requires the previous temperature measurement (T).
          // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
          // Function returns 1 if successful, 0 if failure.

          status = pressure.getPressure(P,T);
          if (status != 0) {
            // Print out the measurement:
            debug("absolute pressure: ");
            debug(P);
            debug(" mb, ");
            debug(P*0.0295333727);
            debugln(" inHg");

            // The pressure sensor returns abolute pressure, which varies with altitude.
            // To remove the effects of altitude, use the sealevel function and your current altitude.
            // This number is commonly used in weather reports.
            // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
            // Result: p0 = sea-level compensated pressure in mb

            pres = pressure.sealevel(P,ALTITUDE);
            debug("relative (sea-level) pressure: ");
            debug(pres);
            debug(" mb, ");
            debug(pres*0.0295333727);
            debugln(" inHg");

            // On the other hand, if you want to determine your altitude from the pressure reading,
            // use the altitude function along with a baseline pressure (sea-level or other).
            // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
            // Result: a = altitude in m.

            a = pressure.altitude(P,pres);
            debug("computed altitude: ");
            debug(a);
            debug(" meters, ");
            debug(a*3.28084);
            debugln(" feet");
          }
          else debugln("error retrieving pressure measurement\n");
        }
        else debugln("error starting pressure measurement\n");
      }
      else debugln("error retrieving temperature measurement\n");
    }
    else debugln("error starting temperature measurement\n");

    // read BH1750 sensor
    uint16_t light = lightMeter.readLightLevel();

    //web server stuff

    WiFiClient client = espServer.available(); /* Check if a client is available */
    if(!client) {
      return;
    }

    /* HTTP Response in the form of HTML Web Page */
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(); //  IMPORTANT
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    
    /* CSS Styling for Buttons and Web Page */
    client.println("<style>");
    client.println("html { font-family: Courier New; display: inline-block; margin: 0px auto; text-align: center;}");
    client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
    client.println("</style>");
    client.println("</head>");
    
    /* The main body of the Web Page */
    client.println("<body>");
    client.println("<h2>yer basic weather station</h2>");
    client.print("<p>Temperature: </p>");
    client.println(temp);
    client.print("<p>Humidity: </p>");
    client.println(humid);
    client.print("<p>Heat Index: </p>");
    client.println(hif);
    client.print("<p>Pressure:  </p>");
    client.println(pres,2);
    client.print("<p>Light: </p>");
    client.println(light);
  }
}
