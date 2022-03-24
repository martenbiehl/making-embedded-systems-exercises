# # Week 1 - Exercise 1: Idea project diagram

## Summary

The system measures the air quality in a room and displaying the readings to a user if they are standing in front of the system. The user can page through different air quality measurements and if they move away the display switches off. The air quality readings are transmitted to a server so they can be logged.

The air quality measures are temperature, humidity, particulate matter (PM2.5 and PM10), eCO2, formaldehyde, volatile organice compounds (TVOC). The presence of the user is detected with an ultrasound sensor. The user can page through the air quality measurements with the onboard button.

The connection to the server is handled by a networking co-processor.

- **Option 1:** Particle Xenon using CoAP over OpenThread
- **Option 2:** ESP32 using MQTT over Wifi

## Diagrams

```mermaid



```

## Parts list

https://www.banggood.com/SM300D2-7-in-1-PM2_5-+-PM10-+-Temperature-+-Humidity-+-CO2-+-eCO2-+-TVOC-Sensor-Tester-Detector-Module-for-Air-Quality-Monitoring-p-1681079.html?cur_warehouse=CN

STM32F429I-DISC1

https://www.st.com/en/evaluation-tools/32f429idiscovery.html
