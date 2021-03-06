# Nerf Gadget
## Bullet speed measurment and remaining rounds indicator.


###Please note, consider using the far cheaper and superior <span style="color:red">[Nerf Gadget 2](https://github.com/paulhayes/nerf_gadget_2)</span>

Measure your nerf gun's bullet speed, and keep a track of how many rounds you've got left with this simple Arduino sketch, created for Arduino Nano ( for mounting on the side of your nerf gun ). Ideal for automatic and semi-automatic nerf guns.

### Components

You'll need:

1. Arduino Nano or similar 
2. 2x Max7129 and LED seven segment display. You can build this yourself, or buy this premade, here's the supplier I used: 
  http://www.kibuck.com/2-digit-spi-module.html?___store=en
3. IR LED Emitter and IR Photodiode. Probably a good idea to buy this as a pair. I used these ( ir53l & bpw41n ) [http://r.ebay.com/zvAGXm](http://r.ebay.com/zvAGXm)
4. 3x push buttons ( I was extremely lazy and bought this debounced 6 button module, but it's complete overkill: http://r.ebay.com/gYIwUL )

### Circuit Diagram
Todo

### Libraries

Download the LedControl.zip from http://playground.arduino.cc/Main/LedControl. And install by extracting the directory from the archive and then in the Arduino IDE Select Sketch->Import Library->Add Library.

### Usage

The default mode is to display the remaining rounds in your gun. To set the current number of rounds, press the reset button ( connected to digital pin 4 ) and it will cycle between the standard nerf magazine sizes. To remove a round manually hit the action button ( digital pin 3 ). 

To switch to bullet speedometer, hit the mode button ( connected to digital pin 2 ), and fire away! Nerf bullet speed is measured in meters per second. For instance the gun I've been testing on fires between 16 and 17 m/s.

### TODO

* Power save mode

### Donate

To encourage me to make more things like this.

[![Flattr this git repo](http://api.flattr.com/button/button-static-50x60.png)](https://flattr.com/submit/auto?user_id=paul_hayes&url=https://github.com/paulhayes/nerf_gadget&title=nerf_gadget&language=&tags=github&category=software)

