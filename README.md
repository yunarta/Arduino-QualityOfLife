# QualityOfLife - Arduino App

This project demonstrates an Arduino-based application designed to configure and connect to a WiFi network using the
ESP32 platform. It features configuration handling via a JSON file stored on the LittleFS file system and provides
functionality for initial setup, WiFi connection, and time synchronization using NTP servers. Debugging and
informational logging are optionally supported through `Serial` output.

---

## Features

1. **JSON Configuration Handling**:
    - The application reads a configuration file (`/config.json`) from the LittleFS file system.
    - Parses the configuration to retrieve network credentials such as SSID and password.

2. **WiFi Management**:
    - Connects to a WiFi network with the provided credentials.
    - Includes retry mechanisms and deep-sleep behavior in case of connection failures.
    - TX power is configured to 19 dBm for the WiFi module.

3. **NTP Time Synchronization**:
    - Synchronizes the system time using NTP servers (`pool.ntp.org` & `time.nist.gov`).
    - Includes retry mechanisms and deep-sleep behavior if synchronization fails.

4. **Logging Options**:
    - Conditionally prints debug and informational messages via `Serial` when `LOG_DEBUG` or `LOG_INFO` macros are
      enabled.

---

## Components

The project uses the following components:

1. **Arduino Framework:**
    - Core functionality implemented with Arduino-compatible libraries.

2. **LittleFS:**
    - Stores and retrieves configuration data in the form of a JSON file.

3. **WiFi Library:**
    - Handles WiFi connection and configuration.

4. **ArduinoJson:**
    - Parses the configuration file for JSON data.

---

## Code Overview

### Configuration Handling (`ArduinoAppConfig`)

- **Initialization:**  
  The `begin` method opens the configuration file located at `/config.json`, parses it as a JSON object, and loads the
  configuration data.

- **Example Debug Output:**
    - `[DEBUG] Failed to open /config.json` (if file is not found).
    - `[DEBUG] JSON configuration parsed successfully`.

### Internet Connection (`connectToInternet`)

- **WiFi Process:**
    - Reads the `SSID` and `password` from the configuration loaded earlier.
    - Configures and connects to the defined WiFi network.
    - Logs successful connection or retries entering deep sleep on failures.

- **Time Synchronization:**
    - Updates system time using two NTP servers.
    - Retires and enters deep sleep if synchronization fails.

- **Example Info Output:**
    - `[INFO] Connecting to WiFi SSID: <your-ssid>`.
    - `[INFO] WiFi connected successfully`.
    - `[INFO] Time synchronized successfully`.

---

## JSON Configuration File Format

The `/config.json` file is expected to have the following structure:

```json
{
  "network": {
    "ssid": "<your-ssid>",
    "password": "<your-wifi-password>"
  }
}
```

---

## How to Use

1. **Preparation:**
    - Ensure the ESP32 development board is correctly set up for Arduino development.
    - Upload the `config.json` file with the required network credentials to the `LittleFS` filesystem.

2. **Code Deployment:**
    - Customize logging macros (`LOG_DEBUG`, `LOG_INFO`) in the code as necessary.
    - Compile and upload the code to your ESP32 device.

3. **Device Operation:**
    - The ESP32 will attempt to:
        1. Parse the configuration file.
        2. Connect to the specified WiFi network.
        3. Synchronize time using NTP servers.

4. **Fallback Behavior:**
    - If connection or synchronization fails, the device will enter deep sleep mode.

---

## Dependencies

The following libraries are required:

1. [`WiFi`](https://www.arduino.cc/reference/en/libraries/wifi/)
2. [`LittleFS`](https://github.com/lorol/LITTLEFS)
3. [`ArduinoJson`](https://arduinojson.org/)

Be sure to install these libraries using the Arduino Library Manager or add them to your project manually.

---

## License

This project is for educational and demonstration purposes. Customize and adapt it to your own needs.

---

## Author

**yunarta**  
Created on 3/15/25