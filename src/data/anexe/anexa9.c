#include <internal.h>
#include <data/anexe/anexe.h>
#include <exports.h>

INTERNAL_FUNCTION struct anexa9_coeficienti_concentratori anexa9_get_concentratori(real_t sigma_r) {
	struct anexa9_coeficienti_concentratori data = { 0 };
	if (sigma_r < 600) {
		data.beta_k_sigma = 1.46;
		data.beta_k_tau = 1.54;
	}
	else if (sigma_r >= 600 && sigma_r <= 800) {
		if (sigma_r > 700) {
			data.beta_k_sigma = 1.62;
			data.beta_k_tau = 1.88;
		} 
		else {
			data.beta_k_sigma = 1.46;
			data.beta_k_tau = 1.54;
		}
	}
	else if (sigma_r >= 800 && sigma_r <= 1000) {
		if (sigma_r > 900) {
			data.beta_k_sigma = 1.77;
			data.beta_k_tau = 2.22;
		}
		else {
			data.beta_k_sigma = 1.62;
			data.beta_k_tau = 1.88;
		}
	}
	else if (sigma_r >= 1000 && sigma_r <= 1200) {
		if (sigma_r > 1100) {
			data.beta_k_sigma = 1.77;
			data.beta_k_tau = 2.22;
		}
		else {
			data.beta_k_sigma = 1.92;
			data.beta_k_tau = 2.39;
		}
	}
	else {
		data.beta_k_sigma = 1.92;
		data.beta_k_tau = 2.39;
	}

	return data;
}