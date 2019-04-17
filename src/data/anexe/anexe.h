#ifndef _ANEXE_H_
#define _ANEXE_H_
#include <exports.h>
#include <structs.h>
#define DEBUG_ANEXA 1

/* anexa 2 */
INTERNAL_FUNCTION real_t anexa2_retrieve_P_me (real_t P_IC);
INTERNAL_FUNCTION real_t anexa2_retrieve_N_me (real_t NI);

/* anexa 3 */
INTERNAL_FUNCTION int    anexa3_get_tip_curea(real_t N_ME, real_t P_IC);
INTERNAL_FUNCTION real_t anexa3_lookup_Dp2    (int tip_curea, real_t Dp1);
INTERNAL_FUNCTION real_t anexa3_approx_Lp     (real_t Lp);
INTERNAL_FUNCTION real_t anexa3_lookup_P0		(int tip_curea, real_t Dp1, real_t NI, real_t I_TCT);
INTERNAL_FUNCTION real_t anexa3_get_CL(int tip_curea, real_t Lp);
INTERNAL_FUNCTION real_t anexa3_get_Cz(real_t zo);
INTERNAL_FUNCTION real_t anexa3_approx_z(real_t z);

/* anexa 4 */
enum tabel4_material {
    OTEL_CARBON_DE_UZ_GENERAL = 1,
    OTEL_CARBON_DE_CALITATE   = 2,
    OTEL_ALIAT                = 3
};
enum tabel4_simbol {
    OL_42  = 0,
    OL_50  = 1,
    OL_60  = 2,

    OLC_15 = 3,
    OLC_35 = 4,
    OLC_45 = 5,
    
    _18_MoCr_10 =   6,
    _18_MoCrNi_20 = 7,
    _40_Cr_10     = 8,
    _41_MoCr_11   = 9
};
enum tabel4_tratament {
    tratament_null = 0,
    tratament_N    = 1, // tratament de normalizare
    tratament_C    = 2, // tratament de cementare
    tratament_I    = 3  // tratament de imbunatatire
};

struct anexa4_data {
    enum tabel4_material  material;
    enum tabel4_simbol    simbol;
    enum tabel4_tratament tratament;
    // tensiuni limita
    int sigma_r;
    int sigma_c;
    int sigma_l;
    int tau_l;
    int tau_c;

    // tensiuni admisibile
    int sigma_iaI;
    int sigma_iaII;
    int sigma_iaIII;
};

INTERNAL_FUNCTION struct anexa4_data anexa4_retrieve_data(enum tabel4_material material, enum tabel4_simbol simbol, enum tabel4_tratament tratament);

/* anexa 5 */
enum toleranta {
    toleranta_j6 = 0,
    toleranta_k6 = 1,
    toleranta_m6 = 2
};

struct anexa5_data {
    int Dca;            // mm
    int Lca_scurt;      // mm
    int Lca_lung;       // mm
};

INTERNAL_FUNCTION struct anexa5_data anexa5_retrieve_from_Dca(int Dca);


/* anexa 6 */
INTERNAL_FUNCTION real_t anexa6_get_Det(real_t det);


/* anexa 7 */

// tabelul 7.1 data as struct
struct anexa7_simbol_data {
    int simbol;
    real_t D;
    real_t B;
    real_t r;
    real_t C;
    real_t Ca;
    real_t D1_r;
    real_t r1;
};
struct anexa7_dr_data {
    struct anexa7_simbol_data data[4]; 
    int data_count;  // how many items from data[] are not null
};
INTERNAL_FUNCTION struct anexa7_dr_data* anexa7_get_dr_data(int dr);

INTERNAL_FUNCTION real_t anexa7_approx_e(real_t fa_by_co);
INTERNAL_FUNCTION real_t anexa7_get_Y(real_t e);

/* anexa 8 */
struct anexa8_pana_data {
    real_t bp;
    real_t hp;
    real_t Lp_min;
    real_t Lp_max;
};

INTERNAL_FUNCTION struct anexa8_pana_data anexa8_get_pana_data(real_t dca);


/* anexa 9 */
struct anexa9_coeficienti_concentratori {
	real_t beta_k_sigma;
	real_t beta_k_tau;
};
INTERNAL_FUNCTION struct anexa9_coeficienti_concentratori anexa9_get_concentratori(real_t sigma_r);


#endif