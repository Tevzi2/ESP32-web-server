#include <WiFi.h>

#ifndef U_SSID
  #define U_SSID "NO_NAME"
#endif

#ifndef U_PASSWORD
  #define U_PASSWORD "NO_PASSWORD"
#endif

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  delay(1000);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println((const char*)U_SSID);
  WiFi.begin((const char*)U_SSID, (const char*)U_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    String htmlFile = "<!DOCTYPE html><html>    <head>        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">        <link rel=\"icon\" href=\"data:,\">        <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\">         <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin>         <link href=\"https://fonts.googleapis.com/css2?family=Roboto:wght@100;400;900&display=swap\" rel=\"stylesheet\">        <title>Control pannel</title>        <style>            html {                font-family: Helvetica;                 display: inline-block;                 margin: 0px auto;                 text-align: center;                height: 100%;                font-family: 'Roboto', sans-serif;                color: white;            }            body {                margin: 0;                padding: 0;                height: 100%;            }            h1 {                text-align: center;                font-size: 38px;                font-weight: 900;            }            h2 {                text-align: center;                font-size: 32px;                font-weight: 900;            }            h3 {                text-align: center;                font-size: 22px;                margin-bottom: 0;            }            h4 {                text-align: center;                font-size: 18px;            }            .main-container {                background: rgb(120,55,164);                background: linear-gradient(49deg, rgba(120,55,164,1) 0%, rgba(253,29,29,1) 28%, rgba(252,176,69,1) 79%);                height: 100%;                width: 100%;                display: flex;                flex-flow: column;            }            .card {                margin: 25px 25px 25px 25px;                padding: 15px 15px 15px 15px;                background: rgba( 255, 255, 255, 0.25 );                box-shadow: 0 8px 32px 0 rgba( 31, 38, 135, 0.37 );                backdrop-filter: blur( 7px );                -webkit-backdrop-filter: blur( 7px );                border-radius: 10px;                border: 1px solid rgba( 255, 255, 255, 0.18 );                box-shadow: 3px 3px 10px 1px rgba(0, 0, 0, 0.2);            }            .flex-big {                display: flex;                flex-flow: row;                width: 100%;                height: 100%;            }            .left {                width: 67%;                grid-area: left;                display: flex;                flex-flow: column;                align-items: center;            }            .right {                width: 33%;                grid-area: right;                display: flex;                flex-flow: column;                align-items: center;            }            .title {                height: 10%;            }            .time-container{                height: 50%;                width: 100%;                font-size: 44px;                font-weight: 400;                margin: 5px 5px 5px 5px;            }            .divider{                border: 1px solid white;                background-color: white;                border-radius: 24px;                width: 80%;                padding: 0 20px 0 20px;                height: 2px;            }            .weather-container {                display: flex;                flex-flow: column;                justify-content: center;                align-items: center;                width: 100%;                height: 100%;                padding: 15px 20px 15px 20px;            }            .tl{                width: 33%;                border-bottom: 3px solid white;                border-right: 3px solid white;                display: flex;                flex-flow: column;                align-items: center;            }            .tm{                width: 33%;                border-bottom: 3px solid white;                display: flex;                flex-flow: column;                align-items: center;            }            .tr{                width: 33%;                border-left: 3px solid white;                border-bottom: 3px solid white;                display: flex;                flex-flow: column;                align-items: center;            }            .bl{                width: 66.35%;                display: flex;                flex-flow: column;                align-items: center;            }            .br{                width: 33%;                border-left: 3px solid white;            }            .temp {                margin-left: 15px;                color: white;                font-weight: 400;                font-size: 60px;            }            .temp-small {                margin-left: 15px;                color: white;                font-weight: 400;                font-size: 18px;                margin: 5px;            }            .flex-row {                height: 100%;                width: 100%;                display: flex;                flex-flow: column;                justify-content: center;                align-items: center;            }            .flex-column {                height: 100%;                display: flex;                flex-flow: row;                justify-content: center;                align-items: center;            }            .status-grid{                width: 100%;                display: flex;                flex-flow: row;            }            .sl {                width: 50%;                display: flex;                flex-flow: column;                justify-content: center;                align-items: center;            }            .sr {                width: 50%;            }            .weather-status {                display: flex;                flex-flow: row;                justify-content: center;                align-items: center;            }            .image-margin {                margin-top: 42px;            }        </style>    </head>    <body>        <div class=\"main-container\">            <div class=\"title\">                <h1>INFO PANEL</h1>            </div>            <div class=\"flex-big\">                <div class=\"left card\">                    <h2 id=\"city\">WEATHER: Slovenske Konjice</h2>                    <div class=\"weather-container\">                        <div class=\"flex-big\">                        <div class=\"tl\">                            <h3>TEMPERATURE</h3>                            <div class=\"flex-row\">                                <div id=\"temp\" class=\"temp\">                                    0 C                                </div>                                <div class=\"temp-small\" id=\"feels-temp\">Feels like: 0 C</div>                                <div class=\"temp-small\" id=\"min-temp\">Min. Temp: 0 C</div>                                <div class=\"temp-small\" id=\"max-temp\">Min. Temp: 0 C</div>                            </div>                        </div>                        <div class=\"tm\">                            <h3>HUMIDITY</h3>                            <div class=\"flex-row\">                                <div id=\"humidity\" class=\"temp\">0 %</div>                                <div class=\"temp-small\" id=\"pressure\">0 hPa</div>                            </div>                        </div>                        <div class=\"tr\">                            <h3>WIND</h3>                            <div class=\"flex-row\">                                <div id=\"wind-speed\" class=\"temp\">0 m/s</div>                                <div id=\"wind-deg\" class=\"temp-small\">0 deg</div>                            </div>                        </div>                        </div>                        <div class=\"flex-big\">                        <div class=\"bl\">                            <h3>STATUS</h3>                            <div class=\"status-grid\">                                <div class=\"sl\">                                    <h4 id=\"status\">Condition: Clear</h4>                                    <p id=\"desc\">Description: Weather is clear and warm</p>                                </div>                                <div class=\"sr\">                                    <h4>Weather conditions</h4>                                    <div class=\"temp-small\" id=\"rain\">Rain: 0 mm</div>                                    <div class=\"temp-small\" id=\"snow\">Snow: 0 mm</div>                                </div>                            </div>                        </div>                        <div class=\"br\">                            <h3>LOCATION INFO</h3>                            <div class=\"image-margin\">                                <div class=\"temp-small\" id=\"country\">SI</div>                                <div class=\"temp-small\" id=\"town\">Slovenske Konjice</div>                                <div class=\"temp-small\" id=\"coords-lat-lon\">45, 15</div>                            </div>                        </div>                        </div>                      </div>                </div>                <div class=\"right card\">                    <h2>DATE</h2>                    <p class=\"time-container\" id=\"Date\"></p>                    <div class=\"divider\"></div>                    <h2>TIME</h2>                    <p class=\"time-container\" id=\"Time\"></p>                </div>            </div>        </div>    </body>    <script>        const timeDisplay = document.getElementById(\"Time\");        const dateDisplay = document.getElementById(\"Date\");        const city = document.getElementById(\"city\");        const town = document.getElementById(\"town\");        const rain = document.getElementById(\"rain\");        const snow = document.getElementById(\"snow\");        const country = document.getElementById(\"country\");        const coords = document.getElementById(\"coords-lat-lon\");        const temp = document.getElementById(\"temp\");        const status = document.getElementById(\"status\");        const desc = document.getElementById(\"desc\");        const tempFeels = document.getElementById(\"feels-temp\");        const minTemp = document.getElementById(\"min-temp\");        const maxTemp = document.getElementById(\"max-temp\");        const humidity = document.getElementById(\"humidity\");        const pressure = document.getElementById(\"pressure\");        const windSpeed = document.getElementById(\"wind-speed\");        const windDeg = document.getElementById(\"wind-deg\");        const API_URL = \"\"; // here goes the openweathermap.org api url        var counter = 0;        fetch(API_URL, {            method: \"GET\"        }).then(res => {            return res.json();        }).then(data => {            city.innerHTML = \"WEATHER: \" + data.name;            town.innerHTML = data.name;            rain.innerHTML = \"Rain: \" + (data.hasOwnProperty(\"rain\") ? data.rain[\"1h\"] : 0) + \" mm\";            snow.innerHTML = \"Snow: \" + (data.hasOwnProperty(\"snow\") ? data.snow[\"1h\"] : 0) + \" mm\";            country.innerHTML = data.sys.country;            coords.innerHTML = data.coord.lat + \", \" + data.coord.lon;            temp.innerHTML = (Math.floor((data.main.temp - 273.15)*100))/100 + \" C\";            status.innerHTML = \"Condition: \"+data.weather[0].main;            desc.innerHTML = \"Description: \"+data.weather[0].description;            tempFeels.innerHTML = \"Feels like: \" + (Math.floor((data.main.feels_like - 273.15)*100))/100 + \" C\";            minTemp.innerHTML = \"Min. Temp: \" + (Math.round((data.main.temp_min - 273.15)*100))/100 + \" C\";            maxTemp.innerHTML = \"Max. Temp: \" + (Math.floor((data.main.temp_min - 273.15)*100))/100 + \" C\";            humidity.innerHTML = data.main.humidity + \"%\";            pressure.innerHTML = data.main.pressure + \" hPa\";            windSpeed.innerHTML = data.wind.speed + \"m/s\";            windDeg.innerHTML = data.wind.deg + \" deg\";        });                function refreshTime() {            counter++;            if(counter == 600) {                fetch(API_URL, {                    method: \"GET\"                }).then(res => {                    return res.json();                }).then(data => {                    city.innerHTML = \"WEATHER: \" + data.name;                    town.innerHTML = data.name;                    rain.innerHTML = \"Rain: \" + (data.hasOwnProperty(\"rain\") ? data.rain[\"1h\"] : 0) + \" mm\";                    snow.innerHTML = \"Snow: \" + (data.hasOwnProperty(\"snow\") ? data.snow[\"1h\"] : 0) + \" mm\";                    country.innerHTML = data.sys.country;                    coords.innerHTML = data.coord.lat + \", \" + data.coord.lon;                    temp.innerHTML = (Math.floor((data.main.temp - 273.15)*100))/100 + \" C\";                    status.innerHTML = data.weather[0].main;                    desc.innerHTML = data.weather[0].description;                    tempFeels.innerHTML = \"Feels like: \" + (Math.floor((data.main.feels_like - 273.15)*100))/100 + \" C\";                    minTemp.innerHTML = \"Min. Temp: \" + (Math.round((data.main.temp_min - 273.15)*100))/100 + \" C\";                    maxTemp.innerHTML = \"Max. Temp: \" + (Math.floor((data.main.temp_min - 273.15)*100))/100 + \" C\";                    humidity.innerHTML = data.main.humidity + \"%\";                    pressure.innerHTML = data.main.pressure + \" hPa\";                    windSpeed.innerHTML = data.wind.speed + \"m/s\";                    windDeg.innerHTML = data.wind.deg + \" deg\";                });                counter = 0;            }            var dateString = new Date().toLocaleString().replace(/\\//g, \". \").split(\", \");            timeDisplay.innerHTML = dateString[1];            dateDisplay.innerHTML = dateString[0];        }        setInterval(refreshTime, 1000);    </script></html>";//endOfVar
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Display the HTML web page
            client.println(htmlFile);
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}