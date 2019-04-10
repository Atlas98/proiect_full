#include <internal.h>
#include <data/anexe/anexe.h>
#include <exports.h>

// lookup data for tabel4_1
const int tabel4_1_lookup_data[13][12] = {
    {OTEL_CARBON_DE_UZ_GENERAL, OL_42, tratament_null, 420, 230, 200, 115, 140, 140, 70, 40},
    {OTEL_CARBON_DE_UZ_GENERAL, OL_50, tratament_null, 500, 270, 240, 140, 165, 170, 75, 45},
    {OTEL_CARBON_DE_UZ_GENERAL, OL_60, tratament_null, 600, 310, 280, 160, 190, 200, 95, 55},

    {OTEL_CARBON_DE_CALITATE, OLC_15, tratament_N, 390, 230, 170, 100, 140, 130, 60, 35},
    {OTEL_CARBON_DE_CALITATE, OLC_15, tratament_C, 500, 300, 220, 125, 180, 170, 75, 45},
    {OTEL_CARBON_DE_CALITATE, OLC_35, tratament_N, 530, 310, 230, 130, 185, 175, 85, 50},
    {OTEL_CARBON_DE_CALITATE, OLC_35, tratament_I, 640, 420, 280, 150, 255, 210, 100, 60},
    {OTEL_CARBON_DE_CALITATE, OLC_45, tratament_N, 610, 360, 260, 155, 220, 200, 95 ,55},
    {OTEL_CARBON_DE_CALITATE, OLC_45, tratament_I, 700, 480, 300, 170, 290, 230, 110, 65},

    {OTEL_ALIAT, _18_MoCr_10  , tratament_C, 790, 540, 340, 190, 325, 260, 120, 70},
    {OTEL_ALIAT, _18_MoCrNi_20, tratament_C, 830, 590, 440, 240, 355, 275, 130, 75},
    {OTEL_ALIAT, _40_Cr_10    , tratament_I, 980, 790, 360, 200, 475, 325, 150, 90},
    {OTEL_ALIAT, _41_MoCr_11  , tratament_I, 1080, 880, 380, 300, 530, 360, 170, 100},
};

// iterate tabel4_1 lookup data to struct
static void extract_to_struct(struct anexa4_data* data, int index) {
    data->material    = tabel4_1_lookup_data[index][0];
    data->simbol      = tabel4_1_lookup_data[index][1];
    data->tratament   = tabel4_1_lookup_data[index][2];

    data->sigma_r     = tabel4_1_lookup_data[index][3];
    data->sigma_c     = tabel4_1_lookup_data[index][4];
    data->sigma_l     = tabel4_1_lookup_data[index][5];
    data->tau_l       = tabel4_1_lookup_data[index][6];
    data->tau_c       = tabel4_1_lookup_data[index][7];
    data->sigma_iaI   = tabel4_1_lookup_data[index][8];
    data->sigma_iaII  = tabel4_1_lookup_data[index][9];
    data->sigma_iaIII = tabel4_1_lookup_data[index][10];
}
INTERNAL_FUNCTION struct anexa4_data anexa4_retrieve_data(enum tabel4_material material, enum tabel4_simbol simbol, enum tabel4_tratament tratament) {
	struct anexa4_data data = { 0 };
    switch(material) {
        case OTEL_CARBON_DE_UZ_GENERAL:
            if     (simbol == OL_42) extract_to_struct(&data, 0);
            else if(simbol == OL_50) extract_to_struct(&data, 1);
            else if(simbol == OL_60) extract_to_struct(&data, 2);
        break;
        case OTEL_CARBON_DE_CALITATE:
            if      (simbol == OLC_15 && tratament == tratament_N)  extract_to_struct(&data, 3);
            else if (simbol == OLC_15 && tratament == tratament_C)  extract_to_struct(&data, 4);
            else if (simbol == OLC_35 && tratament == tratament_N)  extract_to_struct(&data, 5);
            else if (simbol == OLC_35 && tratament == tratament_I)  extract_to_struct(&data, 6);
            else if (simbol == OLC_45 && tratament == tratament_N)  extract_to_struct(&data, 7);
            else if (simbol == OLC_45 && tratament == tratament_I)  extract_to_struct(&data, 8);
        break;
        case OTEL_ALIAT:
            if     (simbol == _18_MoCr_10)   extract_to_struct(&data, 9);
            else if(simbol == _18_MoCrNi_20) extract_to_struct(&data, 10);
            else if(simbol == _40_Cr_10)     extract_to_struct(&data, 11);
            else if(simbol == _41_MoCr_11)   extract_to_struct(&data, 12);
        break;
    }
    return data;
} 

