/* eBaghet configuration file */
/* TOUCHMODE
 *   what mode to the finger sensors. Can be one of:
 *		TOUCH_SWITCH	standard pushbuttons
 *		TOUCH_CAP		capacitive sensors
 *		TOUCH_MP121		Adafruit MP121 board
 *
 * USE_16BIT_SAMPLES
 *  define this to true to use high resolution samples
 *
 * CAPTOUCH_TRIGGER  0-16
 *	Values in the range 6-8 tend to work well
 *
 * STARTING_INSTRUMENT/FIRST_INSTRUMENT/SECOND_INSTRUMENT/THIRD_INSTRUMENT/FOURTH_INSTRUMENT
 *	Selectable starting instrument and other instruments that can be chosen closing some keys
 *	Can be any of BGT (baghet), GHB (Great Highland Bagpipe), BRD (border pipe), SML (small pipe), UIL (uilleann pipe), GAL (gaita gallega), AST (gaita asturiana).
 *  You can even define less instrument if you have memory issues
 *
 * sensor_pins
 *    Digital inputs for sensors or buttons,
 *    in order from HA to LA.
 *
 * CHANTER_VOLUME/DRONE_VOLUME	1-8
 *	for each instrument the relative volume of chanter and drones can be selected
 *
 * ==== DATA RELATIONSHIPS ====
 * For sensor pins, eBaghet recognizes 8 pins which are polled
 * and used to set an 8bit 'touch map,' so it is important that
 * the HA to LA order is preserved.
 * NOTE: ebaghet is coded to recognize LOW as a touch.
 *
 * Finger table, note ratios and note frequencies are all related
 * and should be in identical index positions in the appropriate array.
 * For example, HG (B10001110) is stored as finger_table[2],
 * the ratio of HG from the base frequency is 16:9 which is stored
 * as note_ratios[2]. At setup, the note ratio is used to calculate
 * the actual frequency for each note; HG is stored as note_freqs[2].
 * At runtime the pin states are compared to the finger table.
 * When playing HG, the array index for the HG finger map is used to
 * lookup that note's frequency in the note-freqs array, which is
 * then used to change the note being plated by changing Mozzi's
 * output frequency.
 *
 *
 */

#ifndef EBAGHET_CONFIG_H_
#define EBAGHET_CONFIG_H_

#define USE_16BIT_SAMPLES true

#define GHB 100				// Great Highland Bagpipe
#define BGT 200				// Baghet
#define BRD 300				// Border Pipe
#define SML 400				// Small Pipe
#define UIL 500				// Uilleann Pipe
#define GAL 600             // Gaita Gallega
#define AST 700             // Gaita Asturiana
#define STARTING_INSTRUMENT	GHB
#define FIRST_INSTRUMENT    BGT
#define SECOND_INSTRUMENT	BRD
#define THIRD_INSTRUMENT	SML
#define FOURTH_INSTRUMENT	UIL

// macro definitions for check instrument use (DO NOT MODIFY THIS)
#if (!defined(FIRST_INSTRUMENT))
#define GHB_IN_USE()	(STARTING_INSTRUMENT == GHB)
#define BGT_IN_USE()	(STARTING_INSTRUMENT == BGT)
#define BRD_IN_USE()	(STARTING_INSTRUMENT == BRD)
#define SML_IN_USE()	(STARTING_INSTRUMENT == SML)
#define UIL_IN_USE()	(STARTING_INSTRUMENT == UIL)
#define GAL_IN_USE()	(STARTING_INSTRUMENT == GAL)
#define AST_IN_USE()	(STARTING_INSTRUMENT == AST)
#elif (!defined(SECOND_INSTRUMENT))
#define GHB_IN_USE()	((STARTING_INSTRUMENT == GHB) || (FIRST_INSTRUMENT == GHB))
#define BGT_IN_USE()	((STARTING_INSTRUMENT == BGT) || (FIRST_INSTRUMENT == BGT))
#define BRD_IN_USE()	((STARTING_INSTRUMENT == BRD) || (FIRST_INSTRUMENT == BRD))
#define SML_IN_USE()	((STARTING_INSTRUMENT == SML) || (FIRST_INSTRUMENT == SML))
#define UIL_IN_USE()	((STARTING_INSTRUMENT == UIL) || (FIRST_INSTRUMENT == UIL))
#define GAL_IN_USE()	((STARTING_INSTRUMENT == GAL) || (FIRST_INSTRUMENT == GAL))
#define AST_IN_USE()	((STARTING_INSTRUMENT == AST) || (FIRST_INSTRUMENT == AST))
#elif(!defined(THIRD_INSTRUMENT))
#define GHB_IN_USE()	((STARTING_INSTRUMENT == GHB) || (FIRST_INSTRUMENT == GHB) || (SECOND_INSTRUMENT == GHB))
#define BGT_IN_USE()	((STARTING_INSTRUMENT == BGT) || (FIRST_INSTRUMENT == BGT) || (SECOND_INSTRUMENT == BGT))
#define BRD_IN_USE()	((STARTING_INSTRUMENT == BRD) || (FIRST_INSTRUMENT == BRD) || (SECOND_INSTRUMENT == BRD))
#define SML_IN_USE()	((STARTING_INSTRUMENT == SML) || (FIRST_INSTRUMENT == SML) || (SECOND_INSTRUMENT == SML))
#define UIL_IN_USE()	((STARTING_INSTRUMENT == UIL) || (FIRST_INSTRUMENT == UIL) || (SECOND_INSTRUMENT == UIL))
#define GAL_IN_USE()	((STARTING_INSTRUMENT == GAL) || (FIRST_INSTRUMENT == GAL) || (SECOND_INSTRUMENT == GAL))
#define AST_IN_USE()	((STARTING_INSTRUMENT == AST) || (FIRST_INSTRUMENT == AST) || (SECOND_INSTRUMENT == AST))
#elif (!defined(FOURTH_INSTRUMENT))
#define GHB_IN_USE()	((STARTING_INSTRUMENT == GHB) || (FIRST_INSTRUMENT == GHB) || (SECOND_INSTRUMENT == GHB) || (THIRD_INSTRUMENT == GHB))
#define BGT_IN_USE()	((STARTING_INSTRUMENT == BGT) || (FIRST_INSTRUMENT == BGT) || (SECOND_INSTRUMENT == BGT) || (THIRD_INSTRUMENT == BGT))
#define BRD_IN_USE()	((STARTING_INSTRUMENT == BRD) || (FIRST_INSTRUMENT == BRD) || (SECOND_INSTRUMENT == BRD) || (THIRD_INSTRUMENT == BRD))
#define SML_IN_USE()	((STARTING_INSTRUMENT == SML) || (FIRST_INSTRUMENT == SML) || (SECOND_INSTRUMENT == SML) || (THIRD_INSTRUMENT == SML))
#define UIL_IN_USE()	((STARTING_INSTRUMENT == UIL) || (FIRST_INSTRUMENT == UIL) || (SECOND_INSTRUMENT == UIL) || (THIRD_INSTRUMENT == UIL))
#define GAL_IN_USE()	((STARTING_INSTRUMENT == GAL) || (FIRST_INSTRUMENT == GAL) || (SECOND_INSTRUMENT == GAL) || (THIRD_INSTRUMENT == GAL))
#define AST_IN_USE()	((STARTING_INSTRUMENT == AST) || (FIRST_INSTRUMENT == AST) || (SECOND_INSTRUMENT == AST) || (THIRD_INSTRUMENT == AST))
#else
#define GHB_IN_USE()	((STARTING_INSTRUMENT == GHB) || (FIRST_INSTRUMENT == GHB) || (SECOND_INSTRUMENT == GHB) || (THIRD_INSTRUMENT == GHB) || (FOURTH_INSTRUMENT == GHB))
#define BGT_IN_USE()	((STARTING_INSTRUMENT == BGT) || (FIRST_INSTRUMENT == BGT) || (SECOND_INSTRUMENT == BGT) || (THIRD_INSTRUMENT == BGT) || (FOURTH_INSTRUMENT == BGT))
#define BRD_IN_USE()	((STARTING_INSTRUMENT == BRD) || (FIRST_INSTRUMENT == BRD) || (SECOND_INSTRUMENT == BRD) || (THIRD_INSTRUMENT == BRD) || (FOURTH_INSTRUMENT == BRD))
#define SML_IN_USE()	((STARTING_INSTRUMENT == SML) || (FIRST_INSTRUMENT == SML) || (SECOND_INSTRUMENT == SML) || (THIRD_INSTRUMENT == SML) || (FOURTH_INSTRUMENT == SML))
#define UIL_IN_USE()	((STARTING_INSTRUMENT == UIL) || (FIRST_INSTRUMENT == UIL) || (SECOND_INSTRUMENT == UIL) || (THIRD_INSTRUMENT == UIL) || (FOURTH_INSTRUMENT == UIL))
#define GAL_IN_USE()	((STARTING_INSTRUMENT == GAL) || (FIRST_INSTRUMENT == GAL) || (SECOND_INSTRUMENT == GAL) || (THIRD_INSTRUMENT == GAL) || (FOURTH_INSTRUMENT == GAL))
#define AST_IN_USE()	((STARTING_INSTRUMENT == AST) || (FIRST_INSTRUMENT == AST) || (SECOND_INSTRUMENT == AST) || (THIRD_INSTRUMENT == AST) || (FOURTH_INSTRUMENT == AST))
#endif

#define DRONE_OFF		0
#define DRONE_ON		1
#define STARTING_DRONES	DRONE_ON

#define DRONE_INT_STANDARD	0
#define DRONE_INT_A			1
#define DRONE_INT_C			2
#define STARTING_DRONE_INT	DRONE_INT_STANDARD

#define TOUCH_SWITCH	0
#define TOUCH_CAP		1
#define TOUCH_MPR121	2
// NOTE: for MP121 to work with Arduino, twi_nonblock.h and twi_nonblock.cpp must be deleted from Mozzi library!
// NOTE: TOUCH_CAP is not working with STM32
#define TOUCHMODE TOUCH_CAP
#define CAPTOUCH_TRIGGER 3

// relative volumes 1-8
#define GHB_CHANTER_VOLUME	8
#define GHB_DRONES_VOLUME	4

#define BGT_CHANTER_VOLUME	8
#define BGT_DRONES_VOLUME	4

#define BRD_CHANTER_VOLUME	8
#define BRD_DRONES_VOLUME	4

#define SML_CHANTER_VOLUME	8
#define SML_DRONES_VOLUME	4

#define UIL_CHANTER_VOLUME	8
#define UIL_DRONES_VOLUME	4

#define GAL_CHANTER_VOLUME	8
#define GAL_DRONES_VOLUME	4

#define AST_CHANTER_VOLUME	8
#define AST_DRONES_VOLUME	4

#define START_CHANTER_AFTERWARDS	false

int num_sensors = 8;
#if IS_STM32()
int sensor_pins[] = {PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0};
#else
int sensor_pins[] = { 12, 8, 7, 6, 5, 4, 3, 2 };
#endif


#define MPR121_ADDRESS	0x5A
//#define MPR121_ADDRESS	0x5B
//#define MPR121_ADDRESS	0x5C
//#define MPR121_ADDRESS	0x5D

#endif /* EBAGHET_CONFIG_H_ */
