# eBaghet
open source electronic baghet (italian bagpipe) project for Arduino

Largely based on eChanter by Tim Malcolm 2010-2015 CC by-nc-sa. (http://www.echanter.com/, https://sourceforge.net/projects/echanter/)

Audio based on the Mozzi Synth libraries and examples (http://sensorium.github.com/Mozzi/)
Mozzi, Tim Barrass 2012, CC by-nc-sa.

Sound for the Baghet is provided by Valter Biella http://www.baghet.it/

## Build instruction:
For now, follow the excellent guide at http://www.echanter.com/home/howto-build.

## To program the Arduino:
Download and install the Arduino IDE https://www.arduino.cc/en/main/software (tested on version 1.8.3)

Dowload and install the Mozzi library from http://sensorium.github.com/Mozzi/

Open the Mozzi config file [Arduino dir]/libraries/Mozzi/mozzi_config.h
If you're using HIFI mode, find the line that says AUDIO_MODE and make sure the section of code looks like this:

          //#define AUDIO_MODE STANDARD
          //#define AUDIO_MODE STANDARD_PLUS
          #define AUDIO_MODE HIFI

Scroll down to AUDIO_RATE and make sure the section of code looks like this

          //#define AUDIO_RATE 16384
          #define AUDIO_RATE 32768

Save mozzi_config.h


Start the Arduino IDE
Open the ebaghet sketch from wherever it was unziped (eBaghet.ino is the main sketch)

At this point there are a few things that can be changed in the config file. To edit the file click on the 'eBaghet_config' file tab in the Arduino IDE. If you did not use captouch style sensors change the line

      #define CAPTOUCH true

 to

      #define CAPTOUCH false

If you did use captouch style sensors, then at some point you may want to change the 6 on this line

    #define CAPTOUCH_TRIGGER 6

to something a little higher or lower, depending on how the finger detection works for you. For me, 6 is a good trigger level, but 8 also works OK.

Connect the Arduino
Select the board type from the Tools menu (eg Arduino nano)
Select the processor type from the Tools menu (eg ATMega 328)
Select the Serial port from the Tools menu
Upload the sketch

## Options

The eBaghet has several working mode depending on which keys you close when you turn on the chanter:
* If you don't close any key the chanter has baghet fingering and sound without drones.
* If you close High A key, the chanter has Highland Bagpipe fingering and sound without drones.
* If you close High G key, a standard intonation drone sound, both with Baghet and Highland Bagpipe.
* If you close F key in combination with high G, add to Baghet a drone toned to A, without minor drone. No effect on Highland Bagpipe.
* If you close E key in combination with high G, add to Baghet a drone toned to C, without minor drone. No effect on Highland Bagpipe. 
