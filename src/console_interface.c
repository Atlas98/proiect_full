#include <internal.h>
#include <exports.h>
#include <data/data.h>
#include <testing/test.h>
#include <stdio.h>
#include <stdlib.h>
#include "autocad/autocad.h"

#include <string.h>


// WITH THIS, YOU HAVE TO INTRODUCE BASE VALUES BY HAND, NO PROMPTS GIVEN
// USED WITH PHP
#define PROMPT_BASE_VALUES 0 // prompt base values selection

// CHOICE = didn't implement any control logic based on input on startup, for now I'll use this 
// 1 - computations
// 2 - autocad thingy
// 3 - testing (I don't have enough tests :( ))
#define CHOICE 1


static int console_main();
static int autocad_main();


// External program calls this function
EXPORT_FUNCTION void start_console_app() {

#if CHOICE == 1
	console_main();
#endif
	
#if CHOICE == 2
	FILE* fptr = fopen("desen.SCR", "w+");
	if (fptr == NULL) {
		printf("File ptr is null\n");
		return;
	}
	struct arbore_data arbore;
	
	arbore.a = 528.0;
	arbore.b = 432.0;
	arbore.c = 240.0;
	arbore.Lrotor = 480;
	arbore.Lca = 30;

	arbore.Dventilator = 50;
	arbore.Dca = 50;
	arbore.Det = 55;
	arbore.Dr = 60;
	arbore.Dperii = 65;
	arbore.Drotor = 70;
	arbore.Dumar = 75;

	autocad_generate_arbore(fptr, &arbore);

	fclose(fptr);
#endif

#if CHOICE == 3
	test_anexe_anexa7_test_struct();
	test_anexe_anexa8_get_pana_data();
#endif
}

// MAIN 
static int console_main() {
	setbuf(stdout, NULL);


	struct data* data = get_data_struct(666);
	// base data
	
	if(PROMPT_BASE_VALUES) {
		real_t cs;
		real_t pv;
		real_t nv;
		real_t itct;
		real_t ir;
		real_t l;
		real_t g;
		real_t fm;

		// No informative printf's
		scanf("%lf", &cs);
		scanf("%lf", &pv);
		scanf("%lf", &nv);
		scanf("%lf", &itct);
		scanf("%lf", &ir);
		scanf("%lf", &l);
		scanf("%lf", &g);
		scanf("%lf", &fm);

		base_values_create(data, 0, cs, pv, nv, itct, ir, l, g, fm);
	}
	else {
		base_values_init(data);
	}
	base_find_F(data);
	base_prompt_pick_a(data);
	base_prompt_pick_c(data);

	// capitolul 1
	// un capitol simplu, fara alegeri
	cap1_get_data(data);
	cap1_lookup_N_me(data);
	cap1_lookup_P_me(data);
	cap1_calcul_turatii(data);
	cap1_calcul_momente_rasucire(data);

	// capitolul 2
	// ugh, e mai ciudata incercarea asta cu compute() mai des, compute() e un fel de update
	// la inceput era mai ugly, cu multe alegeri, pana am implementat sa poti alege din anexe automat
	// si a ramas asa, merge tho
	cap2_get_data(data);
	cap2_compute(data);
	cap2_lookup_tip_curea(data);
	cap2_prompt_choose_D_p1(data);
	cap2_compute(data);
	cap2_prompt_choose_Aprel(data);
	cap2_compute(data);
	cap2_compute_L_p(data);
	cap2_compute(data);
	cap2_compute(data);
	cap2_lookup_P_0(data);

	cap2_calcul_numar_curele(data);
	cap2_calcul_verificare_functionare_curele(data);
	cap2_calcul_forta_utila_si_de_pretensionare(data);
	cap2_prompt_choose_Q(data);


	// capitolul 3
	// La dimensiuni e naspa
	cap3_prompt_set_simbol(data);
	cap3_prompt_set_tratament(data);
	cap3_compute_data(data);
	cap3_prompt_choose_Dca(data);
	cap3_retrieve_with_Dca(data);
	cap3_prompt_choose_Lca(data, 1);

	cap3_prompt_set_Det(data);
  	cap3_prompt_set_Dr(data);
	cap3_prompt_set_Dperii(data);
	cap3_prompt_set_Drotor(data);
	cap3_prompt_set_Dumar(data);
  	cap3_solve_dimensions(data); 

	// capitolul 4
	// Cel mai urat cod pe care l-am avut vreodata
	// multe simboluri, fuck shit
	cap4_get_data(data);
	cap4_prompt_set_Fa(data);
	cap4_compute(data);

	// capitolul 5
	// relativ usor
	cap5_get_data(data);
	cap5_prompt_set_Lp_a(data);
	cap5_prompt_set_Lp_b(data);
	cap5_compute(data);

	// capitolul 6
	cap6_get_data(data);

	// print or save data, or both
	base_print_data(stdout, data);
	cap1_print_data(stdout, data);
	cap2_print_data(stdout, data);
	cap3_print_data(stdout, data);
	cap4_print_data(stdout, data);
	cap5_print_data(stdout, data);
	cap6_print_data(stdout, data);

	/* IF YOU WANT TO SAVE THE DATA TO A FILE, UNCOMMENT THIS
	void* dataFileHandle = fopen("data.txt", "w+");
	base_print_data(dataFileHandle, data);
	cap1_print_data(dataFileHandle, data);
	cap2_print_data(dataFileHandle, data);
	cap3_print_data(dataFileHandle, data);
	cap4_print_data(dataFileHandle, data);
	fclose(dataFileHandle);
	*/
	
	return 1;
}

static int autocad_main() {

}