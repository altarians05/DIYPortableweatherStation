# PrintingWeatherStationSENA
Development of a portable, open-source environmental monitoring station. This project enables real-time data collection and visualization using low-cost sensors. Designed for educational and research applications, it promotes learning about environmental monitoring technologies and programming. This is the complete version of the environmental monitoring station, designed for real-time environmental data collection with WiFi connectivity. Powered by an ESP32 board, this station includes advanced sensors and features to monitor various environmental parameters and transmit data wirelessly. The system is ideal for applications in educational research and real-time monitoring of environmental variables.

Main Features:
- Variables Measured: Temperature, Humidity, Pressure, Air Quality.
- BME680 Sensor (Bosch): Combines multiple sensors (temperature, humidity, pressure, and air quality) in a single module.
- Data Storage: MicroSD card used as the primary storage device for recorded data.
- Real-Time Clock: DS3231 RTC module records the time of each measurement.
- Data Display: 0.96" OLED screen with a rotary encoder for an enhanced user interface (HMI).
- Energy Autonomy: Solar energy collection system for sustainable operation.
- WiFi Connectivity: Built-in WiFi on the ESP32 board for remote data access and monitoring.

Connections:
- BME680 Sensor: SCL -> GPIO22, SDA -> GPIO21, 5V, GND.
- RTC DS3231: SCL -> GPIO22, SDA -> GPIO21, 5V, GND.
- OLED 0.96" Display: SCL -> GPIO22, SDA -> GPIO21, 5V, GND.
- MicroSD Module: CS -> GPIO05, MOSI -> GPIO23, SCK -> GPIO18, MISO -> GPIO19, 5V, GND.
- Rotary Encoder KY-040: DT -> GPIO25, CLK -> GPIO26, SW -> GPIO33, 5V, GND.

Project Purpose: This ESP32-based version provides the advantage of WiFi connectivity, allowing real-time data transmission over the internet for remote monitoring. Ideal for use in the Tecnoacademia de Manizales, it enables the study of environmental conditions and their impact on various processes. The station is designed to be a portable and open-source solution, offering flexibility for future expansions, including cloud integration and data visualization on external platforms.

With improved sensors and energy autonomy through solar power, this version is suitable for both educational purposes and practical applications in monitoring and analyzing environmental factors over time.

Perfect for engineers, makers, and researchers looking to explore environmental monitoring with cost-effective and versatile tools.

Download includes: 
- Arduino Codes: Fully documented and ready to upload to your ESP32.
- 3D Models: The enclosure and modular components are available in STEP format, suitable for editing and printing.

Download Links:
- Tinkercad: https://www.tinkercad.com/things/6pniuVdfldQ-estacion-de-monitoreo-iot-rev4
- Thingiverse: https://www.thingiverse.com/thing:6854103
- Grabcad: https://grabcad.com/library/diy-portable-weather-station-1

