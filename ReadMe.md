# BG_DIY_WxStn.ino

[Banggood AOQDQDQD ESP8266 Weather Station Kit](https://www.banggood.com/AOQDQDQD-ESP8266-Weather-Station-Kit-with-Temperature-Humidity-Atmosphetic-Pressure-Light-Sensor-0_96-Display-for-Arduino-IDE-IoT-Starter-p-1751604.html)
with the LM393 Rain Sensor and SI1145 UV Sensor included.

Branches
- *master*: Intended to be starter code for original kit (w/o LCD screen) for external data collection
- *ArduinoJson*: Includes LM393 and SI1145 and provides JSON output using ArduinoJson library
- *DeepSleep*: Includes LM393 and SI1145 and utilizes ESP8266 DeepSleep functionality and only outputs to console.  This
will be the base of the upcoming MQTT branch which will send data influxdb/grafana server.
- *MQTT*: **FUTURE BRANCH** starting from *DeepSleep* branch
- *StringJson*: Predecessor to *ArduinoJson* code and performs the same function using normal string functions.
- *ThingSpeak*: Written at the request of another individual and only includes the LM393 rain sensor.  Data collection works
but ThingSpeak data transfer has not been tested.

***The power portion of the circuit has not been tested.***

Uses libraries from Adafruit, Adi Dax, Sparkfun, Christopher Laws and various individual contributers to the arduino
library ecosystem

Common Downloaded Libraries
- DHT11 - [https://github.com/adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library.git)
- BMP180 - [https://github.com/LowPowerLab/SFE_BMP180.git](https://github.com/LowPowerLab/SFE_BMP180.git)
- BH1750 (AKA GY-30) - [https://github.com/claws/BH1750.git](https://github.com/claws/BH1750.git)
- SI1145 - [https://github.com/adafruit/Adafruit_SI1145_Library](https://github.com/adafruit/Adafruit_SI1145_Library.git)
- ESP8266 [https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino.git)
- WiFiManager [https://github.com/tzapu/WiFiManager](https://github.com/tzapu/WiFiManager.git) : [Demo Youtube Video](https://www.youtube.com/watch?v=Errh7LEEug0)

ArduinoJson Branch Libaries
- ArduinoJSON - [https://github.com/bblanchon/ArduinoJson.git](https://github.com/bblanchon/ArduinoJson.git)

ThingSpeak Branch Libraries
- ThingSpeak - [https://github.com/mathworks/thingspeak-arduino](https://github.com/mathworks/thingspeak-arduino)

Original wifi example file by pileofstuff.ca, his [Youtube video](https://www.youtube.com/watch?v=G_dTu2_HSjk) and his original [files](https://pileofstuff.ca/project_files/banggood_weather_station_kit/)

Another [Youtube video](https://www.youtube.com/watch?v=ONFXzi4LSHk) but backofficeshow of the kit, but no code was offered that I could find.

[GitHub repo](https://github.com/GJKJ/WSKS) with semi-useful info, that was added to my repo to make it easier to find.

Settings you will need to change for your station
- const char* ssid {"XXXXXXXXXX"};       // SSID of your wireless network
- const char* password {"XXXXXXXXXX"};   // Password for your wireless network
- const float ALTITUDE {171.0};          // Altitude of your location (in meters)
- IPAddress ip(###, ###, ###, ###);      // IP address of your device, or remove completely for DHCP
- IPAddress gateway(###, ###, ###, ###); // Gateway IP address of your network, or remove completely for DHCP
- IPAddress subnet(###, ###, ###, ###);  // Network Subnet Mask of your network, or remove completely for DHCP

Revisions:
- 11 July 2021: Code clean-up due to my OCD
- 26 August 2021: First working sketch
- 27 August 2021: More code clean-up and replace web output with json output (StringJson)
- 28 August 2021: Utilize Arduino Json library to construct json output (ArduinoJson)
- 20 November 2021: Added rain sensor with assistance from [here](https://www.youtube.com/watch?v=2layMOhue7M&t)
- 23 November 2021: Added deep sleep with assistance from [here](https://randomnerdtutorials.com/esp8266-deep-sleep-with-arduino-ide/) (DeepSleep,ThingSpeak). Replace Serial(ln) with Debug(ln) to allow enable/disable of debug content in serial monitor.
- 22 December 2021: Standardize format of constants with the sketch.  Added code for SI1145 UV sensor.
