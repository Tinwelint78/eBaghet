/* eBaghet configuration file */
/* CAPTOUCH       true/false
 *    true if using apacitive touch style sensors
 *    false if using touchpad or push button style switches
 *
 * CAPTOUCH_TRIGGER  0-16
 *    Values in the range 6-8 tend to work well
 *
 * sensor_pins
 *    Digital inputs for sensors or buttons,
 *    in order from HA to LA.
 *
 * finger_table
 *    Finger mapings for various notes.
 *
 * drone_freqs
 *    Calculated at setup from base frequency for tenor
 *    and bass drones.
 *
 *
 * ==== DATA RESATIONSHIPS ====
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
#define GHB 100
#define BGT 200

#define CAPTOUCH true
#define CAPTOUCH_TRIGGER 4

int num_sensors = 8;
int sensor_pins[] = {12,8,7,6,5,4,3,2};

#define table_len_GHB 9
byte finger_table_GHB [table_len_GHB] = {
  B00011110, /*HA */
  B10001110, /*HG */
  B11001110, /* F */
  B11101110, /* E */
  B11110001, /* D */
  B11111001, /* C */
  B11111100, /* B */
  B11111110, /*LA */
  B11111111  /*LG */
};

int note_ratios_GHB [table_len_GHB][2]= {
  {2,1},  /*HA */
  {16,9}, /*HG */
  {5,3},  /* F */
  {3,2},  /* E */
  {4,3},  /* D */
  {5,4},  /* C */
  {9,8},  /* B */
  {1,1},  /*LA */
  {8,9}   /*LG */
};

float note_freqs_GHB [table_len_GHB]= {1,1,1,1,1,1,1,1,1};

#define table_len_BGT 14
byte finger_table_BGT [table_len_BGT] = {
  B00000000, /* G */
  B10000000, /* F# */
  B10100000, /* F */
  B11000000, /* E */
  B11010000, /* Eb */
  B11100000, /* D */
  B11101000, /* C# */
  B11110000, /* C */
  B11111000, /* B */
  B11111010, /* Bb */
  B11111100, /* A */
  B11111101, /* Ab */
  B11111110, /* G */
  B11111111  /* F# */
};

int note_ratios_BGT [table_len_BGT][2]= {
            /*Note  Just    EqT     Sampled */
  {16,9},   /* G    789 Hz  791 Hz  (789 Hz)*/
  {5,3},    /* F#   740 Hz  747 Hz  (742 Hz)*/
  {8,5},    /* F    710 Hz  705 Hz          */
  {3,2},    /* E    666 Hz  665 Hz  (658 Hz)*/
  {7,5},    /* Eb   622 Hz  628 Hz          */
  {4,3},    /* D    592 Hz  593 Hz  (586 Hz)*/
  {5,4},    /* C#   555 Hz  559 Hz          */
  {6,5},    /* C    533 Hz  528 Hz  (527 Hz)*/
  {9,8},    /* B    499 Hz  498 Hz  (492 Hz)*/
  {16,15},  /* Bb   474 Hz  470 Hz          */
  {1,1},    /* A    444 Hz  444 Hz  (444 Hz)*/
  {15,16},  /* Ab   416 Hz  419 Hz          */
  {8,9},    /* G    395 Hz  396 Hz  (398 Hz)*/
  {5,6}     /* F#   370 Hz  373 Hz  (363 Hz)*/
};

float note_freqs_BGT [table_len_BGT]= {1,1,1,1,1,1,1,1,1,1,1,1,1,1};

#endif /* EBAGHET_CONFIG_H_ */
