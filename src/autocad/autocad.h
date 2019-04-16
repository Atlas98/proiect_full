#ifndef _AUTOCAD_H_
#define _AUTOCAD_H_

#if __linux__
#define EXPORT_FUNCTION extern
#elif _WIN32
#define EXPORT_FUNCTION __declspec(dllexport)
#endif

struct arbore_data {
	int a;
	int b;
	int c;

	double Dventilator;
	double Dr;	// rulment
	double Dperii;
	double Drotor;
	double Dumar;
	double Dca;
	double Det;

	double Lventilator;
	double Lr;
	double Lperii;
	double Lrotor;
	double Lumar;
	double Lca;
	double Let;
	double Let_dreapta;
};

// structuri pentru desenul final
struct desen_basic_data {
	int a;
	int b;
	int c;



};

// cu desen_basic_data, se obtine desen_full_data
struct desen_full_data {
	int a;
	int b;
	int c;

};

EXPORT_FUNCTION void autocad_generate_arbore(void* filePtr, struct arbore_data* data);
EXPORT_FUNCTION void generate_desen_final(void* filePtr, struct desen_basic_data* basic_data);


#endif