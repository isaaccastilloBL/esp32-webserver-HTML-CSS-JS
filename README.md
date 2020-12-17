# esp32 web server
This program makes your ESP32 a web server capable of hosting and running html and css pages (js in development).

## Features
- Host html code
- Connect to your own local network
- You can access it through a public ip

## Install
- Clone the repository and open the .ino file
- Installing ESP cards from the card manager
- Install the dependent libraries

## Use
- Replace your network credentials with your own
- Replace lines 32 and 33 with your page code. I recommend using [this](http://tomeko.net/online_tools/cpp_text_escape.php)
- Connect your esp32 and upload the code

## Dependences
* [ESPAsyncWebServer library](https://github.com/me-no-dev/ESPAsyncWebServer)
* [AsyncTCP library](https://github.com/me-no-dev/AsyncTCP)
* [ESP32 for Arduino IDE](https://github.com/espressif/arduino-esp32) (you can install it from the card manager)

## Contributing
Bug reports and pull requests are welcome on our GitHub.