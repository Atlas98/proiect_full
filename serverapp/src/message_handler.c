#include "message_handler.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Data ops struct */
static struct DataOps data_ops;

/* I LIKE MACROS  */
/* Using these way too often */

// Call after_stage method then increment stage integer
#define PROGRESS_STAGE()  do_after_stage(data, *stage); \
                          *stage = *stage+1;
// set response message
#define _RESPONSE(string) strcpy(response, string)
/* check if conversion is succesful, else stop handling further */
#define _RESPONSE_ON_FAIL(string)  \
if(value == 0.0) {                 \
    _RESPONSE(string);             \
    return; }                 

#define EXTRACT_VALUE()               value = strtod(msg, NULL);            \
                                        printf("Value: %lf\n", value);\
                                      _RESPONSE_ON_FAIL("Introduce a valid number!")  

// more efficient than comparing strings
enum ACTIONS {
    ACTION_CREATE_DATA = 0,     // returns data pointer
    ACTION_FREE_DATA = 1,
    ACTION_SET_CS = 2,
    ACTION_SET_PV = 3,
    ACTION_SET_NV = 4,
    ACTION_SET_ITCT = 5,
    ACTION_SET_IR = 6,
    ACTION_SET_L = 7,
    ACTION_SET_G = 8,
    ACTION_SET_FM = 9,

    ACTION_SUBMIT_A = 10,
    ACTION_SUBMIT_C = 11,
    ACTION_SUBMIT_DP1 = 12,
    ACTION_SUBMIT_APREL = 13,
    ACTION_SUBMIT_Q = 14,

    // Prompt actions are used to send back a message with given instructions
    ACTION_PROMPT_A = 15,
    ACTION_PROMPT_C = 16,
    ACTION_PROMPT_DP1 = 17,
    ACTION_PROMPT_APREL = 18,  
    ACTION_PROMPT_Q = 19,     

    ACTION_PRINT_BASE_VALUES = 200,
    ACTION_PRINT_CAPITOL_1 = 201,
    ACTION_PRINT_CAPITOL_2 = 202,
    ACTION_PRINT_CAPITOL_3 = 203,

    ACTION_PRINT_ALL_DATA = 240
};

/*
// calculari pentru fiecare stage, dupa ce ai terminat de introdus niste date se vor calcula celelalte
static void do_after_stage(struct data* data, int stage) {
    switch (stage) {
        // Dupa ce dai F_m, se afla F, apoi se cer a si b
        case 8:
            data_ops.base_find_F(data);
        break;
        // dupa ce se afla C, se calculeaza capitolul 1
        case 10:
            data_ops.cap1_get_data(data);
	        data_ops.cap1_lookup_N_me(data);
	        data_ops.cap1_lookup_P_me(data);
	        data_ops.cap1_calcul_turatii(data);
	        data_ops.cap1_calcul_momente_rasucire(data);
	        data_ops.cap2_get_data(data);
	        data_ops.cap2_compute(data);
	        data_ops.cap2_lookup_tip_curea(data);
        break;
        // Dupa ce se afla Dp1
        case 11:
            data_ops.cap2_compute(data);
        break;
        // Dupa ce se afla Aprel
        case 12:
            data_ops.cap2_compute(data);
            data_ops.cap2_compute_L_p(data);
            data_ops.cap2_compute(data);
            data_ops.cap2_compute(data);
            data_ops.cap2_lookup_P_0(data);

            data_ops.cap2_calcul_numar_curele(data);
            data_ops.cap2_calcul_verificare_functionare_curele(data);
            data_ops.cap2_calcul_forta_utila_si_de_pretensionare(data);
        break;
        // Dupa ce se afla Q
        case 13:

        break;
    }

}
*/

INTERNAL_FUNCTION void message_handler_set_dataops(struct DataOps* ops) {
    data_ops = *ops;
}

/* se trimit mesaje - se cer date si daca sunt bune se vor cere altele mai departe */
INTERNAL_FUNCTION void handle_message(struct data* data, char* msg, char* response, int action) {
    printf("Got action: %d\n", action);
    struct data* data_ptr; // pointer to data
    if(data == NULL) {
        printf("Data is null\n");
        _RESPONSE("NULL_DATA_PTR");
    }

    double value;
    switch(action) {
        case ACTION_CREATE_DATA:
            if(data!=NULL) {
                free(data);
                printf("Data is not null, freeing and alloc again");
            }
            data_ptr = malloc(sizeof(struct data)); // alloc a data object
            sprintf(response, "%lu", (unsigned long) data_ptr);
            printf("Data pointer sent: %lu\n", (unsigned long) data_ptr);
        break;
        case ACTION_SET_CS:
            EXTRACT_VALUE();
            data->base_data.Cs = value;
        break;
        case ACTION_SET_PV:
            EXTRACT_VALUE();
            data->base_data.P_V = value;
        break;
        case ACTION_SET_NV:
            EXTRACT_VALUE();
            data->base_data.n_V = value;
        break;
        case ACTION_SET_ITCT:
            EXTRACT_VALUE();
            data->base_data.i_TCT = value;
        break;
        case ACTION_SET_IR:
            EXTRACT_VALUE();
            data->base_data.i_R = value;
        break;
        case ACTION_SET_L:
            EXTRACT_VALUE();
            data->base_data.l = value;
        break;
        case ACTION_SET_G:
            EXTRACT_VALUE();
            data->base_data.G = value;
        break;
        case ACTION_SET_FM:
            EXTRACT_VALUE();
            data->base_data.F_m = value;
        break;

        case ACTION_SUBMIT_A:
            EXTRACT_VALUE();
            data->base_data.a = value;
        break;  
        case ACTION_SUBMIT_C:
            EXTRACT_VALUE();
            data->base_data.c = value;
        break;  
        case ACTION_SUBMIT_DP1:
            EXTRACT_VALUE();
            data->calcul_curele.D_p1 = value;
        break;  
        case ACTION_SUBMIT_APREL:
            EXTRACT_VALUE();
            data->calcul_curele.A_prel = value;
        break;  
        case ACTION_SUBMIT_Q:
            EXTRACT_VALUE();
            data->calcul_curele.q = value;
        break;  

        case ACTION_PROMPT_A:
            _RESPONSE("Alege valoarea lui A: ");
        break;  
        case ACTION_PROMPT_C:
            _RESPONSE("Alege valoarea lui C: ");
        break;  
        case ACTION_PROMPT_DP1:
            _RESPONSE("Alege valoarea lui Dp1: ");
        break;  
        case ACTION_PROMPT_APREL:
            _RESPONSE("Alege valoarea lui Aprel: ");
        break;  
        case ACTION_PROMPT_Q:
            _RESPONSE("Alege valoarea lui Q: ");
        break;  

        case ACTION_PRINT_ALL_DATA:
        printf("Printing data\n");
            {
                void* fhandle = fopen("data.txt", "w+");
                data_ops.base_print_data(fhandle, data);
                data_ops.cap1_print_data(fhandle, data);
                data_ops.cap2_print_data(fhandle, data);
                data_ops.cap3_print_data(fhandle, data);

                fclose(fhandle);
            }
        break;  
    }


} // handle message
/*
INTERNAL_FUNCTION void handle_message(struct data* data, char* msg, char* response, int* stage) {
    double value;
    if(strcmp(msg, "print") == 0) {
        data_ops.cap1_print_data(stdout, data);
        data_ops.cap2_print_data(stdout, data);
        data_ops.cap3_print_data(stdout, data);
        return;
    }

    switch(*stage) {
        case 0: 
            if(strcmp(msg, "start") == 0) {
                _RESPONSE("Valoarea lui Cs:");
                PROGRESS_STAGE();
            }
        break;

        case 1:  // Get valoarea lui Cs
            // msg is valoarea lui Cs
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui Cs:");

            data->base_data.Cs = value;
            _RESPONSE("Valoarea lui P_V = P_ML: ");
            PROGRESS_STAGE();
        break;

        case 2:
            // msg is valoarea lui P_V
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui P_V = P_ML: ");


            data->base_data.P_V = value;
            _RESPONSE("Valoarea lui N_V = N_ML: ");
            PROGRESS_STAGE()
        break;

        case 3:
            // msg is valoarea lui N_V
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui N_V = N_ML: ");

            data->base_data.n_V = value;
            _RESPONSE("Valoarea lui I_TCT: ");
            PROGRESS_STAGE()
        break;

        case 4:
            // msg is valoarea lui I_TCT
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui I_TCT: ");


            data->base_data.i_TCT = value;
            _RESPONSE("Valoarea lui I_R: ");
            PROGRESS_STAGE()
        break;

        case 5:
            // msg is valoarea lui I_R
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui I_R: ");

            data->base_data.i_R = value;
            _RESPONSE("Valoarea lui l (lungimea rotorului): ");
            PROGRESS_STAGE()
        break;

        case 6:
            // msg is valoarea lui l
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui l (lungimea rotorului): ");

            data->base_data.l = value;
            _RESPONSE("Valoarea lui G: ");
            PROGRESS_STAGE()
        break;

        case 7:
            // msg is valoarea lui G
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui G: ");
                
            data->base_data.G = value;
            _RESPONSE("Valoarea lui F_m: ");
            PROGRESS_STAGE()
        break;

        case 8:
            // msg is valoarea lui F_m
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui F_m: ");
            
            data->base_data.F_m = value;
            _RESPONSE("Valoarea lui A: ");
            PROGRESS_STAGE()
        break; 
        
        case 9:
            // msg is valoarea lui A
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui A: ");
            data_ops.base_pick_a(data, value);

            _RESPONSE("Valoarea lui C: ");
            PROGRESS_STAGE()
        break; 
        
        case 10:
            // msg is valoarea lui C
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui C: ");     
            data_ops.base_pick_c(data, value);

            _RESPONSE("Valoarea lui Dp1: ");
            PROGRESS_STAGE()
        break;  

        case 11:
            // msg is valoarea lui Dp1
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui Dp1: ");
            data_ops.cap2_choose_D_p1(data, value);
            
            {
            char string[256];
            sprintf(&string[0], "Valorea lui Aprel intre %lf si %lf: ", data->calcul_curele.valoarea_minima, data->calcul_curele.valoarea_maxima);
            _RESPONSE(string);
            PROGRESS_STAGE()
            }
        break;
        case 12:
            // msg is valoarea lui Aprel
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui Aprel: ");
            data_ops.cap2_choose_Aprel(data, value);

            {
            char string[256];
            sprintf(&string[0], "Valorea lui Q intre %lf si %lf: ", data->calcul_curele.Q_min, data->calcul_curele.Q_max);
            _RESPONSE(string);
            PROGRESS_STAGE()
            }
        break;
        case 13:
            // msg is valoarea lui Q
            value = strtod(msg, NULL);
            _RESPONSE_ON_FAIL("Valoarea lui Q: ");
            data_ops.cap2_choose_Q(data, value);

            _RESPONSE("Introdu simbol: ");
            PROGRESS_STAGE()
        break;
    }

}
*/


EXPORT_FUNCTION void* message_handler_get() {
    return handle_message;
}
