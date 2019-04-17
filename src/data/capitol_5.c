#include <structs.h>
#include <internal.h>
#include <data/anexe/anexe.h>
#include <data/data.h>



EXPORT_FUNCTION void cap5_get_data(struct data* data) {
    struct capitol_5_data* cap5 = &data->pene_paralele;
    struct anexa8_pana_data dt1 = anexa8_get_pana_data(data->dimensionare_arbore_1.Dca);
    cap5->bp_a = dt1.bp;
    cap5->hp_a = dt1.hp;
    cap5->Lp_max_a = dt1.Lp_max;
    cap5->Lp_min_a = dt1.Lp_min;

    struct anexa8_pana_data dt2 = anexa8_get_pana_data(data->dimensionare_arbore_1.Drotor);
    cap5->bp_b = dt2.bp;
    cap5->hp_b = dt2.hp;
    cap5->Lp_max_b = dt2.Lp_max;
    cap5->Lp_min_b = dt2.Lp_min;
}

EXPORT_FUNCTION void cap5_compute(struct data* data) {
    struct capitol_1_data* cap1 = &data->puteri_si_randamente;
    struct capitol_3_data* cap3 = &data->dimensionare_arbore_1;
    struct capitol_5_data* cap5 = &data->pene_paralele;
    
    // a.)
    cap5->Ft_a = 2.0*cap1->Mt1_max/cap3->Dca;
    cap5->sigma_s_a = cap5->Ft_a / (cap5->hp_a/2.0*cap5->Lp_a);
    cap5->tau_f_a = cap5->Ft_a / (cap5->bp_a*cap5->Lp_a);
    // b.)
    cap5->Ft_b = 2.0*cap1->Mt1_max/cap3->Drotor;
    cap5->sigma_s_b = cap5->Ft_b / (cap5->hp_b/2.0*cap5->Lp_b);
    cap5->tau_f_b = cap5->Ft_b / (cap5->bp_b*cap5->Lp_b);
}

EXPORT_FUNCTION void cap5_set_Lp_b(struct data* data, real_t _Lp) {
    data->pene_paralele.Lp_b = _Lp;
}

EXPORT_FUNCTION void cap5_set_Lp_a(struct data* data, real_t _Lp) {
    data->pene_paralele.Lp_a = _Lp;
}

EXPORT_FUNCTION void cap5_prompt_set_Lp_a(struct data* data) {
    if(PROMPT_CAP_5) printf("Introdu valoarea lui Lp intre %lf si %lf: \n", data->pene_paralele.Lp_min_a, data->pene_paralele.Lp_max_a);
    real_t alegere = 0;
    scanf("%lf", &alegere);
    cap5_set_Lp_a(data, alegere);
}
EXPORT_FUNCTION void cap5_prompt_set_Lp_b(struct data* data) {
    if(PROMPT_CAP_5) printf("Introdu valoarea lui Lp intre %lf si %lf: \n", data->pene_paralele.Lp_min_b, data->pene_paralele.Lp_max_b);
    real_t alegere =0;
    scanf("%lf", &alegere);
    cap5_set_Lp_b(data, alegere);
}

EXPORT_FUNCTION void cap5_print_data(void* filePtr, struct data* data) {
    struct capitol_5_data* cap5 = &data->pene_paralele;

    fprintf(filePtr, "===========================================================\n");
    fprintf(filePtr, "===================== Capitolul 5 =========================\n");
    fprintf(filePtr, "  Penele paralele se verifica la solicitare de contact si respectiv la forfecare, tensiunile admisibile fiind:\n");
    fprintf(filePtr, "  * la solicitarea de contact: 120 MPa\n");
    fprintf(filePtr, "  * la solicitarea de forfecare: 80 MPa\n");
    fprintf(filePtr, " a.) Calculul ansamblarii dintre arborele I si roata de curea conducatoare\n");
    fprintf(filePtr, "  Pe capatul de abore, de lungime %lf (mm) este ...\n", data->dimensionare_arbore_1.Lca);
    fprintf(filePtr, "  ... este montata roata de curea condusa la diametrul Dca = %d \n", data->dimensionare_arbore_1.Dca);
    fprintf(filePtr, "  * latimea, bp = %lf\n", cap5->bp_a);
    fprintf(filePtr, "  * inaltimea hp = %lf\n", cap5->hp_a);
    fprintf(filePtr, "  Tinand cont de lungimea capatului de arbore Lca = %lf mm, se adopta \n", data->dimensionare_arbore_1.Lca);
    fprintf(filePtr, "lungimea standardizata a penei Lp = %lf mm, astfel incat Lp < Lca (%lf, %lf)\n", cap5->Lp_a, cap5->Lp_a, data->dimensionare_arbore_1.Lca);
    fprintf(filePtr, "  -> Forta tangentiala care solicita pana este (Ft): %lf\n", cap5->Ft_a);
    fprintf(filePtr, "  -> Tensiunea de contact este (sigma_s): %lf\n", cap5->sigma_s_a);
    fprintf(filePtr, "  -> Tensiunea de forfecare este (tau_f): %lf\n", cap5->tau_f_a);
    fprintf(filePtr, "  b.) Calculul ansamblarii dintre arborele I si rotor\n");
    fprintf(filePtr, "  .. diametrul Drotor = %d mm\n", data->dimensionare_arbore_1.Drotor);
    fprintf(filePtr, "  * latimea, bp = %lf\n", cap5->bp_b);
    fprintf(filePtr, "  * inaltimea, hp = %lf\n", cap5->hp_b);
    fprintf(filePtr, "  Tinand cont de lungimea rotorului (Lrotor): %lf mm, se adopta lungimea standardizata Lp = %lf (Lp < L)\n", data->base_data.l, cap5->Lp_b);
    fprintf(filePtr, "  -> Forta tangentiala care solicita pana este (Ft): %lf\n", cap5->Ft_b);
    fprintf(filePtr, "  -> Tensiunea de contact este (sigma_s): %lf\n", cap5->sigma_s_b);
    fprintf(filePtr, "  -> Tensiunea de forfecare este (tau_f): %lf\n", cap5->tau_f_b);
	fprintf(filePtr, "===========================================================\n");

}