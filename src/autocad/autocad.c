#include "autocad.h"
#include <stdio.h>


/*	Autocad.c
 Se genereaza primul desen only
*/

#define ENTER()	fprintf(filePtr, "\n")
#define COMMENT(comment) fprintf(filePtr, comment); ENTER(); //	Print comment then newline
#define OSMODE(value) fprintf(filePtr, "OSMODE %d", value); ENTER();


static void generate_ventilator(void* filePtr, struct arbore_data* data) {
	double x1 = 0;
	double y1 = (data->Dumar - data->Dventilator) / 2.0;

	double x2 = x1 + data->Lventilator;
	double y2 = y1 + data->Dventilator;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
}
static void generate_etansare(void* filePtr,  struct arbore_data* data) {
	double tesitura_length = (data->Dr - data->Det) / 4.0;

	double x1 = data->Lventilator + tesitura_length;
	double y1 = (data->Dumar - data->Det) / 2.0;

	double x2 = x1 + data->Let - tesitura_length;
	double y2 = y1 + data->Det;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();


	double T1x = x1;
	double T1y = y1;

	double T2x = x1 - tesitura_length;
	double T2y = y1 + tesitura_length;

	double T3x = T2x;
	double T3y = y2 - tesitura_length;

	double T4x = x1;
	double T4y = y2;

	fprintf(filePtr, "_PLINE");
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T1x, T1y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T2x, T2y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T3x, T3y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T4x, T4y);
	ENTER();
	ENTER();
}
static void generate_rulment(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let;
	double y1 = (data->Dumar - data->Dr) / 2.0;

	double x2 = x1 + data->Lr;
	double y2 = y1 + data->Dr;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
}
static void generate_perii(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr;
	double y1 = (data->Dumar - data->Dperii) / 2.0;

	double x2 = x1 + data->Lperii;
	double y2 = y1 + data->Dperii;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
}
static void generate_rotor(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr + data->Lperii;
	double y1 = (data->Dumar - data->Drotor) / 2.0;

	double x2 = x1 + data->Lrotor;
	double y2 = y1 + data->Drotor;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);

	ENTER();
}
static void generate_umar(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr + data->Lperii + data->Lrotor;
	double y1 = 0;

	// la umar, tesitura de 5
	//double tesitura_length = 5;
	double tesitura_length = (data->Dumar - data->Drotor) / 2.0;

	double x2 = x1 + data->Lumar - tesitura_length;
	double y2 = y1 + data->Dumar;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
	
	double T1x = x2;
	double T1y = y2;
	// going to the right
	double T2x = T1x + tesitura_length;
	double T2y = T1y - tesitura_length;

	double T3x = T2x;
	double T3y = y1 + tesitura_length;
	
	double T4x = T1x;
	double T4y = y1;
	fprintf(filePtr, "_PLINE");
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T1x, T1y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T2x, T2y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T3x, T3y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T4x, T4y);
	ENTER();
	ENTER();
}

static void generate_rulment_2(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr + data->Lperii + data->Lrotor \
		+ data->Lumar;
	double y1 = (data->Dumar - data->Dr) / 2.0;

	//double tesitura_length = 2.5;

	double x2 = x1 + data->Lr;
	double y2 = y1 + data->Dr;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
}

static void generate_etansare_2(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr + data->Lperii + data->Lrotor + data->Lumar + data->Lr;
	double y1 = (data->Dumar - data->Det) / 2.0;

	double tesitura_length = (data->Dr - data->Det) / 4.0;

	double x2 = x1 + data->Let_dreapta - tesitura_length;
	double y2 = y1 + data->Det;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();

	// tesitura de 2.5 la rulment
	double T1x = x2;
	double T1y = y2;
	// going to the right
	double T2x = T1x + tesitura_length;
	double T2y = T1y - tesitura_length;

	double T3x = T2x;
	double T3y = y1 + tesitura_length;

	double T4x = T1x;
	double T4y = y1;
	fprintf(filePtr, "_PLINE");
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T1x, T1y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T2x, T2y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T3x, T3y);
	ENTER();
	fprintf(filePtr, "%.2lf,%.2lf", T4x, T4y);
	ENTER();
	ENTER();
}

static void generate_roata_curele(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr + data->Lperii + data->Lrotor \
		+ data->Lumar + data->Lr + data->Let_dreapta;
	double y1 = (data->Dumar - data->Dca) / 2.0;

	double x2 = x1 + data->Lca;
	double y2 = y1 + data->Dca;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
}

static void compute_lengths(struct arbore_data* data) {
	double percent_60 = 60.0 / 100.0;
	data->Lr = percent_60 * data->Dr;
	data->Let = percent_60 * data->Det;
	data->Lventilator = percent_60 * data->Dventilator;
	// calculeaza cu C	
	data->Let_dreapta = data->c - data->Lr / 2.0 - data->Lca / 2.0;
	// calculeaza cu B
	data->Lumar = data->b - data->Lrotor / 2.0 - data->Lr / 2.0;
	// calculeaza cu A
	data->Lperii = data->a - data->Lr / 2.0 - data->Lrotor / 2.0;
}

EXPORT_FUNCTION void autocad_generate_arbore(void* filePtr, struct arbore_data* data) {
	compute_lengths(data);

	OSMODE(0);

	generate_ventilator(filePtr, data);
	generate_etansare(filePtr, data);
	generate_rulment(filePtr, data);
	generate_perii(filePtr, data);
	generate_rotor(filePtr, data);
	generate_umar(filePtr, data);
	generate_etansare_2(filePtr, data);
	generate_rulment_2(filePtr, data);
	generate_roata_curele(filePtr, data);

	printf("Generated arbore!\n");
}
