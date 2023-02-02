# Wi-Fi Router example

## Overview

This example focuses on the networking part, enables forwarding packets between network interfaces. It creates a WiFi soft AP, which uses NAT to forward packets to and from the Station network interface.

![wifi_router](https://github.com/espressif/esp-iot-bridge/blob/master/components/iot_bridge/doc/_static/wifi_router_en.png?raw=true)

### How to use example
#### Hardware Required
- An esp32 series development board
- A Micro-USB cable for power supply and programming

Follow detailed instructions provided specifically for this example.

#### Build and Flash
Run `idf.py flash monitor` to build, flash and monitor the project.

Once a complete flash process has been performed, you can use `idf.py app-flash monitor` to reduce the flash time.

(To exit the serial monitor, type `Ctrl-]`. Please reset the development board f you cannot exit the monitor.)

For more information, see [User_Guide.md](https://github.com/espressif/esp-iot-bridge/blob/master/components/iot_bridge/User_Guide.md).