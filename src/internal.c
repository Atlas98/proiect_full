#include <internal.h>
#include <exports.h>
#include <structs.h>
#include <data/data.h>
#include <console_interface.h>

// TODO: keep this updated?
#if EXPORT_FUNCTIONS_TABLE

const struct DataOps data_ops = {
    .get_data_struct = get_data_struct,
	.data_create = data_create,
	.data_free = data_free,
	.data_load_from_file = data_load_from_file,
	.data_save_to_file = data_save_to_file,

	.base_values_init = base_values_init,
	.base_values_create = base_values_create,
	.base_find_F = base_find_F,
	.base_pick_a = base_pick_a,
	.base_pick_c = base_pick_c,
	.base_print_data = base_print_data,	// print data, optionally to file, else stdout

	.cap1_get_data = cap1_get_data,				// extract initial capitol_1_data  
	.cap1_choose_P_me = cap1_choose_P_me,   // pick a value for P_me, anexa A2.1
	.cap1_choose_N_me = cap1_choose_N_me,		// pick a value for N_me, anexa 2.1
	.cap1_lookup_P_me = cap1_lookup_P_me,				// lookup data from anexa2.c
	.cap1_lookup_N_me = cap1_lookup_N_me,				// lookup data from anexa2.c
	.cap1_calcul_turatii = cap1_calcul_turatii,				// computations
	.cap1_calcul_momente_rasucire = cap1_calcul_momente_rasucire,				// computations
	.cap1_prompt_choose_P_me = cap1_prompt_choose_P_me,				// prompt to pick value for N_me, anexa A2.2
	.cap1_prompt_choose_N_me = cap1_prompt_choose_N_me,				// prompt to pick a value for N_me
	.cap1_print_data = cap1_print_data,		// print data (to file if prefer, else to stdout)
	.cap1_print_to_buffer = cap1_print_to_buffer, // print to a char buffer

	.cap2_get_data = cap2_get_data,				// compute initial data for cap 2
	.cap2_compute = cap2_compute,				// update() 'like function
	.cap2_compute_L_p = cap2_compute_L_p,				// compute Lp with given values
	.cap2_choose_tip_curea = cap2_choose_tip_curea,	// set tip_curea
	.cap2_choose_D_p1 = cap2_choose_D_p1,		// set D_p1
	.cap2_choose_Aprel = cap2_choose_Aprel,	// set A_prel
	.cap2_choose_L_p = cap2_choose_L_p,		// set L_p
	.cap2_choose_P_0 = cap2_choose_P_0,		// set P_0
	.cap2_choose_Q = cap2_choose_Q,		// forta de pretensionare
	.cap2_prompt_choose_tip_curea = cap2_prompt_choose_tip_curea,
	.cap2_prompt_choose_D_p1 = cap2_prompt_choose_D_p1,
	.cap2_prompt_choose_Aprel = cap2_prompt_choose_Aprel,
	.cap2_prompt_choose_L_p = cap2_prompt_choose_L_p,
	.cap2_prompt_choose_P_0 = cap2_prompt_choose_P_0,
	.cap2_prompt_choose_Q = cap2_prompt_choose_Q,
	.cap2_lookup_tip_curea = cap2_lookup_tip_curea,
	.cap2_lookup_P_0 = cap2_lookup_P_0,
	.cap2_calcul_numar_curele = cap2_calcul_numar_curele,
	.cap2_calcul_verificare_functionare_curele = cap2_calcul_verificare_functionare_curele,
	.cap2_calcul_forta_utila_si_de_pretensionare = cap2_calcul_forta_utila_si_de_pretensionare,
	.cap2_print_data = cap2_print_data,	// print data(to file if prefer, else to stdout)

	/* capitol 3 funcs */
	.cap3_compute_data = cap3_compute_data,
	.cap3_retrieve_with_Dca = cap3_retrieve_with_Dca,

	.cap3_set_material = cap3_set_material,
	.cap3_set_simbol = cap3_set_simbol,
	.cap3_set_tratament = cap3_set_tratament,
	.cap3_set_Dca = cap3_set_Dca,
	.cap3_set_Lca = cap3_set_Lca,
	.cap3_set_Det = cap3_set_Det,
	.cap3_set_Dr = cap3_set_Dr,

	.cap3_prompt_set_material = cap3_prompt_set_material,
	.cap3_prompt_set_simbol = cap3_prompt_set_simbol,
	.cap3_prompt_set_tratament = cap3_prompt_set_tratament,
	.cap3_prompt_choose_Dca = cap3_prompt_choose_Dca,
	.cap3_prompt_choose_Lca = cap3_prompt_choose_Lca,

	.cap3_prompt_set_Det = cap3_prompt_set_Det,
	.cap3_prompt_set_Dr = cap3_prompt_set_Dr,
	//.cap3_auto_set_Det)(data_ptr db)
	//.cap3_auto_set_Dr)(data_ptr db),
	.cap3_solve_dimensions = cap3_solve_dimensions,            // with given Det, Dca and Dr, solve the remaining dimenions

	.cap3_print_data = cap3_print_data
};


EXPORT_FUNCTION const struct DataOps* get_data_ops() {
    return &data_ops;
}

#endif

















