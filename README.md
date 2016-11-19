# Firebase ESP8266 Demo
This project shows you how to read MAX30100 heart beat sensor, and publish the data to Firebase Realtime Database.

I use this project for my talk's demo during Google Developer Group's Dev Fest - Semarang, Indonesia. Here's the [keynote file](http://www.slideshare.net/andri_yadi/gdg-dev-fest-develop-with-firebase-and-iot) 

Scenario:
![Scenario](https://raw.githubusercontent.com/andriyadi/Firebase_ESP8266_Demo/master/DemoScenario.jpg)


## Shopping List

* ESP8266 board, I use [ESPectro](http://makestro.com/espectro)
* MAX30100 module
* Firebase account. Register at http://firebase.google.com

## Dependencies

* Firebase Arduino: https://github.com/firebase/firebase-arduino
* Arduino MAX30100: https://github.com/oxullo/Arduino-MAX30100

If you're using [PlatformIO](http://platformio.org), life is easier. Just do `pio run -t upload`, it'll compile and upload the firmware to your board. 

If you're using Arduino IDE, download and install those libraries like usual.

## Setup & Run
Change these in `FirebaseDemo.cpp`:
```
#define FIREBASE_HOST "[FIREBASE_PROJECT_NAME].firebaseio.com"
#define FIREBASE_AUTH "[FIREBASE_PROJECT_KEY]"

#define WIFI_SSID       "[I_WONT_TELL_YOU]"
#define WIFI_PASSWORD   "[I_WONT_TELL_YOU_AS_WELL]"
```

Firebase Database secret/key is now legacy and deprecated, but you can still use it and it's buried under Project Settings. Here's how to get it: 
![Get Firebase Key](https://raw.githubusercontent.com/andriyadi/Firebase_ESP8266_Demo/master/HowToGetTheKey.gif)

###PlatformIO
Again, if you're using [PlatformIO](http://platformio.org), life is easier. Just do `pio run -t upload`, it'll compile and upload the firmware to your board. 

###Arduino IDE
Rename `FirebaseDemo.cpp` to `FirebaseDemo.ino`, and open the `ino` file. If you've installed dependency libraries, (hopefully) you can compile with success. Good luck.

For more hardware learning stuffs: [http://learn.makestro.com](http://learn.makestro.com)

That's it. Enjoy!
