#include <internal.h>
#include <data/anexe/anexe.h>

// P_me table
static const real_t tabel2_1[30] = {
    5.5, 7.5, 8, 10, 11, 12.5, 15, 16, 18.5, 20, 22, 25, 30, 32, 37, 40, 45, 50, 55, 63, 75,
    80, 100, 110, 125, 150, 160, 185, 200, 220
};

// N_me table
static const real_t tabel2_2[4] = {
    750, 1000, 1500, 3000
};

INTERNAL_FUNCTION real_t anexa2_retrieve_P_me(real_t P) {
    int sizeof_tabel2_1 = sizeof(tabel2_1) / sizeof(real_t);
    for(int i = 0; i < sizeof_tabel2_1; i++) {
        real_t value = tabel2_1[i];
        if(value > P) return value;
    }
    return 0;
}

INTERNAL_FUNCTION real_t anexa2_retrieve_N_me(real_t N_I) {
    int sizeof_tabel2_2 = sizeof(tabel2_2) / sizeof(real_t);
    for(int i = 0; i < sizeof_tabel2_2; i++) {
        real_t value = tabel2_2[i];
        if(value > N_I) return value;
    }
    return 0;
}