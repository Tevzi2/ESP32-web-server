ESP32 Web Server
=======

This is a very simple webserver for the ESP32 development board. It has a simple tool in the project that you can use to read in a html file to the `main.cpp` document.

![This is what it looks like](https://github.com/tevzi2/esp32-web-server/infopanel.png)

The html file in the project root called `main.html` is what will be read into the `main.cpp`. The provided page is a simple weather and time info panel. To make it work just make sure to set the variable `API_TOKEN` to the API url of the openweathermap.org. It's a free weather API.

To run the tool with make and node installed simply call this command in the project root:

```
make read_html
```

If you do not have make just call this command with node:

```
node index.js
```

### SETTING UP THE PROJECT

To get the project setup there is only one real step: rename `platform.ini.example` to `platform.ini` and set the compiler flags `U_SSID`and `U_PASSWORD`to the SSID/name and password of you WiFi network. 

After that you can just simply push the file onto your development board.