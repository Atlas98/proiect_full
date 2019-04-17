#include <structs.h>
#include <internal.h>
#include <data/anexe/anexe.h>
#include <data/data.h>
#include <math.h>

// acos(-1) = pi;
#define PI acos(-1.0)

EXPORT_FUNCTION void cap6_get_data(struct data* data) {
    struct base_data* base = &data->base_data;
    struct capitol_1_data* cap1 = &data->puteri_si_randamente;
    struct capitol_2_data* cap2 = &data->calcul_curele;
    struct capitol_3_data* cap3 = &data->dimensionare_arbore_1;
    struct capitol_4_data* cap4 = &data->calcul_rulmenti;
    struct capitol_5_data* cap5 = &data->pene_paralele;
    struct capitol_6_data* cap6 = &data->verificare_arbore;

    real_t drotor_cube = cap3->Drotor * cap3->Drotor * cap3->Drotor;
    cap6->sigma_i_max_3 = 32.0*cap3->M_i3/PI/drotor_cube;
    cap6->sigma_iv_3 = cap6->sigma_i_max_3;

    cap6->tau_t_max_3 = 16*cap3->M_t/PI/drotor_cube;
    cap6->tau_tv_3 = cap6->tau_t_max_3;

    struct anexa9_coeficienti_concentratori concentratori = anexa9_get_concentratori(cap3->sigma_r);
    cap6->beta_k_sigma_3 = concentratori.beta_k_sigma;
    cap6->beta_k_tau_3 = concentratori.beta_k_tau;
}

EXPORT_FUNCTION void cap6_print_data(void* filePtr, struct data* data) {
    fprintf(filePtr, "\n");
    fprintf(filePtr, "===========================================================\n");
    fprintf(filePtr, "=============== Capitolul 6 ===============================\n");

    fprintf(filePtr, "===========================================================\n");

}