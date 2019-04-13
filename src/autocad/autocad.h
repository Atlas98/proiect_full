#ifndef _AUTOCAD_H_
#define _AUTOCAD_H_
#include <exports.h>
#include <structs.h>

struct arbore_data {
	real_t a;
	real_t b;
	real_t c;

	real_t Dventilator;
	real_t Dr;	// rulment
	real_t Dperii;
	real_t Drotor;
	real_t Dumar;
	real_t Dca;
	real_t Det;

	real_t Lventilator;
	real_t Lr;
	real_t Lperii;
	real_t Lrotor;
	real_t Lumar;
	real_t Lca;
	real_t Let;
	real_t Let_dreapta;
};

EXPORT_FUNCTION void autocad_generate_arbore(void* filePtr, struct arbore_data* data);



#endif