#include <internal.h>
#include <data/anexe/anexe.h>

static const int tabel5_1_lookup[46][3] = {
    // {Dca, Ica_scurt, Ica_lung}
    {6, 0, 0},
    {7, 0, 0},
    {8, 0, 0},
    {9, 0, 0},
    {10, 20, 23},
    {11, 20, 23},
    {12, 25, 30},
    {14, 25, 30},
    {16, 28, 40},
    {18, 28, 40},
    {19, 28, 40},
    {20, 36, 50},
    {22, 36, 50},
    {24, 36, 50},
    {25, 42, 60},
    {28, 42, 60},
    {30, 58, 80},
    {32, 58, 80},
    {35, 58, 80},
    {38, 58, 80},
    {40, 82, 110},
    {42, 82, 110},
    {45, 82, 110},

    {48, 82, 110},
    {50, 82, 110},
    {55, 82, 110},
    {56, 82, 110},
    {60, 105, 140},
    {63, 105, 140},
    {65, 105, 140},
    {70, 105, 140},
    {71, 105, 140},
    {75, 105, 140},
    {80, 130, 170},
    {85, 130, 170},
    {90, 130, 170},
    {95, 130, 170},
    {100, 165, 210},
    {110, 165, 210},
    {120, 165, 210},
    {125, 165, 210},
    {130, 200, 250},
    {140, 200, 250},
    {150, 200, 250},
    {160, 240, 300},
    {170, 240, 300}
};
static inline int Dca_to_index(int Dca) {
    switch(Dca) {
        case 6:       return 0;
        case 7:       return 1;
        case 8:       return 2;
        case 9:       return 3;
        case 10:      return 4;
        case 11:      return 5;
        case 12:      return 6;
        case 14:      return 7;
        case 16:      return 8;
        case 18:      return 9;
        case 19:      return 10;
        case 20:      return 11;
        case 22:      return 12;
        case 24:      return 13;
        case 25:      return 14;
        case 28:      return 15;
        case 30:      return 16;
        case 32:      return 17;
        case 35:      return 18;
        case 38:      return 19;
        case 40:      return 20;
        case 42:      return 21;
        case 45:      return 22;
        case 48:      return 23;
        case 50:      return 24;
        case 55:      return 25;
        case 56:      return 26;
        case 60:      return 27;
        case 63:      return 28;
        case 65:      return 29;
        case 70:      return 30;
        case 71:      return 31;
        case 75:      return 32;
        case 80:      return 33;
        case 85:      return 34;
        case 90:      return 35;
        case 95:      return 36;
        case 100:     return 37;
        case 110:     return 38;
        case 120:     return 39;
        case 125:     return 40;
        case 130:     return 41;
        case 140:     return 42;
        case 150:     return 43;
        case 160:     return 44;
        case 170:     return 45;
        default:     return -1;
        break;
    } // switch
}
static inline void extract_data_to_struct(struct anexa5_data* data, int Dca) {
    int Dca_index = Dca_to_index(Dca);
    data->Dca       = tabel5_1_lookup[Dca_index][0];
    data->Lca_scurt = tabel5_1_lookup[Dca_index][1];
    data->Lca_lung  = tabel5_1_lookup[Dca_index][2];
}
INTERNAL_FUNCTION struct anexa5_data anexa5_retrieve_from_Dca(int Dca) {
    struct anexa5_data data = {0};
    extract_data_to_struct(&data, Dca);
    return data;
}
