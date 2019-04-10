#include <internal.h>
#include <data/anexe/anexe.h>
#include <exports.h>

// .data[0] = {.simbol = 0, .D = 0, .B = 0, .r = 0, .C = 0, .Ca = 0, .D1_r = 0, .r1 = 0},
static struct anexa7_dr_data data[21] = {
    {
        .data[0] = {.simbol = 607, .D = 19, .B = 6, .r = 0.5, .C = 2.20, .Ca = 1.18, .D1_r = 9.2, .r1 = 0.3},
        .data[1] = {.simbol = 627, .D = 22, .B = 7, .r = 0.5, .C = 2.60, .Ca = 1.38, .D1_r = 10.0, .r1= 0.3},
        .data[2] = {0},
        .data[3] = {0},
        .data_count = 2
    }, // dr = 7
    {
        .data[0] = {.simbol = 608, .D = 22, .B = 7, .r = 0.5, .C = 2.60, .Ca = 1.38, .D1_r = 10.2, .r1 = 0.3},
        .data[1] = {0},
        .data[2] = {0},
        .data[3] = {0},
        .data_count = 1
    }, // dr = 8
    {
        .data[0] = {.simbol = 609, .D = 24, .B = 7, .r = 0.5, .C = 2.85, .Ca = 1.56, .D1_r = 11.2, .r1 = 0.3},
        .data[1] = {.simbol = 629, .D = 26, .B = 8, .r = 1.0, .C = 3.57, .Ca = 2.00, .D1_r = 14.0, .r1 = 0.6},
        .data[2] = {.simbol = 639, .D = 30, .B = 10, .r = 1.0, .C = 4.57, .Ca = 2.70, .D1_r = 14.0, .r1 = 0},
        .data[3] = {0},
        .data_count = 3
    }, // dr = 9
    {
        .data[0] = {.simbol = 6000, .D = 26, .B = 8, .r = 0.5, .C = 3.60, .Ca = 2.0, .D1_r = 12.2, .r1 = 0.3},
        .data[1] = {.simbol = 6200, .D = 30, .B = 9, .r = 1.0, .C = 4.75, .Ca = 2.7, .D1_r = 15.0, .r1 = 0.6},
        .data[2] = {.simbol = 6300, .D = 35, .B = 11, .r = 1.0, .C = 6.35, .Ca = 3.8, .D1_r = 15.0, .r1 = 0.6},
        .data[3] = {0},
        .data_count = 3
    }, // dr = 10
    {
        .data[0] = {.simbol = 6001, .D = 28, .B = 8, .r = 0.5, .C = 4.00, .Ca = 2.27, .D1_r = 14.2, .r1 = 0.3},
        .data[1] = {.simbol = 6201, .D = 32, .B = 10, .r = 1.0, .C = 5.40, .Ca = 3.00, .D1_r = 17.0, .r1 = 0.6},
        .data[2] = {.simbol = 6301, .D = 37, .B = 12, .r = 1.5, .C = 7.60, .Ca = 4.73, .D1_r = 18.0, .r1 = 1.0},
        .data[3] = {0},
        .data_count = 3
    }, // dr = 12
    {
        .data[0] = {.simbol = 6002, .D = 32, .B = 9, .r = 0.5, .C = 4.40, .Ca = 2.55, .D1_r = 20.2, .r1 = 0.3},
        .data[1] = {.simbol = 6202, .D = 35, .B = 11, .r = 1.0, .C = 6.10, .Ca = 3.60, .D1_r = 20.0, .r1 = 0.6},
        .data[2] = {.simbol = 6302, .D = 42, .B = 13, .r = 1.5, .C = 8.90, .Ca = 5.50, .D1_r = 21.0, .r1 = 1.0},
        .data[3] = {0},
        .data_count = 3
    }, // dr = 15
    {
        .data[0] = {.simbol = 6003, .D = 35, .B = 10, .r = 0.5, .C = 4.70, .Ca = 2.80, .D1_r = 19.2, .r1 = 0.3},
        .data[1] = {.simbol = 6203, .D = 40, .B = 12, .r = 1.0, .C = 7.50, .Ca = 4.60, .D1_r = 22.0, .r1 = 0.6},
        .data[2] = {.simbol = 6303, .D = 47, .B = 14, .r = 1.5, .C = 10.60, .Ca = 6.70, .D1_r = 23.0, .r1 = 1.0},
        .data[3] = {.simbol = 6403, .D = 62, .B = 17, .r = 2.0, .C = 18.0, .Ca = 12.10, .D1_r = 27.0, .r1 = 1.0},
        .data_count = 4
    }, // dr = 17
    {
        .data[0] = {.simbol = 6004, .D = 42, .B = 12, .r = 1.0, .C = 7.40, .Ca = 4.6, .D1_r = 24.0, .r1 = 0.6},
        .data[1] = {.simbol = 6204, .D = 47, .B = 14, .r = 1.5, .C = 10.0, .Ca = 6.3, .D1_r = 25.0, .r1 = 1.0},
        .data[2] = {.simbol = 6304, .D = 52, .B = 15, .r = 2.0, .C = 12.50, .Ca = 8.0, .D1_r = 30.0, .r1 = 1.0},
        .data[3] = {.simbol = 6404, .D = 72, .B = 19, .r = 2.0, .C = 24.00, .Ca = 17.0, .D1_r = 30.0, .r1 = 1.0},
        .data_count = 4
    }, // dr = 20
    {
        .data[0] = {.simbol = 6005, .D = 47, .B = 12, .r = 1.0, .C = 7.9, .Ca = 5.1, .D1_r = 29.0, .r1 = 0.6},
        .data[1] = {.simbol = 6205, .D = 52, .B = 15, .r = 1.5, .C = 11.0, .Ca = 7.1, .D1_r = 31.0, .r1 = 1.0},
        .data[2] = {.simbol = 6305, .D = 62, .B = 17, .r = 2.0, .C = 17.6, .Ca = 11.6, .D1_r = 33.0, .r1 = 1.0},
        .data[3] = {.simbol = 6405, .D = 80, .B = 21, .r = 2.5, .C = 29.2, .Ca = 20.8, .D1_r = 37.0, .r1 = 1.5},
        .data_count = 4
    }, // dr = 25
    {
        .data[0] = {.simbol = 6006, .D = 55, .B = 13, .r = 1.5, .C = 10.4, .Ca = 7.0, .D1_r = 35.0, .r1 = 1.0},
        .data[1] = {.simbol = 6206, .D = 62, .B = 16, .r = 1.5, .C = 15.3, .Ca = 12.2, .D1_r = 36.0, .r1 = 1.0},
        .data[2] = {.simbol = 6306, .D = 72, .B = 19, .r = 2.0, .C = 23.4, .Ca = 16.0, .D1_r = 38.0, .r1 = 1.0},
        .data[3] = {.simbol = 6406, .D = 90, .B = 23, .r = 2.5, .C = 37.2, .Ca = 27.2, .D1_r = 42.0, .r1 = 1.5},
        .data_count = 4
    }, // dr = 30

    //.data[0] = {.simbol = 0, .D = 0, .B = 0, .r = 0, .C = 0, .Ca = 0, .D1_r = 0, .r1 = 0},

    {
        .data[0] = {.simbol = 6007, .D = 62, .B = 14, .r = 1.5, .C = 12.5, .Ca = 8.7, .D1_r = 40, .r1 = 1.0},
        .data[1] = {.simbol = 6207, .D = 72, .B = 17, .r = 2.0, .C = 20.0, .Ca = 14.0, .D1_r = 43, .r1 = 1.0},
        .data[2] = {.simbol = 6307, .D = 80, .B = 21, .r = 2.5, .C = 26.0, .Ca = 18.3, .D1_r = 45, .r1 = 1.5},
        .data[3] = {.simbol = 6407, .D = 100, .B = 25, .r = 2.5, .C = 43.6, .Ca = 31.9, .D1_r = 47, .r1 = 1.5},
        .data_count = 4
    }, // dr = 35
    {
        .data[0] = {.simbol = 6008, .D = 68, .B = 15, .r = 1.5, .C = 13.2, .Ca = 9.5, .D1_r = 45, .r1 = 1.0},
        .data[1] = {.simbol = 6208, .D = 80, .B = 18, .r = 2.0, .C = 25.6, .Ca = 18.2, .D1_r = 48, .r1 = 1.0},
        .data[2] = {.simbol = 6308, .D = 90, .B = 23, .r = 2.5, .C = 32.0, .Ca = 22.8, .D1_r = 50, .r1 = 1.5},
        .data[3] = {.simbol = 6408, .D = 110, .B = 27, .r = 3.0, .C = 50.0, .Ca = 37.5, .D1_r = 53, .r1 = 2.0},
        .data_count = 4
    }, // dr = 40
    {
        .data[0] = {.simbol = 6009, .D = 75, .B = 16, .r = 1.5, .C = 16.5, .Ca = 12.4, .D1_r = 50, .r1 = 1.0},
        .data[1] = {.simbol = 6209, .D = 85, .B = 19, .r = 2.0, .C = 25.6, .Ca = 18.2, .D1_r = 53, .r1 = 1.0},
        .data[2] = {.simbol = 6309, .D = 85, .B = 25, .r = 2.5, .C = 41.5, .Ca = 30.5, .D1_r = 55, .r1 = 1.2},
        .data[3] = {.simbol = 6409, .D = 100, .B = 29, .r = 3.0, .C = 60.4, .Ca = 46.4, .D1_r = 59, .r1 = 2.0},
        .data_count = 4
    }, // dr = 45
    {
        .data[0] = {.simbol = 6010, .D = 80, .B = 16, .r = 1.5, .C = 17.0, .Ca = 13.3, .D1_r = 55, .r1 = 1.0},
        .data[1] = {.simbol = 6210, .D = 90, .B = 20, .r = 2.0, .C = 27.5, .Ca = 20.2, .D1_r = 58, .r1 = 1.0},
        .data[2] = {.simbol = 6310, .D = 110, .B = 27, .r = 3.0, .C = 48.0, .Ca = 36.5, .D1_r = 62, .r1 = 2.0},
        .data[3] = {.simbol = 6410, .D = 130, .B = 41, .r = 3.5, .C = 72.1, .Ca = 56.4, .D1_r = 65, .r1 = 2.0},
        .data_count = 4
    }, // dr = 50
    {
        .data[0] = {.simbol = 6011, .D = 90,  .B = 18, .r = 2.0, .C = 22.4, .Ca = 17.3, .D1_r = 62, .r1 = 1.0},
        .data[1] = {.simbol = 6211, .D = 100, .B = 21, .r = 2.5, .C = 34.0, .Ca = 25.5, .D1_r = 65, .r1 = 1.5},
        .data[2] = {.simbol = 6311, .D = 120, .B = 29, .r = 3.0, .C = 56.0, .Ca = 42.6, .D1_r = 67, .r1 = 2.0},
        .data[3] = {.simbol = 6411, .D = 140, .B = 33, .r = 3.5, .C = 78.0, .Ca = 63.7, .D1_r = 70, .r1 = 2.0},
        .data_count = 4
    }, // dr = 55
    {
        .data[0] = {.simbol = 6012, .D = 95,  .B = 18, .r = 2.0, .C = 23.2, .Ca = 18.6, .D1_r = 67, .r1 = 1.0},
        .data[1] = {.simbol = 6212, .D = 110, .B = 22, .r = 2.5, .C = 41.1, .Ca = 31.5, .D1_r = 70, .r1 = 1.5},
        .data[2] = {.simbol = 6312, .D = 130, .B = 31, .r = 3.5, .C = 64.1, .Ca = 49.4, .D1_r = 73, .r1 = 2.0},
        .data[3] = {.simbol = 6412, .D = 150, .B = 35, .r = 3.5, .C = 85.6, .Ca = 71.4, .D1_r = 75, .r1 = 2.0},
        .data_count = 4
    }, // dr = 60
    {
        .data[0] = {.simbol = 6013, .D = 100, .B = 18, .r = 2.0, .C = 24.0, .Ca = 20.0, .D1_r = 72, .r1 = 1.0},
        .data[1] = {.simbol = 6213, .D = 120, .B = 23, .r = 2.5, .C = 45.0, .Ca = 35.0, .D1_r = 75, .r1 = 1.5},
        .data[2] = {.simbol = 6313, .D = 140, .B = 33, .r = 3.5, .C = 72.6, .Ca = 56.7, .D1_r = 78, .r1 = 2.0},
        .data[3] = {.simbol = 6413, .D = 160, .B = 37, .r = 3.5, .C = 92.6, .Ca = 78.6, .D1_r = 80, .r1 = 2.0},
        .data_count = 4
    }, // dr = 65
    {
        .data[0] = {.simbol = 6014, .D = 110, .B = 20, .r = 2.0, .C = 29.9, .Ca = 24.8, .D1_r = 77, .r1 = 1.0},
        .data[1] = {.simbol = 6214, .D = 125, .B = 24, .r = 2.5, .C = 48.8, .Ca = 38.2, .D1_r = 80, .r1 = 1.5},
        .data[2] = {.simbol = 6314, .D = 150, .B = 35, .r = 3.5, .C = 81.8, .Ca = 64.5, .D1_r = 83, .r1 = 2.0},
        .data[3] = {.simbol = 6414, .D = 180, .B = 42, .r = 4.0, .C = 113.0, .Ca = 107.0, .D1_r = 87, .r1 = 2.5},
        .data_count = 4
    }, // dr = 70
    {
        .data[0] = {.simbol = 6015, .D = 115, .B = 20, .r = 2.0, .C = 31.0,  .Ca = 26.6,  .D1_r = 82, .r1 = 1.0},
        .data[1] = {.simbol = 6215, .D = 130, .B = 25, .r = 2.5, .C = 52.0,  .Ca = 42.0,  .D1_r = 85, .r1 = 1.5},
        .data[2] = {.simbol = 6315, .D = 160, .B = 37, .r = 3.5, .C = 89.0,  .Ca = 73.0,  .D1_r = 88, .r1 = 2.0},
        .data[3] = {.simbol = 6415, .D = 190, .B = 45, .r = 4.0, .C = 120.0, .Ca = 117.0, .D1_r = 92, .r1 = 2.5},
        .data_count = 4
    }, // dr = 75
    {
        .data[0] = {.simbol = 6016, .D = 125, .B = 22, .r = 2.0, .C = 37.5,  .Ca = 32.0,  .D1_r = 87, .r1 = 1.0},
        .data[1] = {.simbol = 6216, .D = 140, .B = 26, .r = 3.0, .C = 57.0,  .Ca = 45.5,  .D1_r = 92, .r1 = 2.0},
        .data[2] = {.simbol = 6316, .D = 170, .B = 39, .r = 3.5, .C = 96.5,  .Ca = 81.7,  .D1_r = 93, .r1 = 2.0},
        .data[3] = {.simbol = 6416, .D = 200, .B = 46, .r = 4.0, .C = 128.0, .Ca = 127.0, .D1_r = 97, .r1 = 2.5},
        .data_count = 4
    }, // dr = 80
    {
        .data[0] = {.simbol = 6017, .D = 130, .B = 22, .r = 2.0, .C = 38.5,  .Ca = 34.0,  .D1_r = 92,  .r1 = 1.0},
        .data[1] = {.simbol = 6217, .D = 150, .B = 28, .r = 3.0, .C = 65.4,  .Ca = 54.1,  .D1_r = 97,  .r1 = 2.0},
        .data[2] = {.simbol = 6317, .D = 180, .B = 41, .r = 4.0, .C = 104.0, .Ca = 91.0,  .D1_r = 100, .r1 = 2.5},
        .data[3] = {.simbol = 6417, .D = 210, .B = 52, .r = 5.0, .C = 136.0, .Ca = 138.0, .D1_r = 105, .r1 = 3.0},
        .data_count = 4
    } // dr = 85


};

static int get_dr_index(int dr) {
    switch(dr) {
        case 7:     return 0;
        case 8:     return 1;
        case 9:     return 2;
        case 10:    return 3;
        case 12:    return 4;
        case 15:    return 5;
        case 17:    return 6;
        case 20:    return 7;
        case 25:    return 8;
        case 30:    return 9;
        case 35:    return 10;
        case 40:    return 11;
        case 45:    return 12;
        case 50:    return 13;
        case 55:    return 14;
        case 60:    return 15;
        case 65:    return 16;
        case 70:    return 17;
        case 75:    return 18;
        case 80:    return 19;
        case 85:    return 20;
    } // switch
    return -1;
} // get dr index

static real_t e_arr[9] = {
    0.19, 0.22, 0.26, 0.28, 0.30, 0.34, 0.38, 0.42, 0.44
};
static real_t fa_by_co_arr[9] = {
    0.014, 0.028, 0.056, 0.084, 0.11, 0.17, 0.28, 0.42, 0.56
};
static real_t Y_arr[9] = {
    2.30, 1.99, 1.71, 1.55, 1.45, 1.31, 1.15, 1.04, 1.00
};

INTERNAL_FUNCTION struct anexa7_dr_data* anexa7_get_dr_data(int dr) {
    return &data[get_dr_index(dr)];
}

static int get_closest_index_from_e_arr(real_t value, int index1, int index2) {
    real_t value1 = fa_by_co_arr[index1];
    real_t value2 = fa_by_co_arr[index2];

    real_t delta_1 = value - value1;
    real_t delta_2 = value2 - value;
    

    if(delta_1 > delta_2) {
        return index2;
    }
    else {
        return index1;
    }
    return -1;
}
INTERNAL_FUNCTION real_t anexa7_approx_e(real_t fa_by_co) {

    if(fa_by_co <= fa_by_co_arr[0]) {
        //printf("Returned first index\n");
        return e_arr[0];
    }
    else if (fa_by_co >= fa_by_co_arr[0] && fa_by_co <= fa_by_co_arr[1]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 0, 1)];
    }
    else if (fa_by_co >= fa_by_co_arr[1] && fa_by_co <= fa_by_co_arr[2]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 1, 2)];
    }
    else if (fa_by_co >= fa_by_co_arr[2] && fa_by_co <= fa_by_co_arr[3]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 2, 3)];
    }
    else if (fa_by_co >= fa_by_co_arr[3] && fa_by_co <= fa_by_co_arr[4]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 3, 4)];
    }
    else if (fa_by_co >= fa_by_co_arr[4] && fa_by_co <= fa_by_co_arr[5]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 4, 5)];
    }
    else if (fa_by_co >= fa_by_co_arr[5] && fa_by_co <= fa_by_co_arr[6]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 5, 6)];
    }
    else if (fa_by_co >= fa_by_co_arr[6] && fa_by_co <= fa_by_co_arr[7]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 6, 7)];
    }
    else if (fa_by_co >= fa_by_co_arr[7] && fa_by_co <= fa_by_co_arr[8]) {
        return e_arr[get_closest_index_from_e_arr(fa_by_co, 7, 8)];
    }
    else if (fa_by_co >= fa_by_co_arr[8]) {
        return e_arr[8];
    }
    return -1;
} // approx e

INTERNAL_FUNCTION real_t anexa7_get_Y(real_t e) {
    if(e == e_arr[0]) return Y_arr[0];
    else if(e == e_arr[1]) return Y_arr[1];
    else if(e == e_arr[2]) return Y_arr[2];
    else if(e == e_arr[3]) return Y_arr[3];
    else if(e == e_arr[4]) return Y_arr[4];
    else if(e == e_arr[5]) return Y_arr[5];
    else if(e == e_arr[6]) return Y_arr[6];
    else if(e == e_arr[7]) return Y_arr[7];
    else if(e == e_arr[8]) return Y_arr[8];
}
