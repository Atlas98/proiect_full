#include <internal.h>
#include <structs.h>
#include <data/anexe/anexe.h>
#include <data/data.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI acos(-1.0)

EXPORT_FUNCTION void cap1_get_data(struct data* db) {
	struct base_values* base_data = &db->base_data;
    struct capitol_1_data* capitol1 = &db->puteri_si_randamente; 
   
    capitol1->n_tct = 0.955;
    capitol1->n_pr  = 0.9925;
    capitol1->n_pLA = 0.985;
    capitol1->n_a   = 0.98;

    capitol1->n_tot = capitol1->n_tct * capitol1->n_pr * capitol1->n_pLA * capitol1->n_pLA * capitol1->n_a;
    capitol1->P_I = base_data->P_V / capitol1->n_tot;

    capitol1->P_IC  = capitol1->P_I   * base_data->Cs;
    capitol1->P_II  = capitol1->P_I   * capitol1->n_tct * capitol1->n_pLA;
    capitol1->P_III = capitol1->P_II  * capitol1->n_pr;
    capitol1->P_IV  = capitol1->P_III * capitol1->n_a * capitol1->n_pr;
    capitol1->P_V   = capitol1->P_IV;

	// calculul turatiilor
	capitol1->i_tot = db->base_data.i_TCT * db->base_data.i_R;
	capitol1->N_I   = db->base_data.n_V   * capitol1->i_tot;
}

EXPORT_FUNCTION void cap1_choose_P_me(struct data* db, real_t value) {
	struct capitol_1_data* cap1 = &db->puteri_si_randamente;
    cap1->P_ME = value;
}
EXPORT_FUNCTION void cap1_prompt_choose_P_me(struct data* db) {
	printf("Alege o valoare pentru Pme (> PIC = %lf), din anexa 2.1\n", db->puteri_si_randamente.P_IC);
	real_t chosen_value = 0;
	scanf("%lf", &chosen_value);
	cap1_choose_P_me(db, chosen_value);
}
EXPORT_FUNCTION void cap1_lookup_P_me(struct data* db) {
	real_t Pme_retrieved = anexa2_retrieve_P_me(db->puteri_si_randamente.P_IC);
	cap1_choose_P_me(db, Pme_retrieved);
}

// Necesar pentru calculul celorlalte turatii
EXPORT_FUNCTION void cap1_choose_N_me(struct data* db, real_t value) {
	struct capitol_1_data* cap1 = &db->puteri_si_randamente;
	cap1->N_ME = value;
	cap1->N_I = value;
	
	cap1->N_II  = cap1->N_I   / db->base_data.i_TCT;
	cap1->N_III = cap1->N_II;
	cap1->N_IV  = cap1->N_III / db->base_data.i_TCT;
	cap1->N_V   = cap1->N_IV;
}
EXPORT_FUNCTION void cap1_prompt_choose_N_me(struct data* db) {
	printf("Alege o valoare pentru N_me (> n_I = %lf), din anexa 2.2\n", db->puteri_si_randamente.N_I);
	real_t chosen_value = 0;
	scanf("%lf", &chosen_value);
	cap1_choose_N_me(db, chosen_value);
}
EXPORT_FUNCTION void cap1_lookup_N_me(struct data* db) {
	real_t Nme_retrieved = anexa2_retrieve_N_me(db->puteri_si_randamente.N_I);
	cap1_choose_N_me(db, Nme_retrieved);
}

EXPORT_FUNCTION void cap1_calcul_turatii(struct data* db) {
	struct capitol_1_data* cap1 = &db->puteri_si_randamente;

	cap1->N_II = cap1->N_I / db->base_data.i_TCT;
	cap1->N_III = cap1->N_II;
	cap1->N_IV = cap1->N_III / db->base_data.i_R;
	cap1->N_V = cap1->N_IV;
}
EXPORT_FUNCTION void cap1_calcul_momente_rasucire(struct data* db) {
	struct capitol_1_data* cap1 = &db->puteri_si_randamente;

	real_t preCalc = 30*1000000/PI;
	
	cap1->Mt1 = preCalc * cap1->P_I   / cap1->N_I;
	cap1->Mt2 = preCalc * cap1->P_II  / cap1->N_II;
	cap1->Mt3 = preCalc * cap1->P_III / cap1->N_III;
	cap1->Mt4 = preCalc * cap1->P_IV  / cap1->N_IV;
	cap1->Mt5 = preCalc * cap1->P_V   / cap1->N_V;

	cap1->Mt1_max = preCalc * cap1->P_IC / cap1->N_I;
}

EXPORT_FUNCTION void cap1_print_data(void* filePtr, struct data* db) {
	struct capitol_1_data* cap1 = &db->puteri_si_randamente;
	fprintf(filePtr, "===========================================================\n");
	fprintf(filePtr, "================ Capitolul 1 ==============================\n");
	fprintf(filePtr, "	-> Randamentul total (N_tot): %lf\n"								, cap1->n_tot);
	fprintf(filePtr, "	-> Puterea prin arborele I (PI): %lf\n"							, cap1->P_I);
	fprintf(filePtr, "	-> Puterea de calcul a arborelui I (PIC): %lf\n"					, cap1->P_IC);
	fprintf(filePtr, "	-> Puterea maxima pe care o poate debita motorul (Pme): %lf\n"		, cap1->P_ME);
	fprintf(filePtr, "	-> Puterea prin arborele II (PII): %lf\n"							, cap1->P_II);
	fprintf(filePtr, "	-> Puterea prin arborele III (PIII): %lf\n"						, cap1->P_III);
	fprintf(filePtr, "	-> Puterea prin arborele IV (PIV): %lf\n"							, cap1->P_IV);
	fprintf(filePtr, "	-> Puterea prin arborele V (PV): %lf\n"							, cap1->P_V);
	fprintf(filePtr, "\n");
	fprintf(filePtr, "	-> Turatia in sarcina a arborelui electric (N_I): %lf [rot/min]\n"	, cap1->N_I);
	fprintf(filePtr, "	-> Turatia de mers in gol (N_me): %lf [rot/min]\n"					, cap1->N_I);
	fprintf(filePtr, "	-> Turatia arborelui II: %lf [rot/min]\n"							, cap1->N_II);
	fprintf(filePtr, "	-> Turatia arborelui III: %lf [rot/min]\n"							, cap1->N_III);
	fprintf(filePtr, "	-> Turatia arborelui IV: %lf [rot/min]\n"							, cap1->N_IV);
	fprintf(filePtr, "	-> Turatia arborelui V: %lf [rot/min]\n"							, cap1->N_V);
	fprintf(filePtr, "\n");
	fprintf(filePtr, "	Momentele de torsiune pentru arbori:\n");
	fprintf(filePtr, "	-> Arborele I:   %lf [N*mm]\n", cap1->Mt1);
	fprintf(filePtr, "	-> Arborele II:  %lf [N*mm]\n", cap1->Mt2);
	fprintf(filePtr, "	-> Arborele III: %lf [N*mm]\n", cap1->Mt3);
	fprintf(filePtr, "	-> Arborele IV:  %lf [N*mm]\n", cap1->Mt4);
	fprintf(filePtr, "	-> Arborele V:   %lf [N*mm]\n", cap1->Mt5);
	fprintf(filePtr, "\n");
	fprintf(filePtr, "	Momentul de torsiune maxim pentru arborele I: %lf\n", cap1->Mt1_max);
	fprintf(filePtr, "===========================================================\n");
}
EXPORT_FUNCTION void cap1_print_to_buffer(char* filePtr, struct data* db) {
	struct capitol_1_data* cap1 = &db->puteri_si_randamente;
	
	char* format = \
	"===========================================================\n"\
	"================ Capitolul 1 ==============================\n"\
	"	-> Randamentul total (N_tot): %lf\n"							\
	"	-> Puterea prin arborele I (PI): %lf\n"						\
	"	-> Puterea de calcul a arborelui I (PIC): %lf\n"				\
	"	-> Puterea maxima pe care o poate debita motorul (Pme): %lf\n"	\
	"	-> Puterea prin arborele II (PII): %lf\n"\
	"	-> Puterea prin arborele III (PIII): %lf\n"	\
	"	-> Puterea prin arborele IV (PIV): %lf\n"\
	"	-> Puterea prin arborele V (PV): %lf\n"\
	"\n"\
	"	-> Turatia in sarcina a arborelui electric (N_I): %lf [rot/min]\n"\
	"	-> Turatia de mers in gol (N_me): %lf [rot/min]\n"\
	"	-> Turatia arborelui II: %lf [rot/min]\n"\
	"	-> Turatia arborelui III: %lf [rot/min]\n"\
	"	-> Turatia arborelui IV: %lf [rot/min]\n"\
	"	-> Turatia arborelui V: %lf [rot/min]\n"\
	"\n"\
	"	Momentele de torsiune pentru arbori:\n"\
	"	-> Arborele I:   %lf [N*mm]\n"\
	"	-> Arborele II:  %lf [N*mm]\n"\
	"	-> Arborele III: %lf [N*mm]\n"\
	"	-> Arborele IV:  %lf [N*mm]\n"\
	"	-> Arborele V:   %lf [N*mm]\n"\
	"\n"\
	"	Momentul de torsiune maxim pentru arborele I: %lf\n"\
	"===========================================================\n";

	sprintf(filePtr, format, cap1->n_tot, cap1->P_I, cap1->P_IC, cap1->P_ME, cap1->P_II, cap1->P_III, \
	cap1->P_IV, cap1->P_V, cap1->N_I, cap1->N_II, cap1->N_III, cap1->N_IV, cap1->N_V, cap1->Mt1, cap1->Mt2, cap1->Mt3, cap1->Mt4, cap1->Mt5, cap1->Mt1_max);
}