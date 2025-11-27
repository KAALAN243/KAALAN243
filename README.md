On_DAc Full ESP-IDF Workspace (Internal DAC)

Default pins used (change in headers if needed):
 - ST7789: MOSI=23, SCLK=18, CS=5, DC=16, RST=17, BL=4
 - Buttons: PLAY=13, NEXT=12, PREV=14, VOL+=27, VOL-=26
 - Audio: Internal DAC (GPIO25 / DAC1)

Build steps (ESP-IDF installed and environment sourced):
 1) cd On_DAc_ESP32_Workspace
 2) Generate logo.h (see tools/README below)
 3) idf.py set-target esp32
 4) idf.py menuconfig   # ensure Classic BT enabled (if using A2DP)
 5) idf.py build
 6) idf.py -p /dev/ttyUSB0 flash monito
 - Linux/macOS: zip -r On_DAc_ESP32_Workspace.zip On_DAc_ESP32_Workspace
 - Windows PowerShell: Compress-Archive -Path .\On_DAc_ESP32_Workspace\ -DestinationPath .\On_DAc_ESP32_Workspace.zip