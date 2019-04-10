#include <internal.h>
#include <data/anexe/anexe.h>
#include <exports.h>
#include <math.h>

#define TABLE_SIZE 65
real_t det_table[TABLE_SIZE] = {
    4.5, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
    18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 25.5, 27.5, 29, 32, 33, 35,
    37, 38.5, 41.5, 44.5, 46.5, 48, 51, 54, 56, 58, 59, 61, 64, 66,
    67.5, 70.5, 73.5, 80.5, 85.5, 90.5, 94.5, 99.5, 104.5, 109.5, 114.5,
    119.5, 124.5, 128, 133, 138, 143, 148, 153, 158, 163, 173
};

INTERNAL_FUNCTION real_t anexa6_get_Det(real_t dca) {
    real_t det = 0;

    for(int i = 0; i < TABLE_SIZE; i++) {
        if(det_table[i] >= dca) {
            det = det_table[i];
            break;
        }
    } // for

    return ceil(det);
}