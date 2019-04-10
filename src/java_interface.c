#include <internal.h>
#if JAVA_INTERFACE_ACTIVE 
#include <jni.h>
#include <stdlib.h>
#include <data/data.h>
#include <exports.h>
#include <structs.h>
struct data dat;

// init data and get pointer
extern JNIEXPORT void JNICALL
Java_com_example_atlas_testapplication_NativeData_initData(JNIEnv* env, jobject thiz, \
	jint k, jDouble Cs, jDouble P_V_ME, jDouble n_V, jDouble i_TCT, jDouble i_R, jDouble l, jDouble G, jDouble F_m, jDouble F) {

}

extern JNIEXPORT jstring JNICALL
Java_com_example_atlas_testapplication_CPP_stringFromJNI(JNIEnv* env, jobject thiz) {
	return (*env)->NewStringUTF(env, "Null");
}

extern JNIEXPORT void JNICALL
Java_com_example_atlas_testapplication_NativeData_retrieveAllData(JNIEnv* env, jobject thisObj) {
	jclass clazz = (*env)->GetObjectClass(env, thisObj);

	jfieldID k_field = (*env)->GetFieldID(env, clazz, "k", "I");
	jfieldID Cs_field = (*env)->GetFieldID(env, clazz, "Cs", "D");
	jfieldID P_V_ME_field = (*env)->GetFieldID(env, clazz, "P_V_ME", "D");
	jfieldID n_V_field = (*env)->GetFieldID(env, clazz, "n_V", "D");
	jfieldID i_TCT_field = (*env)->GetFieldID(env, clazz, "i_TCT", "D");
	jfieldID i_R_field = (*env)->GetFieldID(env, clazz, "i_R", "D");
	jfieldID l_field = (*env)->GetFieldID(env, clazz, "l", "D");
	jfieldID G_field = (*env)->GetFieldID(env, clazz, "G", "D");
	jfieldID F_m_field = (*env)->GetFieldID(env, clazz, "F_m", "D");
	jfieldID F_field = (*env)->GetFieldID(env, clazz, "F", "D");
	jfieldID a_field = (*env)->GetFieldID(env, clazz, "a", "D");
	jfieldID b_field = (*env)->GetFieldID(env, clazz, "b", "D");
	jfieldID c_field = (*env)->GetFieldID(env, clazz, "c", "D");
	/*
	// capitol 1
	jfieldID n_tct_field = (*env)->GetFieldID(env, clazz, "n_tct", "D");
	jfieldID n_pr_field = (*env)->GetFieldID(env, clazz, "n_pr", "D");
	jfieldID n_pLA_field = (*env)->GetFieldID(env, clazz, "n_pLA", "D");
	jfieldID n_a_field = (*env)->GetFieldID(env, clazz, "n_a", "D");
	jfieldID n_tot_field = (*env)->GetFieldID(env, clazz, "n_tot", "D");
	jfieldID P_I_field = (*env)->GetFieldID(env, clazz, "P_I", "D");
	jfieldID P_IC_field = (*env)->GetFieldID(env, clazz, "P_IC", "D");
	jfieldID P_ME_field = (*env)->GetFieldID(env, clazz, "P_ME", "D");
	jfieldID P_II_field = (*env)->GetFieldID(env, clazz, "P_II", "D");
	jfieldID P_III_field = (*env)->GetFieldID(env, clazz, "P_III", "D");
	jfieldID P_IV_field = (*env)->GetFieldID(env, clazz, "P_IV", "D");
	jfieldID P_V_field = (*env)->GetFieldID(env, clazz, "P_V", "D");

	jfieldID i_tot_field = (*env)->GetFieldID(env, clazz, "i_tot", "D");
	jfieldID N_I_field = (*env)->GetFieldID(env, clazz, "N_I", "D");
	jfieldID N_ME_field = (*env)->GetFieldID(env, clazz, "N_ME", "D");
	jfieldID N_II_field = (*env)->GetFieldID(env, clazz, "N_II", "D");
	jfieldID N_III_field = (*env)->GetFieldID(env, clazz, "N_III", "D");
	jfieldID N_IV_field = (*env)->GetFieldID(env, clazz, "N_IV", "D");
	jfieldID N_V_field = (*env)->GetFieldID(env, clazz, "N_V", "D");

	jfieldID Mt1_field = (*env)->GetFieldID(env, clazz, "Mt1", "D");
	jfieldID Mt2_field = (*env)->GetFieldID(env, clazz, "Mt2", "D");
	jfieldID Mt3_field = (*env)->GetFieldID(env, clazz, "Mt3", "D");
	jfieldID Mt4_field = (*env)->GetFieldID(env, clazz, "Mt4", "D");
	jfieldID Mt5_field = (*env)->GetFieldID(env, clazz, "Mt5", "D");
	jfieldID Mt1_max_field = (*env)->GetFieldID(env, clazz, "Mt1_max", "D");

	// capitol 2
	jfieldID Cf_field = (*env)->GetFieldID(env, clazz, "Cf", "D");
	//jfieldID N_I_field = (*env)->GetFieldID(env, clazz, "N_I", "D");
	//jfieldID P_IC_field = (*env)->GetFieldID(env, clazz, "P_IC", "D");
	jfieldID tip_curea_field = (*env)->GetFieldID(env, clazz, "tip_curea", "I");

	jfieldID D_p1_field = (*env)->GetFieldID(env, clazz, "D_p1_field", "D");

	jfieldID D_p2_field = (*env)->GetFieldID(env, clazz, "D_p2", "D");
	jfieldID valoarea_minima_field = (*env)->GetFieldID(env, clazz, "valoarea_minima", "D");
	jfieldID valoarea_maxima_field = (*env)->GetFieldID(env, clazz, "valoarea_maxima", "D");
	jfieldID A_prel_field = (*env)->GetFieldID(env, clazz, "A_prel", "D");

	jfieldID unghi_ramuri_curele_prel_field = (*env)->GetFieldID(env, clazz, "unghi_ramuri_curele_prel", "D");
	jfieldID unghi_inf_roata_conducatoare_prel_field = (*env)->GetFieldID(env, clazz, "unghi_inf_roata_conducatoare_prel", "D");
	jfieldID unghi_inf_roata_condusa_prel_field = (*env)->GetFieldID(env, clazz, "unghi_inf_roata_condusa_prel", "D");
	jfieldID L_p_field = (*env)->GetFieldID(env, clazz, "L_p", "D");

	jfieldID p_field = (*env)->GetFieldID(env, clazz, "p", "D");
	jfieldID q_field = (*env)->GetFieldID(env, clazz, "q", "D");
	jfieldID A_field = (*env)->GetFieldID(env, clazz, "A", "D");

	jfieldID unghi_ramuri_curele_def_field = (*env)->GetFieldID(env, clazz, "unghi_ramuri_curele_def", "D");
	jfieldID unghi_inf_roata_conducatoare_def_field = (*env)->GetFieldID(env, clazz, "unghi_inf_roata_conducatoare_def", "D");
	jfieldID unghi_inf_roata_condusa_def_field = (*env)->GetFieldID(env, clazz, "unghi_inf_roata_condusa_def", "D");

	jfieldID P_0_field = (*env)->GetFieldID(env, clazz, "P_0", "D");
	jfieldID C_L_field = (*env)->GetFieldID(env, clazz, "C_L", "D");
	jfieldID C_beta_field = (*env)->GetFieldID(env, clazz, "C_beta", "D");
	jfieldID z0_field = (*env)->GetFieldID(env, clazz, "z0", "D");
	jfieldID C_z_field = (*env)->GetFieldID(env, clazz, "C_z", "D");
	jfieldID z_field = (*env)->GetFieldID(env, clazz, "z", "D");

	jfieldID V_periferic_field = (*env)->GetFieldID(env, clazz, "V_periferic", "D");
	jfieldID f_incovoiere_field = (*env)->GetFieldID(env, clazz, "f_incovoiere", "D");
	jfieldID functionare_transmisie_field = (*env)->GetFieldID(env, clazz, "functionare_transmisie", "I");

	jfieldID F_u_field = (*env)->GetFieldID(env, clazz, "F_u", "D");
	jfieldID Q_min_field = (*env)->GetFieldID(env, clazz, "Q_min", "D");
	jfieldID Q_max_field = (*env)->GetFieldID(env, clazz, "Q_max", "D");
	jfieldID Q_field = (*env)->GetFieldID(env, clazz, "Q", "D");

	 */

	printf("Aplication started\n");
	struct data* data = get_data_struct(7);
	base_values_init(data);
	base_find_F(data);


	(*env)->SetIntField(env, thisObj, k_field, data->k);
	(*env)->SetDoubleField(env, thisObj, Cs_field, data->base_data.Cs);
	(*env)->SetDoubleField(env, thisObj, P_V_ME_field, data->base_data.P_V);
	(*env)->SetDoubleField(env, thisObj, n_V_field, data->base_data.n_V);
	(*env)->SetDoubleField(env, thisObj, i_TCT_field, data->base_data.i_TCT);
	(*env)->SetDoubleField(env, thisObj, i_R_field, data->base_data.i_R);
	(*env)->SetDoubleField(env, thisObj, l_field, data->base_data.l);
	(*env)->SetDoubleField(env, thisObj, G_field, data->base_data.G);
	(*env)->SetDoubleField(env, thisObj, F_m_field, data->base_data.F_m);
	(*env)->SetDoubleField(env, thisObj, F_field, data->base_data.F);
}

extern JNIEXPORT void JNICALL
Java_com_example_atlas_testapplication_NativeData_computeWithA(JNIEnv* env, jobject thisObj, jDouble A) {

}

extern JNIEXPORT void JNICALL
Java_com_example_atlas_testapplication_NativeData_capitol2RetrieveData(JNIEnv* env, jobject thisObj) {

}

struct capitol_3_data_test {
	int material;									// materialul ales
	int simbol;										// ce fel de material e
	int tratament;									// tratamentul ales
	Double sigma_r;									// tensiunea limita de rupere la intindere
	Double sigma_c;									// tensiunea limita de curgere la intindere
	Double sigma_l;									// tensiunea limita la oboseala de incovoiere pentru ciclu alternat simetric
	Double tau_l;									// tensiunea limita la oboseala de torsiune pentru ciclu alternat simetric
	Double tau_c;									// tensiunea limita de curgere la torsiune
	Double sigma_iaI;								// tensiunea admisibila la incovoiere pentru solicitarea statica
	Double sigma_iaII;								// tensiunea admisibila la incovoiere pentru solicitare pulsatoare
	Double sigma_iaIII;								// tensiunea admisibila la incovoiere pentru solicitare alternant simetrica

	// 3.2 Calculul reactiunilor radiale din reazeme
	Double F_r1;									// Reactiunea radiala din reazemul I
	Double F_r5;									// Reactiunea radiala din reazemul II

	// 3.3 Trasarea diagramelor de momente
	Double M_i1;									// Momentul incovoietor in sectiunea 1
	Double M_i2;									// Momentul incovoietor in sectiunea 2
	Double M_i3;									// Momentul incovoietor in sectiunea 3
	Double M_i4;									// Momentul incovoietor in sectiunea 4
	Double M_i5;									// Momentul incovoietor in sectiunea 5
	Double M_i6;									// Momentul incovoietor in sectiunea 6
	Double M_i7;									// Momentul incovoietor in sectiunea 7

	Double M_t;										// Momentul de torsiune maxim cu o variatie uniforma in sectiunea 3 si 7
	Double M_i_echiv_1;								// Momentul de incovoiere echivalent intr-o sectiune (1)
	Double M_i_echiv_2;								// Momentul de incovoiere echivalent intr-o sectiune (2)
	Double M_i_echiv_3s;							// Momentul de incovoiere echivalent intr-o sectiune (3) - stanga
	Double M_i_echiv_3d;							// Momentul de incovoiere echivalent intr-o sectiune (3) - dreapta
	Double M_i_echiv_4;								// Momentul de incovoiere echivalent intr-o sectiune (4)
	Double M_i_echiv_5;								// Momentul de incovoiere echivalent intr-o sectiune (5)
	Double M_i_echiv_6;								// Momentul de incovoiere echivalent intr-o sectiune (6)
	Double M_i_echiv_7;								// Momentul de incovoiere echivalent intr-o sectiune (7)

	Double alfa;									// coeficientul care tine cont de modul de variatie in timp a celor doua solicitari

	// 3.4 Dimensionarea arborelui la solicitare compusa statica in sapte sectiune
	Double d_1;
	Double d_2;
	Double d_3;
	Double d_4;
	Double d_5;
	Double d_6;
	Double d_7;

	// 3.5 Stabilirea dimensiunlor finale ale diferitelor tronsoane ale arborelui
	int Lca_scurt;									// pentru ales
	int Lca_lung;									// pentru ales

	int Dca;										// diametrul capatului de arbor
	int Dventilator;								// diametrul ventilatorului
	int Lca;										// lungimea capatului
	int Det;										// diametrul tronsorului de etansare
	int Dr;											// Diametrul rulmentilor
	int Dperii;										// Diametrul periilor
	int Drotor;										// Diametrul rotorului
	int Dumar;										// Diametrul umarului
};
#endif