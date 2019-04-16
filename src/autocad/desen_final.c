#include "autocad.h"



// compute basic data into full_data
static void compute_full_data(struct desen_full_data* full_data, struct desen_basic_data* basic_data) {

}


// se genereaza desenul final
EXPORT_FUNCTION void generate_desen_final(void* filePtr, struct desen_basic_data* basic_data) {
    struct desen_full_data data = {0};

    compute_full_data(&data, basic_data); 
} // generate desen final