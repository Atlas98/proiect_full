/* Everything related to the base values */
#include <internal.h>
#include "data.h"
#include <structs.h>
#include <stdio.h>
#include <stdlib.h>

/* fill database with values  */
EXPORT_FUNCTION void base_values_init(struct data* db) {
    switch(db->k) {
		case 4:
			db->base_data.k = 4;
			db->base_data.Cs = 1.4;
			db->base_data.P_V = 1.1;
			db->base_data.n_V = 80;
			db->base_data.i_TCT = 1.8;
			db->base_data.i_R = 4.5;
			db->base_data.l = 260;
			db->base_data.G = 290;
			db->base_data.F_m = 435;
		break;
		case 18:
			db->base_data.k = 18;
			db->base_data.Cs = 1.4;
			db->base_data.P_V = 3.7;
			db->base_data.n_V = 360;
			db->base_data.i_TCT = 1.8;
			db->base_data.i_R = 4.5;
			db->base_data.l = 140;
			db->base_data.G = 200;
			db->base_data.F_m = 500;
		break;
		case 7:
		    db->base_data.k     = 7;
		    db->base_data.Cs    = 1.4;
		    db->base_data.P_V   = 1.7;
		    db->base_data.n_V   = 150;
		    db->base_data.i_TCT = 2.5;
		    db->base_data.i_R   = 6.3;
		    db->base_data.l     = 320;
		    db->base_data.G     = 380;
		    db->base_data.F_m   = 570;
		break;
		case 25:
			db->base_data.k = 25;
			db->base_data.Cs = 1.4;
			db->base_data.P_V = 1.7;
			db->base_data.n_V = 150;
			db->base_data.i_TCT = 2.5;
			db->base_data.i_R = 6.3;
			db->base_data.l = 320;
			db->base_data.G = 380;
			db->base_data.F_m = 570;
		break;
		case 28:
			db->base_data.k = 28;
			db->base_data.Cs = 1.2;
			db->base_data.P_V = 48;
			db->base_data.n_V = 97;
			db->base_data.i_TCT = 1.8;
			db->base_data.i_R = 3.6;
			db->base_data.l = 480;
			db->base_data.G = 100;
			db->base_data.F_m = 400;
			break;
		case 11:
			db->base_data.k = 11;
			db->base_data.Cs = 1.4;
			db->base_data.P_V = 2.5;
			db->base_data.n_V = 110;
			db->base_data.i_TCT = 1.8;
			db->base_data.i_R = 5;
			db->base_data.l = 420;
			db->base_data.G = 530;
			db->base_data.F_m = 795;
			break;
		case 19:
			db->base_data.k = 19;
			db->base_data.Cs = 1.4;
			db->base_data.P_V = 3.9;
			db->base_data.n_V = 290;
			db->base_data.i_TCT = 1.6;
			db->base_data.i_R = 5.6;
			db->base_data.l = 160;
			db->base_data.G = 250;
			db->base_data.F_m = 625;
			break;
		case 26:
			db->base_data.k = 26;
			db->base_data.Cs = 1.4;
			db->base_data.P_V = 5.7;
			db->base_data.n_V = 250;
			db->base_data.i_TCT = 1.8;
			db->base_data.i_R = 6.3;
			db->base_data.l = 300;
			db->base_data.G = 600;
			db->base_data.F_m = 1500;
			break;
		case 1:
			db->base_data.k = 1;
			db->base_data.Cs = 1.4;
			db->base_data.P_V = 0.5;
			db->base_data.n_V = 170;
			db->base_data.i_TCT = 1.25;
			db->base_data.i_R = 3.15;
			db->base_data.l = 200;
			db->base_data.G = 200;
			db->base_data.F_m = 300;
		break;
		

        default: printf("No valid k value\n");
        break;
    }
    
}

EXPORT_FUNCTION void base_values_create(struct data* db, int k, real_t Cs, real_t P_V, real_t N_V, real_t i_TCT, real_t i_R, real_t l, real_t G, real_t F_m) {
	db->base_data.k = k;
	db->base_data.Cs = Cs;
	db->base_data.P_V = P_V;
	db->base_data.n_V = N_V;
	db->base_data.i_TCT = i_TCT;
	db->base_data.i_R = i_R;
	db->base_data.l = l;
	db->base_data.G = G;
	db->base_data.F_m = F_m;
}

EXPORT_FUNCTION void base_find_F(struct data* db) {
	struct base_values* data = &db->base_data;
    data->F = data->G + data->F_m;
}
EXPORT_FUNCTION void base_pick_a(struct data* db, real_t a_value) {
	struct base_values* base_data = &db->base_data;

    /*real_t l_times_2 = base_data->l*2; // a + b
    real_t a_min = 0.5 * l_times_2;
    real_t a_max = 0.6 * l_times_2;

    if(!(a_value < a_max && a_value > a_min)) {
        printf("that value for _a_ is invalid\n");
        return;
    } */

    base_data->a = a_value;
    base_data->b = (base_data->l)*2 - base_data->a;
}
EXPORT_FUNCTION void base_pick_c(struct data* db, real_t c_value) {
	struct base_values* base_data = &db->base_data;

    /*real_t l_times_2 = base_data->l*2; // a + b
    real_t c_min = 0.2 * l_times_2;
    real_t c_max = 0.3 * l_times_2;

    if(!(c_value < c_max && c_value > c_min)) {
        printf("that value for _c_ is invalid\n");
        return;
    } */
    base_data->c = c_value;
}

/* prompts you to pick a value in console, usable in C
    base_pick_a and base_pick_c are intended for matlab
    oh and reduntant l_times_2 thingy, i'm lazy
*/
EXPORT_FUNCTION void base_prompt_pick_a(struct data* db) {
	struct base_values* data = &db->base_data;  // extract base_value struct pointer to work with it

    real_t l_times_2 = data->l*2; // a + b
    real_t a_min = 0.5 * l_times_2;
    real_t a_max = 0.6 * l_times_2;

    real_t a_value = 0;
    if(PROMPT_BASE_VALUES) printf("Pick a value for _a_ inbetween: %lf and %lf\n", a_min, a_max);
    scanf("%lf", &a_value);
    if(a_value != 0) base_pick_a(db, a_value);
    else if(DEBUG_BASE_VALUES) printf("No value chosen\n");
}
EXPORT_FUNCTION void base_prompt_pick_c(struct data* db) {
	struct base_values* data = &db->base_data; // extract base_value struct pointer to work with it

    real_t l_times_2 = data->l*2; // a + b
    real_t c_min = 0.2 * l_times_2;
    real_t c_max = 0.3 * l_times_2;
    
    real_t c_value = 0;
    if(PROMPT_BASE_VALUES) printf("Pick a value for _c_ inbetween: %lf and %lf\n", c_min, c_max);
    scanf("%lf", &c_value);
    if(c_value != 0) base_pick_c(db, c_value);
    else if(DEBUG_BASE_VALUES) printf("No value chosen\n");
}

EXPORT_FUNCTION void base_print_data(void* filePtr, struct data* db) {
	struct base_values* data = &db->base_data;

	fprintf(filePtr, "===========================================================\n");
	fprintf(filePtr, "===================VALORILE INITIALE=======================\n");
	fprintf(filePtr, "	Coeficientul de suprasarcina (Cs): %lf\n"							, data->Cs    );
	fprintf(filePtr, "	Puterea arborelui masinii de lucru (Pml = Pv): %lf\n"				, data->P_V   );
	fprintf(filePtr, "	Turatia arborelui masinii de lucru (Nml = Nv): %lf\n"			    , data->n_V   );
	fprintf(filePtr, "	Raportul de transmisie pentru curelele trapezoidale (iTCT): %lf\n"  , data->i_TCT );
	fprintf(filePtr, "	Raportul de transmitere pentru reductor (iR): %lf\n"				, data->i_R   );
	fprintf(filePtr, "	Lungimea rotorului (l): %lf\n"										, data->l     );
	fprintf(filePtr, "	Greutatea rotorului  (G): %lf\n"									, data->G     );
	fprintf(filePtr, "	Forta electromagnetica de interactiune rotor-stator (Fm): %lf\n"	, data->F_m   );
	fprintf(filePtr, "	Forta maxima pe rotor (F): %lf\n"									, data->F     );
	fprintf(filePtr, "	Distanta dintre reazamele 1 si 5, a+b=2*l: %lf\n"					,(data->l)*2  );
	fprintf(filePtr, "	a = %lf\n", data->a);
	fprintf(filePtr, "	b = %lf\n", data->b);
	fprintf(filePtr, "	c = %lf\n", data->c);
	fprintf(filePtr, "===========================================================\n");
}



