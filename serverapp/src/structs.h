 #ifndef _STRUCTS_H_
 #define _STRUCTS_H_
/* Provides base values for a given K */

typedef double real_t;
#define EXPORT_FUNCTIONS_TABLE 1

enum TIP_CUREA {
	SPZ 	= 1,
	SPA 	= 2,
	SPB 	= 3,
	_16x15  = 4,
	SPC 	= 5
};

struct base_values {
    int k;          // numarul de ordine din apelul grupei
    real_t Cs;      // coeficientul de suprasarcina
    real_t P_V;     // puterea arborelui masinii de lucru
    real_t n_V;     // turatia arobrelui masinii de lucru
    real_t i_TCT;   // raportul de transmitere pentru curelele trapezoidale
    real_t i_R;     // raportul de transmitere pentru reductor
    real_t l;       // lungimea rotorului
    real_t G;       // greutatea rotorului
    real_t F_m;     // forta electromagnetica, de interactiune dintre stator si rotor

    /* extra base values, needs to be calculated with compute_extra_base_values(struct base_values*) */
    real_t F;       // forta maxima pe rotor - trebuie aflat
    real_t a;       // valoarea lui a        - trebuie aflat
    real_t b;       // valoarea lui b        - trebuie aflat
    real_t c;       // valoarea lui c        - trebuie aflat
};

struct capitol_1_data {
    real_t n_tct;									// randament transmisie prin curele
    real_t n_pr;									// randament pereche de rulmenti
    real_t n_pLA;									// randament pereche de lagare de alunecare
    real_t n_a;										// randament angrenaj cilindric
    real_t n_tot;									// randament total al transmisiei

    real_t P_I;										// putere arbore 1
    real_t P_IC;									// putere arbore 1 + coef supra sarcina
    real_t P_ME;									// puterea maxima care poate fi debitata, se alege din anexa 2.1
    real_t P_II;									// putere arbore 2
    real_t P_III;									// putere arbore 3
    real_t P_IV;									// putere arbore 4
    real_t P_V;										// putere arbore 5

	/* Calculul turatiilor */
	real_t i_tot;									// raportul de transmitere total al transmisiei
	real_t N_I;										// turatia in sarcina(cand se debiteaza puterea Pi) a arborelui motorului electric
	real_t N_ME;									// Turatia de mers in gold (cand se debiteaza puetere 0 - anexa 2.2
	real_t N_II;									// Turatia arbore 2
	real_t N_III;									// Turatia arbore 3
	real_t N_IV;									// Turatia arbore 4
	real_t N_V;										// Turatia arbore 5

	/* calculul momentelor de rasucire */
	real_t Mt1;										// momentul de rasucire prin arborele 1
	real_t Mt2;										// momentul de rasucire prin arborele 2
	real_t Mt3;										// momentul de rasucire prin arborele 3
	real_t Mt4;										// momentul de rasucire prin arborele 4
	real_t Mt5;										// momentul de rasucire prin arborele 5
	real_t Mt1_max;
};

/* de la capitolul 2.5: calcule de verificare */
#define VITEZA_ADMISIBILA	 50.0
#define FRECVENTA_ADMISIBILA 80.0
struct capitol_2_data {
	// 2.1 Alegerea tipului de curele
	real_t Cf;										// coeficientul de functionare
	real_t N_I;										// turatia rotii conducatoare
	real_t P_IC;									// Puterea de calcul-- de calculat 
	enum TIP_CUREA tip_curea;						// tipul de curea

	// 2.2 Alegerea diametrului rotii conducatoare
	real_t D_p1;									// diametrul primitiv al rotii conducatoare

	// 2.3 Calculul elementelor geometrice ale transmisiei
	real_t D_p2;									// Diametrul primitiv al rotii conduse
	real_t valoarea_minima;							// distanta dintre axe - minim
	real_t valoarea_maxima;							// distanta dintre axe - maxim
	real_t A_prel;									// Distanta dintre axe preliminara

	real_t unghi_ramuri_curele_prel;				// unghiul dintre ramurile curelelor (gamma)
	real_t unghi_inf_roata_conducatoare_prel;		// unghiul de infasurare pentru roata conducatoare
	real_t unghi_inf_roata_condusa_prel;			// unghiul de infasurare pentru roata condusa
	real_t L_p;										// Lungimea primitiva pentru curele
	
	real_t p;										// necesar pentru a calcula distanta dintre axe A
	real_t q;										// necesar pentru a calcula distanta dintre axe A
	real_t A;										// Distanta dintre axe definitiva, respunzatoare lungimii primitive standardizate

	real_t unghi_ramuri_curele_def;					// unghiul dintre ramurile curelelor (gamme), corespunzatoare distantei dintre axe
	real_t unghi_inf_roata_conducatoare_def;		// unghiul de infasurare pentru roata conducatoare, corespunzatoare distantei dintre axe
	real_t unghi_inf_roata_condusa_def;				// unghiul de infasurare pentru roata condusa, corespunzatoare distantei dintre axe
	
	// 2.4 Calcul numarului de curele
	real_t P_0;										// Din anexa 3
	real_t C_L;										// Coeficientul de lungime al curelelor
	real_t C_beta;									// Coeficientul unghiului de infasurare pe roata conducatoare _prel
	real_t z0;										// numarul preliminar de curele					
	real_t C_z;										// coeficientul numarului de curele
	real_t z;										// numarul final de curele

	// 2.5 Calcule de verificare a functionarii curelelor
	real_t V_periferic;								// viteza periferica a rotii conducatoare	
	real_t f_incovoiere;							// frecventa incovoierilor, pentru o transmisie prin curele cu x = 2 roti
	int functionare_transmisie;						// transmisia prin curele proiectata functioneaza(1) - nu functioneaza(0)

	// 2.6 Calculul fortei utile si a fortei de pretensionare
	real_t F_u;										// forta utila
	real_t Q_min;
	real_t Q_max;
	real_t Q;										// forta de pretensionare
};

struct capitol_3_data {
	int material;									// materialul ales
	int simbol;										// ce fel de material e
	int tratament;									// tratamentul ales
	real_t sigma_r;									// tensiunea limita de rupere la intindere
	real_t sigma_c;									// tensiunea limita de curgere la intindere
	real_t sigma_l;									// tensiunea limita la oboseala de incovoiere pentru ciclu alternat simetric
	real_t tau_l;									// tensiunea limita la oboseala de torsiune pentru ciclu alternat simetric
	real_t tau_c;									// tensiunea limita de curgere la torsiune
	real_t sigma_iaI;								// tensiunea admisibila la incovoiere pentru solicitarea statica
	real_t sigma_iaII;								// tensiunea admisibila la incovoiere pentru solicitare pulsatoare
	real_t sigma_iaIII;								// tensiunea admisibila la incovoiere pentru solicitare alternant simetrica
	
	// 3.2 Calculul reactiunilor radiale din reazeme
	real_t F_r1;									// Reactiunea radiala din reazemul I		
	real_t F_r5;									// Reactiunea radiala din reazemul II
	
	// 3.3 Trasarea diagramelor de momente
	real_t M_i1;									// Momentul incovoietor in sectiunea 1
	real_t M_i2;									// Momentul incovoietor in sectiunea 2
	real_t M_i3;									// Momentul incovoietor in sectiunea 3
	real_t M_i4;									// Momentul incovoietor in sectiunea 4
	real_t M_i5;									// Momentul incovoietor in sectiunea 5
	real_t M_i6;									// Momentul incovoietor in sectiunea 6
	real_t M_i7;									// Momentul incovoietor in sectiunea 7

	real_t M_t;										// Momentul de torsiune maxim cu o variatie uniforma in sectiunea 3 si 7
	real_t M_i_echiv_1;								// Momentul de incovoiere echivalent intr-o sectiune (1)
	real_t M_i_echiv_2;								// Momentul de incovoiere echivalent intr-o sectiune (2)
	real_t M_i_echiv_3s;							// Momentul de incovoiere echivalent intr-o sectiune (3) - stanga
	real_t M_i_echiv_3d;							// Momentul de incovoiere echivalent intr-o sectiune (3) - dreapta
	real_t M_i_echiv_4;								// Momentul de incovoiere echivalent intr-o sectiune (4)
	real_t M_i_echiv_5;								// Momentul de incovoiere echivalent intr-o sectiune (5)
	real_t M_i_echiv_6;								// Momentul de incovoiere echivalent intr-o sectiune (6)
	real_t M_i_echiv_7;								// Momentul de incovoiere echivalent intr-o sectiune (7)

	real_t alfa;									// coeficientul care tine cont de modul de variatie in timp a celor doua solicitari
	
	// 3.4 Dimensionarea arborelui la solicitare compusa statica in sapte sectiune
	real_t d_1;
	real_t d_2;
	real_t d_3;
	real_t d_4;
	real_t d_5;
	real_t d_6;
	real_t d_7;

	// 3.5 Stabilirea dimensiunlor finale ale diferitelor tronsoane ale arborelui
	real_t Lca_scurt;									// pentru ales
	real_t Lca_lung;									// pentru ales

	int Dca;										// diametrul capatului de arbor
	real_t Lca;										// lungimea capatului
	
	int Dventilator;								// diametrul ventilatorului
	real_t Lventilator;								// lungimea ventilatorului

	int Det;										// diametrul tronsorului de etansare
	real_t Let;										// lungimea tronsonului de etansare

	int Dr;											// diametrul rulmentilor
	real_t Lr;											// lungimea rulmentilor

	int Dperii;										// diametrul periilor
	real_t Lperii;										// lungimea periilor

	int Drotor;										// diametrul rotorului
	real_t Lrotor;										// lungimea rotorului

	int Dumar;										// diametrul umarului
	real_t Lumar;										// lungimea umarului
};


struct capitol_4_data {
	int Dr;										// diametrul fusului, din capitolul trecut
	real_t N_I;
	real_t Fr1;
	real_t Fr5;
	real_t Fa;
	real_t Fr;
	real_t Fr_b;


	// 4.1
	// a) Montajul in sistem flotant
	real_t Fa_by_Fr; // common to all
	real_t Fa_by_Fr_b; // common to b

	int _1_simbol;
	real_t _1_D;
	real_t _1_B;
	real_t _1_C;
	real_t _1_C0;
	real_t _1_Fa_by_C0;
	real_t _1_e;
	
	real_t _1_X;
	real_t _1_Y;
	real_t _1_Fe;
	real_t _1_L;
	real_t _1_Lh;
	real_t _1_X_b;
	real_t _1_Y_b;
	real_t _1_Fe_b;
	real_t _1_L_b;
	real_t _1_Lh_b;

	int _2_simbol;
	real_t _2_D;
	real_t _2_B;
	real_t _2_C;
	real_t _2_C0;
	real_t _2_Fa_by_C0;
	real_t _2_e;

	real_t _2_X;
	real_t _2_Y;
	real_t _2_Fe;
	real_t _2_L;
	real_t _2_Lh;
	real_t _2_X_b;
	real_t _2_Y_b;
	real_t _2_Fe_b;
	real_t _2_L_b;
	real_t _2_Lh_b;


	int _3_simbol;
	real_t _3_D;
	real_t _3_B;
	real_t _3_C;
	real_t _3_C0;
	real_t _3_Fa_by_C0;
	real_t _3_e;

	real_t _3_X;
	real_t _3_Y;
	real_t _3_Fe;
	real_t _3_L;
	real_t _3_Lh;
	real_t _3_X_b;
	real_t _3_Y_b;
	real_t _3_Fe_b;
	real_t _3_L_b;
	real_t _3_Lh_b;

	int _4_simbol;
	real_t _4_D;
	real_t _4_B;
	real_t _4_C;
	real_t _4_C0;
	real_t _4_Fa_by_C0;
	real_t _4_e;

	real_t _4_X;
	real_t _4_Y;
	real_t _4_Fe;
	real_t _4_L;
	real_t _4_Lh;
	real_t _4_X_b;
	real_t _4_Y_b;
	real_t _4_Fe_b;
	real_t _4_L_b;
	real_t _4_Lh_b;
};

struct data {
	int					  k;						// numarul K (identifier for data)
	struct base_values	  base_data;				// base data
	struct capitol_1_data puteri_si_randamente;		// din capitolul 1
	struct capitol_2_data calcul_curele;			// din capitolul 2
	struct capitol_3_data dimensionare_arbore_1;	// din capitolul 3
	struct capitol_4_data calcul_rulmenti;			// din capitolul 4
};


#if EXPORT_FUNCTIONS_TABLE
// TODO: UPDATE THIS
typedef void* data_ptr;
typedef void* file_ptr;

struct DataOps {
	data_ptr (*get_data_struct)(int);
	data_ptr (*data_create)(void);
	void (*data_free)(data_ptr);
	data_ptr (*data_load_from_file)(char*);
	int (*data_save_to_file)(data_ptr, char*);

	void (*base_values_init)(data_ptr);
	void(*base_values_create)(data_ptr, int, real_t, real_t, real_t, real_t, real_t, real_t, real_t, real_t);
	void(*base_find_F)(data_ptr);
	void(*base_pick_a)(data_ptr, real_t);
	void(*base_pick_c)(data_ptr, real_t);
	void(*base_print_data)(file_ptr, data_ptr);		// print data, optionally to file, else stdout


	void (*cap1_get_data)(data_ptr);				// extract initial capitol_1_data  
	void (*cap1_choose_P_me)(data_ptr, real_t);     // pick a value for P_me, anexa A2.1
	void (*cap1_choose_N_me)(data_ptr, real_t);		// pick a value for N_me, anexa 2.1
	void (*cap1_lookup_P_me)(data_ptr);				// lookup data from anexa2.c
	void (*cap1_lookup_N_me)(data_ptr);				// lookup data from anexa2.c
	void (*cap1_calcul_turatii)(data_ptr);				// computations
	void (*cap1_calcul_momente_rasucire)(data_ptr);				// computations
	void (*cap1_prompt_choose_P_me)(data_ptr);				// prompt to pick value for N_me, anexa A2.2
	void (*cap1_prompt_choose_N_me)(data_ptr);				// prompt to pick a value for N_me
	void (*cap1_print_data)(file_ptr, data_ptr);		// print data (to file if prefer, else to stdout)
	void (*cap1_print_to_buffer)(char* buffer, data_ptr);

	void (*cap2_get_data)(data_ptr);				// compute initial data for cap 2
	void (*cap2_compute)(data_ptr);				// update() 'like function
	void (*cap2_compute_L_p)(data_ptr);				// compute Lp with given values
	void (*cap2_choose_tip_curea)(data_ptr, int);		// set tip_curea
	void (*cap2_choose_D_p1)(data_ptr, real_t);		// set D_p1
	void (*cap2_choose_Aprel)(data_ptr, real_t);		// set A_prel
	void (*cap2_choose_L_p)(data_ptr, real_t);		// set L_p
	void (*cap2_choose_P_0)(data_ptr, real_t);		// set P_0
	void (*cap2_choose_Q)(data_ptr, real_t);		// forta de pretensionare
	void (*cap2_prompt_choose_tip_curea)(data_ptr);
	void (*cap2_prompt_choose_D_p1)(data_ptr);
	void (*cap2_prompt_choose_Aprel)(data_ptr);
	void (*cap2_prompt_choose_L_p)(data_ptr);
	void (*cap2_prompt_choose_P_0)(data_ptr);
	void (*cap2_prompt_choose_Q)(data_ptr);
	void (*cap2_lookup_tip_curea)(data_ptr db);
	void (*cap2_lookup_P_0)(data_ptr db);
	void (*cap2_calcul_numar_curele)(data_ptr db);
	void (*cap2_calcul_verificare_functionare_curele)(data_ptr db);
	void (*cap2_calcul_forta_utila_si_de_pretensionare)(data_ptr db);
	void (*cap2_print_data)(file_ptr, data_ptr);		// print data(to file if prefer, else to stdout)

	/* capitol 3 funcs */
	void (*cap3_compute_data)(data_ptr db);
	void (*cap3_retrieve_with_Dca     )(data_ptr db);

	void (*cap3_set_material)(data_ptr db, int material);
	void (*cap3_set_simbol)(data_ptr db, int simbol);
	void (*cap3_set_tratament)(data_ptr db, int tratament);
	void (*cap3_set_Dca)(data_ptr db, int Dca);
	void (*cap3_set_Lca)(data_ptr db, int Ica);
	void (*cap3_set_Det)(data_ptr db, int _Det);
	void (*cap3_set_Dr)(data_ptr db, int _Dr);

	void (*cap3_prompt_set_material)(data_ptr db);
	void (*cap3_prompt_set_simbol)(data_ptr db);
	void (*cap3_prompt_set_tratament)(data_ptr db);
	void (*cap3_prompt_choose_Dca)(data_ptr db);
	void (*cap3_prompt_choose_Lca)(data_ptr db, int auto_scurt);

	void (*cap3_prompt_set_Det)(data_ptr db);
	void (*cap3_prompt_set_Dr)(data_ptr db);
	//void (*cap3_auto_set_Det)(data_ptr db)
	//void (*cap3_auto_set_Dr)(data_ptr db);
	void (*cap3_solve_dimensions)(data_ptr db);            // with given Det, Dca and Dr, solve the remaining dimenions

	void (*cap3_print_data)(file_ptr, data_ptr);
};

//EXPORT_FUNCTION struct DataOps* get_data_ops();

// function pointer, returns struct with data operations from the main library
typedef void* (*get_data_ops)(void); 

// function pointer to a function that gets a function pointer, to handle messages in networking_interface.c
// the function pointer comes from the main library of course :)
typedef void* (*message_handler_get_ptr)(void);

#endif
#endif