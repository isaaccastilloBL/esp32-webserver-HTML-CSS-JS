/*
  _______  ______    _______  _______  _______  ______
  |       ||    _ |  |       ||       ||       ||    _ |
  |    _  ||   | ||  |   _   ||    _  ||    ___||   | ||
  |   |_| ||   |_||_ |  | |  ||   |_| ||   |___ |   |_||_
  |    ___||    __  ||  |_|  ||    ___||    ___||    __  |
  |   |    |   |  | ||       ||   |    |   |___ |   |  | |
  |___|    |___|  |_||_______||___|    |_______||___|  |_|
  https://github.com/Proper920

*/

/*---------------------------LIBRARIES------------------------*/

#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>

/*--------------------------SET WEB SERVER PORT TO 80-----------------------*/

AsyncWebServer server(80);

/*---------------------------WI-FI CREDENTIALS------------------------*/

const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_SSID";

/*---------------------------GLOBAL VARIABLES------------------------*/

const int ledout = 2; //Assign output variables to GPIO pins

const char index_html[] PROGMEM = {/*Put here your HTML code in string format*/};
const char master_css[] PROGMEM = {/*Put here your CSS code in string format*/};

/*---------------------------GET YOUR PUBLIC IP------------------------*/

String publicIp()
{
  WiFiClient client;
  if (client.connect("api.ipify.org", 80)) //connect to ipify.org
  {
    client.println("GET / HTTP/1.0");
    client.println("Host: api.ipify.org");
    client.println();
  } else {
    Serial.println("Failed connection");
    return String();
  }
  delay(5000);
  String line;
  while (client.available())
  {
    line = client.readStringUntil('\n'); //Read your public ip
  }
  return line;
}

/*---------------------RETURNS ERROR 402 IF QUERY NOT FOUND------------------*/

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}

/*---------------------SETUP------------------*/

void setup() {
  Serial.begin(115200);

  // Initialize the output variables as outputs
  pinMode(ledout, OUTPUT);
  digitalWrite(ledout, LOW);

  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    digitalWrite(ledout, HIGH); //Led 2 blinks while connecting
    delay(250);
    Serial.println("Connecting...");
    digitalWrite(ledout, LOW);
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println();

  //Show your local ip
  Serial.println("Local IP");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Call the function to show your public ip
  Serial.println("Public IP");
  Serial.println(publicIp());

  //When the server is ready the led 2 lights up
  digitalWrite(ledout, HIGH);

  //Sends a response when this request is made
  //---------V-------
  server.on("/", [](AsyncWebServerRequest * request)
  {
    request->send(200, "text/html", index_html);
  });

  //Sends a response when this request is made
  //---------VVVVVVVVVVV-------
  server.on("/master.css", [](AsyncWebServerRequest * request) //Change master.css to the name of your stylesheet
  {
    request->send(200, "text/css", master_css);
  });

  //Call the error function if the application is not found
  server.onNotFound(notFound);

  //Starts the server
  server.begin();
}

/*----------------------------LOOP--------------------------*/

void loop() {
}
