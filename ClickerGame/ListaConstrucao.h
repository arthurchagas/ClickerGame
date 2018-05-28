#pragma once
#include "NoConstrucao.h"
#include "Lista.h"

class ListaConstrucao : protected Lista {
public:

	ListaConstrucao();
	~ListaConstrucao();

	void inserir_final(Construcao* I);
	void remover_final();
	void inserir_comeco(Construcao* I);
	void remover_comeco();
	void remover_por_chave(int chave);
	long double recalcular_rate_global();
	NoConstrucao* encontrar_por_chave(int chave);
	NoConstrucao* get_ultimo();
	NoConstrucao* get_primeiro();

	void esvazia();
private:
	NoConstrucao* primeiro;
	NoConstrucao* ultimo;
};
