/* eBaghet configuration file */
/* TOUCHMODE
 *   what mode to the finger sensors. Can be one of:
 *		TOUCH_SWITCH	standard pushbuttons
 *		TOUCH_CAP		capacitive sensors
 *		TOUCH_MP121		Adafruit MP121 board
 *
 * CAPTOUCH_TRIGGER  0-16
 *	Values in the range 6-8 tend to work well
 *
 * STARTING_INSTRUMENT/FIRST_INSTRUMENT/SECOND_INSTRUMENT/THIRD_INSTRUMENT/FOURTH_INSTRUMENT
 *	Selectable starting instrument and other instruments that can be chosen closing some keys
 *	Can be any of BGT (baghet), GHB (Great Highland Bagpipe), BRD (border pipe), SML (small pipe) or UIL (uillean pipe).
 *	Uillean pipe for now has great highland bagpipe fingering
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


#define GHB 100				// Great Highland Bagpipe
#define BGT 200				// Baghet
#define BRD 300				// Border Pipe
#define SML 400				// Small Pipe
#define UIL 500				// Uillean Pipe
#define STARTING_INSTRUMENT	GHB
#define FIRST_INSTRUMENT	BGT
#define SECOND_INSTRUMENT	BRD
#define THIRD_INSTRUMENT	SML
#define FOURTH_INSTRUMENT	UIL

#define DRONE_OFF		0
#define DRONE_ON		1
#define STARTING_DRONES	DRONE_ON

#define DRONE_INT_STANDARD	0
#define DRONE_INT_A			1
#define DRONE_INT_C			2
#define STARTING_DRONE_INT	DRONE_INT_STANDARD

#define TOUCH_SWITCH	0
#define TOUCH_CAP		1
#define TOUCH_MP121		2
// NOTE: for MP121 to work with Arduino, twi_nonblock.h and twi_nonblock.cpp must be deleted from Mozzi library!
#define TOUCHMODE TOUCH_CAP
#define CAPTOUCH_TRIGGER 4

// relative volumes 1-8
#define GHB_CHANTER_VOLUME	8
#define GHB_DRONES_VOLUME	4

#define BGT_CHANTER_VOLUME	8
#define BGT_DRONES_VOLUME	4

#define BRD_CHANTER_VOLUME	8
#define BRD_DRONES_VOLUME	8

#define SML_CHANTER_VOLUME	8
#define SML_DRONES_VOLUME	8

#define UIL_CHANTER_VOLUME	8
#define UIL_DRONES_VOLUME	8

int num_sensors = 8;
#if IS_STM32()
int sensor_pins[] = {PA7, PA6, PA5, PA4, PA3, PA2, PA1, PA0};
#else
int sensor_pins[] = { 12, 8, 7, 6, 5, 4, 3, 2 };
#endif


#endif /* EBAGHET_CONFIG_H_ */
