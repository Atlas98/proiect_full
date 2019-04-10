#include <internal.h>
#include <data/anexe/anexe.h>
#include <structs.h>

#include <stdlib.h>
#include <stdio.h>

static const int Lp_table[26] = {
    630, 710  , 800 , 900 , 1000, 1120, 1250, 1400, 1600, 1700, 1800, 2000, 2240,
    2500, 2800, 3150, 3550, 3750, 4000, 4500, 5000, 5600, 6300, 7100, 8000, 9000
};

static const int tabel3_5_Dp1_table[10] = {
    63, 71, 80, 90, 100, 112, 125, 140, 160, 180
};
static const int tabel3_6_Dp1_table[10] = {
    90, 100, 112, 125, 140, 160, 180, 200, 224, 250
};
static const int tabel3_7_Dp1_table[10] = {
    140, 160, 180, 200, 224, 250, 280, 315, 355, 400
};
static const int tabel3_8_Dp1_table[10] = {
    180, 200, 224, 250, 280, 315, 355, 400, 450, 500
};
static const int tabel3_9_Dp1_table[10] = {
    224, 250, 280, 315, 355, 400, 450, 500, 560, 630
};

// tabel A3.2
// tabel A3.2 lookup_table[tip_curea, LP]
static const real_t tabel3_2_lookup[5][26] = {
	{0.82, 0.84, 0.86, 0.88, 0.90, 0.93, 0.94, 0.96, 1.00, 1.01, 1.01, 1.02, 1.07, 1.07, 1.09, 1.11, 1.13, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // SPZ
	{-1.0, -1.0, 0.81, 0.83, 0.83, 0.87, 0.89, 0.91, 0.93, 0.94, 0.95, 0.96, 0.98, 1.00, 1.02, 1.04, 1.06, 1.07, 1.08, 1.09, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0}, // SPA
	{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 0.82, 0.84, 0.86, 0.87, 0.88, 0.90, 0.92, 0.94, 0.96, 0.98, 1.00, 1.01, 1.02, 1.04, 1.06, 1.08, 1.10, 1.12, 1.14, -1.0}, // SPB
	{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 0.85, 0.86, 0.87, 0.89, 0.91, 0.93, 0.94, 0.96, 0.97, 0.98, 0.99, 1.00, 1.03, 1.05, 1.07, 1.09, 1.10, 1.12}, // 16x15
	{-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 0.83, 0.86, 0.88, 0.90, 0.92, 0.93, 0.94, 0.96, 0.98, 1.00, 1.02, 1.04, 1.06, 1.08}, // SPC
};

static int get_index_of_Lp(real_t Lp) {
	int LpInt = (int)Lp;
	switch (LpInt) {
	case 630:	 return 0;
		break;
	case 710:	 return 1;
		break;
	case 800:	 return 2;
		break;
	case 900:	 return 3;
		break;
	case 1000:	 return 4;
		break;
	case 1120:	 return 5;
		break;
	case 1250:	 return 6;
		break;
	case 1400:	 return 7;
		break;
	case 1600:	 return 8;
		break;
	case 1700:	 return 9;
		break;
	case 1800:	 return 10;
		break;
	case 2000:	 return 11;
		break;
	case 2240:	 return 12;
		break;
	case 2500:	 return 13;
		break;
	case 2800:	 return 14;
		break;
	case 3150:	 return 15;
		break;
	case 3550:	 return 16;
		break;
	case 3750:	 return 17;
		break;
	case 4000:	 return 18;
		break;
	case 4500:	 return 19;
		break;
	case 5000:	 return 20;
		break;
	case 5600:	 return 21;
		break;
	case 6300:	 return 22;
		break;
	case 7100:	 return 23;
		break;
	case 8000:	 return 24;
		break;
	case 9000:	 return 25;
		break;
	} // switch
	return -1;
} 

INTERNAL_FUNCTION real_t anexa3_get_CL(int tip_curea, real_t Lp) {
	int indexof_LP = get_index_of_Lp(Lp);

	return tabel3_2_lookup[tip_curea - 1][indexof_LP];
	return 0;
}

// tabel A3.3
// tabel A3.3 lookup_table[

// tabel A3.4
INTERNAL_FUNCTION real_t anexa3_get_Cz(real_t z0) {
	if (z0 >= 0 && z0 <= 3) return 0.95;
	else if (z0 >= 3 && z0 <= 6)  return 0.90;
	else if (z0 >= 6) return 0.85;
	return -1;
}
INTERNAL_FUNCTION real_t anexa3_approx_z(real_t z) {
	// TODO: optimize
	if (z < 0.0)  return -1;	// debugging
	if (z <= 2.0) return 2;
	if (z < 3.0)  return 3;
	if (z < 4.0)  return 4;
	if (z < 5.0)  return 5;
	if (z < 6.0)  return 6;
	if (z < 7.0)  return 7;
	if (z < 8.0)  return 8;
	if (z >= 8.0)  return 8;
	return -1;
}



// tabel A3.5 -> tabel A3.9
INTERNAL_FUNCTION int anexa3_get_tip_curea(real_t N_me, real_t P_IC) {
    if (N_me == 750) {
        if      (P_IC >= 0   && P_IC <= 7)    return SPZ;
        else if (P_IC >= 7   && P_IC <= 22)   return SPA;
        else if (P_IC >= 22  && P_IC <= 45)   return SPB;
        else if (P_IC >= 45  && P_IC <= 100)  return _16x15;
        else if (P_IC >= 100 && P_IC <= 300)  return SPC;
    } // if n_me == 750
    
    else if (N_me == 1000) {
        if      (P_IC >= 0   && P_IC <= 10)   return SPZ;
        else if (P_IC >= 10  && P_IC <= 29)   return SPA;
        else if (P_IC >= 29  && P_IC <= 55)   return SPB;
        else if (P_IC >= 55  && P_IC <= 120)  return _16x15;
        else if (P_IC >= 120 && P_IC <= 300)  return SPC;
    } // if n_me == 750

    else if (N_me == 1500) {
        if      (P_IC >= 0  && P_IC <= 7)     return SPZ;
        else if (P_IC >= 15 && P_IC <= 40)    return SPA;
        else if (P_IC >= 40 && P_IC <= 80)    return SPB;
        else if (P_IC >= 80 && P_IC <= 190)   return _16x15;
    } // if n_me == 750

    else if (N_me == 3000) {
        if      (P_IC >= 0  && P_IC <= 26)     return SPZ;
        else if (P_IC >= 26 && P_IC <= 75)     return SPA;
        else if (P_IC >= 75 && P_IC <= 130)    return SPB;
    } // if n_me == 750

    return -1; // to know that the result is invalid
}

INTERNAL_FUNCTION real_t anexa3_approx_Lp(real_t Lp) {
	static int Lp_table_size = sizeof(Lp_table) / sizeof(int);
	static const int* array = &Lp_table[0];
	if (Lp <= *array) return *array;
	if (Lp >= *(array + Lp_table_size - 1)) return *(array + Lp_table_size - 1);
	
	int min = 0;
	int max = 0;
	for (int i = 0; i < Lp_table_size; i++) {
		if (i + 1 == Lp_table_size) break;
		min = *(array + i);
		max = *(array + i + 1);
		if (Lp >= min && Lp <= max) break;
	}
	real_t delta_min = Lp - min;
	real_t delta_max = max - Lp;

	if (delta_min > delta_max) return max;
	else return min;

	return -1;
}

static real_t approx_from_array(const int* array, int array_size, real_t value) {
    int min = 0;
    int max = 0;
    for(int i = 0; i < array_size; i++) {
        if(i + 1 == array_size) break;
        min = *(array + i);
        max = *(array + i + 1);
        if(value >= min && value <= max) break;
    }
     real_t delta_min = value - min;
     real_t delta_max = max   - value;

    if(delta_min > delta_max) return max;
    else return min;
    
    return -1;
}
INTERNAL_FUNCTION real_t anexa3_lookup_Dp2(int tip_curea, real_t Dp1) {
    static int tabel3_5_size = sizeof(tabel3_5_Dp1_table) / sizeof(int);
    static int tabel3_6_size = sizeof(tabel3_5_Dp1_table) / sizeof(int);
    static int tabel3_7_size = sizeof(tabel3_5_Dp1_table) / sizeof(int);
    static int tabel3_8_size = sizeof(tabel3_5_Dp1_table) / sizeof(int);
    static int tabel3_9_size = sizeof(tabel3_5_Dp1_table) / sizeof(int);

    switch(tip_curea) {
    case SPZ:
        return approx_from_array(&tabel3_5_Dp1_table[0], tabel3_5_size, Dp1);
        break;
    case SPA:
        return approx_from_array(&tabel3_6_Dp1_table[0], tabel3_6_size, Dp1);
        break;
    case SPB:
        return approx_from_array(&tabel3_7_Dp1_table[0], tabel3_7_size, Dp1);
        break;
    case _16x15:
        return approx_from_array(&tabel3_8_Dp1_table[0], tabel3_8_size, Dp1);
        break;
    case SPC:
        return approx_from_array(&tabel3_9_Dp1_table[0], tabel3_9_size, Dp1);
        break;
    }
	return -1;
} // anexa3_lookup_Dp2


// LOOKUP P_0 - big ass function down here

// lookup_table for P_0 [tip_curea][Dp1][I_TCT][N_I - rot/min]
static const real_t P_0_lookup_table[5][10][3][4] = {
	{
		{
			//750, 1000, 1500, 3000  
			{0.54, 0.68, 0.93, 1.45}, // i tct = 1.0
			{0.65, 0.83, 1.15, 1.88}, // i tct = 1.5
			{0.69, 0.87, 1.23, 2.02}  // i tct = 3.0
		}, // dp1_row_63
		{
			//750, 1000, 1500, 3000  
			{0.70, 0.89, 1.25, 2.00}, // i tct = 1.0
			{0.81, 1.04, 1.47, 2.43}, // i tct = 1.5
			{0.84, 1.09, 1.54, 2.57}  // i tct = 3.0
		}, // dp1_row_71
		{
			//750, 1000, 1500, 3000  
			{0.88, 1.14, 1.60, 2.60}, // i tct = 1.0
			{0.99, 1.29, 1.82, 3.04}, // i tct = 1.5
			{1.03, 1.33, 1.90, 3.18}  // i tct = 3.0
		}, // dp1_row_80
		{
			//750, 1000, 1500, 3000  
			{1.08, 1.40, 1.98, 3.27}, // i tct = 1.0
			{1.19, 1.54, 2.20, 3.69}, // i tct = 1.5
			{1.23, 1.60, 2.28, 3.64}  // i tct = 3.0
		}, // dp1_row_90
		{
			//750, 1000, 1500, 3000  
			{1.28, 1.66, 2.35, 3.90}, // i tct = 1.0
			{1.38, 1.81, 2.58, 4.33}, // i tct = 1.5
			{1.43, 1.85, 2.65, 4.47}  // i tct = 3.0
		}, // dp1_row_100
		{
			//750, 1000, 1500, 3000  
			{1.51, 1.97, 2.80, 4.63}, // i tct = 1.0
			{1.62, 2.12, 3.02, 5.07}, // i tct = 1.5
			{1.66, 2.16, 3.10, 5.24}  // i tct = 3.0
		}, // dp1_row_112
		{
			//750, 1000, 1500, 3000  
			{1.77, 2.30, 3.27, 5.40}, // i tct = 1.0
			{1.87, 2.45, 3.50, 5.83}, // i tct = 1.5
			{1.91, 2.49, 3.57, 5.97}  // i tct = 3.0
		}, // dp1_row_125
		{
			//750, 1000, 1500, 3000  
			{2.06, 2.68, 3.81, 6.19}, // i tct = 1.0
			{2.16, 2.82, 4.04, 6.67}, // i tct = 1.5
			{2.20, 2.87, 4.11, 6.81}  // i tct = 3.0
		}, // dp1_row_140
		{
			//750, 1000, 1500, 3000  
			{2.43, 3.17, 4.51, 7.27}, // i tct = 1.0
			{2.54, 3.32, 4.74, 7.73}, // i tct = 1.5
			{2.57, 3.36, 4.81, 7.87}  // i tct = 3.0
		}, // dp1_row_160
		{
			//750, 1000, 1500, 3000  
			{2.80, 3.65, 5.19, 8.17}, // i tct = 1.0
			{2.91, 3.79, 5.41, 8.51}, // i tct = 1.5
			{2.95, 3.85, 5.48, 8.76}  // i tct = 3.0
		}, // dp1_row_180
	}, // TIP_CUREA = SPZ

	{
		{
			//750, 1000, 1500, 3000  
			{1.18, 1.48, 2.02, 2.95}, // i tct = 1.0
			{1.41, 1.81, 2.52, 3.97}, // i tct = 1.5
			{1.49, 1.92, 2.69, 4.29}  // i tct = 3.0
		}, // dp1_row_90
		{
			//750, 1000, 1500, 3000  
			{1.48, 1.89, 2.61, 3.99}, // i tct = 1.0
			{1.73, 2.22, 3.11, 4.96}, // i tct = 1.5
			{1.81, 2.33, 3.28, 5.28}  // i tct = 3.0
		}, // dp1_row_100
		{
			//750, 1000, 1500, 3000  
			{1.85, 2.38, 3.31, 5.15}, // i tct = 1.0
			{2.10, 2.71, 3.81, 6.12}, // i tct = 1.5
			{2.18, 2.82, 3.98, 6.43}  // i tct = 3.0
		}, // dp1_row_112
		{
			//750, 1000, 1500, 3000  
			{2.25, 2.90, 4.06, 6.34}, // i tct = 1.0
			{2.49, 3.23, 4.56, 7.30}, // i tct = 1.5
			{2.58, 3.35, 4.73, 7.65}  // i tct = 3.0
		}, // dp1_row_125
		{
			//750, 1000, 1500, 3000  
			{2.71, 3.50, 4.91, 7.65}, // i tct = 1.0
			{2.95, 3.82, 5.41, 8.51}, // i tct = 1.5
			{3.03, 3.93, 5.58, 8.90}  // i tct = 3.0
		}, // dp1_row_140
		{
			//750, 1000, 1500, 3000  
			{3.30, 4.27, 6.00, 9.27}, // i tct = 1.0
			{3.55, 4.60, 6.51, 10.23}, // i tct = 1.5
			{3.63, 4.71, 6.67, 10.52}  // i tct = 3.0
		}, // dp1_row_160
		{
			//750, 1000, 1500, 3000  
			{3.89, 5.03, 7.06, 10.67}, // i tct = 1.0
			{4.14, 5.36, 7.58, 11.63}, // i tct = 1.5
			{4.22, 5.47, 7.73, 11.99}  // i tct = 3.0
		}, // dp1_row_180
		{
			//750, 1000, 1500, 3000  
			{4.47, 5.78, 8.09, 11.92}, // i tct = 1.0
			{4.71, 6.12, 8.51, 12.88}, // i tct = 1.5
			{4.79, 6.23, 8.76, 13.25}  // i tct = 3.0
		}, // dp1_row_200
		{
			//750, 1000, 1500, 3000  
			{5.15, 6.67, 9.27, 13.17}, // i tct = 1.0
			{5.39, 6.99, 9.79, 14.13}, // i tct = 1.5
			{5.47, 7.09, 9.93, 14.42}  // i tct = 3.0
		}, // dp1_row_224
		{
			//750, 1000, 1500, 3000  
			{5.29, 7.58, 10.50, 14.13}, // i tct = 1.0
			{6.12, 7.95, 11.20, 15.10}, // i tct = 1.5
			{6.20, 8.02, 11.50, 15.46}  // i tct = 3.0
		} // dp1_row_250
	}, // TIP_CUREA = SPA
	{
		{
			//750, 1000, 1500, 3000  
			{3.08, 3.82, 5.19, 7.15}, // i tct = 1.0
			{3.53, 4.53, 6.26, 9.17}, // i tct = 1.5
			{3.70, 4.75, 6.61, 9.89}  // i tct = 3.0
		}, // dp1_row_140
		{
			//750, 1000, 1500, 3000  
			{3.92, 5.00, 6.86, 9.49}, // i tct = 1.0
			{4.44, 5.70, 7.95, 11.55}, // i tct = 1.5
			{4.61, 5.93, 8.25, 12.28}  // i tct = 3.0
		}, // dp1_row_160
		{
			//750, 1000, 1500, 3000  
			{4.81, 6.16, 8.46, 11.63}, // i tct = 1.0
			{5.33, 6.86, 9.49, 13.69}, // i tct = 1.5
			{5.50, 7.07, 9.86, 14.35}  // i tct = 3.0
		}, // dp1_row_180
		{
			//750, 1000, 1500, 3000  
			{5.70, 7.30, 10.01, 13.39}, // i tct = 1.0
			{6.20, 8.02, 11.11, 15.46}, // i tct = 1.5
			{6.37, 8.24, 11.41, 16.12}  // i tct = 3.0
		}, // dp1_row_200
		{
			//750, 1000, 1500, 3000  
			{6.73, 8.51, 11.85, 15.16}, // i tct = 1.0
			{7.24, 9.35, 12.88, 17.22}, // i tct = 1.5
			{7.43, 9.57, 13.15, 17.88}  // i tct = 3.0
		}, // dp1_row_224
		{
			//750, 1000, 1500, 3000  
			{7.87, 10.01, 13.69, 16.49}, // i tct = 1.0
			{8.32, 10.74, 14.72, 18.47}, // i tct = 1.5
			{8.54, 10.97, 15.09, 19.21}  // i tct = 3.0
		}, // dp1_row_250
		{
			//750, 1000, 1500, 3000  
			{9.13, 11.63, 15.68, 16.41}, // i tct = 1.0
			{9.57, 12.28, 16.71, 19.21}, // i tct = 1.5
			{9.79, 12.58, 17.10, 19.87}  // i tct = 3.0
		}, // dp1_row_280
		{
			//750, 1000, 1500, 3000  
			{10.51, 13.39, 17.81, -1}, // i tct = 1.0
			{11.04, 14.13, 18.84, -1}, // i tct = 1.5
			{11.18, 14.35, 19.21, -1}  // i tct = 3.0
		}, // dp1_row_315
		{
			//750, 1000, 1500, 3000  
			{12.07, 15.30, 19.94, -1}, // i tct = 1.0
			{12.58, 16.04, 21.05, -1}, // i tct = 1.5
			{12.81, 16.26, 21.34, -1}  // i tct = 3.0
		}, // dp1_row_355
		{
			//750, 1000, 1500, 3000  
			{13.84, 17.37, 22.00, -1}, // i tct = 1.0
			{14.35, 18.10, 23.11, -1}, // i tct = 1.5
			{14.50, 18.33, 23.40, -1}  // i tct = 3.0
		} // dp1_row_400
	}, // TIP_CUREA = SPB

	{
		{
			//750, 1000, 1500, 3000  
			{5.14, 6.52, 8.76, 10.89}, // i tct = 1.0
			{5.91, 7.58, 10.38, 13.91}, // i tct = 1.5
			{6.16, 7.87, 10.89, 14.94}  // i tct = 3.0
		}, // dp1_row_180
		{
			//750, 1000, 1500, 3000  
			{6.24, 7.95, 10.67, 13.03}, // i tct = 1.0
			{7.00, 8.94, 12.28, 16.12}, // i tct = 1.5
			{7.25, 9.35, 12.81, 17.15}  // i tct = 3.0
		}, // dp1_row_200
		{
			//750, 1000, 1500, 3000  
			{7.58, 9.64, 12.95, 15.16}, // i tct = 1.0
			{8.32, 10.67, 14.50, 18.18}, // i tct = 1.5
			{8.54, 10.97, 15.01, 19.21}  // i tct = 3.0
		}, // dp1_row_224
		{
			//750, 1000, 1500, 3000  
			{8.90, 11.41, 15.23, 16.63}, // i tct = 1.0
			{9.71, 12.44, 16.78, 19.65}, // i tct = 1.5
			{9.94, 12.73, 17.37, 20.68}  // i tct = 3.0
		}, // dp1_row_250
		{
			//750, 1000, 1500, 3000  
			{10.52, 13.32, 17.74, 17.30}, // i tct = 1.0
			{11.26, 14.35, 19.28, 20.39}, // i tct = 1.5
			{11.48, 14.72, 19.80, 21.34}  // i tct = 3.0
		}, // dp1_row_280
		{
			//750, 1000, 1500, 3000  
			{12.28, 15.53, 20.39, -1}, // i tct = 1.0
			{13.03, 16.56, 21.93, -1}, // i tct = 1.5
			{13.32, 16.93, 22.45, -1}  // i tct = 3.0
		}, // dp1_row_315
		{
			//750, 1000, 1500, 3000  
			{14.28, 17.96, 23.04, -1}, // i tct = 1.0
			{15.01, 18.99, 24.56, -1}, // i tct = 1.5
			{15.23, 19.36, 25.17, -1}  // i tct = 3.0
		}, // dp1_row_355
		{
			//750, 1000, 1500, 3000  
			{16.41, 20.53, 25.54, -1}, // i tct = 1.0
			{17.15, 21.56, 27.16, -1}, // i tct = 1.5
			{17.44, 21.93, 27.67, -1}  // i tct = 3.0
		}, // dp1_row_400
		{
			//750, 1000, 1500, 3000  
			{18.69, 23.18, 27.67, -1}, // i tct = 1.0
			{19.43, 24.21, 29.22, -1}, // i tct = 1.5
			{19.72, 24.56, 29.73, -1}  // i tct = 3.0
		}, // dp1_row_450
		{
			//750, 1000, 1500, 3000  
			{20.90, 25.54, 29.00, -1}, // i tct = 1.0
			{21.64, 26.57, 30.54, -1}, // i tct = 1.5
			{21.83, 26.94, 31.13, -1}  // i tct = 3.0
		} // dp1_row_500
	}, // TIP_CUREA = 16x15

	{
		{
			//750, 1000, 1500, 3000  
			{8.10, 10.16, 13.25, 11.92}, // i tct = 1.0
			{9.42, 11.92, 15.82, 16.93}, // i tct = 1.5
			{9.79, 12.44, 16.71, 18.62}  // i tct = 3.0
		}, // dp1_row_224
		{
			//750, 1000, 1500, 3000  
			{9.94, 12.51, 16.19, 13.62}, // i tct = 1.0
			{11.18, 14.20, 18.84, 18.65}, // i tct = 1.5
			{11.63, 14.79, 19.72, 20.31}  // i tct = 3.0
		}, // dp1_row_250
		{
			//750, 1000, 1500, 3000  
			{12.00, 15.10, 19.43, 11.13}, // i tct = 1.0
			{13.25, 16.78, 22.08, 19.14}, // i tct = 1.5
			{13.69, 17.37, 22.89, 20.83}  // i tct = 3.0
		}, // dp1_row_280
		{
			//750, 1000, 1500, 3000  
			{14.35, 18.03, 22.89, -1}, // i tct = 1.0
			{15.60, 19.72, 25.46, -1}, // i tct = 1.5
			{16.04, 20.31, 26.35, -1}  // i tct = 3.0
		}, // dp1_row_315
		{
			//750, 1000, 1500, 3000  
			{17.00, 21.20, 26.27, -1}, // i tct = 1.0
			{18.25, 22.89, 28.92, -1}, // i tct = 1.5
			{18.62, 23.48, 29.81, -1}  // i tct = 3.0
		}, // dp1_row_355
		{
			//750, 1000, 1500, 3000  
			{19.80, 24.51, 29.44, -1}, // i tct = 1.0
			{21.05, 26.20, 32.09, -1}, // i tct = 1.5
			{21.49, 26.79, 32.97, -1}  // i tct = 3.0
		}, // dp1_row_400
		{
			//750, 1000, 1500, 3000  
			{22.82, 27.95, 32.09, -1}, // i tct = 1.0
			{24.07, 29.66, 34.66, -1}, // i tct = 1.5
			{24.51, 30.21, 35.55, -1}  // i tct = 3.0
		}, // dp1_row_450
		{
			//750, 1000, 1500, 3000  
			{25.69, 31.06, 33.56, -1}, // i tct = 1.0
			{26.94, 32.75, 36.21, -1}, // i tct = 1.5
			{27.38, 33.94, 37.02, -1}  // i tct = 3.0
		}, // dp1_row_500
		{
			//750, 1000, 1500, 3000  
			{28.92, 34.30, 33.86, -1}, // i tct = 1.0
			{30.18, 35.99, 36.43, -1}, // i tct = 1.5
			{30.62, 36.58, 37.31, -1}  // i tct = 3.0
		}, // dp1_row_560
		{
			//750, 1000, 1500, 3000  
			{32.38, 37.39, -1, -1}, // i tct = 1.0
			{33.63, 39.08, -1, -1}, // i tct = 1.5
			{34.08, 39.67, -1, -1}  // i tct = 3.0
		} // dp1_row_630
	} // TIP_CUREA = SPC
};


static real_t approx_I_TCT(real_t I_TCT) {
	if (I_TCT < 1.0) return 1.0;
	else if (I_TCT >= 1.0 && I_TCT <= 1.5) {
		if ((I_TCT - 1.0) > (1.5 - I_TCT)) return 1.5;
		else return 1.0;
	}
	else if (I_TCT >= 1.5 && I_TCT <= 3.0) {
		if ((I_TCT - 1.5) > (3.0 - I_TCT)) return 3.0;
		else return 1.5;
	}
	else if (I_TCT > 3) return 3.0;

	return -1;
} // aprox_I_TCT
static int get_I_TCT_index(real_t I_TCT) {
	real_t I_TCT_approx = approx_I_TCT(I_TCT);

	if		(I_TCT_approx == 1.0) return 0;
	else if (I_TCT_approx == 1.5) return 1;
	else if (I_TCT_approx == 3.0) return 2;
	return -1;
}
static int get_NI_index(real_t NI) {
	if		(NI == 750.0)  return 0;
	else if (NI == 1000.0) return 1;
	else if (NI == 1500.0) return 2;
	else if (NI == 3000.0) return 3;
	return -1;
}
static int get_Dp1_index(int tip_curea, real_t dp1) {
	switch(tip_curea) {
	case SPZ:
		if		(dp1 == 63.0)  return 0;
		else if (dp1 == 71.0)  return 1;
		else if (dp1 == 80.0)  return 2;
		else if (dp1 == 90.0)  return 3;
		else if (dp1 == 100.0) return 4;
		else if (dp1 == 112.0) return 5;
		else if (dp1 == 125.0) return 6;
		else if (dp1 == 140.0) return 7;
		else if (dp1 == 160.0) return 8;
		else if (dp1 == 180.0) return 9;
	break;
	case SPA:
		if		(dp1 == 90.0)  return 0;
		else if (dp1 == 100.0)  return 1;
		else if (dp1 == 112.0)  return 2;
		else if (dp1 == 125.0)  return 3;
		else if (dp1 == 140.0) return 4;
		else if (dp1 == 160.0) return 5;
		else if (dp1 == 180.0) return 6;
		else if (dp1 == 200.0) return 7;
		else if (dp1 == 224.0) return 8;
		else if (dp1 == 250.0) return 9;
	break;
	case SPB:
		if		(dp1 == 140.0)  return 0;
		else if (dp1 == 160.0)  return 1;
		else if (dp1 == 180.0)  return 2;
		else if (dp1 == 200.0)  return 3;
		else if (dp1 == 224.0) return 4;
		else if (dp1 == 250.0) return 5;
		else if (dp1 == 280.0) return 6;
		else if (dp1 == 315.0) return 7;
		else if (dp1 == 355.0) return 8;
		else if (dp1 == 400.0) return 9;
	break;
	case _16x15:
		if		(dp1 == 180.0)  return 0;
		else if (dp1 == 200.0)  return 1;
		else if (dp1 == 224.0)  return 2;
		else if (dp1 == 250.0)  return 3;
		else if (dp1 == 280.0) return 4;
		else if (dp1 == 315.0) return 5;
		else if (dp1 == 355.0) return 6;
		else if (dp1 == 400.0) return 7;
		else if (dp1 == 450.0) return 8;
		else if (dp1 == 500.0) return 9;
	break;
	case SPC:
		if		(dp1 == 224.0)  return 0;
		else if (dp1 == 250.0)  return 1;
		else if (dp1 == 280.0)  return 2;
		else if (dp1 == 315.0)  return 3;
		else if (dp1 == 355.0) return 4;
		else if (dp1 == 400.0) return 5;
		else if (dp1 == 450.0) return 6;
		else if (dp1 == 500.0) return 7;
		else if (dp1 == 560.0) return 8;
		else if (dp1 == 630.0) return 9;
	break;
	}	
	return -1;
}

static real_t lookup_P0(int tip_curea, real_t Dp1, real_t NI, real_t I_TCT) {
	real_t I_TCT_approx = approx_I_TCT(I_TCT);

	int I_TCT_index = get_I_TCT_index(I_TCT_approx);
	int Dp1_index = get_Dp1_index(tip_curea, Dp1);
	int NI_index = get_NI_index(NI);
	real_t P0 = P_0_lookup_table[tip_curea -1][Dp1_index][I_TCT_index][NI_index];

	return P0;
}


INTERNAL_FUNCTION real_t anexa3_lookup_P0(int tip_curea, real_t Dp1, real_t NI, real_t I_TCT) {
	if (!(tip_curea == SPZ || tip_curea == SPA || tip_curea == SPB || tip_curea == _16x15 || tip_curea == SPC)) {
		if (DEBUG_ANEXA) printf("Nu se poate alege un P0, tipul de curea nu e potrivit\n");
		return -1;
	}
	if (!(NI == 750 || NI == 1000 || NI == 1500 || NI == 3000)) {
		if (DEBUG_ANEXA) printf("Nu se poate alege un P0, numarul de rotatii nu e potrivit");
		return -1;
	}
	// mai mult cod de verificare Dp1 pentru fiecare tip de curea - lene
	if (Dp1 < 63 && Dp1 > 630) {
		if (DEBUG_ANEXA) printf("Nu se poate alege un P0, lungimea rotii conducatoare nu e potrivita");
		return -1;
	}

	return lookup_P0(tip_curea, Dp1, NI, I_TCT);
	return -1;
}