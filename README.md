# Ethernet_and_433hmz

This IoT project is an integration of 433Mhz RF Transmitter-Reciever Module,
Utrasonic sensor and Wifi module.

The project was based on the Master-Slave concept, the slave collects
the data using ultrasonic sensor and sends it to the master using RF technology.

Based on ASK technique, the RF module is a low cost transmitter
can transmit signals up to 100 meters

An ultrasonic sensor (HC-SR04) is an electronic device that measures the
distance of a target object by emitting ultrasonic sound waves,
and converts the reflected sound into an electrical signal.
Ultrasonic waves travel faster than the speed of audible sound
(i.e. the sound that humans can hear).
The Detection Distance of HC-SR04: 2 cm to 450 cm

NodeMCU includes firmware that runs on the ESP8266 Wi-Fi SoC
and hardware which is based on the ESP-12 module,
It can act as both WiFi Hotspot or can connect to one.

The master recieves the data from the slave and using Wifi module like nodeMCU,
it sends the data to a web based application. A mobile app is used to broadcast
network credentials from smartphone.

Link to the mobile app is as follows:-
https://play.google.com/store/apps/details?id=com.khoazero123.iot_esptouch_demo&hl=en_IN&gl=US
