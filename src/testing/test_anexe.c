#include <data/anexe/anexe.h>
#include <testing/test.h>
#include <structs.h>
#include <stdio.h>

int anexa3_get_tip_curea(real_t N_me, real_t P_IC); 
real_t anexa3_lookup_Dp2(int tip_curea, real_t Dp1);

INTERNAL_FUNCTION int test_anexe_anexa3_tip_and_dp2() {
    int test1 = 0;
    int test2 = 0;

    int tip_test = anexa3_get_tip_curea(1500, 40); // must return SPA
    if(tip_test == SPA) test1 = 1;
	if (DEBUG_TEST && test1) printf("Tip test passed!\n");

    real_t lookup_dp2 = anexa3_lookup_Dp2(_16x15, 260); 
    if(lookup_dp2 == 224) test2 = 1;
	if (DEBUG_TEST && test2) printf("Dp2 test passed!\n");


    if(test1 && test2) {
        if(DEBUG_TEST) printf("Anexa 3L tip_curea & dp2 -> testing succeded\n");
        return 1;
    }
    return 0;
}
INTERNAL_FUNCTION int test_anexe_anexa3_lookup_P0() {
	int test_SPZ	= 0;
	int test_SPA	= 0;
	int test_SPB	= 0;
	int test_16x15  = 0;
	int test_SPC	= 0;

	real_t P0_SPZ = anexa3_lookup_P0(SPZ, 100.0, 1500.0, 1.9);
	if (DEBUG_TEST) printf("P0 SPZ value is: %lf\n", P0_SPZ);
	if (P0_SPZ == 2.58) test_SPZ = 1;
	if (DEBUG_TEST && test_SPZ) printf("Test SPZ: passed!\n");

	real_t P0_SPA = anexa3_lookup_P0(SPA, 160.0, 750, 1.4);
	if (DEBUG_TEST) printf("P0 SPA value is: %lf\n", P0_SPA);
	if (P0_SPA == 3.55) test_SPA = 1;
	if (DEBUG_TEST && test_SPA) printf("Test SPA: passed!\n");

	real_t P0_SPB = anexa3_lookup_P0(SPB, 400.0, 1500.0, 3.1);
	if (DEBUG_TEST) printf("P0 SPB value is: %lf\n", P0_SPA);
	if (P0_SPB == 23.40) test_SPB = 1;
	if (DEBUG_TEST && test_SPB) printf("Test SPB: passed!\n");

	real_t P0_16x15 = anexa3_lookup_P0(_16x15, 224.0, 750.0, 3.0);
	if (DEBUG_TEST) printf("P0 16x15 value is: %lf\n", P0_SPA);
	if (P0_16x15 == 8.54) test_16x15 = 1;
	if (DEBUG_TEST && test_16x15) printf("Test 16x15: passed!\n");

	real_t P0_SPC = anexa3_lookup_P0(SPC, 280.0, 3000.0, 1.1);
	if (DEBUG_TEST) printf("P0 SPC value is: %lf\n", P0_SPA);
	if (P0_SPC == 11.13) test_SPC = 1;
	if (DEBUG_TEST && test_SPC) printf("Test SPC: passed!\n");
	
	if (test_SPZ && test_SPA && test_SPB && test_16x15 && test_SPC) return 1;
	return 0;
}
INTERNAL_FUNCTION int test_anexe_anexa4_data_extract() {
	struct anexa4_data data = anexa4_retrieve_data(OTEL_CARBON_DE_CALITATE, OLC_15, tratament_C);
	if(data.sigma_r     == 500 &&
	   data.sigma_c     == 300 &&
	   data.sigma_l     == 220 &&
	   data.tau_l       == 125 &&
	   data.tau_c       == 180 &&
	   data.sigma_iaI   == 170 &&
	   data.sigma_iaII  == 75  &&
	   data.sigma_iaIII == 45) {
		if(DEBUG_TEST) printf("Testul anexa4 : passed!\n");
		return 1;
	} // if correct
	return -1;
} // data extract

INTERNAL_FUNCTION int test_anexe_anexa7_test_struct() {
	struct anexa7_dr_data* data = anexa7_get_dr_data(30);
	printf("data count: %d\n", data->data_count);
	struct anexa7_simbol_data sData = data->data[0];

	printf("simbol: %d, D:%lf B:%lf, r:%lf C:%lf Ca:%lf, D1_r:%lf, r1:%lf\n", sData.simbol, sData.D, sData.B, sData.r, sData.C, sData.Ca, sData.D1_r, sData.r1);

	real_t e1 = anexa7_approx_e(0.019);
	real_t e2 = anexa7_approx_e(0.014);
	real_t e3 = anexa7_approx_e(0.0086);
	real_t e4 = anexa7_approx_e(0.0048);
	printf("The four numbers: %lf %lf %lf %lf\n", e1, e2, e3, e4);
	return 1;
}

INTERNAL_FUNCTION int test_anexe_anexa8_get_pana_data() {
	struct anexa8_pana_data dt = anexa8_get_pana_data(55);
	printf("Bp : %lf\n", dt.bp);
	printf("Hp : %lf\n", dt.hp);
	printf("Lp_max : %lf\n", dt.Lp_max);
	printf("Lp_min : %lf\n", dt.Lp_min);
}