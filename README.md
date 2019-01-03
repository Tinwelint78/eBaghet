# eBaghet

Open source electronic Baghet (Italian bagpipes) project for Arduino.

Largely based on eChanter by Tim Malcolm 2010-2015 CC by-nc-sa. ([echanter site](http://www.echanter.com/), [sourceforge repository](https://sourceforge.net/projects/echanter/))

Audio based on the Mozzi Synth libraries and examples
Mozzi, Tim Barrass 2012, CC by-nc-sa.

Sound for the Baghet is provided by [Valter Biella](http://www.baghet.it/)

## Build instruction:
For now, follow the excellent guide at [echanter site](http://www.echanter.com/home/howto-build).

## To program the Arduino:
Download and install the [Arduino IDE](https://www.arduino.cc/en/main/software) (tested on version 1.8.3)

Download and install my forked version of the Mozzi library from [this site](https://github.com/Tinwelint78/Mozzi)

## Additional step for STM32F1 (Blue Pill)

The eBaghet source is compatible with Blue Pill (STM32F1), and can benefit from high resolution sound samples in this platform.

To install and make STM32F1 work, follow the tutorial by [Luca Dentella](http://www.lucadentella.it/en/2017/07/13/stm32-e-arduino/).

Then download the Arduino_STM32 repository from [Roger Clark Melbourne site](https://github.com/rogerclarkmelbourne/Arduino_STM32), unzip somewhere, rename the Arduino_STM32-master folder to Arduino_STM32 and move it to C:/Program Files (x86)/Arduino/hardware.

## Configuration

Open the Mozzi config file [Arduino dir]/libraries/Mozzi/mozzi_config.h
If you're using HIFI mode, find the line that says AUDIO_MODE and make sure the section of code looks like this:

          //#define AUDIO_MODE STANDARD
          //#define AUDIO_MODE STANDARD_PLUS
          #define AUDIO_MODE HIFI

Scroll down to AUDIO_RATE and make sure the section of code looks like this

          //#define AUDIO_RATE 16384
          #define AUDIO_RATE 32768
		  
If you don't want to use HIFI mode, you can activate stereo hack, to have drone sound on a channel and the chanter on another one, like this:

		  #define STEREO_HACK true
		
Save mozzi_config.h

Start the Arduino IDE
Open the eBaghet sketch from wherever it was unzipped (eBaghet.ino is the main sketch)

At this point there are a few things that can be changed in the config file. To edit the file click on the 'eBaghet_config' file tab in the Arduino IDE.

You can define order with which instruments are presented:

	  #define STARTING_INSTRUMENT	GHB
	  #define FIRST_INSTRUMENT	BGT
	  #define SECOND_INSTRUMENT	BRD
	  #define THIRD_INSTRUMENT	SML
	  #define FOURTH_INSTRUMENT	UIL

GHB is Great Highland Bagpipes, BGT is Baghet, BRD is border pipes, SML is small pipes, UIL is Uillean pipes (sound only, fingering is like GHB).

You can define if by default the chanter starts with a drone sound:
	
	  #define STARTING_DRONES	DRONE_ON
	
or not, modifying the line above to:

	  #define STARTING_DRONES	DRONE_OFF

and you can chose the starting intonation of the drones for the Baghet:

	  #define STARTING_DRONE_INT	DRONE_INT_STANDARD

If you leave DRONE_INT_STANDARD, the Baget starts with a G drone. If you substitute with DRONE_INT_A, it starts with an A drone, and if you substitute with DRONE_INT_C, it starts with a C drone.

Then you can chose which style of sensors you are using for the fingering:

	  #define TOUCHMODE TOUCH_CAP
With TOUCH_CAP, you use captouch sensor, with TOUCH_SWITCH standard pushbuttons and with TOUCH_MP121 the MP121 breakout board by [Adafruit](https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/overview). 
NOTE: MP121 is not working with STM32 right now and I have tested just a little with Arduino Nano, so it is totally experimental.

If you did use captouch style sensors, then at some point you may want to change the 4 on this line

      #define CAPTOUCH_TRIGGER 4

to something a little higher or lower, depending on how the finger detection works for you. For me, 4 is a good trigger level, but 6 also works OK.

You can also decide relative volumes for drones and chanter for all instruments, modifying these lines:

	  #define GHB_CHANTER_VOLUME	8
	  #define GHB_DRONES_VOLUME		4
      
	  #define BGT_CHANTER_VOLUME	8
	  #define BGT_DRONES_VOLUME		4
      
	  #define BRD_CHANTER_VOLUME	8
	  #define BRD_DRONES_VOLUME		8
      
	  #define SML_CHANTER_VOLUME	8
	  #define SML_DRONES_VOLUME		8
      
	  #define UIL_CHANTER_VOLUME	8
	  #define UIL_DRONES_VOLUME		8

You can change the numbers to any value between 1 and 8 (1 is minimum volume, 8 is maximum volume).

Last thing you can change are the pins where the eight finger sensors are connected. There is one line for STM32 and one for other Arduino boards:

	  #if IS_STM32()
	  int sensor_pins[] = {PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0};
	  #else
	  int sensor_pins[] = { 12, 8, 7, 6, 5, 4, 3, 2 };
	  #endif
	  
They are ordered from high A (12 and PA7) to low A (2 and PA0). 
	  
## Programming

Connect the Arduino
Select the board type from the Tools menu (eg Arduino nano)
Select the processor type from the Tools menu (eg ATMega 328)
Select the Serial port from the Tools menu
Upload the sketch

## Options

The eBaghet has several working mode depending on which keys you close when you turn on the chanter power:
* If you don't close any key the chanter will start with the instrument defined by STARTING_INSTRUMENT (default Great Highland Bagpipes) and with drones or not depending on STARTING_DRONES definition (default drones on).
* If you close High A key, the chanter will start with the instrument defined by FIRST_INSTRUMENT (default Baghet) and with drones or not depending on STARTING_DRONES definition (default drones on) and with intonation defined by STARTING_DRONE_INT (default standard intonation, G drones).
* If you close High G key, the chanter will start with the instrument defined by SECOND_INSTRUMENT (default Border pipes) and with drones or not depending on STARTING_DRONES definition (default drones on).
* If you close F key, the chanter will start with the instrument defined by THIRD_INSTRUMENT (default Small pipes) and with drones or not depending on STARTING_DRONES definition (default drones on).
* If you close E key, the chanter will start with the instrument defined by FOURTH_INSTRUMENT (default Uillean pipes) and with drones or not depending on STARTING_DRONES definition (default drones on).
* If you close D key, the drones will be turned off or on depending on the reverse of what is defined by STARTING_DRONES (default drones off).
* If you close C key and the instrument is Baghet, the drones will change intonation to A. if DRONE_INT_A is defined as STARTING_DRONE_INT, the drones will return to normal G intonation.
* If you close B key and the instrument is Baghet, the drones will change intonation to C. if DRONE_INT_C is defined as STARTING_DRONE_INT, the drones will return to normal G intonation.

## Fingering

Great Highland Bagpipes, border pipes, small pipes and Uillean pipes follow this finger chart:

![GHB](docs/GHB.png)


For the Baghet, follow this finger chart (According to [Manuale del Baghet](http://www.baghet.it/manuale%20baghet%202012.pdf) by Valter Biella):

![Baghet](docs/Baghet.png)

Dashed keys can be closed or open as comfort of position needs.
