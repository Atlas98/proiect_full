#include <internal.h>
#include <data/data.h>
#include <exports.h>
#include <data/anexe/anexe.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

EXPORT_FUNCTION void cap3_set_material(struct data* db, int _material) {
	db->dimensionare_arbore_1.material = _material;
}
EXPORT_FUNCTION void cap3_set_simbol(struct data* db, int _simbol) {
	db->dimensionare_arbore_1.simbol = _simbol;
}
EXPORT_FUNCTION void cap3_set_tratament(struct data* db, int _tratament) {
	db->dimensionare_arbore_1.tratament = _tratament;
}
EXPORT_FUNCTION void cap3_prompt_set_material(struct data* db) {
	if(PROMPT_CAP_3) {
		printf("Alege un material: \n");
		printf("1 - Otel carbon de uz general\n");
		printf("2 - Otel carbon de calitate\n");
		printf("3 - Otel aliat\n");
		//printf("Alegerea facuta: ");
	}

	int alegere;
	scanf("%d", &alegere);
	cap3_set_material(db, alegere);
}
EXPORT_FUNCTION void cap3_prompt_set_simbol(struct data* db) {
	if(PROMPT_CAP_3) printf("Simbolul otelului, din anexa 4: \n");

	char simbol_string[16];
	scanf("%s", &simbol_string[0]);

	const char* simbol_string_ptr = &simbol_string[0];
	if (strncmp(simbol_string_ptr, "OL_42", 16) == 0)				cap3_set_simbol(db, OL_42);
	else if (strncmp(simbol_string_ptr, "OL_50", 16) == 0)			cap3_set_simbol(db, OL_50);
	else if (strncmp(simbol_string_ptr, "OL_60", 16) == 0)			cap3_set_simbol(db, OL_60);
	else if (strncmp(simbol_string_ptr, "OLC_15", 16) == 0)			cap3_set_simbol(db, OLC_15);
	else if (strncmp(simbol_string_ptr, "OLC_35", 16) == 0)			cap3_set_simbol(db, OLC_35);
	else if (strncmp(simbol_string_ptr, "OLC_45", 16) == 0)			cap3_set_simbol(db, OLC_45);
	else if (strncmp(simbol_string_ptr, "18_MoCr_10", 16) == 0)		cap3_set_simbol(db, _18_MoCr_10);
	else if (strncmp(simbol_string_ptr, "18_MoCrNi_20", 16) == 0)	cap3_set_simbol(db, _18_MoCrNi_20);
	else if (strncmp(simbol_string_ptr, "40_Cr_10", 16) == 0)		cap3_set_simbol(db, _40_Cr_10);
	else if (strncmp(simbol_string_ptr, "41_MoCr_11", 16) == 0)		cap3_set_simbol(db, _41_MoCr_11);
}
EXPORT_FUNCTION void cap3_prompt_set_tratament(struct data* db) {
	if(PROMPT_CAP_3) {
		printf("Alege un material: 0 - null, 1 - N, 2 - C, 3 - I\n");
		//printf("0 - nici unul\n");
		//printf("1 - N (de normalizare)\n");
		//printf("2 - C (de cementare)\n");
		//printf("3 - I (de imbunatatire)\n");
	}

	//printf("Alegerea facuta: ");
	int alegere;
	scanf("%d", &alegere);
	cap3_set_tratament(db, alegere);
}

// retrieve data with given values
EXPORT_FUNCTION void cap3_compute_data(struct data* db) {
	struct base_values* base = &db->base_data;
	struct capitol_1_data* cap1 = &db->puteri_si_randamente;
	struct capitol_2_data* cap2 = &db->calcul_curele;
	struct capitol_3_data* cap3 = &db->dimensionare_arbore_1;

	if (cap3->simbol >= OL_42 && cap3->simbol <= OL_60)					cap3->material = OTEL_CARBON_DE_UZ_GENERAL;
	else if (cap3->simbol >= OLC_15 && cap3->simbol <= OLC_45)			cap3->material = OTEL_CARBON_DE_CALITATE;
	else if (cap3->simbol >= _18_MoCr_10 && cap3->simbol <= _41_MoCr_11)  cap3->material = OTEL_ALIAT;

	struct anexa4_data anexa_data = anexa4_retrieve_data(cap3->material, cap3->simbol, cap3->tratament);

	cap3->sigma_r = anexa_data.sigma_r;
	cap3->sigma_c = anexa_data.sigma_c;
	cap3->sigma_l = anexa_data.sigma_l;
	cap3->tau_l = anexa_data.tau_l;
	cap3->tau_c = anexa_data.tau_c;
	cap3->sigma_iaI = anexa_data.sigma_iaI;
	cap3->sigma_iaII = anexa_data.sigma_iaII;
	cap3->sigma_iaIII = anexa_data.sigma_iaIII;

	real_t temp_1 = base->F * base->b + cap2->Q * base->c;
	real_t temp_2 = base->a + base->b;

	cap3->F_r1 = temp_1 / temp_2;
	cap3->F_r5 = base->F - cap2->Q - cap3->F_r1;

	// 3.3 Trasarea diagramelor de momente
	cap3->M_i1 = 0;
	cap3->M_i7 = 0;
	cap3->M_i3 = cap3->F_r1 * base->a;
	cap3->M_i5 = cap2->Q	* base->c;
	cap3->M_i2 = cap3->M_i3 / 2.0;
	cap3->M_i4 = (cap3->M_i3 + cap3->M_i5) / 2.0;
	cap3->M_i6 = cap3->M_i5 / 2.0;

	cap3->M_t = cap1->Mt1_max;
	cap3->alfa = cap3->sigma_iaIII / cap3->sigma_iaII;

	cap3->M_i_echiv_1 = sqrt(cap3->M_i1 * cap3->M_i1);
	cap3->M_i_echiv_2 = sqrt(cap3->M_i2 * cap3->M_i2);
	cap3->M_i_echiv_3s = sqrt(cap3->M_i3 * cap3->M_i3);
	cap3->M_i_echiv_3d = sqrt((cap3->M_i3 * cap3->M_i3) + (cap3->alfa*cap3->M_t * cap3->alfa*cap3->M_t));
	cap3->M_i_echiv_4 = sqrt((cap3->M_i4 * cap3->M_i4) + (cap3->alfa*cap3->M_t * cap3->alfa*cap3->M_t));
	cap3->M_i_echiv_5 = sqrt((cap3->M_i5 * cap3->M_i5) + (cap3->alfa*cap3->M_t * cap3->alfa*cap3->M_t));
	cap3->M_i_echiv_6 = sqrt((cap3->M_i6 * cap3->M_i6) + (cap3->alfa*cap3->M_t * cap3->alfa*cap3->M_t));
	cap3->M_i_echiv_7 = sqrt((cap3->M_i7 * cap3->M_i7) + (cap3->alfa*cap3->M_t * cap3->alfa*cap3->M_t));

	real_t temp_3 = acos(-1.0) * cap3->sigma_iaIII;

	cap3->d_1 = pow(((cap3->M_i_echiv_1*32.0) / temp_3), (1.0 / 3.0));
	cap3->d_2 = pow(((cap3->M_i_echiv_2*32.0) / temp_3), (1.0 / 3.0));
	cap3->d_3 = pow(((cap3->M_i_echiv_3d*32.0) / temp_3), (1.0 / 3.0));
	cap3->d_4 = pow(((cap3->M_i_echiv_4*32.0) / temp_3), (1.0 / 3.0));
	cap3->d_5 = pow(((cap3->M_i_echiv_5*32.0) / temp_3), (1.0 / 3.0));
	cap3->d_6 = pow(((cap3->M_i_echiv_6*32.0) / temp_3), (1.0 / 3.0));
	cap3->d_7 = pow(((cap3->M_i_echiv_7*32.0) / temp_3), (1.0 / 3.0));
}

EXPORT_FUNCTION void cap3_set_Dca(struct data* db, int _Dca) {
	db->dimensionare_arbore_1.Dca = _Dca;
	db->dimensionare_arbore_1.Dventilator = _Dca;
}
EXPORT_FUNCTION void cap3_prompt_choose_Dca(struct data* db) {
	if(PROMPT_CAP_3) printf("Alege valoarea diametrului capatului, mai mare decat D7 (%lf) si sau chiar mai mare decat D6 (%lf): \n" \
		, db->dimensionare_arbore_1.d_7, db->dimensionare_arbore_1.d_6);
	int alegere;
	
	scanf("%d", &alegere);
	cap3_set_Dca(db, alegere);
}
EXPORT_FUNCTION void cap3_set_Lca(struct data* db, real_t Lca) {
	db->dimensionare_arbore_1.Lca = Lca;
}
EXPORT_FUNCTION void cap3_prompt_choose_Lca(struct data* db, int auto_scurt) {
	if (auto_scurt) {
		db->dimensionare_arbore_1.Lca = db->dimensionare_arbore_1.Lca_scurt;
		return;
	}
	if(PROMPT_CAP_3) {
		printf("Alege valoarea lungimii capatalui de arbore\n");
		printf("1 - Lca scurt = %lf\n", db->dimensionare_arbore_1.Lca_scurt);
		printf("2 - Lca lung = %lf\n", db->dimensionare_arbore_1.Lca_lung);
	}
	//printf("Alegerea facuta: ");
	int alegere;
	scanf("%d", &alegere);
	if (alegere == 1) {
		cap3_set_Lca(db, db->dimensionare_arbore_1.Lca_scurt);
		return;
	}
	else if (alegere == 2) {
		cap3_set_Lca(db, db->dimensionare_arbore_1.Lca_lung);
		return;
	}
	else {
		cap3_set_Lca(db, db->dimensionare_arbore_1.Lca_scurt);
		return;
	}
	cap3_set_Lca(db, db->dimensionare_arbore_1.Lca_scurt);
}

EXPORT_FUNCTION void cap3_retrieve_with_Dca(struct data* db) {
	struct capitol_3_data* dimensionari = &db->dimensionare_arbore_1;

	struct anexa5_data anexa5 = anexa5_retrieve_from_Dca(dimensionari->Dca);
	dimensionari->Lca_scurt = anexa5.Lca_scurt;
	dimensionari->Lca_lung = anexa5.Lca_lung;
}

EXPORT_FUNCTION void cap3_set_Det(struct data* db, int _Det) {
	db->dimensionare_arbore_1.Det = _Det;
}
EXPORT_FUNCTION void cap3_set_Dr(struct data* db, int _Dr) {
	db->dimensionare_arbore_1.Dr = _Dr;
}
EXPORT_FUNCTION void cap3_prompt_set_Det(struct data* db) {
	if(PROMPT_CAP_3) printf("Introdu o valoare pentru Det din A6.1, astfel incat D1_et sa fie mai mare decat %lf (Dca): \n", (real_t) db->dimensionare_arbore_1.Dca);
	int alegere;
	scanf("%d", &alegere);
	cap3_set_Det(db, alegere);
}
EXPORT_FUNCTION void cap3_prompt_set_Dr(struct data* db) {
	if(PROMPT_CAP_3) printf("Introdu o valoare pentru Dr: \n");
	int alegere;
	scanf("%d", &alegere);
	cap3_set_Dr(db, alegere);
}

EXPORT_FUNCTION void cap3_solve_dimensions(struct data* db) {
// [16:51, 28.3.2019] +40 764 440 075: d perii = dr + 5
// [16:51, 28.3.2019] +40 764 440 075: d rotor = d perii +5
// [16:51, 28.3.2019] +40 764 440 075: d umar = d rotor +5
	struct capitol_3_data* cap3 = &db->dimensionare_arbore_1;
	cap3->Lventilator = 60.0/100.0 * cap3->Dca;
	cap3->Let 		  = 60.0/100.0 * cap3->Det;
	cap3->Lr 		  = 60.0/100.0 * cap3->Dr;
	
	cap3->Dperii = cap3->Dr 	+ 5;
	cap3->Drotor = cap3->Dperii + 5;
	cap3->Dumar  = cap3->Drotor + 5;

	cap3->Lperii = 60.0/100.0 * cap3->Dperii;
	cap3->Lrotor = 60.0/100.0 * cap3->Drotor;
	cap3->Lumar  = 60.0/100.0 * cap3->Dumar;
}	


static inline char* get_simbol_string(int simbol) {
	if (simbol == OL_42)				return "OL_42";
	else if (simbol == OL_50)			return "OL_50";
	else if (simbol == OL_60)			return "OL_60";

	else if (simbol == OLC_15)			return "OLC_15";
	else if (simbol == OLC_35)			return "OLC_35";
	else if (simbol == OLC_45)			return "OLC_45";

	else if (simbol == _18_MoCr_10)		return "_18_MoCr_10";
	else if (simbol == _18_MoCrNi_20)	return "_18_MoCrNi_20";
	else if (simbol == _40_Cr_10)		return "_40_Cr_10";
	else if (simbol == _41_MoCr_11)		return "_41_MoCr_11";

	return "null";
}
EXPORT_FUNCTION void cap3_print_data(void* filePtr, struct data* db) {
	struct capitol_3_data* cap3 = &db->dimensionare_arbore_1;
	fprintf(filePtr, "===================== Capitolul 3 =========================\n");
	fprintf(filePtr, "		Se alege otelul %s\n", get_simbol_string(db->dimensionare_arbore_1.simbol));
	fprintf(filePtr, "	-> Tensiunea limita de rupere la intindere: %lf\n", cap3->sigma_r);
	fprintf(filePtr, "	-> Tensiunea limita de curgere la intindere: %lf\n", cap3->sigma_c);
	fprintf(filePtr, "	-> Tensiunea limita la oboseala de incovoiere pentru ciclu alternant simetric: %lf\n", cap3->sigma_l);
	fprintf(filePtr, "	-> Tensiunea limita la oboseala de torsiune entru ciclu alternant simetric: %lf\n", cap3->tau_l);
	fprintf(filePtr, "	-> Tensiunea limita la curgere la torsiune: %lf\n", cap3->tau_c);
	fprintf(filePtr, "	-> Tensiunea admisibila la incovoiere pentru solicitare statica: %lf\n", cap3->sigma_iaI);
	fprintf(filePtr, "	-> Tensiunea admisibila la incovoiere pentru solicitare pulsatoare: %lf\n", cap3->sigma_iaII);
	fprintf(filePtr, "	-> Tensiunea admisibila la incovoiere pentru solicitare alternant simetric: %lf\n", cap3->sigma_iaIII);
	fprintf(filePtr, "	3.2 Calculul reactiunilor radiale din reazeme\n");
	fprintf(filePtr, "	-> Reactiunea radiala din reazemul I (Fr1): %lf\n", cap3->F_r1);
	fprintf(filePtr, "	-> Reactiunea radiala din reazemul V (Fr5): %lf\n", cap3->F_r5);
	fprintf(filePtr, "	3.3 Trasarea diagramelor de momente\n");
	fprintf(filePtr, "	-> Momentul de incovoiere in sectiunea 1 (Mi_1): %lf\n", cap3->M_i1);
	fprintf(filePtr, "	-> Momentul de incovoiere in sectiunea 2 (Mi_2): %lf\n", cap3->M_i2);
	fprintf(filePtr, "	-> Momentul de incovoiere in sectiunea 3 (Mi_3): %lf\n", cap3->M_i3);
	fprintf(filePtr, "	-> Momentul de incovoiere in sectiunea 4 (Mi_4): %lf\n", cap3->M_i4);
	fprintf(filePtr, "	-> Momentul de incovoiere in sectiunea 5 (Mi_5): %lf\n", cap3->M_i5);
	fprintf(filePtr, "	-> Momentul de incovoiere in sectiunea 6 (Mi_6): %lf\n", cap3->M_i6);
	fprintf(filePtr, "	-> Momentul de incovoiere in sectiunea 7 (Mi_7): %lf\n", cap3->M_i7);
	fprintf(filePtr, "		Coeficientul alfa, care tine cont de modul de variatie in timp a celor doua solicitari: %lf\n", cap3->alfa);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 1 (Mi_echiv_1): %lf\n", cap3->M_i_echiv_1);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 2 (Mi_echiv_2): %lf\n", cap3->M_i_echiv_2);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 3 la stanga  (Mi_echiv_3s): %lf\n", cap3->M_i_echiv_3s);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 3 la dreapta (Mi_echiv_3d): %lf\n", cap3->M_i_echiv_3d);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 4 (Mi_echiv_4): %lf\n", cap3->M_i_echiv_4);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 5 (Mi_echiv_5): %lf\n", cap3->M_i_echiv_5);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 6 (Mi_echiv_6): %lf\n", cap3->M_i_echiv_6);
	fprintf(filePtr, "	-> Momentul de incovoiere echivalent in sectiunea 7 (Mi_echiv_7): %lf\n", cap3->M_i_echiv_7);
	fprintf(filePtr, "	3.4 Dimensionarea arborelui la solicitare compusa statica in sapte sectiuni");
	fprintf(filePtr, "	-> Dx min pentru sectiunea 1: %lf\n", cap3->d_1);
	fprintf(filePtr, "	-> Dx min pentru sectiunea 2: %lf\n", cap3->d_2);
	fprintf(filePtr, "	-> Dx min pentru sectiunea 3: %lf\n", cap3->d_3);
	fprintf(filePtr, "	-> Dx min pentru sectiunea 4: %lf\n", cap3->d_4);
	fprintf(filePtr, "	-> Dx min pentru sectiunea 5: %lf\n", cap3->d_5);
	fprintf(filePtr, "	-> Dx min pentru sectiunea 6: %lf\n", cap3->d_6);
	fprintf(filePtr, "	-> Dx min pentru sectiunea 7: %lf\n", cap3->d_7);
	fprintf(filePtr, "	Tabelul 3.3: \n");
	fprintf(filePtr, "Diametrul capatului (Dca): %d [mm]\n", cap3->Dca);
	fprintf(filePtr, "Lungimea capatului (Lca): %lf [mm]\n", cap3->Lca);
	fprintf(filePtr, "Diametrul ventilatorului (Dventilator): %d [mm]\n", cap3->Dventilator);
	fprintf(filePtr, "Diametrul tronsonului de etansare (Det): %d [mm]\n", cap3->Det);
	fprintf(filePtr, "Diametrul rulmentului (Dr): %d [mm]\n", cap3->Dr);
	fprintf(filePtr, "Diametrul periilor (Dperii) : %d [mm]\n", cap3->Dperii);
	fprintf(filePtr, "Diametrul rotorului (Drotor): %d [mm]\n", cap3->Drotor);
	fprintf(filePtr, "Diametrul umarului (Dumar): %d [mm]\n", cap3->Dumar);
	fprintf(filePtr, "\n");
	fprintf(filePtr, "Lungimea Ventilatorului (Lventilator): %lf [mm]\n", cap3->Lventilator);
	fprintf(filePtr, "Lungimea tronsonului de etansare (Let): %lf [mm]\n", cap3->Let);
	fprintf(filePtr, "Lungimea rulmentului (Lr): %lf [mm]\n", cap3->Lr);
	fprintf(filePtr, "Lungimea periilor (Lperii) : %lf [mm]\n", cap3->Lperii);
	fprintf(filePtr, "Lungimea rotorului (Lrotor): %lf [mm]\n", cap3->Lrotor);
	fprintf(filePtr, "Lungimea umarului (Lumar): %lf [mm]\n", cap3->Lumar);
	fprintf(filePtr, "===========================================================\n");
}

