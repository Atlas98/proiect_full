#include <internal.h>
#include <data/data.h>
#include <data/anexe/anexe.h>
#include <math.h>
#include <stdio.h>

#define ISSET(field) field != 0
#define ISNOTSET(field) field == 0

static inline char* get_tip_curea_string(int tip);

EXPORT_FUNCTION void cap2_get_data(struct data* db) {
	struct base_values* base_data = &db->base_data;
	struct capitol_1_data* capitol1 = &db->puteri_si_randamente;
	struct capitol_2_data* capitol2 = &db->calcul_curele;

	capitol2->Cf   = base_data->Cs;
	capitol2->N_I  = capitol1->N_I;
	capitol2->P_IC = capitol1->P_I * capitol2->Cf;
}

EXPORT_FUNCTION void cap2_compute(struct data* db) {
	struct capitol_2_data* cap2 = &db->calcul_curele;
	real_t delta_dp = 0;  // multiple uses

	// ---------------------------- D_p1 ----------------------------------------------------------
	if (ISNOTSET(cap2->D_p1)) {
		if (DEBUG_CAP_2) printf("Valoare nesetata Dp1\n");
		return;
	}
	
	cap2->D_p2 = anexa3_lookup_Dp2(cap2->tip_curea , cap2->D_p1 * db->base_data.i_TCT);
	cap2->valoarea_minima = 0.7 * (cap2->D_p1 + cap2->D_p2);
	cap2->valoarea_maxima = 2.0 * (cap2->D_p1 + cap2->D_p2);
	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	// ---------------- A_PREL --------------------------------------------------------------------
	if (ISNOTSET(cap2->A_prel)) {
		if (DEBUG_CAP_2) printf("Valoare nesetata Aprel\n");
		return;
	}
	// daca nu e setat, se calculeaza, daca e, se poate recalcula cu (recompute != 0)
	
	delta_dp = (real_t) cap2->D_p2 - cap2->D_p1;
	

	real_t calcul_unghi_ramuri_curele_prel = 2.0 * asin(delta_dp / (2.0*cap2->A_prel));
	real_t local_unghi_ramuri			   = (real_t) RAD_TO_DEGREES(calcul_unghi_ramuri_curele_prel);

	cap2->unghi_ramuri_curele_prel		    = (real_t) local_unghi_ramuri;
	cap2->unghi_inf_roata_conducatoare_prel = (real_t) 180.0 - local_unghi_ramuri;
	cap2->unghi_inf_roata_condusa_prel      = (real_t) 180.0 + local_unghi_ramuri;
	if (DEBUG_CAP_2) printf("Unghiurile: %lf %lf %lf \n", cap2->unghi_ramuri_curele_prel, cap2->unghi_inf_roata_conducatoare_prel, cap2->unghi_inf_roata_condusa_prel);
	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	// ----------------------- L_p ----------------------------------------------------------------

	if (ISNOTSET(cap2->L_p)) {
		if(DEBUG_CAP_2) printf("Valoare nesetata Lp\n");
		return;
	}
	if (DEBUG_CAP_2) printf("Calculez A\n");
	cap2->p = 0.25  * cap2->L_p - 0.393 * (cap2->D_p1 + cap2->D_p2);
	cap2->q = 0.125 * (cap2->D_p2 - cap2->D_p1) * (cap2->D_p2 - cap2->D_p1);
	cap2->A = cap2->p + sqrt(cap2->p * cap2->p - cap2->q);
	
	delta_dp = cap2->D_p2 - cap2->D_p1;
	real_t calcul_temp = 2.0 * (real_t)asin(delta_dp / (2 * cap2->A));

	cap2->unghi_ramuri_curele_def			= RAD_TO_DEGREES(calcul_temp);
	cap2->unghi_inf_roata_conducatoare_def  = 180.0 - cap2->unghi_ramuri_curele_def;
	cap2->unghi_inf_roata_condusa_def		= 180.0 + cap2->unghi_ramuri_curele_def;

	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------
}

EXPORT_FUNCTION void cap2_choose_tip_curea(struct data* db, int tip_curea) {
	switch (tip_curea) {
		case SPZ:    db->calcul_curele.tip_curea = SPZ;
			break;
		case SPA:    db->calcul_curele.tip_curea = SPA;
			break;
		case SPB:    db->calcul_curele.tip_curea = SPB;
			break;
		case _16x15: db->calcul_curele.tip_curea = _16x15;
			break;
		case SPC:    db->calcul_curele.tip_curea = SPC;
			break;
		default: if (DEBUG_CAP_2) printf("Tipul de curea ales este invalid, alege un numar de la 1 la 5!\n");
			break;
	} // switch
} // cap2 choose tip curea

EXPORT_FUNCTION void cap2_prompt_choose_tip_curea(struct data* db) {
	if (PROMPT_CAP_2) printf("Tipul de curea de ales, cu %lf rotatii pe minut si %lf kW: \n", db->calcul_curele.N_I, db->calcul_curele.P_IC);
	if (PROMPT_CAP_2) printf(" 1 - SPZ\n 2 - SPB\n 3 - SPB\n 4 - 16x15\n 5 - SPC\n");
	int valoare_aleasa;
	scanf("%d", &valoare_aleasa);
	cap2_choose_tip_curea(db, valoare_aleasa);
	
} // prompt choose
EXPORT_FUNCTION void cap2_lookup_tip_curea(struct data* db) {
	int tip = anexa3_get_tip_curea(db->puteri_si_randamente.N_ME, db->puteri_si_randamente.P_IC);
	cap2_choose_tip_curea(db, tip);
}

EXPORT_FUNCTION void cap2_choose_D_p1(struct data* db, real_t dp1) {
	db->calcul_curele.D_p1 = dp1;
}
EXPORT_FUNCTION void cap2_prompt_choose_D_p1(struct data* db) {
	if (PROMPT_CAP_2) printf("Alege o valoare pentru D_p1 din anexa 3.5: \n");
	real_t dp1_ales = 0;
	scanf("%lf", &dp1_ales);
	cap2_choose_D_p1(db, dp1_ales);
}

EXPORT_FUNCTION void cap2_choose_Aprel(struct data* db, real_t Aprel) {
	db->calcul_curele.A_prel = Aprel;
}
EXPORT_FUNCTION void cap2_prompt_choose_Aprel(struct data* db) {
	if (PROMPT_CAP_2) printf("Alege o valoare pentru Aprel din intervalul %lf si %lf: \n"
					, db->calcul_curele.valoarea_minima, db->calcul_curele.valoarea_maxima);

	real_t Aprel_ales = 0;
	scanf("%lf", &Aprel_ales);
	cap2_choose_Aprel(db, Aprel_ales);
}

EXPORT_FUNCTION void cap2_compute_L_p(struct data* db) {
	struct capitol_2_data* cap2 = &db->calcul_curele;

	if (ISNOTSET(cap2->A_prel) || ISNOTSET(cap2->D_p2)) {
		if(DEBUG_CAP_2) printf("Imposibil de calculat, alege Aprel si Dp2\n");
		return;
	}

	// despartim pe componente
	real_t componenta1 = (real_t) 2.0 * cap2->A_prel*cos(DEGREES_TO_RAD(cap2->unghi_ramuri_curele_prel) / 2);
	real_t componenta2 = (real_t) DEGREES_TO_RAD(cap2->unghi_inf_roata_conducatoare_prel) * cap2->D_p1 / 2.0;
	real_t componenta3 = (real_t) DEGREES_TO_RAD(cap2->unghi_inf_roata_condusa_prel) * cap2->D_p2 / 2.0;

	real_t Lp_approx = anexa3_approx_Lp(componenta1 + componenta2 + componenta3);
	cap2->L_p = Lp_approx;
}
EXPORT_FUNCTION void cap2_choose_L_p(struct data* db, real_t Lp) {
	db->calcul_curele.L_p = Lp;
}
EXPORT_FUNCTION void cap2_prompt_choose_L_p(struct data* db) {
	if (ISNOTSET(db->calcul_curele.L_p)) {
		if(DEBUG_CAP_2) printf("Imposibil de ales, mai intai trebuie calculat\n");
		return;
	}

	printf("Alege o valoare pentru Lp din anexa 3.2 (Lp calculat = %lf): ", db->calcul_curele.L_p);
	real_t Lp_ales = 0.0;
	scanf("%lf", &Lp_ales);
	cap2_choose_L_p(db, Lp_ales);
}
EXPORT_FUNCTION void cap2_choose_P_0(struct data* db, real_t p0) {
	db->calcul_curele.P_0 = p0;
}
EXPORT_FUNCTION void cap2_prompt_choose_P_0(struct data* db) {
	struct capitol_2_data* cap2 = &db->calcul_curele;
	printf("Alege o valoare pentru P_0 din anexa 3: \n");
	printf(" -> tip curea = %s\n", get_tip_curea_string(cap2->tip_curea));
	printf(" -> Turatia rotii conducatoare: %lf\n", cap2->N_I);
	printf(" -> diametrul primitiv al rotii conducatoare: %lf\n", cap2->D_p1);
	printf(" -> raportul de transmitere: %lf\n", db->base_data.i_TCT);
	printf("Valoare P_0: ");

	real_t P_0 = 0.0;
	scanf("%lf", &P_0);
	cap2_choose_P_0(db, P_0);
}
EXPORT_FUNCTION void cap2_lookup_P_0(struct data* db) {
	int tip_curea = db->calcul_curele.tip_curea;
	real_t Dp1	  = db->calcul_curele.D_p1;
	real_t NI	  = db->calcul_curele.N_I;
	real_t I_TCT  = db->base_data.i_TCT;

	real_t P0 = anexa3_lookup_P0(tip_curea, Dp1, NI, I_TCT);
	db->calcul_curele.P_0 = P0;
}

EXPORT_FUNCTION void cap2_choose_Q(struct data* db, real_t Q) {
	db->calcul_curele.Q = Q;
}
EXPORT_FUNCTION void cap2_prompt_choose_Q(struct data* db) {
	if (PROMPT_CAP_2) printf("Alege o valoare pentru Q cuprins intre valorile: %lf si %lf, multiplu de 10, eventual 5\n", db->calcul_curele.Q_min, db->calcul_curele.Q_max);
	real_t Q_ales = 0.0;
	scanf("%lf", &Q_ales);
	cap2_choose_Q(db, Q_ales);
}

EXPORT_FUNCTION void cap2_calcul_numar_curele(struct data* db) {
	struct capitol_2_data* cap2 = &db->calcul_curele;
	// extrage coeficientul de lungime al curelelor
	int tip_curea	= cap2->tip_curea;
	real_t Lp		=cap2->L_p;
	cap2->C_L		= anexa3_get_CL(tip_curea, Lp);
	
	real_t temp_1 = 180 - cap2->unghi_inf_roata_conducatoare_prel;
	cap2->C_beta = 1 - DEGREES_TO_RAD(temp_1);

	real_t temp_2 = cap2->Cf * db->puteri_si_randamente.P_I;
	real_t temp_3 = cap2->C_L * cap2->C_beta * cap2->P_0;
	cap2->z0 = temp_2 / temp_3;
	// numarul de curele preliminar din tabelul A3.3 din anexa 3
	cap2->C_z = anexa3_get_Cz(cap2->z0);
	cap2->z = cap2->z0 / cap2->C_z;
	cap2->z = anexa3_approx_z(cap2->z);
}
EXPORT_FUNCTION void cap2_calcul_verificare_functionare_curele(struct data* db) {
	struct capitol_2_data* cap2 = &db->calcul_curele;

	real_t temp_1 = acos(-1.0) * cap2->D_p1 * cap2->N_I;
	cap2->V_periferic = temp_1 / 60000.0;

	real_t temp_2 = cap2->V_periferic * 2 * 1000 / cap2->L_p;
	cap2->f_incovoiere = temp_2;

	if (cap2->V_periferic <= VITEZA_ADMISIBILA && cap2->f_incovoiere <= FRECVENTA_ADMISIBILA) cap2->functionare_transmisie = 1; // functioneaza
	else cap2->functionare_transmisie = 0;
}
EXPORT_FUNCTION void cap2_calcul_forta_utila_si_de_pretensionare(struct data* db) {
	struct capitol_2_data* cap2 = &db->calcul_curele;
	real_t temp_1 = cap2->Cf * db->puteri_si_randamente.P_I;
	cap2->F_u = temp_1 * 1000 / cap2->V_periferic; // [Newtons -> * 10e+03]

	cap2->Q_min = 1.5 * cap2->F_u;
	cap2->Q_max = 2.0 * cap2->F_u;
}

static inline char* get_tip_curea_string(int tip) {
	switch (tip) {
	case 0:		 return "cureaua nu a fost aleasa";
		break;
	case SPZ:	 return "SPZ";
		break;
	case SPA:	 return "SPA";
		break;
	case SPB:	 return "SPB";
		break;
	case _16x15: return "16x15";
		break;
	case SPC:	 return "SPC";
		break;
	default:	if (DEBUG_CAP_2) printf("Eroare get_tip_curea_string(int)\n");
		break;
	}
	return "null";
}
EXPORT_FUNCTION void cap2_print_data(void* filePtr, struct data* db) {
	struct capitol_2_data* cap2 = &db->calcul_curele;
	fprintf(filePtr, "===========================================================\n");
	fprintf(filePtr, "================ Capitolul 2 ==============================\n");
	fprintf(filePtr, " => 2.1 Alegerea Tipului curelelor\n");
	fprintf(filePtr, "	Tipul de curele trapezoidale inguste se stabileste in functie de turatia rotii conducatoare si de\n \
		puterea de calcul corespunzatoare. Pe baza bilantului cinematic s-a stabilit ca turatia rotii conducatoare \
		este N1 = %lf rot/min. Adoptand pentru coeficientul de functionare Cf are valoarea coeficientului de serviciu \
		Cs data prin tema (Cf = Cs = %lf)\n", cap2->N_I, cap2->Cf);
	fprintf(filePtr, "	-> Puterea de calcul (P_IC) este: %lf\n", cap2->P_IC);
	fprintf(filePtr, "	-> Tipul de curea este: %s\n", get_tip_curea_string(cap2->tip_curea));
	fprintf(filePtr, " => 2.2 Alegerea diametrului rotii conducatoare\n");
	fprintf(filePtr, "	-> Diametrul primitiv al rotii conducatoare (Dp1): %lf\n", cap2->D_p1);
	fprintf(filePtr, " => 2.3 Calculul elementelor geometrice ale transmisiei\n");
	fprintf(filePtr, "	-> Diametrul primitiv al rotii conduse (Dp2): %lf\n", cap2->D_p2);
	fprintf(filePtr, "	Distanta dintre axe preliminara se alege din intervalul dat de: \n");
	fprintf(filePtr, "	 * valoarea minima: %lf\n", cap2->valoarea_minima);
	fprintf(filePtr, "	 * valoarea maxima: %lf\n", cap2->valoarea_maxima);
	fprintf(filePtr, "	Se adopta Aprel = %lf\n", cap2->A_prel);
	fprintf(filePtr, "\n");
	fprintf(filePtr, "	Unghiul caracteristice transmisiei sunt:\n");
	fprintf(filePtr, "	 * unghiul dintre ramurile curelelor: gamma = %lf\n", cap2->unghi_ramuri_curele_prel);
	fprintf(filePtr, "	 * unghiul de infasurare pentru roata conducatoare: B1 = 180 - %lf = %lf\n", cap2->unghi_ramuri_curele_prel,cap2->unghi_inf_roata_conducatoare_prel);
	fprintf(filePtr, "	 * unghiul de infasurare pentru roata condusa: B2 = 180 + %lf = %lf\n", cap2->unghi_ramuri_curele_prel,cap2->unghi_inf_roata_condusa_prel);
	fprintf(filePtr, "	Lungimea primitiva necesara pentru curele Lp, aleasa din anexa A3.2 = %lf\n", cap2->L_p);
	fprintf(filePtr, "	Distanta dintre axe definitive A = %lf\n", cap2->A);
	fprintf(filePtr, "	 * unghiul dintre ramurile curelelor: %lf\n", cap2->unghi_ramuri_curele_def);
	fprintf(filePtr, "	 * unghiul de infasurare pentru roata conducatoare: 180 - %lf = %lf\n", cap2->unghi_ramuri_curele_def,cap2->unghi_inf_roata_conducatoare_def);
	fprintf(filePtr, "	 * unghiul de infasurare pentru roata conduse: 180 + %lf = %lf\n", cap2->unghi_ramuri_curele_def,cap2->unghi_inf_roata_condusa_def);
	fprintf(filePtr, " => 2.4 Calculul numarului de curele\n");
	fprintf(filePtr, "	Numarul de curele necesar se stabileste in functie de puterea P0 pe care o poate transmite \
			 o singura curea. Acesta depinde tipul curelelor (%s), de turatia rotii conducatoare (%lf rot/min) \
			, de diametrul primitiv al rotii conducatoare (%lf mm) si de raportul de transmitere ( %lf ). \
			Din Anexa 3, rezulta P0 = %lf kW\n", get_tip_curea_string(cap2->tip_curea), cap2->N_I, cap2->D_p1, db->base_data.i_TCT, cap2->P_0);
	fprintf(filePtr, "\n");
	fprintf(filePtr, "	-> Coeficientul de lungime al curelelor (C_L): %lf\n", cap2->C_L);
	fprintf(filePtr, "	-> Coeficientul unghiului de infasurare pe roata conducatoare (C_beta): %lf\n", cap2->C_beta);
	fprintf(filePtr, "	-> Numarul preliminar de curele este (z0): %lf\n", cap2->z0);
	fprintf(filePtr, "	-> Pentru numarul preliminar de curele (Cz): %lf\n", cap2->C_z);
	fprintf(filePtr, "	Se adopta z = %lf\n", cap2->z);
	fprintf(filePtr, " => 2.5 Calcule de verificare a functionarii curelelor\n");
	fprintf(filePtr, "	-> Viteza periferica a rotii conducatoare (V): %lf (max = %lf)\n", cap2->V_periferic, VITEZA_ADMISIBILA);
	fprintf(filePtr, "	-> Frecventa incovoierilor (f): %lf (max = %lf)\n", cap2->f_incovoiere, FRECVENTA_ADMISIBILA);
	fprintf(filePtr, " => 2.6 Calculul fortei utile si al fortei de pretensionare\n");
	fprintf(filePtr, "	-> Forta utila (Fu): %lf\n", cap2->F_u);
	fprintf(filePtr, "	-> Q = (1.5 // 2) * F_u = %lf // %lf N [newton]\n", cap2->Q_min, cap2->Q_max);
	fprintf(filePtr, "	S-a adoptat Q = %lf\n", cap2->Q);
	fprintf(filePtr, "===========================================================\n");
}