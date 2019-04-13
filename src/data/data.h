#ifndef _DATA_H_
#define _DATA_H_
#include <exports.h>
#include <structs.h>

// trigonometric functions for use
#define DEGREES_TO_RAD(x) (x*acos(-1.0)/180.0)
#define RAD_TO_DEGREES(x) (x*180.0/acos(-1.0))

// define EXTRA_DEBUG_MESSAGES (boolean), if you want to see extra printf messages regarding the workings of the program
#define DEBUG_BASE_VALUES 0
#define DEBUG_CAP_1 0
#define DEBUG_CAP_2 0 
#define DEBUG_CAP_3 0
#define DEBUG_CAP_4 0
#define DEBUG_CAP_4 0
#define PROMPT_BASE_VALUES 1
#define PROMPT_CAP_1 1
#define PROMPT_CAP_2 1
#define PROMPT_CAP_3 1
#define PROMPT_CAP_4 1
#define PROMPT_CAP_5 1

/* This function makes sure you have all values set before continuing */
//EXPORT_FUNCTION int check_integrity(struct data* db, int chapter);  // unused

/* load base_data struct for given k from a database stored in-memory 
	I should come up with a new idea for this, it doesn't apply for all college groups */
EXPORT_FUNCTION struct data* get_data_struct(int k);						   // locate from in-memory database array
EXPORT_FUNCTION struct data* data_create();									   // create data, return pointer
EXPORT_FUNCTION void data_free(struct data*);								   // free memory 
EXPORT_FUNCTION struct data* data_load_from_file(char* filename);			   // load from file (binary mode) -- not really useful			
EXPORT_FUNCTION int data_save_to_file(struct data* data, char* filename);      // save to file (binary) -- not really useful
//EXPORT_FUNCTION void data_load_to_database(struct data* dataPtr, int k);	   // load to the in-memory array || NOT USABLE - use data_create and data_free

/* base funcs */
EXPORT_FUNCTION void base_values_init(struct data*);						   // load data for given k
EXPORT_FUNCTION void base_values_create(struct data*, \
	int k, real_t Cs, real_t P_V, real_t N_V, real_t i_TCT, real_t i_R, real_t l, real_t G, real_t F_m); // create with base values

EXPORT_FUNCTION void base_find_F					(struct data*);			   // calculeaza valoarea fortei
EXPORT_FUNCTION void base_pick_a					(struct data*, real_t);    // for use in interfaces
EXPORT_FUNCTION void base_pick_c					(struct data*, real_t);    // for use in interfaces

/* prompts you to pick a value in console, usable in C
    base_pick_a and base_pick_c are intended for matlab
    oh and reduntant l_times_2 thingy, i'm lazy
*/
EXPORT_FUNCTION void base_prompt_pick_a				(struct data*);				// prompt to pick a
EXPORT_FUNCTION void base_prompt_pick_c				(struct data*);				// prompt to pick c
EXPORT_FUNCTION void base_print_data				(void*, struct data*);		// print data, optionally to file, else stdout


/* capitolul 1 funcs */
EXPORT_FUNCTION void cap1_get_data					(struct data*);				// extract initial capitol_1_data  
EXPORT_FUNCTION void cap1_choose_P_me				(struct data*, real_t);     // pick a value for P_me, anexa A2.1
EXPORT_FUNCTION void cap1_choose_N_me				(struct data*, real_t);		// pick a value for N_me, anexa 2.1
EXPORT_FUNCTION void cap1_lookup_P_me				(struct data*);				// lookup data from anexa2.c
EXPORT_FUNCTION void cap1_lookup_N_me				(struct data*);				// lookup data from anexa2.c

EXPORT_FUNCTION void cap1_calcul_turatii			(struct data*);				// computations
EXPORT_FUNCTION void cap1_calcul_momente_rasucire	(struct data*);				// computations

EXPORT_FUNCTION void cap1_prompt_choose_P_me		(struct data*);				// prompt to pick value for N_me, anexa A2.2
EXPORT_FUNCTION void cap1_prompt_choose_N_me		(struct data*);				// prompt to pick a value for N_me
EXPORT_FUNCTION void cap1_print_data				(void*, struct data*);		// print data (to file if prefer, else to stdout)
EXPORT_FUNCTION void cap1_print_to_buffer           (char* filePtr, struct data*); // print to a char buffer using sprintf

/* capitolul 2 funcs */
EXPORT_FUNCTION void cap2_get_data					(struct data*);				// compute initial data for cap 2
EXPORT_FUNCTION void cap2_compute					(struct data*);				// update() 'like function
EXPORT_FUNCTION void cap2_compute_L_p				(struct data*);				// compute Lp with given values
EXPORT_FUNCTION void cap2_choose_tip_curea			(struct data*, int);		// set tip_curea
EXPORT_FUNCTION void cap2_choose_D_p1				(struct data*, real_t);		// set D_p1
EXPORT_FUNCTION void cap2_choose_Aprel				(struct data*, real_t);		// set A_prel
EXPORT_FUNCTION void cap2_choose_L_p				(struct data*, real_t);		// set L_p
EXPORT_FUNCTION void cap2_choose_P_0				(struct data*, real_t);		// set P_0
EXPORT_FUNCTION void cap2_choose_Q					(struct data*, real_t);		// forta de pretensionare


EXPORT_FUNCTION void cap2_prompt_choose_tip_curea					(struct data*);
EXPORT_FUNCTION void cap2_prompt_choose_D_p1						(struct data*);
EXPORT_FUNCTION void cap2_prompt_choose_Aprel						(struct data*);
EXPORT_FUNCTION void cap2_prompt_choose_L_p							(struct data*);
EXPORT_FUNCTION void cap2_prompt_choose_P_0							(struct data*);
EXPORT_FUNCTION void cap2_prompt_choose_Q							(struct data*);

EXPORT_FUNCTION void cap2_lookup_tip_curea							(struct data* db);
EXPORT_FUNCTION void cap2_lookup_P_0								(struct data* db);

EXPORT_FUNCTION void cap2_calcul_numar_curele						(struct data* db);
EXPORT_FUNCTION void cap2_calcul_verificare_functionare_curele		(struct data* db);
EXPORT_FUNCTION void cap2_calcul_forta_utila_si_de_pretensionare	(struct data* db);

EXPORT_FUNCTION void cap2_print_data								(void*, struct data*);		// print data(to file if prefer, else to stdout)

/* capitol 3 funcs */
EXPORT_FUNCTION void cap3_compute_data 		(struct data* db);
EXPORT_FUNCTION void cap3_retrieve_with_Dca     (struct data* db);

EXPORT_FUNCTION void cap3_set_material			(struct data* db, int material);
EXPORT_FUNCTION void cap3_set_simbol			(struct data* db, int simbol);
EXPORT_FUNCTION void cap3_set_tratament			(struct data* db, int tratament);
EXPORT_FUNCTION void cap3_set_Dca				(struct data* db, int Dca);
EXPORT_FUNCTION void cap3_set_Lca               (struct data* db, real_t Lca);
EXPORT_FUNCTION void cap3_set_Det(struct data* db, int _Det);
EXPORT_FUNCTION void cap3_set_Dr(struct data* db, int _Dr);

EXPORT_FUNCTION void cap3_prompt_set_material	(struct data* db);
EXPORT_FUNCTION void cap3_prompt_set_simbol		(struct data* db);
EXPORT_FUNCTION void cap3_prompt_set_tratament	(struct data* db);
EXPORT_FUNCTION void cap3_prompt_choose_Dca		(struct data* db);
EXPORT_FUNCTION void cap3_prompt_choose_Lca     (struct data* db, int auto_scurt);

EXPORT_FUNCTION void cap3_prompt_set_Det(struct data* db);
EXPORT_FUNCTION void cap3_prompt_set_Dr(struct data* db);
//EXPORT_FUNCTION void cap3_auto_set_Det(struct data* db)
//EXPORT_FUNCTION void cap3_auto_set_Dr(struct data* db);
EXPORT_FUNCTION void cap3_solve_dimensions(struct data* db);            // with given Det, Dca and Dr, solve the remaining dimensions
EXPORT_FUNCTION void cap3_print_data			(void* filePtr, struct data* db);

/* capitol 4 funcs */
EXPORT_FUNCTION void cap4_get_data(struct data* data);
EXPORT_FUNCTION void cap4_set_Fa(struct data* data, real_t Fa);
EXPORT_FUNCTION void cap4_prompt_set_Fa(struct data* data);
EXPORT_FUNCTION void cap4_compute(struct data* data);
EXPORT_FUNCTION void cap4_print_data(void* filePtr, struct data* data);

EXPORT_FUNCTION void cap5_get_data(struct data* data);
EXPORT_FUNCTION void cap5_compute(struct data* data);
EXPORT_FUNCTION void cap5_set_Lp_a(struct data* data, real_t Lp);
EXPORT_FUNCTION void cap5_set_Lp_b(struct data* data, real_t Lp);
EXPORT_FUNCTION void cap5_prompt_set_Lp_a(struct data* data);
EXPORT_FUNCTION void cap5_prompt_set_Lp_b(struct data* data);
EXPORT_FUNCTION void cap5_print_data(void* filePtr, struct data* data);
#endif