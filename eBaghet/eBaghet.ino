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

*/

#include <MozziGuts.h>
#include "ebaghet_config.h"
#if USE_16BIT_SAMPLES
#include "Sample16.h" // Sample template
#else
#include <Sample.h> // Sample template
#endif
#include <Oscil.h>

#if GHB_IN_USE()
#include "ghb.h"
#endif
#if BGT_IN_USE()
#include "baghet.h"
#endif
#if BRD_IN_USE()
#include "border.h"
#endif
#if SML_IN_USE()
#include "smallpipe.h"
#endif
#if UIL_IN_USE()
#include "uilleann.h"
#endif
#if GAL_IN_USE()
#include "gallega.h"
#endif
#if AST_IN_USE()
#include "asturiana.h"
#endif

#if (TOUCHMODE == TOUCH_MPR121)
#if IS_STM32()
#include <SoftWire.h>
#include <Adafruit_MPR121_STM32.h>
#else
#include <Wire.h>
#include <Adafruit_MPR121.h>
#endif
#endif
#include <tables/sin512_int8.h>

#define CONTROL_RATE 256 //512 // 64 // powers of 2 please

#if USE_16BIT_SAMPLES
#if GHB_IN_USE()
Sample16 <INST_NUM_CELLS_GHB, AUDIO_RATE>instrumentGHB ( INST_DATA_GHB );
Sample16 <DRONE_NUM_CELLS_GHB, AUDIO_RATE>droneGHB ( DRONE_DATA_GHB );
#endif
#if BGT_IN_USE()
Sample16 <INST_NUM_CELLS_BGT, AUDIO_RATE>instrumentBGT ( INST_DATA_BGT );
//Sample16 <DRONE_MAJ_NUM_CELLS_BGT, AUDIO_RATE>droneminBGT ( DRONE_MAJ_DATA_BGT );
Sample16 <DRONE_MAJ_NUM_CELLS_BGT, AUDIO_RATE>dronemajBGT ( DRONE_MAJ_DATA_BGT );
Sample16 <DRONE_ALL_NUM_CELLS_BGT, AUDIO_RATE>droneBGT ( DRONE_ALL_DATA_BGT );
#endif
#if BRD_IN_USE()
Sample16 <INST_NUM_CELLS_BRD, AUDIO_RATE>instrumentBRD ( INST_DATA_BRD );
Sample16 <DRONE_NUM_CELLS_BRD, AUDIO_RATE>droneBRD ( DRONE_DATA_BRD );
#endif
#if SML_IN_USE()
Sample16 <INST_NUM_CELLS_SML, AUDIO_RATE>instrumentSML ( INST_DATA_SML );
Sample16 <DRONE_NUM_CELLS_SML, AUDIO_RATE>droneSML ( DRONE_DATA_SML );
#endif
#if UIL_IN_USE()
Sample16 <INST_NUM_CELLS_UIL, AUDIO_RATE>instrumentUIL ( INST_DATA_UIL );
Sample16 <DRONE_NUM_CELLS_UIL, AUDIO_RATE>droneUIL ( DRONE_DATA_UIL );
#endif
#if GAL_IN_USE()
Sample16 <INST_NUM_CELLS_GAL, AUDIO_RATE>instrumentGAL ( INST_DATA_GAL );
Sample16 <DRONE_NUM_CELLS_GAL, AUDIO_RATE>droneGAL ( DRONE_DATA_GAL );
#endif
#if AST_IN_USE()
Sample16 <INST_NUM_CELLS_AST, AUDIO_RATE>instrumentAST ( INST_DATA_AST );
Sample16 <DRONE_NUM_CELLS_AST, AUDIO_RATE>droneAST ( DRONE_DATA_AST );
#endif
#else
#if GHB_IN_USE()
Sample <INST_NUM_CELLS_GHB, AUDIO_RATE>instrumentGHB ( INST_DATA_GHB );
Sample <DRONE_NUM_CELLS_GHB, AUDIO_RATE>droneGHB ( DRONE_DATA_GHB );
//Oscil <512, AUDIO_RATE>droneGHB ( SIN512_DATA );
#endif
#if BGT_IN_USE()
Sample <INST_NUM_CELLS_BGT, AUDIO_RATE>instrumentBGT ( INST_DATA_BGT );
//Sample <DRONE_MIN_NUM_CELLS_BGT, AUDIO_RATE>droneminBGT ( DRONE_MIN_DATA_BGT );
Sample <DRONE_MAJ_NUM_CELLS_BGT, AUDIO_RATE>dronemajBGT ( DRONE_MAJ_DATA_BGT );
Sample <DRONE_ALL_NUM_CELLS_BGT, AUDIO_RATE>droneBGT ( DRONE_ALL_DATA_BGT );
#endif
#if BRD_IN_USE()
Sample <INST_NUM_CELLS_BRD, AUDIO_RATE>instrumentBRD ( INST_DATA_BRD );
Sample <DRONE_NUM_CELLS_BRD, AUDIO_RATE>droneBRD ( DRONE_DATA_BRD );
#endif
#if SML_IN_USE()
Sample <INST_NUM_CELLS_SML, AUDIO_RATE>instrumentSML ( INST_DATA_SML );
Sample <DRONE_NUM_CELLS_SML, AUDIO_RATE>droneSML ( DRONE_DATA_SML );
#endif
#if UIL_IN_USE()
Sample <INST_NUM_CELLS_UIL, AUDIO_RATE>instrumentUIL ( INST_DATA_UIL );
Sample <DRONE_NUM_CELLS_UIL, AUDIO_RATE>droneUIL ( DRONE_DATA_UIL );
#endif
#if GAL_IN_USE()
Sample <INST_NUM_CELLS_GAL, AUDIO_RATE>instrumentGAL ( INST_DATA_GAL );
Sample <DRONE_NUM_CELLS_GAL, AUDIO_RATE>droneGAL ( DRONE_DATA_GAL );
#endif
#if AST_IN_USE()
Sample <INST_NUM_CELLS_AST, AUDIO_RATE>instrumentAST ( INST_DATA_AST );
Sample <DRONE_NUM_CELLS_AST, AUDIO_RATE>droneAST ( DRONE_DATA_AST );
#endif
#endif

int curr_sensor = 0;

byte fmap = 0;
int i, j, k = 0; //general counters
int note_detected = 0;
int note_playing = 0;
int instrument = STARTING_INSTRUMENT;
byte usedrones = STARTING_DRONES;
byte droneintonation = STARTING_DRONE_INT;

byte startchanter = 0;

#if (TOUCHMODE == TOUCH_MPR121)
#if IS_STM32()
Adafruit_MPR121_STM32 cap = Adafruit_MPR121_STM32();
#else
Adafruit_MPR121 cap = Adafruit_MPR121();
#endif
#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif
#endif

// prototypes definition (to correct a VisualMicro bug)
void set_freqs ( void );
#if (TOUCHMODE == TOUCH_CAP)
uint8_t readCapacitivePin ( int pinToMeasure );
#endif

void setup()
{
#if (TOUCHMODE == TOUCH_SWITCH)
	pinMode ( sensor_pins[0], INPUT );
	pinMode ( sensor_pins[1], INPUT );
	pinMode ( sensor_pins[2], INPUT );
	pinMode ( sensor_pins[3], INPUT );
	pinMode ( sensor_pins[4], INPUT );
	pinMode ( sensor_pins[5], INPUT );
	pinMode ( sensor_pins[6], INPUT );
	pinMode ( sensor_pins[7], INPUT );
#elif (TOUCHMODE == TOUCH_MPR121)
	cap.begin ( MPR121_ADDRESS );
	delay ( 1000 );
#endif
#if (TOUCHMODE == TOUCH_CAP)
#if defined(FIRST_INSTRUMENT)

	if ( readCapacitivePin ( sensor_pins[0] ) >= CAPTOUCH_TRIGGER )
	{
		instrument = FIRST_INSTRUMENT;
	}

#if defined(SECOND_INSTRUMENT)
	else if ( readCapacitivePin ( sensor_pins[1] ) >= CAPTOUCH_TRIGGER )
	{
		instrument = SECOND_INSTRUMENT;
	}

#if defined (THIRD_INSTRUMENT)
	else if ( readCapacitivePin ( sensor_pins[2] ) >= CAPTOUCH_TRIGGER )
	{
		instrument = THIRD_INSTRUMENT;
	}

#if defined (FOURTH_INSTRUMENT)
	else if ( readCapacitivePin ( sensor_pins[3] ) >= CAPTOUCH_TRIGGER )
	{
		instrument = FOURTH_INSTRUMENT;
	}

#endif	//defined (FOURTH_INSTRUMENT)
#endif	//defined (THIRD_INSTRUMENT)
#endif	//defined(SECOND_INSTRUMENT)
#endif	//defined(FIRST_INSTRUMENT)

	if ( readCapacitivePin ( sensor_pins[4] ) >= CAPTOUCH_TRIGGER )
	{
		if ( usedrones == DRONE_OFF )
		{
			usedrones = DRONE_ON;
		}
		else
		{
			usedrones = DRONE_OFF;
		}
	}

	if ( instrument == BGT && usedrones == DRONE_ON )
	{
		if ( readCapacitivePin ( sensor_pins[5] ) >= CAPTOUCH_TRIGGER )
		{
			if ( droneintonation == DRONE_INT_A )
			{
				droneintonation = DRONE_INT_STANDARD;
			}
			else
			{
				droneintonation = DRONE_INT_A;
			}
		}
		else if ( readCapacitivePin ( sensor_pins[6] ) >= CAPTOUCH_TRIGGER )
		{
			if ( droneintonation == DRONE_INT_C )
			{
				droneintonation = DRONE_INT_STANDARD;
			}
			else
			{
				droneintonation = DRONE_INT_C;
			}
		}
	}

#elif (TOUCHMODE == TOUCH_MPR121)
#if defined(FIRST_INSTRUMENT)

	// use filtered data: the MPR121 take initial value as base value (not true if something is touched when the system starts)
	// TODO: verify if 128 is good in every conditions
	if ( cap.filteredData ( 7 ) < 128 )
	{
		instrument = FIRST_INSTRUMENT;
	}

#if defined(SECOND_INSTRUMENT)
	else if ( cap.filteredData ( 6 ) < 128 )
	{
		instrument = SECOND_INSTRUMENT;
	}

#if defined (THIRD_INSTRUMENT)
	else if ( cap.filteredData ( 5 ) < 128 )
	{
		instrument = THIRD_INSTRUMENT;
	}

#if defined (FOURTH_INSTRUMENT)
	else if ( cap.filteredData ( 4 ) < 128 )
	{
		instrument = FOURTH_INSTRUMENT;
	}

#endif	//defined (FOURTH_INSTRUMENT)
#endif	//defined (THIRD_INSTRUMENT)
#endif	//defined(SECOND_INSTRUMENT)
#endif	//defined(FIRST_INSTRUMENT)

	if ( cap.filteredData ( 3 ) < 128 )
	{
		if ( usedrones == DRONE_OFF )
		{
			usedrones = DRONE_ON;
		}
		else
		{
			usedrones = DRONE_OFF;
		}
	}

	if ( instrument == BGT && usedrones == DRONE_ON )
	{
		if ( cap.filteredData ( 2 ) < 128 )
		{
			if ( droneintonation == DRONE_INT_A )
			{
				droneintonation = DRONE_INT_STANDARD;
			}
			else
			{
				droneintonation = DRONE_INT_A;
			}
		}
		else if ( cap.filteredData ( 1 ) < 128 )
		{
			if ( droneintonation == DRONE_INT_C )
			{
				droneintonation = DRONE_INT_STANDARD;
			}
			else
			{
				droneintonation = DRONE_INT_C;
			}
		}
	}

#else
#if defined(FIRST_INSTRUMENT)

	if ( digitalRead ( sensor_pins[0] ) == LOW )
	{
		instrument = FIRST_INSTRUMENT;
	}

#if defined(SECOND_INSTRUMENT)
	else if ( digitalRead ( sensor_pins[1] ) == LOW )
	{
		instrument = SECOND_INSTRUMENT;
	}

#if defined (THIRD_INSTRUMENT)
	else if ( digitalRead ( sensor_pins[2] ) == LOW )
	{
		instrument = THIRD_INSTRUMENT;
	}

#if defined (FOURTH_INSTRUMENT)
	else if ( digitalRead ( sensor_pins[3] ) == LOW )
	{
		instrument = FOURTH_INSTRUMENT;
	}

#endif	//defined (FOURTH_INSTRUMENT)
#endif	//defined (THIRD_INSTRUMENT)
#endif	//defined(SECOND_INSTRUMENT)
#endif	//defined(FIRST_INSTRUMENT)

	if ( digitalRead ( sensor_pins[4] ) == LOW )
	{
		if ( usedrones == DRONE_OFF )
		{
			usedrones = DRONE_ON;
		}
		else
		{
			usedrones = DRONE_OFF;
		}
	}

	if ( instrument == BGT && usedrones == DRONE_ON )
	{
		if ( digitalRead ( sensor_pins[5] ) == LOW )
		{
			if ( droneintonation == DRONE_INT_A )
			{
				droneintonation = DRONE_INT_STANDARD;
			}
			else
			{
				droneintonation = DRONE_INT_A;
			}
		}
		else if ( digitalRead ( sensor_pins[6] ) == LOW )
		{
			if ( droneintonation == DRONE_INT_C )
			{
				droneintonation = DRONE_INT_STANDARD;
			}
			else
			{
				droneintonation = DRONE_INT_C;
			}
		}
	}

#endif
#if START_CHANTER_AFTERWARDS
	startchanter = 0;
#else
	startchanter = 1;
#endif
	// init frequency tables for all instruments
	set_freqs ( );
	startMozzi ( CONTROL_RATE ); // set a control rate of 64 (powers of 2 please)

	if ( instrument == GHB )
	{
#if GHB_IN_USE()
		instrumentGHB.setLoopingOn();
		//instrumentGHB.setStart ( note_starts_GHB[0] );
		//instrumentGHB.setEnd ( note_stops_GHB[0] );
		instrumentGHB.start();
		//instrumentGHB.setFreq ( ( float ) INST_SAMPLERATE_GHB / ( float ) INST_NUM_CELLS_GHB );
		instrumentGHB.setFreq ( note_freqs_GHB[0] ); // set the frequency

		if ( usedrones != DRONE_OFF )
		{
			droneGHB.setFreq ( ( float ) INST_SAMPLERATE_GHB / DRONE_NUM_CELLS_GHB * 0.99736842105263f ); // set the frequency
			//droneGHB.setFreq ( ( float ) INST_SAMPLERATE_GHB / DRONE_NUM_CELLS_GHB ); // set the frequency
			//droneGHB.setFreq ( 440.0f ); // set the frequency
			droneGHB.setLoopingOn();
		}

#endif
	}
	else if ( instrument == BGT )
	{
#if BGT_IN_USE()
		instrumentBGT.setLoopingOn();
		instrumentBGT.setFreq ( note_freqs_BGT[0] ); // set the frequency

		if ( usedrones != DRONE_OFF )
		{
			if ( droneintonation == DRONE_INT_STANDARD )
			{
				droneBGT.setLoopingOn();
				droneBGT.setFreq ( ( float ) INST_SAMPLERATE_BGT / DRONE_ALL_NUM_CELLS_BGT ); // set the frequency
			}
			else if ( usedrones == DRONE_INT_A )
			{
				dronemajBGT.setLoopingOn();
				dronemajBGT.setFreq ( ( float ) INST_SAMPLERATE_BGT / DRONE_MAJ_NUM_CELLS_BGT * 1.125f ); // set the frequency to A (9/8 G)
			}
			else if ( usedrones == DRONE_INT_C )
			{
				dronemajBGT.setLoopingOn();
				dronemajBGT.setFreq ( ( float ) INST_SAMPLERATE_BGT / DRONE_MAJ_NUM_CELLS_BGT * 1.35f ); // set the frequency to C (9/8 * 6/5 G)
			}
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()
		instrumentBRD.setLoopingOn();
		instrumentBRD.setFreq ( note_freqs_BRD[0] ); // set the frequency

		if ( usedrones != DRONE_OFF )
		{
			droneBRD.setLoopingOn();
			droneBRD.setFreq ( ( float ) INST_SAMPLERATE_BRD / DRONE_NUM_CELLS_BRD ); // set the frequency
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()
		instrumentSML.setLoopingOn();
		instrumentSML.setFreq ( note_freqs_SML[0] ); // set the frequency

		if ( usedrones != DRONE_OFF )
		{
			droneSML.setLoopingOn();
			droneSML.setFreq ( ( float ) INST_SAMPLERATE_SML / DRONE_NUM_CELLS_SML ); // set the frequency
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()
		instrumentUIL.setLoopingOn();
		instrumentUIL.setFreq ( note_freqs_UIL[0] ); // set the frequency

		if ( usedrones != DRONE_OFF )
		{
			droneUIL.setLoopingOn();
			droneUIL.setFreq ( ( float ) INST_SAMPLERATE_UIL / DRONE_NUM_CELLS_UIL * 4.0f / 3.0f ); // set the frequency (drones on D)
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()
		instrumentGAL.setLoopingOn();
		instrumentGAL.setFreq ( note_freqs_GAL[0] ); // set the frequency

		if ( usedrones != DRONE_OFF )
		{
			droneGAL.setLoopingOn();
			droneGAL.setFreq ( ( float ) INST_SAMPLERATE_GAL / DRONE_NUM_CELLS_GAL ); // set the frequency
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()
		instrumentAST.setLoopingOn();
		instrumentAST.setFreq ( note_freqs_AST[0] ); // set the frequency

		if ( usedrones != DRONE_OFF )
		{
			droneAST.setLoopingOn();
			droneAST.setFreq ( ( float ) INST_SAMPLERATE_AST / DRONE_NUM_CELLS_AST ); // set the frequency
		}

#endif
	}
}

void set_freqs ( )
{
	// setup freq. tables
	float f;
#if GHB_IN_USE()
	f = INST_SAMPLERATE_GHB / INST_NUM_CELLS_GHB;

	for ( i = 0; i < table_len_GHB; i++ )
	{
		note_freqs_GHB[i] = ( f * note_ratios_GHB[i][0] ) / note_ratios_GHB[i][1];
	}

#endif
#if BGT_IN_USE()
	f = INST_SAMPLERATE_BGT / INST_NUM_CELLS_BGT;

	for ( i = 0; i < table_len_BGT; i++ )
	{
		note_freqs_BGT[i] = ( f * note_ratios_BGT[i][0] ) / note_ratios_BGT[i][1];
	}

#endif
#if BRD_IN_USE()
	f = INST_SAMPLERATE_BRD / INST_NUM_CELLS_BRD * 1.14f;

	for ( i = 0; i < table_len_BRD; i++ )
	{
		note_freqs_BRD[i] = ( f * note_ratios_BRD[i][0] ) / note_ratios_BRD[i][1];
	}

#endif
#if SML_IN_USE()
	f = INST_SAMPLERATE_SML / INST_NUM_CELLS_SML * 1.1378882f;

	for ( i = 0; i < table_len_SML; i++ )
	{
		note_freqs_SML[i] = ( f * note_ratios_SML[i][0] ) / note_ratios_SML[i][1];
	}

#endif
#if UIL_IN_USE()
	f = INST_SAMPLERATE_UIL / INST_NUM_CELLS_UIL * 1.1442786f;

	for ( i = 0; i < table_len_UIL; i++ )
	{
		note_freqs_UIL[i] = ( f * note_ratios_UIL[i][0] ) / note_ratios_UIL[i][1];
	}

#endif
#if GAL_IN_USE()
	f = INST_SAMPLERATE_GAL / INST_NUM_CELLS_GAL;

	for ( i = 0; i < table_len_GAL; i++ )
	{
		note_freqs_GAL[i] = ( f * note_ratios_GAL[i][0] ) / note_ratios_GAL[i][1];
	}

#endif
#if AST_IN_USE()
	f = INST_SAMPLERATE_AST / INST_NUM_CELLS_AST;

	for ( i = 0; i < table_len_AST; i++ )
	{
		note_freqs_AST[i] = ( f * note_ratios_AST[i][0] ) / note_ratios_AST[i][1];
	}

#endif
}
void updateControl()
{
	byte fb = 0;
	int sensor_val = 0;
	// put changing controls in here
	/* Read the relevant pin registers and construct a single byte 'map'   */
	/* of the pin states. Touched pins will be HIGH, untouched pins LOW    */
#if (TOUCHMODE == TOUCH_CAP)

	// set map
	if ( readCapacitivePin ( sensor_pins[curr_sensor] ) >= CAPTOUCH_TRIGGER )
	{
		// make bit to be 1
		fmap |= ( 1 << ( 7 - curr_sensor ) );
	}

	curr_sensor++;

	//increment, return until all sensors are sampled, then toggle bitmap, reset counter and continue
	if ( curr_sensor % num_sensors == 0 )
	{
		//fmap = ~fmap; // toggle bitmap because bushbutton code is LOW when touched.
		curr_sensor = 0; // rset counter
	}
	else
	{
		return;
	}

#elif (TOUCHMODE == TOUCH_MPR121)
	//fmap = cap.touched();
	//fmap &= B11111111;
	fmap = 0;

	for ( int i = 0; i < num_sensors; i++ )
	{
		// use filtered data: the MPR121 take initial value as base value (not true if something is touched when the system starts)
		// TODO: verify if 128 is good in every conditions
		if ( cap.filteredData ( i ) < 150 )
		{
			fmap |= ( 1 << i );
		}
	}

#else
	// pushbuttonetc, finger sensors
	fmap = PIND >> 2;  // get rid of lowest 2 bytes,  fill top 2 bytes
	fb = PINB; // D8, D11 (bits 0, 3)

	if ( fb & B00000001 ) // true only if bit ZERO is 1
	{
		// make  bit 6 in fmap to be 1
		fmap |= ( 1 << 6 );
	}
	else
	{
		// untouched make bit 6 to be 0
		fmap &= ~ ( 1 << 6 );
	}

	if ( fb & B00010000 ) // true only if bit 3 is 1
	{
		// make  bit 7 in fmap to be 1
		fmap |= ( 1 << 7 );
	}
	else
	{
		// untouched make bit 7 to be 0
		fmap &= ~ ( 1 << 7 );
	}

#endif
	note_detected = -1;

	if ( instrument == BGT )
	{
#if BGT_IN_USE()

		for ( i = 0; i < table_len_BGT; i++ )
		{
			if ( ( ( fmap ^ finger_table_BGT[i][0] ) & finger_table_BGT[i][1] ) == 0 )
			{
				note_detected = i;
			}
		}

		// detect starting note
		if ( startchanter == 0 )
		{
			if ( note_detected == BGT_STARTING_NOTE )
			{
				startchanter = 1;
			}
		}

#endif
	}
	else if ( instrument == GHB )
	{
#if GHB_IN_USE()

		for ( i = 0; i < table_len_GHB; i++ )
		{
			if (((fmap ^ finger_table_GHB[i][0]) & finger_table_GHB[i][1]) == 0)
			{
				note_detected = i;
			}
		}

		// detect starting note
		if ( startchanter == 0 )
		{
			if ( note_detected == GHB_STARTING_NOTE )
			{
				startchanter = 1;
			}
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()

		for ( i = 0; i < table_len_BRD; i++ )
		{
			if (((fmap ^ finger_table_BRD[i][0]) & finger_table_BRD[i][1]) == 0)
			{
				note_detected = i;
			}
		}

		// detect starting note
		if ( startchanter == 0 )
		{
			if ( note_detected == BRD_STARTING_NOTE )
			{
				startchanter = 1;
			}
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()

		for ( i = 0; i < table_len_SML; i++ )
		{
			if (((fmap ^ finger_table_SML[i][0]) & finger_table_SML[i][1]) == 0)
			{
				note_detected = i;
			}
		}

		// detect starting note
		if ( startchanter == 0 )
		{
			if ( note_detected == SML_STARTING_NOTE )
			{
				startchanter = 1;
			}
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()

		for ( i = 0; i < table_len_UIL; i++ )
		{
			if (((fmap ^ finger_table_UIL[i][0]) & finger_table_UIL[i][1]) == 0)
			{
				note_detected = i;
			}
		}

		// detect starting note
		if ( startchanter == 0 )
		{
			if ( note_detected == UIL_STARTING_NOTE )
			{
				startchanter = 1;
			}
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()

		for ( i = 0; i < table_len_GAL; i++ )
		{
			if (((fmap ^ finger_table_GAL[i][0]) & finger_table_GAL[i][1]) == 0)
			{
				note_detected = i;
			}
		}

		// detect starting note
		if ( startchanter == 0 )
		{
			if ( note_detected == GAL_STARTING_NOTE )
			{
				startchanter = 1;
			}
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()

		for ( i = 0; i < table_len_AST; i++ )
		{
			if (((fmap ^ finger_table_AST[i][0]) & finger_table_AST[i][1]) == 0)
			{
				note_detected = i;
			}
		}

		// detect starting note
		if ( startchanter == 0 )
		{
			if ( note_detected == AST_STARTING_NOTE )
			{
				startchanter = 1;
			}
		}

#endif
	}

	if ( note_detected != note_playing )
	{
		note_playing = note_detected;

		if ( instrument == GHB )
		{
#if GHB_IN_USE()
			instrumentGHB.setFreq ( note_freqs_GHB[note_playing] );

#endif
		}
		else if ( instrument == BGT )
		{
#if BGT_IN_USE()
			instrumentBGT.setFreq ( note_freqs_BGT[note_playing] );
#endif
		}
		else if ( instrument == BRD )
		{
#if BRD_IN_USE()
			instrumentBRD.setFreq ( note_freqs_BRD[note_playing] );
#endif
		}
		else if ( instrument == SML )
		{
#if SML_IN_USE()
			instrumentSML.setFreq ( note_freqs_SML[note_playing] );
#endif
		}
		else if ( instrument == UIL )
		{
#if UIL_IN_USE()
			instrumentUIL.setFreq ( note_freqs_UIL[note_playing] );
#endif
		}
		else if ( instrument == GAL )
		{
#if GAL_IN_USE()
			instrumentGAL.setFreq ( note_freqs_GAL[note_playing] );
#endif
		}
		else if ( instrument == AST )
		{
#if AST_IN_USE()
			instrumentAST.setFreq ( note_freqs_AST[note_playing] );
#endif
		}
	}

	// reset fingermap
	fmap = 0;
}
#if (STEREO_HACK == true)
// needed for stereo output
int audio_out_1, audio_out_2;
void updateAudio()
{
#if USE_16BIT_SAMPLES

	if ( instrument == GHB )
	{
#if GHB_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( ( ( int32_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 9 );
		}
		else
		{
			audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) >> 9 );
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == BGT )
	{
#if BGT_IN_USE()

		if ( usedrones == DRONE_OFF )
		{
			audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 9 );
			audio_out_2 = 0;
		}
		else if ( droneintonation == DRONE_INT_STANDARD )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( ( ( int32_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 9 );
		}
		else
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( (  ( int32_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) >> 9 );
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( ( ( int32_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 9 );
		}
		else
		{
			audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) >> 9 );
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( ( ( int32_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 9 );
		}
		else
		{
			audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) >> 9 );
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( ( ( int32_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 9 );
		}
		else
		{
			audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) >> 9 );
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( ( ( int32_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 9 );
		}
		else
		{
			audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) >> 9 );
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) >> 9 );
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( int16_t ) ( ( ( int32_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 9 );
		}
		else
		{
			audio_out_1 = ( int16_t ) ( ( ( int32_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) >> 9 );
			audio_out_2 = 0;
		}

#endif
	}

#else

	if ( instrument == GHB )
	{
#if GHB_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 3;
		}
		else
		{
			audio_out_1 = ( ( int16_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) >> 3;
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == BGT )
	{
#if BGT_IN_USE()

		if ( usedrones == DRONE_OFF )
		{
			audio_out_1 = ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 3;
			audio_out_2 = 0;
		}
		else if ( droneintonation == DRONE_INT_STANDARD )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 3;
		}
		else
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) >> 3;
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 3;
		}
		else
		{
			audio_out_1 = ( ( int16_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) >> 3;
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 3;
		}
		else
		{
			audio_out_1 = ( ( int16_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) >> 3;
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 3;
		}
		else
		{
			audio_out_1 = ( ( int16_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) >> 3;
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 3;
		}
		else
		{
			audio_out_1 = ( ( int16_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) >> 3;
			audio_out_2 = 0;
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				audio_out_1 = ( ( int16_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) >> 3;
			}
			else
			{
				audio_out_1 = 0;
			}

			audio_out_2 = ( ( int16_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 3;
		}
		else
		{
			audio_out_1 = ( ( int16_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) >> 3;
			audio_out_2 = 0;
		}

#endif
	}

#endif
}
#else
int updateAudio()
{
	//for Arduino STANDARD and STANDARD PLUS the sample is nearly 9 bits (between -244 and 243)
	//for STM32 STANDARD and STANDARD PLUS the sample is 11 bits (between -1024 and 1023)
	//for HIFI, both Arduino and STM32 is 15 bits (between -16384 and 16383)
#if (AUDIO_MODE == HIFI)
#if USE_16BIT_SAMPLES

	if ( instrument == GHB )
	{
#if GHB_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME + ( int32_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 6 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) >> 5 );
		}

#endif
	}
	else if ( instrument == BGT )
	{
#if BGT_IN_USE()

		if ( usedrones == DRONE_OFF )
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 5 );
		}
		else if ( droneintonation == DRONE_INT_STANDARD )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int32_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 6 );
			}
		}
		else
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int32_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) >> 6 );
			}
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME + ( int32_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 6 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) >> 5 );
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentSML.next() * SML_CHANTER_VOLUME + ( int32_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 6 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) >> 5 );
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME + ( int32_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 6 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) >> 5 );
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME + ( int32_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 6 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) >> 5 );
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentAST.next() * AST_CHANTER_VOLUME + ( int32_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 6 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 6 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) >> 5 );
		}

#endif
	}

#else

	if ( instrument == GHB )
	{
#if GHB_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME + ( int16_t ) droneGHB.next() * GHB_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) droneGHB.next() * GHB_DRONES_VOLUME ) << 2;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) << 3;
		}

#endif
	}
	else if ( instrument == BGT )
	{
#if BGT_IN_USE()

		if ( usedrones == DRONE_OFF )
		{
			return ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) << 3;
		}
		else if ( droneintonation == DRONE_INT_STANDARD )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int16_t ) droneBGT.next() * BGT_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) droneBGT.next() * BGT_DRONES_VOLUME ) << 2;
			}
		}
		else
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int16_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) << 2;
			}
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME + ( int16_t ) droneBRD.next() * BRD_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) droneBRD.next() * BRD_DRONES_VOLUME ) << 2;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) << 3;
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentSML.next() * SML_CHANTER_VOLUME + ( int16_t ) droneSML.next() * SML_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) droneSML.next() * SML_DRONES_VOLUME ) << 2;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) << 3;
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME + ( int16_t ) droneUIL.next() * UIL_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) droneUIL.next() * UIL_DRONES_VOLUME ) << 2;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) << 3;
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME + ( int16_t ) droneGAL.next() * GAL_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) droneGAL.next() * GAL_DRONES_VOLUME ) << 2;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) << 3;
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentAST.next() * AST_CHANTER_VOLUME + ( int16_t ) droneAST.next() * AST_DRONES_VOLUME ) << 2;
			}
			else
			{
				return ( ( int16_t ) droneAST.next() * AST_DRONES_VOLUME ) << 2;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) << 3;
		}

#endif
	}

#endif
#else
#if USE_16BIT_SAMPLES

	if ( instrument == GHB )
	{
#if GHB_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME + ( int32_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 10 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) >> 9 );
		}

#endif
	}
	else if ( instrument == BGT )
	{
#if BGT_IN_USE()

		if ( usedrones == DRONE_OFF )
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 9 );
		}
		else if ( droneintonation == DRONE_INT_STANDARD )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int32_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 10 );
			}
		}
		else
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int32_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) >> 10 );
			}
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME + ( int32_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 10 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) >> 9 );
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentSML.next() * SML_CHANTER_VOLUME + ( int32_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 10 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) >> 9 );
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME + ( int32_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 10 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) >> 9 );
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME + ( int32_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 10 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) >> 9 );
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( int16_t ) ( ( ( int32_t ) instrumentAST.next() * AST_CHANTER_VOLUME + ( int32_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 10 );
			}
			else
			{
				return ( int16_t ) ( ( ( int32_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 10 );
			}
		}
		else
		{
			return ( int16_t ) ( ( ( int32_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) >> 9 );
		}

#endif
	}

#else

	if ( instrument == GHB )
	{
#if GHB_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME + ( int16_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 4;
			}
			else
			{
				return ( ( int16_t ) droneGHB.next() * GHB_DRONES_VOLUME ) >> 4;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentGHB.next() * GHB_CHANTER_VOLUME ) >> 3;
		}

#endif
	}
	else if ( instrument == BGT )
	{
#if BGT_IN_USE()

		if ( usedrones == DRONE_OFF )
		{
			return ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME ) >> 3;
		}
		else if ( droneintonation == DRONE_INT_STANDARD )
		{
			if ( startchanter != 0 )
			{
				return  ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int16_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 4;
			}
			else
			{
				return  ( ( int16_t ) droneBGT.next() * BGT_DRONES_VOLUME ) >> 4;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentBGT.next() * BGT_CHANTER_VOLUME + ( int16_t ) dronemajBGT.next() * BGT_DRONES_VOLUME ) >> 4;
		}

#endif
	}
	else if ( instrument == BRD )
	{
#if BRD_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME + ( int16_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 4;
			}
			else
			{
				return ( ( int16_t ) droneBRD.next() * BRD_DRONES_VOLUME ) >> 4;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentBRD.next() * BRD_CHANTER_VOLUME ) >> 3;
		}

#endif
	}
	else if ( instrument == SML )
	{
#if SML_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentSML.next() * SML_CHANTER_VOLUME + ( int16_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 4;
			}
			else
			{
				return ( ( int16_t ) droneSML.next() * SML_DRONES_VOLUME ) >> 4;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentSML.next() * SML_CHANTER_VOLUME ) >> 3;
		}

#endif
	}
	else if ( instrument == UIL )
	{
#if UIL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME + ( int16_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 4;
			}
			else
			{
				return ( ( int16_t ) droneUIL.next() * UIL_DRONES_VOLUME ) >> 4;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentUIL.next() * UIL_CHANTER_VOLUME ) >> 3;
		}

#endif
	}
	else if ( instrument == GAL )
	{
#if GAL_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME + ( int16_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 4;
			}
			else
			{
				return ( ( int16_t ) droneGAL.next() * GAL_DRONES_VOLUME ) >> 4;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentGAL.next() * GAL_CHANTER_VOLUME ) >> 3;
		}

#endif
	}
	else if ( instrument == AST )
	{
#if AST_IN_USE()

		if ( usedrones != DRONE_OFF )
		{
			if ( startchanter != 0 )
			{
				return ( ( int16_t ) instrumentAST.next() * AST_CHANTER_VOLUME + ( int16_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 4;
			}
			else
			{
				return ( ( int16_t ) droneAST.next() * AST_DRONES_VOLUME ) >> 4;
			}
		}
		else
		{
			return ( ( int16_t ) instrumentAST.next() * AST_CHANTER_VOLUME ) >> 3;
		}

#endif
	}

#endif
#endif
}
#endif
void loop()
{
	audioHook(); // required here
}
#if (TOUCHMODE == TOUCH_CAP)
// captouch code from eChanter, unrolled to be faster and more reliable, courtesy of
//  Danial Martinez, GPL v2
//  https://github.com/danielmartinez/eClarin
//
uint8_t readCapacitivePin ( int pinToMeasure )
{
	// Variables used to translate from Arduino to AVR pin naming
#if IS_STM32()
	volatile uint32_t *port;
	volatile uint32_t *pin;
#else
	volatile uint8_t *port;
	volatile uint8_t *ddr;
	volatile uint8_t *pin;
#endif
	// Here we translate the input pin number from
	//  Arduino pin number to the AVR PORT, PIN, DDR,
	//  and which bit of those registers we care about.
	byte bitmask;
	port = portOutputRegister ( digitalPinToPort ( pinToMeasure ) );
#if not IS_STM32()
	ddr = portModeRegister ( digitalPinToPort ( pinToMeasure ) );
#endif
	bitmask = digitalPinToBitMask ( pinToMeasure );
	pin = portInputRegister ( digitalPinToPort ( pinToMeasure ) );
	// Discharge the pin first by setting it low and output
	*port &= ~ ( bitmask );
#if IS_STM32()
	pinMode ( pinToMeasure, OUTPUT );
#else
	*ddr  |= bitmask;
#endif
	// delay(1);
	// Make the pin an input with the internal pull-up on
#if IS_STM32()
	pinMode ( pinToMeasure, INPUT_PULLUP );
#else
	*ddr &= ~ ( bitmask );
#endif
	*port |= bitmask;
	// Now see how long the pin to get pulled up. This manual unrolling of the loop
	// decreases the number of hardware cycles between each read of the pin,
	// thus increasing sensitivity.
	uint8_t cycles = 17;

	if ( *pin & bitmask )
	{
		cycles =  0;
	}
	else if ( *pin & bitmask )
	{
		cycles =  1;
#if (CAPTOUCH_TRIGGER == 1)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  2;
#if (CAPTOUCH_TRIGGER == 2)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  3;
#if (CAPTOUCH_TRIGGER == 3)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  4;
#if (CAPTOUCH_TRIGGER == 4)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  5;
#if (CAPTOUCH_TRIGGER == 5)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  6;
#if (CAPTOUCH_TRIGGER == 6)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  7;
#if (CAPTOUCH_TRIGGER == 7)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  8;
#if (CAPTOUCH_TRIGGER == 8)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles =  9;
#if (CAPTOUCH_TRIGGER == 9)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles = 10;
#if (CAPTOUCH_TRIGGER == 10)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles = 11;
#if (CAPTOUCH_TRIGGER == 11)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles = 12;
#if (CAPTOUCH_TRIGGER == 12)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles = 13;
#if (CAPTOUCH_TRIGGER == 13)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles = 14;
#if (CAPTOUCH_TRIGGER == 14)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles = 15;
#if (CAPTOUCH_TRIGGER == 15)
		goto exit;
#endif
	}
	else if ( *pin & bitmask )
	{
		cycles = 16;
	}

exit:
	// Discharge the pin again by setting it low and output
	//  It's important to leave the pins low if you want to
	//  be able to touch more than 1 sensor at a time - if
	//  the sensor is left pulled high, when you touch
	//  two sensors, your body will transfer the charge between
	//  sensors.
	*port &= ~ ( bitmask );
#if IS_STM32()
	pinMode ( pinToMeasure, OUTPUT );
#else
	*ddr  |= bitmask;
#endif
	return cycles;
}
#endif
