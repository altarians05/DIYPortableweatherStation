# PrintingWeatherStationSENA
This project is a portable environmental monitoring station designed for air quality analysis, weather tracking, and gas measurement. Built as an open-source solution 🛠️🌐, it integrates IoT capabilities, making it ideal for educational projects, environmental research, and DIY enthusiasts. 🤓🔧

✨ Key Features ✨
- ✅ Multi-sensor integration for temperature, humidity, air pressure, and gas concentration. 🌡️💧⚡
- ✅ Compact and lightweight portable design. 🎒📏
- ✅ Compatibility with Raspberry Pi 🍓 and Arduino 🤖 for easy customization.
- ✅ Open-source documentation 📂 and designs 🖌️ to encourage collaboration 🤝.
- ✅ Perfect for outdoor monitoring 🏞️ and data logging 📊.
- ✅ MicroSD card 📀 used for recorded data storage.
- ✅ DS3231 RTC module 🕒 records the time of each measurement.
- ✅ 0.96" OLED screen 🖥️ with a rotary encoder for an enhanced HMI.
- ✅ Solar energy collection ☀️🔋 for sustainable operation.
- ✅ Built-in WiFi on the ESP32 board 📶 for remote data access and monitoring.
- ✅ Example Arduino scripts 💻 for sensor integration.

Perfect for 🔬 Engineers, Makers 🛠️, and Researchers 📚 looking to explore environmental monitoring with cost-effective 🌟 and versatile tools.

Download Includes 📂:
- 📜 Arduino Codes: Fully documented and ready to upload to your ESP32. 🚀
- 📐 3D Models: The enclosure and modular components are available in STEP format, suitable for editing and printing. 
- ⚡ Electronics Wiring Diagram: Comprehensive connection diagrams created in Fritzing, guiding the setup of all electronic components. 🔌🖥️

Download Links 🔗:
- 📌 Tinkercad: https://www.tinkercad.com/things/6pniuVdfldQ-estacion-de-monitoreo-iot-rev4
- 📌 Thingiverse: https://www.thingiverse.com/thing:6854103
- 📌 Grabcad: https://grabcad.com/library/diy-portable-weather-station-1

⚙️ Connections:
- 🌡️ BME680 Sensor: 🛠️ SCL -> GPIO22, 🛠️ SDA -> GPIO21, ⚡ 5V, 🌍 GND
- ⏰ RTC DS3231: 🛠️ SCL -> GPIO22, 🛠️ SDA -> GPIO21, ⚡ 5V, 🌍 GND
- 📟 OLED 0.96" Display: 🛠️ SCL -> GPIO22, 🛠️ SDA -> GPIO21, ⚡ 5V, 🌍 GND
- 💾 MicroSD Module: 🛠️ CS -> GPIO05, 🛠️ MOSI -> GPIO23, 🛠️ SCK -> GPIO18, 🛠️ MISO -> GPIO19, ⚡ 5V, 🌍 GND
- 🔄 Rotary Encoder KY-040: 🛠️ DT -> GPIO25, 🛠️ CLK -> GPIO26, 🛠️ SW -> GPIO33, ⚡ 5V, 🌍 GND

📚 Libraries and Resources: To make your setup easier, here’s a list of libraries and guides for the components used in this project. 💡
- 🛠️ BME680 Sensor
  - 📂 Library: Download Here
  - 📖 Guide: How to Use
  - 🎓 Tutorial: Simple Example

- ⏰ RTC DS3231
  📂 Library: RTClib by Adafruit
  📖 Guide: Setup Instructions
  🎓 Tutorial: Simple Example

- 📟 OLED 0.96'' Display
  📂 Library: Library Link 1, Library Link 2
  📖 Guide: Setup Instructions
  🎓 Tutorial: Beginner Guide 1, Beginner Guide 2

- 💾 MicroSD Module
  📂 Library: Download Here
  📖 Guide: Setup Instructions
  🎓 Tutorial: Example Project

- 🔄 Rotary Encoder KY-040
  📂 Library: Not Required 🎉
  📖 Guides: Guide 1, Guide 2
  🎓 Tutorials: Beginner Guide 1, Beginner Guide 2

💡 Support the Project!
If you find this project useful or inspiring, consider supporting it in each link by:
- ⭐ Following the project on all platforms.
- 👍 Giving it a like to help boost its visibility.
- 💬 Leaving a comment with your thoughts or suggestions.

As an open-source research initiative 🌱, your interaction helps us gain visibility 👀 and continue contributing to the community 🌍. Together, we can inspire more innovations ✨ and improvements!
