## About
Small Arduino project I made for 13v battery discharge control based on the voltage divider output monitoring. Firmware will check the voltage with defined delay, display output on the 128x64 i2c OLED display *(SSD1306)*, and shut the power relay down when min. voltage reached.


Project is configured to build, upload and monitor with `arduino-cli` utility on any platform. Default configuration includes only **Uno** board for now.


## Build
```sh
$ arduino-cli compile
```


## Upload
```sh
$ arduino-cli upload -p <DEVICE_PATH>
```
