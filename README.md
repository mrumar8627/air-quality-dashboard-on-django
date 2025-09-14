# Air Quality Monitoring Dashboard

This project uses the **ESP8266 NodeMCU**, **DHT11 sensor**, and **MQ series gas sensor** to monitor real-time environmental conditions (temperature, humidity, and air quality). The data is displayed on a live dashboard built using **Chart.js** and served through a simple web interface.

## Components Needed:

- **ESP8266 NodeMCU** (or any similar ESP8266 board)
- **DHT11 Temperature and Humidity Sensor**
- **MQ Gas Sensor** (e.g., MQ-2, MQ-7, etc.)
- **Jumper Wires**
- **Breadboard**
- **10k Ohm Resistor** (for pull-up resistor in case of DHT11)
- **LCD Display (Optional)**

## Wiring Instructions:

### 1. **Wiring the DHT11 Sensor:**
   - **DHT11 VCC** → **ESP8266 3V3**
   - **DHT11 GND** → **ESP8266 GND**
   - **DHT11 Data** → **ESP8266 D4 (GPIO2)**

### 2. **Wiring the MQ Gas Sensor:**
   - **MQ Sensor VCC** → **ESP8266 5V**
   - **MQ Sensor GND** → **ESP8266 GND**
   - **MQ Sensor OUT** → **ESP8266 A0 (Analog Pin)**

### 3. **Optional LCD Wiring (For Displaying Data Locally)**:
   - **VCC** → **ESP8266 5V**
   - **GND** → **ESP8266 GND**
   - **SDA** → **ESP8266 D2 (GPIO4)**
   - **SCL** → **ESP8266 D1 (GPIO5)**

> **Note:** If you don’t have an LCD, the data will only be visible through the web interface.

## Step-by-Step Instructions:

### 1. **Setting Up the Hardware:**
   - Connect the **DHT11** sensor and **MQ gas sensor** to the **ESP8266 NodeMCU** as per the wiring instructions.
   - If you're using an **LCD**, wire it up to the **ESP8266** as described.
   - Make sure all the connections are correct to avoid any issues during testing.

### 2. **Setting Up the Arduino IDE:**
   - **Download and Install Arduino IDE** from [here](https://www.arduino.cc/en/software).
   - Install the **ESP8266 board package**:
     - Open the Arduino IDE and go to **File** → **Preferences**.
     - Add the following URL to the "Additional Boards Manager URLs" field:  
       `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
     - Go to **Tools** → **Board** → **Boards Manager** → Search for **ESP8266** and click **Install**.
   - Install the **DHT sensor library**:
     - Go to **Sketch** → **Include Library** → **Manage Libraries**.
     - Search for **DHT sensor library** by Adafruit and click **Install**.

### 3. **Uploading the Arduino Code to ESP8266:**
   - Open the **Arduino IDE** and select the **ESP8266** board from **Tools** → **Board** → Select your board (e.g., NodeMCU 1.0).
   - Connect your **ESP8266** to your computer via a USB cable.
   - Copy the Arduino code (the code you provided earlier) into the **Arduino IDE**.
   - Ensure you set the correct **WiFi SSID** and **Password** in the code.
   - Click **Upload** to upload the code to the **ESP8266**.
   
### 4. **Setting Up the Frontend (Dashboard):**
   - Create a new directory for the **web dashboard** files on your computer.
   - Copy the **`index.html`** (the one you modified earlier) into this directory.
   - Open the **`index.html`** file in a text editor and update the **API endpoint** (`const API = "/api/nodemcu/";`) to point to the **IP address** of your ESP8266. You can get this IP address from the **Serial Monitor** after uploading the code.

### 5. **Running the Dashboard:**
   - You can serve the **`index.html`** file from any web server (such as **Apache**, **Nginx**, or **Python HTTP Server**).
     - If you have **Python** installed, you can use a simple HTTP server:
       ```bash
       python -m http.server 8080
       ```
     - Visit `http://localhost:8080` in your browser to see the real-time dashboard.
     - If your ESP8266 is connected to a Wi-Fi network, the data should be updated on the dashboard every few seconds.

### 6. **Setting Up GitHub Pages (Optional):**
   - If you want to showcase the project live, you can deploy your **HTML** page on **GitHub Pages**.
   - Follow these steps to create a **gh-pages** branch and push your code:
     - In your local project directory, create a new branch:
       ```bash
       git checkout -b gh-pages
       ```
     - Push to GitHub:
       ```bash
       git push origin gh-pages
       ```
     - Go to **Settings** → **GitHub Pages** in your GitHub repository, and select **gh-pages** as the source.
     - Your page will be available at: `https://YOUR_USERNAME.github.io/REPOSITORY_NAME/`.

---

## Troubleshooting:

1. **No Data on Dashboard:**
   - Check the **Serial Monitor** for any error messages.
   - Make sure your **Wi-Fi credentials** in the code are correct.
   - Ensure the **ESP8266** is connected to the network and can be accessed by the frontend.

2. **MQ Sensor Data Is Not Updating:**
   - Ensure your MQ sensor is connected to the correct analog pin.
   - If using an analog sensor, ensure the sensor is calibrated properly.

---

## Conclusion

You have now successfully set up a **Real-Time Air Quality Monitoring Dashboard** using **ESP8266** and **DHT11**. This project can be further enhanced by adding more sensors, integrating data logging, or expanding the frontend interface.

---

### **License:**
Feel free to use this project for educational purposes. Please provide proper credit if you use or modify it. This project is licensed under the MIT License.

---

### **Contact:**
If you have any questions or need help with this project, feel free to reach out through my **LinkedIn** or **GitHub** profile.

