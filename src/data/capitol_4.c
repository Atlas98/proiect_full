#include <structs.h>
#include <internal.h>
#include <data/anexe/anexe.h>
#include <data/data.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


EXPORT_FUNCTION void cap4_get_data(struct data* data) {
    struct capitol_4_data* cap4 = &data->calcul_rulmenti;
    struct capitol_3_data* cap3 = &data->dimensionare_arbore_1;
    struct capitol_2_data* cap2 = &data->calcul_curele;

    cap4->Dr = cap3->Dr;
    cap4->N_I = cap2->N_I;
    cap4->Fr1 = cap3->F_r1;
    cap4->Fr5 = abs(cap3->F_r5);
    
    real_t Fr_max;
    real_t Fr_min;

    if(cap4->Fr1 > cap4->Fr5) {
        Fr_max = cap4->Fr1;
        Fr_min = cap4->Fr5;
    }
    else {
        Fr_max = cap4->Fr5;
        Fr_min = cap4->Fr1;
    }
    cap4->Fr = Fr_max;
    cap4->Fr_b = Fr_min;
}

EXPORT_FUNCTION void cap4_set_Fa(struct data* data, real_t Fa) {
    data->calcul_rulmenti.Fa = Fa;
}
EXPORT_FUNCTION void cap4_prompt_set_Fa(struct data* data) {
    if(PROMPT_CAP_4) printf("Introdu valoarea fortei axiale intre %lf si %lf: \n", data->calcul_curele.Q * 0.1, data->calcul_curele.Q * 0.2);
    real_t alegere;
    scanf("%lf", &alegere);
    cap4_set_Fa(data, alegere);
}
EXPORT_FUNCTION void cap4_compute(struct data* data) {
    struct capitol_4_data* cap4 = &data->calcul_rulmenti;
    struct capitol_3_data* cap3 = &data->dimensionare_arbore_1;
    struct capitol_2_data* cap2 = &data->calcul_curele;

    struct anexa7_dr_data* dr_data = anexa7_get_dr_data(cap4->Dr);
    struct anexa7_simbol_data data_1 = dr_data->data[0];
    struct anexa7_simbol_data data_2 = dr_data->data[1];
    struct anexa7_simbol_data data_3 = dr_data->data[2];
    struct anexa7_simbol_data data_4 = dr_data->data[3];

    cap4->_1_simbol = data_1.simbol;
    cap4->_1_D = data_1.D;
    cap4->_1_B = data_1.B;
    cap4->_1_C = data_1.C;
    cap4->_1_C0 = data_1.Ca; // ca is c0

    cap4->_1_Fa_by_C0 = cap4->Fa / (cap4->_1_C0 * 1000);
    cap4->_1_e = anexa7_approx_e(cap4->_1_Fa_by_C0);


    cap4->Fa_by_Fr = cap4->Fa / cap4->Fr;
    cap4->Fa_by_Fr_b = cap4->Fa / cap4->Fr_b;
    real_t Fe_max;

    real_t Lh_const = 1000000.0/(60.0*data->puteri_si_randamente.N_I);

    // a.) sistem flotant
    if(cap4->Fa_by_Fr <= cap4->_1_e) {
        cap4->_1_X = 1;
        cap4->_1_Y = 0;
    }
    else {
        cap4->_1_X = 0.56;
        cap4->_1_Y = anexa7_get_Y(cap4->_1_e);
    }
    cap4->_1_Fe = cap4->_1_X * cap4->Fr + cap4->_1_Y * cap4->Fa;

    cap4->_1_L = pow(cap4->_1_C*1000/cap4->_1_Fe, 3);
    cap4->_1_Lh = cap4->_1_L * Lh_const;

    // b
    if(cap4->Fa_by_Fr_b <= cap4->_1_e) {
        cap4->_1_X_b = 1;
        cap4->_1_Y_b = 0;
    }
    else {
        cap4->_1_X_b = 0.56;
        cap4->_1_Y_b = anexa7_get_Y(cap4->_1_e);
    }
    cap4->_1_Fe_b = cap4->_1_X_b * cap4->Fr_b + cap4->_1_Y_b * cap4->Fa;

    Fe_max = (cap4->_1_Fe_b > cap4->_1_Fe) ? cap4->_1_Fe_b : cap4->_1_Fe;
    cap4->_1_L_b = pow(cap4->_1_C*1000/Fe_max, 3);
    cap4->_1_Lh_b = cap4->_1_L_b * Lh_const;

    // ============================
    cap4->_2_simbol = data_2.simbol;
    cap4->_2_D = data_2.D;
    cap4->_2_B = data_2.B;
    cap4->_2_C = data_2.C;
    cap4->_2_C0 = data_2.Ca; // ca is c0
    
    cap4->_2_Fa_by_C0 = cap4->Fa / (cap4->_2_C0 * 1000);
    cap4->_2_e = anexa7_approx_e(cap4->_2_Fa_by_C0);

    if(cap4->Fa_by_Fr >= cap4->_1_e) {
        cap4->_2_X = 0;
        cap4->_2_Y = 1;
    }
    else {
        cap4->_2_X = 0.56;
        cap4->_2_Y = anexa7_get_Y(cap4->_2_e);
    }
    cap4->_2_Fe = cap4->_2_X * cap4->Fr + cap4->_2_Y * cap4->Fa;
    cap4->_2_L = pow(cap4->_2_C*1000/cap4->_2_Fe, 3);
    cap4->_2_Lh = cap4->_2_L * Lh_const;

    // b
    if(cap4->Fa_by_Fr_b <= cap4->_2_e) {
        cap4->_2_X_b = 1;
        cap4->_2_Y_b = 0;
    }
    else {
        cap4->_2_X_b = 0.56;
        cap4->_2_Y_b = anexa7_get_Y(cap4->_1_e);
    }
    cap4->_2_Fe_b = cap4->_2_X_b * cap4->Fr_b + cap4->_2_Y_b * cap4->Fa;
    
    Fe_max = (cap4->_2_Fe_b > cap4->_2_Fe) ? cap4->_2_Fe_b : cap4->_2_Fe;
    cap4->_2_L_b = pow(cap4->_2_C*1000/Fe_max, 3);
    cap4->_2_Lh_b = cap4->_2_L_b * Lh_const;


    // ================================
    if(dr_data->data_count > 2) {
        cap4->_3_simbol = data_3.simbol;
        cap4->_3_D = data_3.D;
        cap4->_3_B = data_3.B;
        cap4->_3_C = data_3.C;
        cap4->_3_C0 = data_3.Ca; // ca is c0
        
        cap4->_3_Fa_by_C0 = cap4->Fa / (cap4->_3_C0 * 1000);
        cap4->_3_e = anexa7_approx_e(cap4->_3_Fa_by_C0);

        if(cap4->Fa_by_Fr >= cap4->_3_e) {
            cap4->_3_X = 0;
            cap4->_3_Y = 1;
        }
        else {
            cap4->_3_X = 0.56;
            cap4->_3_Y = anexa7_get_Y(cap4->_3_e);
        }
        cap4->_3_Fe = cap4->_3_X * cap4->Fr + cap4->_3_Y * cap4->Fa;
        cap4->_3_L = pow(cap4->_3_C*1000/cap4->_3_Fe, 3);
        cap4->_3_Lh = cap4->_3_L * Lh_const;

        // b
        if(cap4->Fa_by_Fr_b <= cap4->_3_e) {
            cap4->_3_X_b = 1;
            cap4->_3_Y_b = 0;
        }
        else {
            cap4->_3_X_b = 0.56;
            cap4->_3_Y_b = anexa7_get_Y(cap4->_3_e);
        }
        cap4->_3_Fe_b = cap4->_3_X_b * cap4->Fr_b + cap4->_3_Y_b * cap4->Fa;
        
        Fe_max = (cap4->_3_Fe_b > cap4->_3_Fe) ? cap4->_3_Fe_b : cap4->_3_Fe;
        cap4->_3_L_b = pow(cap4->_3_C*1000/Fe_max, 3);
        cap4->_3_Lh_b = cap4->_3_L_b * Lh_const;
    }

    if(dr_data->data_count == 4) {
        cap4->_4_simbol = data_4.simbol;
        cap4->_4_D = data_4.D;
        cap4->_4_B = data_4.B;
        cap4->_4_C = data_4.C;
        cap4->_4_C0 = data_4.Ca; // ca is c0
        
        cap4->_4_Fa_by_C0 = cap4->Fa / (cap4->_4_C0 * 1000);
        cap4->_4_e = anexa7_approx_e(cap4->_4_Fa_by_C0);

        if(cap4->Fa_by_Fr <= cap4->_4_e) {
            cap4->_4_X = 1;
            cap4->_4_Y = 0;
        }
        else {
            cap4->_4_X = 0.56;
            cap4->_4_Y = anexa7_get_Y(cap4->_4_e);
        }
        cap4->_4_Fe = cap4->_4_X * cap4->Fr + cap4->_4_Y * cap4->Fa;
        cap4->_4_L = pow(cap4->_4_C*1000/cap4->_4_Fe, 3);
        cap4->_4_Lh = cap4->_4_L * Lh_const;

        // b
        if(cap4->Fa_by_Fr_b <= cap4->_4_e) {
            cap4->_4_X_b = 1;
            cap4->_4_Y_b = 0;
        }
        else {
            cap4->_4_X_b = 0.56;
            cap4->_4_Y_b = anexa7_get_Y(cap4->_4_e);
        }
        cap4->_4_Fe_b = cap4->_4_X_b * cap4->Fr_b + cap4->_1_Y_b * cap4->Fa;
        
        Fe_max = (cap4->_4_Fe_b > cap4->_4_Fe) ? cap4->_4_Fe_b : cap4->_4_Fe;
        cap4->_4_L_b = pow(cap4->_4_C*1000/Fe_max, 3);
        cap4->_4_Lh_b = cap4->_4_L_b * Lh_const;
    }

    // b.)

} // func end

EXPORT_FUNCTION void cap4_compute_a(struct data* data) {
    struct capitol_4_data* cap4 = &data->calcul_rulmenti;
    struct capitol_3_data* cap3 = &data->dimensionare_arbore_1;
    struct capitol_2_data* cap2 = &data->calcul_curele;

} //
EXPORT_FUNCTION void cap4_compute_b(struct data* data) {
    struct capitol_4_data* cap4 = &data->calcul_rulmenti;
    struct capitol_3_data* cap3 = &data->dimensionare_arbore_1;
    struct capitol_2_data* cap2 = &data->calcul_curele;


}

EXPORT_FUNCTION void cap4_print_data(void* filePtr, struct data* data) {
    struct capitol_4_data* cap4 = &data->calcul_rulmenti;
    fprintf(filePtr, "================ Capitolul 4 ==============================\n");
    fprintf(filePtr, "Smb dr - D - B - C - C0 - Fa/C0 --- e\n");
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_1_simbol, cap4->Dr, cap4->_1_D, cap4->_1_B, cap4->_1_C, cap4->_1_C0, cap4->_1_Fa_by_C0, cap4->_1_e);
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_2_simbol, cap4->Dr, cap4->_2_D, cap4->_2_B, cap4->_2_C, cap4->_2_C0, cap4->_2_Fa_by_C0, cap4->_2_e);
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_3_simbol, cap4->Dr, cap4->_3_D, cap4->_3_B, cap4->_3_C, cap4->_3_C0, cap4->_3_Fa_by_C0, cap4->_3_e);
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_4_simbol, cap4->Dr, cap4->_4_D, cap4->_4_B, cap4->_4_C, cap4->_4_C0, cap4->_4_Fa_by_C0, cap4->_4_e);

    fprintf(filePtr, "\n");
    fprintf(filePtr, "Smb --- Fa/Fr ----- X -------- Y ------ Fe ------------ L -------- Lh\n");
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr, cap4->_1_X, cap4->_1_Y, cap4->_1_Fe, cap4->_1_L, cap4->_1_Lh);
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr, cap4->_1_X, cap4->_1_Y, cap4->_1_Fe, cap4->_2_L, cap4->_2_Lh);
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr, cap4->_1_X, cap4->_1_Y, cap4->_1_Fe, cap4->_3_L, cap4->_3_Lh);
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr, cap4->_1_X, cap4->_1_Y, cap4->_1_Fe, cap4->_4_L, cap4->_4_Lh);
    fprintf(filePtr, "===========================================================\n");

    fpritnf(filePtr, "\n");
    fprintf(filePtr, "b.)\n");
    fprintf(filePtr, "Smb dr - D - B - C - C0 - Fa/C0 --- e\n");
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_1_simbol, cap4->Dr, cap4->_1_D, cap4->_1_B, cap4->_1_C, cap4->_1_C0, cap4->_1_Fa_by_C0, cap4->_1_e);
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_2_simbol, cap4->Dr, cap4->_2_D, cap4->_2_B, cap4->_2_C, cap4->_2_C0, cap4->_2_Fa_by_C0, cap4->_2_e);
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_3_simbol, cap4->Dr, cap4->_3_D, cap4->_3_B, cap4->_3_C, cap4->_3_C0, cap4->_3_Fa_by_C0, cap4->_3_e);
    fprintf(filePtr, "%d  %d %.0lf %.0lf %.1lf %.1lf %.4lf %.4lf\n", cap4->_4_simbol, cap4->Dr, cap4->_4_D, cap4->_4_B, cap4->_4_C, cap4->_4_C0, cap4->_4_Fa_by_C0, cap4->_4_e);

    fprintf(filePtr, "\n");
    fprintf(filePtr, "Smb --- Fa/Fr ----- X -------- Y ------ Fe ------------ L -------- Lh\n");
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr_b, cap4->_1_X_b, cap4->_1_Y_b, cap4->_1_Fe_b, cap4->_1_L_b, cap4->_1_Lh_b);
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr_b, cap4->_1_X_b, cap4->_1_Y_b, cap4->_1_Fe_b, cap4->_2_L_b, cap4->_2_Lh_b);
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr_b, cap4->_1_X_b, cap4->_1_Y_b, cap4->_1_Fe_b, cap4->_3_L_b, cap4->_3_Lh_b);
    fprintf(filePtr, "%d --- %.3lf --- %.2lf -- %.2lf -- %.3lf -- %.0lf --- %.0lf\n", cap4->_1_simbol, cap4->Fa_by_Fr_b, cap4->_1_X_b, cap4->_1_Y_b, cap4->_1_Fe_b, cap4->_4_L_b, cap4->_4_Lh_b);
    fprintf(filePtr, "===========================================================\n");
}