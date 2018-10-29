# IFTTT button 
----

This is a button to control them all ;-)

It is a physical button attached to one ESP8266 GPIO pin (in the code D3 but you can just change it). D3 was selected because it has the capability to be used as interrupt pin (to keep the ESP8266 in light sleep mode most of the time when possible) and D3 is the wemos button shield pin. It has been currently tested with wemos but also with other "nodemcu" regular boards.

## Features
So, main features of this little code are the following.

   - Captivate portal to be able the "magic button" ease to deploy (nearly) anywhere:
     - it creates a Wi-Fi AP (similary to a page that you find in some hotel that you find to introduce connection name and password). You just need to select your router SSID from the SSID list showed and enter the router password. This is only made one and while deployed within router range not more chages will be required.
     - DISCLAIMER ;-) "anywhere" means that you need a router (or your phone hotspot,...) and Internet connection to make it works.
    - A physical button that can trigger any other physical or virtual event:
      - It use a button that when pressed triggers an IFTTT event using the fantastic IFTTT webhook channel. Just sign-up at IFTTT if you haven't do it yet ;-). It's awesome!!!
      - DISCLAIMER ;-) "any" means any third party service supported by IFTTT or any other service that you can also create using another webhook channel event.
    - Low battery power use
      - While not the lowest one (using deepSleep) it enters light sleep mode.

### Tech

The following libraries are required for the code in order to compile. Both of them can be esily installed from the arduino IDE Library Manager window.

* [https://github.com/tzapu/WiFiManager] - Incredible captive portal implementation
* [https://github.com/romkey/IFTTTWebhook] - really easy to use IFTTT event triggering library

And of course platform.io, arduino IDE or whatever editor+compilation chain you prefer.

### Todos
 - An easy way to update IFTTT SSL fingerprint would be welcome ([https://github.com/romkey/IFTTTWebhook/issues/5])
 - Or a certificate auto-updating feature covering ESP32 and ESP8266 cases
