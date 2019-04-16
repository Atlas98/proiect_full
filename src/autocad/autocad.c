#include "autocad.h"
#include <stdio.h>

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
	double x1 = data->Lventilator;
	double y1 = (data->Dumar - data->Det) / 2.0;

	double x2 = x1 + data->Let;
	double y2 = y1 + data->Det;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
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
	// Are tesitura

	double x2 = x1 + data->Lumar;
	double y2 = y1 + data->Dumar;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
}

static void generate_rulment_2(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr + data->Lperii + data->Lrotor \
		+ data->Lumar;
	double y1 = (data->Dumar - data->Dr) / 2.0;

	double x2 = x1 + data->Lr;
	double y2 = y1 + data->Dr;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
	ENTER();
}

static void generate_etansare_2(void* filePtr, struct arbore_data* data) {
	double x1 = data->Lventilator + data->Let + data->Lr + data->Lperii + data->Lrotor + data->Lumar + data->Lr;
	double y1 = (data->Dumar - data->Det) / 2.0;

	double x2 = x1 + data->Let_dreapta;
	double y2 = y1 + data->Det;
	fprintf(filePtr, "RECTANGLE %.2lf,%.2lf %.2lf,%.2lf", x1, y1, x2, y2);
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
	// calculeaza cu C	
	data->Let_dreapta = data->c - data->Lr / 2 - data->Lca / 2;
	// calculeaza cu B
	data->Lumar = data->b - data->Lrotor / 2 - data->Lr / 2;
	// calculeaza cu A
	data->Lperii = data->a - data->Lr / 2 - data->Lrotor / 2;
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
