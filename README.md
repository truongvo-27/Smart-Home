# SmartHome_IoT

🚀 **An IoT-based Smart Home System using ESP32, Firebase & PyQt**

## 📌 Overview
This project is an **IoT-based smart home system** that allows users to remotely control home appliances (air conditioners, air purifiers, lights) and monitor environmental parameters (temperature, humidity, fine dust concentration) via a **web interface and a desktop application**. The system is powered by **ESP32** and communicates with **Google Firebase** for real-time data synchronization.

## 🌟 Features
- **Remote Control**: Turn on/off home appliances via a web dashboard and a desktop app.
- **Real-time Monitoring**: Track temperature, humidity, and air quality.
- **Data Visualization**: Display sensor data in graphical format.
- **Firebase Integration**: Store and retrieve data in real-time.
- **User-friendly Web UI**: Built with **HTML, CSS, JavaScript**.
- **Desktop Application**: Developed using **Python & PyQt** for an intuitive user experience.

## 🛠️ Technologies Used
- **Hardware**: ESP32, DHT11/DHT22 (temperature & humidity sensor), PM2.5 sensor, Relays.
- **Cloud Backend**: Google Firebase (Realtime Database, Authentication).
- **Frontend**: HTML, CSS, JavaScript.
- **Desktop App**: Python, PyQt.
- **Communication Protocols**: HTTP, MQTT.

## 📷 Screenshots
![Dashboard Preview](![image](https://github.com/user-attachments/assets/107af6da-0144-45ee-ba7e-758eb5b15be2)

![Desktop App Preview](![image](https://github.com/user-attachments/assets/7d2f4abf-c317-4db4-9764-098b87b654da)

## 🚀 Getting Started
### 📌 Hardware Requirements
- **ESP32 Board**
- **DHT11/DHT22 Sensor** (for temperature & humidity)
- **PM2.5 Sensor** (for air quality monitoring)
- **Relay Modules** (to control appliances)
- **Jumper Wires & Breadboard**

### 🔧 Installation & Setup
1. **Clone this repository**
   ```bash
   git clone https://github.com/HuynhDucRio/SmartHome_IoT.git
   cd SmartHome_IoT
   ```
2. **Flash code to ESP32** (Using Arduino IDE or PlatformIO)
3. **Setup Firebase**:
   - Create a Firebase project
   - Enable Realtime Database
   - Obtain API keys & update in the code
4. **Run the Web UI**:
   - Open `index.html` in a browser
   - Connect with Firebase to visualize data
5. **Run the Desktop App**:
   - Install dependencies: `pip install -r requirements.txt`
   - Run the PyQt app: `python app.py`

## 🔗 Project Demo & Repo
- **GitHub Repository**: [SmartHome_IoT](https://github.com/HuynhDucRio/SmartHome_IoT)

## 📬 Contact
📧 **Email**: ducdep102@gmail.com    

## 📜 License
This project is licensed under the **MIT License** - feel free to use and modify! 🎉
