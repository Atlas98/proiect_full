#include <internal.h>
#include <data/anexe/anexe.h>
#include <exports.h>

// 20 elements, 5 columns (bp, hp, lp_min, lp_max)
const real_t tabel8_1[20][4] = {
    {2, 2, 6, 20}, // row 1
    {3, 3, 6, 36}, // row 2
    {4, 4, 8, 45}, // row 3
    {5, 5, 10, 56}, // row 4
    {6, 6, 14, 70}, // row 5
    {8, 7, 18, 90}, // row 6
    {10, 8, 22, 110}, // row 7
    {12, 8, 28, 140}, // row 8
    {14, 9, 36, 160}, // row 9
    {16, 10, 45, 180}, // row 10
    {18, 11, 50, 200}, // row 11
    {20, 12, 56, 220}, // row 12
    {22, 14, 63, 250}, // row 13
    {25, 14, 70, 280}, // row 14
    {28, 16, 80, 320}, // row 15
    {32, 18, 90, 360}, // row 16
    {36, 20, 100, 400}, // row 17
    {40, 22, 100, 400}, // row 18
    {45, 25, 110, 450}, // row 19
    {50, 28, 125, 500}, // row 20
}; // tabel 8_1

static void extract_to_struct(struct anexa8_pana_data* ptr, int row) {
    ptr->bp = tabel8_1[row][0];
    ptr->hp = tabel8_1[row][1];
    ptr->Lp_min = tabel8_1[row][2];
    ptr->Lp_max = tabel8_1[row][3];
}

INTERNAL_FUNCTION struct anexa8_pana_data anexa8_get_pana_data(real_t dca) {
    struct anexa8_pana_data data;
    if(dca >= 6 && dca <= 8) {
        extract_to_struct(&data, 0);
    }
    else if(dca >= 8 && dca <= 8) extract_to_struct(&data, 1);
    else if(dca >= 10 && dca <= 10) extract_to_struct(&data, 2);
    else if(dca >= 12 && dca <= 17) extract_to_struct(&data, 3);
    else if(dca >= 17 && dca <= 22) extract_to_struct(&data, 4);
    else if(dca >= 22 && dca <= 30) extract_to_struct(&data, 5);
    else if(dca >= 30 && dca <= 38) extract_to_struct(&data, 6);
    else if(dca >= 38 && dca <= 44) extract_to_struct(&data, 7);
    else if(dca >= 44 && dca <= 50) extract_to_struct(&data, 8);
    else if(dca >= 50 && dca <= 58) extract_to_struct(&data, 9);
    else if(dca >= 58 && dca <= 65) extract_to_struct(&data, 10);
    else if(dca >= 65 && dca <= 75) extract_to_struct(&data, 11);
    else if(dca >= 75 && dca <= 85) extract_to_struct(&data, 12);
    else if(dca >= 85 && dca <= 95) extract_to_struct(&data, 13);
    else if(dca >= 95 && dca <= 110) extract_to_struct(&data, 14);
    else if(dca >= 110 && dca <= 130) extract_to_struct(&data, 15);
    else if(dca >= 130 && dca <= 150) extract_to_struct(&data, 16);
    else if(dca >= 150 && dca <= 170) extract_to_struct(&data, 17);
    else if(dca >= 170 && dca <= 200) extract_to_struct(&data, 18);
    else if(dca >= 200 && dca <= 230) extract_to_struct(&data, 19);

    return data;
} // func
