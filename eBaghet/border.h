#ifndef BORDER_H_
#define BORDER_H_

#define table_len_BRD 9
byte finger_table_BRD[table_len_BRD] =
{
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

int note_ratios_BRD[table_len_BRD][2] =
{
	{ 2, 1 }, /*HA */
	{ 16, 9 }, /*HG */
	{ 5, 3 }, /* F */
	{ 3, 2 }, /* E */
	{ 4, 3 }, /* D */
	{ 5, 4 }, /* C */
	{ 9, 8 }, /* B */
	{ 1, 1 }, /*LA */
	{ 8, 9 }  /*LG */
};

float note_freqs_BRD[table_len_BRD] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };

#define INST_NUM_CELLS_BRD 114
#define DRONE_NUM_CELLS_BRD 400
#define INST_SAMPLERATE_BRD 44100

#if IS_STM32()

const int16_t __attribute__ ( ( section ( ".progmem.data" ) ) ) INST_DATA_BRD[] =
{
	1420, 1883, 1337, 1176, 1710, 2334, 2333, 1586, 1490, 3348, 6790, 11303, 16389, 20154, 21075, 20041,
	18366, 15943, 12759, 9720, 7239, 4930, 2621, 484, -1472, -3473, -5574, -7458, -8956, -10239, -11249,
	-11758, -11548, -10094, -7271, -4112, -1732, -242, 697, 1300, 1939, 2795, 3261, 2810, 1780, 628,
	-481, -1491, -2592, -3811, -4850, -5666, -6155, -6028, -5578, -5322, -5241, -5112, -4735, -3916,
	-2699, -1452, -624, -190, 231, 522, 422, 56, -552, -1400, -2041, -2052, -1629, -1112, -579, -184,
	-130, -552, -1338, -2122, -2749, -3102, -3021, -2544, -1754, -850, 5, 872, 1738, 2361, 2657, 2720,
	2354, 1603, 875, 329, 98, 161, 258, 375, 610, 933, 1221, 1307, 987, 152, -1203, -2985, -5108, -7382,
	-8410, -7027, -4427, -1868
};

const int16_t __attribute__ ( ( section ( ".progmem.data" ) ) ) DRONE_DATA_BRD[] =
{
	1565, 2474, 3252, 4299, 6467, 8963, 11392, 14110, 16762, 19282, 21714, 23087, 22676, 20424, 16991,
	15219, 17002, 19656, 21193, 22757, 22855, 19702, 16412, 14963, 13248, 11335, 11727, 14289, 16144,
	15585, 13509, 10849, 7839, 5453, 4364, 4338, 4728, 4367, 3314, 2317, 457, -2034, -2919, -1825, -46,
	1110, 983, 427, -657, -3275, -5885, -7213, -8168, -7983, -5456, -2053, 281, 1075, 1092, 770, -903,
	-3494, -4727, -4823, -5169, -4879, -4210, -5306, -7398, -8482, -9020, -8834, -6943, -5325, -5606,
	-6050, -6015, -6645, -7143, -5967, -3308, 37, 3304, 5044, 4275, 1835, -1019, -3729, -5389, -5058,
	-2847, 665, 5022, 9838, 13771, 14412, 11784, 8677, 6065, 3604, 2169, 1622, 735, -593, -2060, -3147,
	-3009, -1861, -489, 743, 1579, 1826, 1040, -1220, -4390, -7427, -9364, -9417, -8171, -6933, -5781,
	-4493, -3691, -3561, -3500, -3229, -2720, -1600, 273, 2079, 2673, 1763, -190, -2604, -4544, -5002,
	-3809, -1435, 1194, 2863, 3283, 2694, 883, -1206, -1915, -1588, -1310, -1135, -1250, -1818, -2839,
	-4888, -7440, -8772, -8562, -7394, -5643, -4582, -5385, -7371, -9429, -11481, -13403, -14239,
	-13765, -13344, -13724, -14176, -14554, -15084, -14883, -13416, -11361, -9005, -6296, -4120,
	-3333, -3357, -3334, -3427, -3676, -3379, -2289, -766, 681, 1523, 1847, 2233, 3168, 4829, 6505,
	7580, 8377, 8486, 7540, 6462, 5055, 3282, 3273, 5145, 6998, 8992, 11103, 11811, 11196, 10514, 10267,
	9925, 8947, 8706, 10093, 10787, 9471, 7235, 3677, -743, -2325, -93, 3041, 6186, 9024, 8739, 5561,
	3115, 1497, -489, -872, 1418, 4926, 8096, 9278, 8074, 6153, 4739, 3989, 4116, 5046, 5572, 4498,
	2656, 478, -3587, -8244, -10069, -9398, -8512, -8439, -9249, -10106, -11674, -15073, -18014,
	-19135, -19877, -19386, -16861, -14335, -12780, -12036, -11997, -11804, -11401, -11029, -9839,
	-7844, -5815, -4154, -3836, -5374, -7451, -8489, -7992, -6150, -3505, -1041, 386, 594, -268, -1433,
	-1639, -491, 1887, 5295, 8340, 9318, 7911, 5087, 2282, 126, -1121, -349, 2373, 5259, 7709, 9738,
	10004, 7761, 4467, 1951, 357, -953, -1781, -2383, -3885, -6038, -7644, -8353, -8195, -7417, -6529,
	-5557, -4573, -4273, -5127, -6825, -8665, -10198, -11076, -10774, -9714, -9155, -8869, -7553,
	-5575, -4261, -3427, -2373, -1505, -914, 70, 920, 408, -1195, -2769, -3695, -3365, -1423, 1263,
	3456, 4867, 5582, 5236, 3735, 2005, 1196, 1487, 2313, 3261, 3961, 4038, 3504, 2277, 316, -1494,
	-2249, -1978, -1009, 126, 803, 946, 703, 280, 96, 256, 503, 655, 792, 1149, 1644, 2128, 2837, 3823,
	5123, 6957, 8710, 9478, 9299, 8455, 6818, 4440, 2095, 457, -892, -2064, -2381, -2351, -2906, -3794,
	-4688, -5449, -6123, -7063, -7463, -6662, -5861, -5529, -4934, -3872, -2179, -351
};
#else

const int8_t __attribute__ ( ( section ( ".progmem.data" ) ) ) INST_DATA_BRD[] =
{
	5, 7, 5, 4, 6, 9, 9, 6, 5, 12, 26, 43, 63, 78, 81, 77, 71, 61, 49, 37, 28, 19, 10, 1,
	-6, -14, -22, -29, -35, -40, -44, -46, -45, -40, -29, -16, -7, -1, 2, 5, 7, 10,
	12, 10, 6, 2, -2, -6, -11, -15, -19, -22, -24, -24, -22, -21, -21, -20, -19, -16,
	-11, -6, -3, -1, 0, 2, 1, 0, -3, -6, -8, -8, -7, -5, -3, -1, -1, -3, -6, -9, -11, -13,
	-12, -10, -7, -4, 0, 3, 6, 9, 10, 10, 9, 6, 3, 1, 0, 0, 1, 1, 2, 3, 4, 5, 3, 0, -5, -12,
	-20, -29, -33, -28, -18, -8
};

const int8_t __attribute__ ( ( section ( ".progmem.data" ) ) ) DRONE_DATA_BRD[] =
{
	6, 9, 12, 16, 25, 34, 44, 54, 64, 74, 84, 89, 87, 79, 65, 58, 65, 76, 82, 88, 88, 76, 63, 57, 51, 43, 45,
	55, 62, 60, 52, 42, 30, 21, 16, 16, 18, 16, 12, 8, 1, -8, -12, -8, -1, 4, 3, 1, -3, -13, -23, -28, -32,
	-31, -22, -8, 1, 4, 4, 2, -4, -14, -19, -19, -21, -19, -17, -21, -29, -33, -35, -35, -27, -21, -22,
	-24, -24, -26, -28, -24, -13, 0, 12, 19, 16, 7, -4, -15, -21, -20, -12, 2, 19, 38, 53, 55, 45, 33, 23,
	13, 8, 6, 2, -3, -8, -13, -12, -8, -2, 2, 6, 7, 4, -5, -18, -29, -37, -37, -32, -27, -23, -18, -15, -14,
	-14, -13, -11, -7, 1, 8, 10, 6, -1, -11, -18, -20, -15, -6, 4, 11, 12, 10, 3, -5, -8, -7, -6, -5, -5, -8,
	-12, -19, -29, -34, -34, -29, -22, -18, -21, -29, -37, -45, -52, -56, -54, -52, -54, -55, -57, -59,
	-58, -52, -45, -35, -25, -16, -13, -14, -13, -14, -15, -14, -9, -3, 2, 5, 7, 8, 12, 18, 25, 29, 32, 32,
	29, 25, 19, 12, 12, 19, 27, 34, 43, 45, 43, 40, 39, 38, 34, 33, 39, 41, 36, 28, 14, -3, -10, -1, 11, 23,
	34, 33, 21, 12, 5, -2, -4, 5, 19, 31, 35, 31, 23, 18, 15, 15, 19, 21, 17, 10, 1, -14, -32, -40, -37, -33,
	-33, -36, -40, -46, -59, -70, -75, -78, -76, -66, -56, -50, -47, -47, -46, -45, -43, -39, -31, -23,
	-17, -15, -21, -29, -33, -31, -24, -14, -5, 1, 2, -2, -6, -7, -2, 7, 20, 32, 36, 30, 19, 8, 0, -5, -2, 9,
	20, 29, 37, 38, 30, 17, 7, 1, -4, -7, -10, -16, -24, -30, -33, -32, -29, -26, -22, -18, -17, -20, -27,
	-34, -40, -43, -42, -38, -36, -35, -30, -22, -17, -14, -10, -6, -4, 0, 3, 1, -5, -11, -15, -14, -6, 4,
	13, 18, 21, 20, 14, 7, 4, 5, 8, 12, 15, 15, 13, 8, 1, -6, -9, -8, -4, 0, 3, 3, 2, 1, 0, 0, 1, 2, 3, 4, 6, 8, 10,
	14, 19, 26, 33, 36, 36, 32, 26, 17, 8, 1, -4, -8, -10, -10, -12, -15, -19, -22, -24, -28, -29, -26,
	-23, -22, -20, -16, -9, -2
};

#endif

#endif /* BORDER_H_ */
