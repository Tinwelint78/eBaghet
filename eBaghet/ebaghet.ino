/*
	eBaghet, Mauro Stefano Giani 2017 CC by-nc-sa,
	largely based on eChanter by Tim Malcolm 2010-2015 CC by-nc-sa.
*/
/*  Audio based on the Mozzi Synth libraries and examples
    Download and install from http://sensorium.github.com/Mozzi/
    Mozzi, Tim Barrass 2012, CC by-nc-sa.
*/

/*
    Circuit Diagrams ...

    Finger Sensor inputs (BGT)
      D2 -> LA	(LG)
      D3 -> B	(A)
      D4 -> C	(B)
      D5 -> D	(C)
      D6 -> E	(D)
      D7 -> F	(E)
      D8 -> HG	(HF#)
      D12-> HA	(HG)

	Audio Outputs
      D9 in standard mode
      D9 + D10 in HIFI mode

	use HA (HG) sensor while turning on to select GHB instead of Baghet
	use HG (HF#) sensor to turn on drone sounds (standard)
	use F (E) sensor in combination with HG to tone low drone to A (Baghet only)
	use E (D) sensor in combinaton with HG to tone low drone to C (Baghet only)

*/

#include <MozziGuts.h>
#include <Sample.h> // Sample template

#include "ebaghet_config.h"
#include "ghb.h"
#include "baghet.h"

#define CONTROL_RATE 256 //512 // 64 // powers of 2 please

Sample <INST_NUM_CELLS_GHB, AUDIO_RATE>instrumentGHB(INST_DATA_GHB);
Sample <DRONE_NUM_CELLS, AUDIO_RATE>drone(DRONE_DATA);
Sample <INST_NUM_CELLS_BGT, AUDIO_RATE>instrumentBGT(INST_DATA_BGT);
Sample <DRONE_MIN_NUM_CELLS_BGT, AUDIO_RATE>droneminBGT(DRONE_MIN_DATA_BGT);
Sample <DRONE_MAJ_NUM_CELLS_BGT, AUDIO_RATE>dronemajBGT(DRONE_MAJ_DATA_BGT);

int curr_sensor = 0;

byte fmap = 0;  //D2-D7 (bits 2,3,4,5,6,7)
int i, j, k = 0; //general counters
int note_detected = 0;
int note_playing = 0;
int instrument = BGT;

#define DRONE_OFF		0
#define DRONE_STANDARD	1
#define DRONE_A			2
#define DRONE_C			3
byte usedrones = 0;

void setup() {

#if CAPTOUCH
#else
  pinMode(2, INPUT); pinMode(3, INPUT); pinMode(4, INPUT); pinMode(5, INPUT);
  pinMode(6, INPUT); pinMode(7, INPUT); pinMode(8, INPUT); pinMode(12, INPUT);
#endif

  instrument = BGT;
  usedrones = DRONE_OFF;

#if CAPTOUCH // compiler didn't like narrower defs so we have code repetition :(
  if (readCapacitivePin(sensor_pins[0]) >= CAPTOUCH_TRIGGER) { /* HA (HG) sensor touched */
    instrument = GHB;

  }
#else
  if (digitalRead(sensor_pins[0]) == LOW) {  /* HA (HG) sensor touched */
    instrument = GHB;
  }
#endif

#if CAPTOUCH // compiler didn't like narrower defs so we have code repetition :(
  if (readCapacitivePin(sensor_pins[1]) >= CAPTOUCH_TRIGGER) { /* HG (HF#) sensor touched */
    if (readCapacitivePin(sensor_pins[2]) >= CAPTOUCH_TRIGGER) { /* F (E) sensor touched */
      usedrones = DRONE_A;
    } else if (readCapacitivePin(sensor_pins[3]) >= CAPTOUCH_TRIGGER) { /* E (D) sensor touched */
      usedrones = DRONE_C;
    } else {
      usedrones = DRONE_STANDARD;
    }
  }
#else
  if (digitalRead(sensor_pins[1]) == LOW) {  /* HG (HF#) sensor touched */
    if (digitalRead(sensor_pins[2]) == LOW) { /* F (E) sensor touched */
      usedrones = DRONE_A;
    } else if (digitalRead(sensor_pins[3]) == LOW) { /* E (D) sensor touched */
      usedrones = DRONE_C;
    } else {
      usedrones = DRONE_STANDARD;
    }
  }
#endif
  if (instrument == GHB) {
    set_freqs(INST_SAMPLERATE / INST_NUM_CELLS_GHB);
  } else if (instrument == BGT) {
    set_freqs(INST_SAMPLERATE / INST_NUM_CELLS_BGT);
  }

  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)

  if (instrument == GHB) {
    instrumentGHB.setLoopingOn();
    instrumentGHB.setFreq(note_freqs_GHB[0]); // set the frequency
    if (usedrones != DRONE_OFF) {
      drone.setLoopingOn();
      drone.setFreq((float)INST_SAMPLERATE / DRONE_NUM_CELLS); // set the frequency
    }
  } else if (instrument == BGT) {
    instrumentBGT.setLoopingOn();
    instrumentBGT.setFreq(note_freqs_BGT[0]); // set the frequency
    if (usedrones == DRONE_STANDARD) {
      droneminBGT.setLoopingOn();
      droneminBGT.setFreq((float)INST_SAMPLERATE / DRONE_MIN_NUM_CELLS_BGT); // set the frequency
      dronemajBGT.setLoopingOn();
      dronemajBGT.setFreq((float)INST_SAMPLERATE / DRONE_MAJ_NUM_CELLS_BGT); // set the frequency
    } else if (usedrones == DRONE_A) {
      dronemajBGT.setLoopingOn();
      dronemajBGT.setFreq((float)INST_SAMPLERATE / DRONE_MAJ_NUM_CELLS_BGT * 1.125f); // set the frequency to A (9/8 G)
    } else if (usedrones == DRONE_C) {
      dronemajBGT.setLoopingOn();
      dronemajBGT.setFreq((float)INST_SAMPLERATE / DRONE_MAJ_NUM_CELLS_BGT * 1.35f); // set the frequency to C (9/8 * 6/5 G)
    }
  }

}

void set_freqs(float f) {

  if (instrument == BGT) {
    // setup freq. table
    for (i = 0; i < table_len_BGT; i++) {
      note_freqs_BGT[i] = (f * note_ratios_BGT[i][0]) / note_ratios_BGT[i][1];
    }
  } else if (instrument == GHB) {
    // setup freq. table
    for (i = 0; i < table_len_GHB; i++) {
      note_freqs_GHB[i] = (f * note_ratios_GHB[i][0]) / note_ratios_GHB[i][1];
    }
  }


}


void updateControl() {

  byte fb = 0;

  int sensor_val = 0;
  // put changing controls in here

  /* Read the relevant pin registers and construct a single byte 'map'   */
  /* of the pin states. Touched pins will be HIGH, untouched pins LOW    */


#if CAPTOUCH
  // set map
  if (readCapacitivePin(sensor_pins[curr_sensor]) >= CAPTOUCH_TRIGGER) {
    // make bit to be 1
    fmap |= (1 << (7 - curr_sensor));
  }
  curr_sensor++;

  //increment, return until all sensors are sampled, then toggle bitmap, reset counter and continue
  if (curr_sensor % num_sensors == 0) {
    //fmap = ~fmap; // toggle bitmap because bushbutton code is LOW when touched.
    curr_sensor = 0; // rset counter
  } else {
    return;
  }


#else // pushbuttonetc, finger sensors

  fmap = PIND >> 2;  // get rid of lowest 2 bytes,  fill top 2 bytes


  fb = PINB; // D8, D11 (bits 0, 3)

  if (fb & B00000001) { // true only if bit ZERO is 1
    // make  bit 6 in fmap to be 1
    fmap |= (1 << 6);
  } else {
    // untouched make bit 6 to be 0
    fmap &= ~(1 << 6);
  }

  if (fb & B00010000) { // true only if bit 3 is 1
    // make  bit 7 in fmap to be 1
    fmap |= (1 << 7);
  } else {
    // untouched make bit 7 to be 0
    fmap &= ~(1 << 7);
  }

#endif

  note_detected = -1;

  if (instrument == BGT) {
    for (i = 0; i < table_len_BGT; i++) {
      if ((fmap ^ finger_table_BGT[i]) == 0) {
        note_detected = i;
      }
    }
    // gracenotes
    if (note_detected == -1) {
      if (((fmap >> 7) & 1 ) == 0) {
        note_detected = 0;
      }
      else if (((fmap >> 6) & 1 ) == 0) {
        if (((fmap >> 5) & 1 ) == 0) {
          note_detected = 1;
        } else {
          note_detected = 2;
        }
      }
      else if (((fmap >> 5) & 1 ) == 0) {
        if (((fmap >> 4) & 1 ) == 0) {
          note_detected = 3;
        } else {
          note_detected = 4;
        }
      }
      else if (((fmap >> 4) & 1 ) == 0) {
        if (((fmap >> 3) & 1 ) == 0) {
          note_detected = 5;
        } else {
          note_detected = 6;
        }
      }
      else if (((fmap >> 3) & 1 ) == 0) {
        note_detected = 7;
      }
      else if (((fmap >> 2) & 1 ) == 0) {
        if (((fmap >> 1) & 1 ) == 0) {
          note_detected = 8;
        } else {
          note_detected = 9;
        }
      }
      else if (((fmap >> 1) & 1 ) == 0) {
        if (((fmap >> 0) & 1 ) == 0) {
          note_detected = 10;
        } else {
          note_detected = 11;
        }
      }
      else if (((fmap >> 0) & 1 ) == 0) {
        note_detected = 12;
      }
      else {
        note_detected = 13;
      }
    }
  } else if (instrument == GHB) {
    for (i = 0; i < table_len_GHB; i++) {
      if ((fmap ^ finger_table_GHB[i]) == 0) {
        note_detected = i;
      }
    }
    // gracenotes
    if (note_detected == -1) {
      if (((fmap >> 7) & 1 ) == 0) {
        note_detected = 0;
      }
      else if (((fmap >> 6) & 1 ) == 0) {
        note_detected = 1;
      }
      else if (((fmap >> 5) & 1 ) == 0) {
        note_detected = 2;
      }
      else if (((fmap >> 4) & 1 ) == 0) {
        note_detected = 3;
      }
      else if (((fmap >> 3) & 1 ) == 0) {
        note_detected = 4;
      }
      else if (((fmap >> 2) & 1 ) == 0) {
        note_detected = 5;
      }
      else if (((fmap >> 1) & 1 ) == 0) {
        note_detected = 6;
      }
      else if (((fmap >> 0) & 1 ) == 0) {
        note_detected = 7;
      }
      else {
        /* LG or no note? */ note_detected = 8;
      }
    }
  }



  if (note_detected != note_playing) {
    note_playing = note_detected;
    if (instrument == GHB) {
      instrumentGHB.setFreq(note_freqs_GHB[note_playing]);
    } else if (instrument == BGT) {
      instrumentBGT.setFreq(note_freqs_BGT[note_playing]);
    }

  }

  // reset fingermap
  fmap = 0;

}


int updateAudio() {

#if (AUDIO_MODE == HIFI)
  if (instrument == GHB) {
    if (usedrones != DRONE_OFF) {
      return ((int16_t)instrumentGHB.next() + (int16_t)drone.next()) << 6;
    } else {
      return ((int16_t)instrumentGHB.next()) << 6;
    }
  } else if (instrument == BGT) {
    if (usedrones == DRONE_OFF) {
      return ( (int16_t)instrumentBGT.next()) << 6;
    } else if (usedrones == DRONE_STANDARD) {
      return ( (int16_t)instrumentBGT.next() + (int16_t)droneminBGT.next() + (int16_t)dronemajBGT.next()) << 4;
    } else {
      return ( (int16_t)instrumentBGT.next() + (int16_t)dronemajBGT.next()) << 5;
    }
  }
#else
  if (instrument == GHB) {
    if (usedrones != DRONE_OFF) {
      return ((int16_t)instrumentGHB.next() + (int16_t)drone.next())
    } else {
      return ((int16_t)instrumentGHB.next());
    }
  } else if (instrument == BGT) {
    if (usedrones == DRONE_OFF) {
      return ( (int16_t)instrumentBGT.next());
    } else if (usedrones == DRONE_STANDARD) {
      return ( (int16_t)instrumentBGT.next() + (int16_t)droneminBGT.next() + (int16_t)dronemajBGT.next());
    } else {
      return ( (int16_t)instrumentBGT.next() + (int16_t)dronemajBGT.next());
    }
  }
#endif


}


void loop() {
  audioHook(); // required here


}

#if CAPTOUCH

// captouch code from eChanter, unrolled to be faster and more reliable, courtesy of
//  Danial Martinez, GPL v2
//  https://github.com/danielmartinez/eClarin
//
uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  // delay(1);
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin to get pulled up. This manual unrolling of the loop
  // decreases the number of hardware cycles between each read of the pin,
  // thus increasing sensitivity.
  uint8_t cycles = 17;
  if (*pin & bitmask) {
    cycles =  0;
  }
  else if (*pin & bitmask) {
    cycles =  1;
  }
  else if (*pin & bitmask) {
    cycles =  2;
  }
  else if (*pin & bitmask) {
    cycles =  3;
  }
  else if (*pin & bitmask) {
    cycles =  4;
  }
  else if (*pin & bitmask) {
    cycles =  5;
  }
  else if (*pin & bitmask) {
    cycles =  6;
  }
  else if (*pin & bitmask) {
    cycles =  7;
  }
  else if (*pin & bitmask) {
    cycles =  8;
  }
  else if (*pin & bitmask) {
    cycles =  9;
  }
  else if (*pin & bitmask) {
    cycles = 10;
  }
  else if (*pin & bitmask) {
    cycles = 11;
  }
  else if (*pin & bitmask) {
    cycles = 12;
  }
  else if (*pin & bitmask) {
    cycles = 13;
  }
  else if (*pin & bitmask) {
    cycles = 14;
  }
  else if (*pin & bitmask) {
    cycles = 15;
  }
  else if (*pin & bitmask) {
    cycles = 16;
  }

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}

#endif

