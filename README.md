#Water Meter using the ESP8266

The goal of this project is to monitor my water meter using a remote system comprised of an ESP8266 and a MAG3110 Magnetometer.  The device is intended to be solar powered using a cannibalized solar cell and battery from a solar floodlight.

Data will be processed locally on the ESP8266 to determine instantaneous use, and will be sent via WiFi to an InfluxDB instance running on a Raspberry Pi.
