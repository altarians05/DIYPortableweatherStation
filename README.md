# PrintingWeatherStationSENA
This project is a portable environmental monitoring station designed for air quality analysis, weather tracking, and gas measurement. Built as an open-source solution 🛠️🌐, it integrates IoT capabilities, making it ideal for educational projects, environmental research, and DIY enthusiasts. 🤓🔧

![Render2](https://github.com/user-attachments/assets/8b6a5cb7-3b91-4732-8c34-d4d53aa1e22a)

https://github.com/user-attachments/assets/fe1a357f-786f-4a88-b8d0-5f952dd97595

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

![Render1](https://github.com/user-attachments/assets/a28f2512-0d2d-4490-8a30-01b58cd39081)

Download Includes 📂:
- 📜 Arduino Codes: Fully documented and ready to upload to your ESP32. 🚀
- 📐 3D Models: The enclosure and modular components are available in STEP format, suitable for editing and printing. 
- ⚡ Electronics Wiring Diagram: Comprehensive connection diagrams created in Fritzing, guiding the setup of all electronic components. 🔌🖥️

Download Links 🔗:
- 📌 [Tinkercad](https://www.tinkercad.com/things/6pniuVdfldQ-estacion-de-monitoreo-iot-rev4)
- 📌 [Thingiverse](https://www.thingiverse.com/thing:6854103)
- 📌 [Grabcad](https://grabcad.com/library/diy-portable-weather-station-1)

⚙️ Connections:
- 🌡️ BME680 Sensor: 🛠️ SCL -> GPIO22, 🛠️ SDA -> GPIO21, ⚡ 5V, 🌍 GND
- ⏰ RTC DS3231: 🛠️ SCL -> GPIO22, 🛠️ SDA -> GPIO21, ⚡ 5V, 🌍 GND
- 📟 OLED 0.96" Display: 🛠️ SCL -> GPIO22, 🛠️ SDA -> GPIO21, ⚡ 5V, 🌍 GND
- 💾 MicroSD Module: 🛠️ CS -> GPIO05, 🛠️ MOSI -> GPIO23, 🛠️ SCK -> GPIO18, 🛠️ MISO -> GPIO19, ⚡ 5V, 🌍 GND
- 🔄 Rotary Encoder KY-040: 🛠️ DT -> GPIO25, 🛠️ CLK -> GPIO26, 🛠️ SW -> GPIO33, ⚡ 5V, 🌍 GND

![05_Circuit_Diagram_ESPWROOM32](https://github.com/user-attachments/assets/f012310b-f9d6-4136-87b6-e23a1d1326a4)

📚 Libraries and Resources:
- 🛠️ BME680 Sensor
  - 📂 Library: [Download Here](https://n9.cl/2wgdx)
  - 📖 Guide: [How to Use](https://n9.cl/31472)
  - 🎓 Tutorial: [Simple Example](https://n9.cl/s88k9)

- ⏰ RTC DS3231
  - 📂 Library: [RTClib by Adafruit](https://github.com/adafruit/RTClib)
  - 📖 Guide: [Setup Instructions](https://n9.cl/o9x3j) 
  - 🎓 Tutorial: [Simple Example](https://n9.cl/v09a0) 

- 📟 OLED 0.96'' Display
  - 📂 Library: [Library Link 1](www.n9.cl/xlc9w), [Library Link 2](www.n9.cl/xv1dp)
  - 📖 Guide: [Setup Instructions](https://n9.cl/l03ufr) 
  - 🎓 Tutorial: [Beginner Guide 1](www.n9.cl/jzy5xj), [Beginner Guide 2](www.n9.cl/f29yyf) 

- 💾 MicroSD Module
  - 📂 Library: [Download Here](https://n9.cl/z0hjuf)
  - 📖 Guide: [Setup Instructions](https://n9.cl/nbez7)
  - 🎓 Tutorial: [Example Project](https://n9.cl/s88k9)

- 🔄 Rotary Encoder KY-040
  - 📂 Library: Not Required 🎉
  - 📖 Guides: [Guide 1](https://n9.cl/tbt4g), [Guide 2](https://n9.cl/v2f8)
  - 🎓 Tutorials: [Beginner Guide 1](https://n9.cl/rmjnv), [Beginner Guide 2](https://n9.cl/bn3d6)

💡 Support the Project!
If you find this project useful or inspiring, consider supporting it in each link by:
- ⭐ Following the project on all platforms.
- 👍 Giving it a like to help boost its visibility.
- 💬 Leaving a comment with your thoughts or suggestions.

As an open-source research initiative 🌱, your interaction helps us gain visibility 👀 and continue contributing to the community 🌍. Together, we can inspire more innovations ✨ and improvements!
