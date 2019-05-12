#include <structs.h>
#include <internal.h>
#include <data/anexe/anexe.h>
#include <data/data.h>
#include <math.h>

// acos(-1) = pi;
#define PI acos(-1.0)

EXPORT_FUNCTION void cap6_get_data(struct data* data) {
    struct base_values* base = &data->base_data;
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



	// niste calcule pag 25
	// dr dperii dumar drotor
	real_t dr_calc = (cap3->Dr*cap3->Dr*cap3->Dr*cap3->Dr * cap3->Lr);
	real_t dperii_calc = (cap3->Dperii*cap3->Dperii*cap3->Dperii*cap3->Dperii * cap3->Lperii);
	real_t dumar_calc = (cap3->Dumar*cap3->Dumar*cap3->Dumar*cap3->Dumar * cap3->Lumar);
	real_t drotor_calc = (cap3->Drotor*cap3->Drotor*cap3->Drotor*cap3->Drotor * cap3->Lrotor);

	real_t temp = (dr_calc + dperii_calc + dumar_calc + drotor_calc) / (base->a + base->b);
	cap6->d_p_F = pow(temp, 1.0 / 4.0);

	cap6->I_F = PI * cap6->d_p_F * cap6->d_p_F * cap6->d_p_F * cap6->d_p_F / 64.0;

	temp = sqrt(pow(base->a, 3) * pow((base->a + 2 * base->b), 3)) * base->b * base->F / 2.1 / 100000 / 9 / sqrt(3)/(base->a+base->b)/cap6->I_F;
	cap6->f_F_max = temp;

}

EXPORT_FUNCTION void cap6_print_data(void* filePtr, struct data* data) {
	struct capitol_6_data* cap6 = &data->verificare_arbore;

    fprintf(filePtr, "\n");
    fprintf(filePtr, "===========================================================\n");
    fprintf(filePtr, "=============== Capitolul 6 ===============================\n");
	fprintf(filePtr, "D_p,f = %lf\n", cap6->d_p_F);
	fprintf(filePtr, "If = %lf\n", cap6->I_F);
	fprintf(filePtr, "f_F,max = %lf\n", cap6->f_F_max);
	/*fprintf(filePtr, "x9 = %lf\n",);
	fprintf(filePtr, "Psi F1 = %lf\n",);
	fprintf(filePtr, "Psi F5 = %lf\n",);	 */


    fprintf(filePtr, "===========================================================\n");

}