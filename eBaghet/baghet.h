/* Baghet sounds, courtesy of Valter Biella              */
/* Sample range [-127, 127] for use with Mozzi Synth     */
/* For independant Arduino/PWM use add 127 to each value */

#define INST_NUM_CELLS_BGT 100
#define DRONE_MIN_NUM_CELLS_BGT 224
#define DRONE_MAJ_NUM_CELLS_BGT 449
#define INST_SAMPLERATE 44100

const int8_t __attribute__((section(".progmem.data"))) INST_DATA_BGT []  =
/* Chanter Sol */
{-6, 29, 70, 98, 108, 110, 116, 125, 127, 112, 88, 66, 52, 40, 18, -15, -50, -72, -81,
 -84, -87, -92, -97, -97, -91, -79, -65, -51, -35, -19, -1, 20, 38, 51, 59, 65, 72, 77,
 76, 71, 65, 62, 57, 48, 33, 15, 0, -14, -26, -35, -41, -44, -45, -47, -48, -47, -42, -33,
 -23, -16, -12, -6, 6, 21, 30, 34, 35, 41, 47, 49, 49, 48, 51, 52, 47, 37, 31, 34, 42, 44,
 35, 19, 2, -13, -24, -33, -42, -55, -74, -97, -114, -117, -109, -102, -103, -107, -101,
 -80, -53, -31};

/* Bordone Minore*/
const int8_t __attribute__((section(".progmem.data"))) DRONE_MIN_DATA_BGT []  =
{0, 1, 3, 4, 5, 5, 6, 6, 6, 7, 10, 13, 14, 17, 20, 20, 18, 17, 15, 12, 9, 7, 6, 6, 8, 11,
 13, 17, 22, 27, 36, 46, 56, 63, 70, 76, 81, 84, 88, 96, 105, 115, 123, 127, 126, 122, 116,
 109, 100, 90, 83, 82, 82, 80, 75, 67, 54, 40, 28, 20, 13, 9, 5, 1, 0, 3, 6, 5, 3, 1, 0,
 -1, 5, 12, 13, 10, 11, 15, 18, 16, 13, 11, 7, 1, -5, -10, -16, -24, -30, -33, -38, -46,
 -55, -63, -72, -82, -91, -100, -105, -106, -106, -107, -105, -99, -93, -89, -85, -78,
 -71, -65, -57, -44, -31, -21, -10, 1, 7, 6, 3, 2, 3, 2, 0, -1, -1, -2, -3, -3, -4, -7,
 -10, -8, -6, -7, -13, -16, -16, -15, -14, -11, -7, -1, 2, 2, 3, 4, 5, 8, 16, 25, 33, 42,
 53, 63, 66, 64, 62, 60, 54, 46, 40, 37, 33, 24, 12, 1, -10, -23, -33, -38, -40, -43, -41,
 -33, -28, -26, -23, -19, -14, -13, -13, -10, -6, -2, 1, 2, 2, 2, 1, 0, -1, -4, -6, -6,
 -5, -6, -10, -16, -20, -24, -30, -36, -42, -49, -56, -64, -70, -72, -74, -74, -72, -69,
 -66, -62, -57, -51, -45, -39, -30, -20, -13, -7, -4, -2};

/* Bordone Maggiore*/
const int8_t __attribute__((section(".progmem.data"))) DRONE_MAJ_DATA_BGT []  =
{1, 5, 10, 16, 22, 27, 32, 38, 44, 49, 53, 57, 60, 62, 64, 64, 64, 66, 68, 70, 71, 70, 69,
 66, 63, 61, 58, 56, 54, 53, 51, 48, 45, 41, 36, 30, 24, 20, 16, 13, 10, 7, 3, -2, -7,
 -12, -17, -21, -23, -24, -26, -28, -30, -31, -32, -33, -34, -34, -34, -32, -30, -28,
 -26, -22, -18, -14, -10, -5, 1, 5, 10, 14, 19, 24, 30, 36, 42, 48, 55, 60, 64, 67, 72,
 77, 80, 84, 88, 93, 96, 97, 98, 98, 99, 100, 101, 100, 100, 99, 97, 94, 89, 84, 79, 73,
 67, 62, 55, 48, 42, 35, 27, 18, 10, 2, -5, -12, -17, -23, -29, -35, -39, -43, -48, -51,
 -52, -54, -56, -58, -58, -59, -59, -59, -58, -57, -56, -53, -50, -46, -42, -39, -36,
 -31, -25, -20, -15, -9, -1, 6, 11, 15, 22, 29, 36, 42, 50, 58, 64, 68, 71, 74, 75, 76,
 77, 78, 79, 81, 82, 81, 80, 76, 70, 65, 63, 62, 59, 53, 45, 37, 29, 22, 16, 10, 3, -3,
 -5, -7, -13, -23, -33, -38, -43, -49, -53, -53, -53, -56, -61, -66, -71, -77, -80, -80,
 -79, -79, -80, -79, -76, -74, -73, -72, -69, -67, -67, -67, -64, -58, -53, -48, -39, -30,
 -23, -19, -16, -10, -5, 0, 6, 15, 27, 40, 52, 61, 66, 71, 76, 83, 91, 99, 107, 113, 118,
 122, 124, 125, 125, 126, 126, 124, 122, 122, 120, 116, 112, 109, 107, 101, 95, 89, 84, 76,
 67, 57, 48, 40, 33, 27, 22, 15, 2, -10, -18, -24, -32, -40, -45, -49, -54, -59, -61, -62,
 -65, -70, -70, -67, -66, -67, -65, -60, -56, -55, -54, -49, -43, -38, -32, -24, -18, -13,
 -8, 1, 9, 15, 19, 25, 32, 38, 41, 44, 47, 49, 52, 56, 59, 60, 61, 63, 65, 64, 62, 60, 60,
 59, 57, 55, 55, 54, 50, 46, 43, 40, 36, 32, 29, 27, 22, 16, 12, 8, 2, -6, -10, -13, -17,
 -21, -22, -21, -23, -27, -30, -30, -31, -33, -35, -34, -33, -33, -33, -32, -30, -32, -34,
 -33, -31, -30, -30, -28, -25, -24, -27, -28, -27, -26, -28, -30, -30, -29, -30, -33, -35,
 -36, -38, -40, -42, -44, -47, -50, -52, -53, -56, -60, -65, -67, -67, -69, -71, -73, -75,
 -77, -79, -82, -84, -86, -87, -88, -90, -93, -96, -98, -100, -103, -106, -108, -108, -109,
 -110, -112, -114, -116, -117, -116, -116, -116, -116, -114, -113, -113, -113, -111, -109,
 -106, -104, -100, -96, -91, -87, -83, -77, -72, -67, -62, -56, -49, -43, -38, -33, -27,
 -22, -16, -9};
