#ifndef ASTURIANA_H_
#define ASTURIANA_H_


#define table_len_AST 19
byte finger_table_AST[table_len_AST][2] =
{
	{ B01110110, B11111111 },	/* F5 */
	{ B01111010, B11111111 },	/* E5 */
	{ B01111000, B11111111 },	/* Eb5 */
	{ B01111100, B11111111 },	/* D5 */
	{ B00110110, B11111111 },	/* C#5 */
	{ B01111110, B11111111 },	/* C5 */
	{ B01001110, B11100000 },	/* B4 */
	{ B10001110, B11000000 },	/* Bb4 */
	{ B11001110, B11111000 },	/* A4 */
	{ B11000110, B11111000 },	/* Ab4 */
	{ B11101110, B11110000 },	/* G4 */
	{ B11110111, B11111001 },	/* F#4 */
	{ B11110110, B11111001 },	/* F4 */
	{ B11111010, B11111110 },	/* E4 */
	{ B11111000, B11111110 },	/* Eb4 */
	{ B11111100, B11111111 },	/* D4 */
	{ B11111101, B11111111 },	/* C#4 */
	{ B11111110, B11111111 },	/* C4 */
	{ B11111111, B11111111 }	/* B3 */
};

int note_ratios_AST[table_len_AST][2] =
{
	{ 8, 3 },   /* F5 */
	{ 5, 2 },   /* E5 */
	{ 12, 5 },	/* Eb5 */
	{ 9, 4 },   /* D5 */
	{ 32, 15 },	/* C#5 */
	{ 2, 1 },   /* C5 */
	{ 15, 8 },  /* B4 */
	{ 7, 4 }, 	/* Bb4 */
	{ 5, 3 },   /* A4 */
	{ 8, 5 }, 	/* Ab4 */
	{ 3, 2 },   /* G4 */
	{ 7, 5 },   /* F#4 */
	{ 4, 3 },   /* F4 */
	{ 5, 4 },   /* E4 */
	{ 6, 5 },  	/* Eb4 */
	{ 9, 8 },   /* D4 */
	{ 16, 15 }, /* C#4 */
	{ 1, 1 },	/* C4 */
	{ 15, 16 }	/* B3 */
};

// starting note is C4
#define AST_STARTING_NOTE	17

float note_freqs_AST[table_len_AST] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };


#define INST_NUM_CELLS_AST 85
#define DRONE_NUM_CELLS_AST 339
#define INST_SAMPLERATE_AST 44100

#if USE_16BIT_SAMPLES
const int16_t __attribute__ ( ( section ( ".progmem.data" ) ) ) INST_DATA_AST[] =
{
	7615, 18467, 21897, 26499, 27857, 24373, 15099, 6449, 3143, 664, 1506, 4320, 3317, 653, 
	1049, 1641, -4265, -11755, -10873, -5146, -4190, -5053, -1426, -962, -5860, -7150, -3233, 
	-1108, -950, 2283, 5326, 4240, 2996, 3154, 1521, 1133, 2991, 208, -7666, -10342, -8628, 
	-10914, -13886, -12104, -7325, -2766, 2463, 9024, 14396, 18630, 22901, 23380, 18510, 12148, 
	7452, 2839, -2752, -6569, -9462, -14085, -18714, -20039, -17647, -13763, -9545, -3797, 
	2760, 7743, 11710, 14788, 15012, 13410, 11515, 6052, -2180, -8226, -13104, -18254, -20930, 
	-21804, -21504, -17891, -15190, -14468, -6215
};

const int16_t __attribute__ ( ( section ( ".progmem.data" ) ) ) DRONE_DATA_AST[] =
{
	277, 1113, 1875, 2245, 2866, 3815, 4657, 5587, 6895, 8039, 8190, 7891, 7877, 8533, 9772, 10870, 
	11624, 12188, 12908, 13798, 14496, 14852, 15003, 15002, 14748, 14443, 14318, 14281, 13959, 13437, 
	13150, 13059, 12780, 12269, 11665, 10627, 9081, 7669, 6488, 5436, 4485, 3122, 1365, -162, -1396, 
	-2707, -4266, -5894, -7192, -8155, -8730, -9095, -9864, -10766, -11081, -10907, -10443, -9671, 
	-8933, -8138, -6994, -5589, -4004, -2300, -652, 817, 2169, 3300, 4411, 5705, 6808, 7677, 8190, 8098, 
	8162, 8832, 9042, 8631, 8528, 8292, 7541, 7191, 7089, 6565, 6028, 5941, 5995, 5583, 5099, 5189, 
	5589, 5626, 5581, 5742, 5664, 5232, 4999, 5083, 4507, 3439, 2359, 1715, 1099, -910, -3168, -4997, 
	-6775, -7421, -8129, -9784, -10660, -11773, -13247, -13942, -15095, -15915, -15795, -15082, -14212, 
	-13834, -12000, -9468, -8180, -6841, -5577, -4510, -3246, -1422, 752, 1254, 1363, 1882, 1436, 1503, 
	2059, 945, -1172, -2324, -2312, -2879, -4527, -5900, -6262, -7468, -9509, -9987, -10823, -12616, 
	-13447, -13281, -13931, -14578, -13569, -12644, -12014, -11394, -11243, -11198, -10762, -9939, 
	-9682, -9632, -8446, -7082, -6110, -4908, -4059, -3931, -3558, -2747, -1946, -1134, -684, -660, 
	-360, 290, 1136, 2553, 4111, 4650, 4056, 3398, 3328, 4066, 5243, 6206, 6612, 6713, 7288, 7822, 7833, 
	8113, 8714, 8832, 8646, 8649, 8480, 8234, 8203, 8423, 8710, 8939, 8861, 8294, 7681, 7027, 6325, 
	5752, 5064, 4226, 3188, 1675, 247, -682, -1513, -2775, -4698, -6648, -8103, -8984, -9104, -9212, 
	-10176, -11084, -11116, -10561, -9359, -7755, -6575, -5770, -4777, -3595, -2314, -772, 858, 2237, 
	3282, 3925, 4789, 6218, 7589, 8645, 9058, 8734, 8475, 8271, 7579, 7003, 6642, 6043, 5546, 5232, 
	4645, 4133, 4005, 4014, 3904, 3349, 2676, 2382, 2174, 1957, 2121, 2248, 2067, 1771, 1677, 1639, 
	1360, 902, 161, -277, -1177, -3247, -5048, -6523, -7130, -6715, -7524, -8634, -8968, -10280, -10955, 
	-10605, -11082, -11258, -10564, -9382, -8947, -7993, -5045, -2559, -1126, 160, 1034, 1800, 3002, 
	5326, 7690, 8300, 9115, 9734, 9364, 9871, 10530, 9366, 7085, 6087, 5771, 4364, 2696, 2620, 2279, 38, 
	-1420, -1816, -3310, -4765, -5052, -5870, -7656, -8400, -7825, -7253, -6412, -5967, -6306, -6509, 
	-5996, -5220, -4994, -4485, -3538, -2990, -2410, -1622, -1348, -1013, -254 

};

#else
const int8_t __attribute__ ( ( section ( ".progmem.data" ) ) ) INST_DATA_AST[] =
{
	29, 71, 84, 102, 107, 94, 58, 24, 12, 2, 5, 16, 12, 2, 4, 6, -17, -46, -43, -20, -17, -20, 
	-6, -4, -23, -28, -13, -5, -4, 8, 20, 16, 11, 12, 5, 4, 11, 0, -30, -41, -34, -43, -54, 
	-47, -29, -11, 9, 34, 55, 72, 88, 90, 71, 47, 28, 11, -11, -26, -37, -55, -73, -78, -69, 
	-54, -37, -15, 10, 30, 45, 57, 58, 51, 44, 23, -9, -32, -51, -71, -82, -85, -84, -70, -59, 
	-57, -25
};

const int8_t __attribute__ ( ( section ( ".progmem.data" ) ) ) DRONE_DATA_AST[] =
{
	1, 4, 7, 8, 11, 14, 18, 21, 26, 31, 31, 30, 30, 33, 37, 42, 45, 47, 50, 53, 56, 57, 58, 58, 
	57, 55, 55, 55, 54, 52, 50, 50, 49, 47, 45, 41, 35, 29, 25, 21, 17, 12, 5, -1, -6, -11, -17, 
	-23, -28, -32, -34, -36, -39, -42, -43, -43, -41, -38, -35, -32, -28, -22, -16, -9, -3, 3, 
	8, 12, 17, 22, 26, 29, 31, 31, 31, 34, 35, 33, 33, 32, 29, 27, 27, 25, 23, 23, 23, 21, 19, 
	20, 21, 21, 21, 22, 21, 20, 19, 19, 17, 13, 9, 6, 4, -4, -13, -20, -27, -29, -32, -38, -42, 
	-46, -52, -55, -59, -62, -62, -59, -56, -54, -47, -37, -32, -27, -22, -18, -13, -6, 2, 4, 5, 
	7, 5, 5, 7, 3, -5, -10, -9, -12, -18, -23, -25, -29, -37, -39, -42, -49, -53, -52, -54, -57, 
	-53, -50, -47, -45, -44, -44, -42, -39, -38, -38, -33, -28, -24, -20, -16, -16, -14, -11, 
	-8, -5, -3, -3, -2, 1, 4, 9, 15, 18, 15, 13, 12, 15, 20, 24, 25, 26, 28, 30, 30, 31, 33, 34, 
	33, 33, 32, 31, 31, 32, 33, 34, 34, 32, 29, 27, 24, 22, 19, 16, 12, 6, 0, -3, -6, -11, -19, 
	-26, -32, -35, -36, -36, -40, -43, -44, -41, -37, -31, -26, -23, -19, -14, -9, -3, 3, 8, 12, 
	15, 18, 24, 29, 33, 35, 33, 32, 32, 29, 27, 25, 23, 21, 20, 18, 16, 15, 15, 15, 12, 10, 9, 
	8, 7, 8, 8, 8, 6, 6, 6, 5, 3, 0, -2, -5, -13, -20, -26, -28, -27, -30, -34, -35, -40, -43, 
	-42, -43, -44, -41, -37, -35, -31, -20, -10, -5, 0, 4, 6, 11, 20, 29, 32, 35, 37, 36, 38, 
	40, 36, 27, 23, 22, 16, 10, 10, 8, 0, -6, -8, -13, -19, -20, -23, -30, -33, -31, -29, -25, 
	-24, -25, -26, -24, -21, -20, -18, -14, -12, -10, -7, -6, -4, -1
};

#endif

#endif /* ASTURIANA_H_ */

