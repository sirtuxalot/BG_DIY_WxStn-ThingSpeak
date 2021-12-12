# BG_DIY_WxStn.ino

[Banggood AOQDQDQD ESP8266 Weather Station Kit](https://www.banggood.com/AOQDQDQD-ESP8266-Weather-Station-Kit-with-Temperature-Humidity-Atmosphetic-Pressure-Light-Sensor-0_96-Display-for-Arduino-IDE-IoT-Starter-p-1751604.html) 

Uses libraries from Adafruit, Adi Dax, Sparkfun, Christopher Laws and various individual contributers to the arduino
library ecosystem

Common Downloaded Libraries
- DHT11 - [https://github.com/adafruit/DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)
- BMP180 - [https://github.com/LowPowerLab/SFE_BMP180.git](https://github.com/LowPowerLab/SFE_BMP180.git)
- BH1750 (AKA GY-30) - [https://github.com/claws/BH1750.git](https://github.com/claws/BH1750.git)
- ESP8266 [https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino)
- ArduinoJSON - [https://github.com/bblanchon/ArduinoJson.git](https://github.com/bblanchon/ArduinoJson.git)

Original wifi example file by pileofstuff.ca, his [Youtube video](https://www.youtube.com/watch?v=G_dTu2_HSjk) and his original [files](https://pileofstuff.ca/project_files/banggood_weather_station_kit/)

Another [Youtube video](https://www.youtube.com/watch?v=ONFXzi4LSHk) but backofficeshow of the kit, but no code was offered that I could find.

[GitHub repo](https://github.com/GJKJ/WSKS) with semi-useful info, that was added to my repo to make it easier to find.

Settings you will need to change for your station
- const char* ssid = "XXXXXXXXXX";       // SSID of your wireless network
- const char* password = "XXXXXXXXXX";   // Password for your wireless network
- \#defi#define ALTITUDE 171.0            // Altitude of your location (in meters)
- IPAddress ip(192, 168, 254, 128);      // IP address of your device, or remove completely for DHCP
- IPAddress gateway(192, 168, 254, 1);   // Gateway IP address of your network, or remove completely for DHCP
- IPAddress subnet(255, 255, 255, 0);    // Network Subnet Mask of your network, or remove completely for DHCP

Revisions:
- 11 July 2021: Code clean-up due to my OCD
- 26 August 2021: First working sketch
- 27 August 2021: More code clean-up and replace web output with json output
- 28 August 2021: Utilize Arduino Json library to construct json output
- 20 November 2021: Added rain sensor with assistance from [here](https://www.youtube.com/watch?v=2layMOhue7M&t)
- 23 November 2021: Added deep sleep with assistance from [here](https://randomnerdtutorials.com/esp8266-deep-sleep-with-arduino-ide/)
